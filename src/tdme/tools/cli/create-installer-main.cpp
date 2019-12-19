#include <cassert>
#include <fstream>
#include <string>
#include <vector>

#include <ext/zlib/zlib.h>

#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Time.h>

using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Properties;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;
using tdme::utils::Time;

namespace tdme {
namespace tools {
namespace cli {
namespace installer {
	struct FileInformation {
		string name;
		uint64_t bytes;
		uint8_t compressed;
		uint64_t bytesCompressed;
		uint64_t offset;
		bool executable;
	};
};
};
};
};

using tdme::tools::cli::installer::FileInformation;

void scanDirData(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				// shader
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".c") == true) return true;
				// audio
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".ogg") == true) return true;
				// models
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tm") == true) return true;
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dae") == true) return true;
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".fbx") == true) return true;
				// meta
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tmm") == true) return true;
				// level
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tl") == true) return true;
				// particle system
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tps") == true) return true;
				// xml
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".xml") == true) return true;
				// images
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".png") == true) return true;
				// fonts
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".fnt") == true) return true;
				// fonts
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".fnt") == true) return true;
				// files without ending
				if (fileName.find(".") == string::npos) return true;
				// properties
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".properties") == true) return true;
				// tdme archive
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".ta") == true) return true;
				//
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(folder) == false) {
		Console::println("Error: scanDirData: file does not exist: " + folder);
	} else
	if (FileSystem::getInstance()->isPath(folder) == false) {
		if (listFilter.accept(".", folder) == true) {
			totalFiles.push_back(folder);
		} else {
			Console::println("Error: scanDirData: file exist, but does not match filter: " + folder);
		}
	} else {
		FileSystem::getInstance()->list(folder, files, &listFilter);
		for (auto fileName: files) {
			if (FileSystem::getInstance()->isPath(folder + "/" + fileName) == false) {
				totalFiles.push_back(folder + "/" + fileName);
			} else {
				scanDirData(folder + "/" + fileName, totalFiles);
			}
		}
	}
}

void scanDirBin(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				#if defined(_WIN32)
					if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".exe") == true) return true;
					if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dll") == true) return true;
				#elif defined(__APPLE__)
					if (fileName.find(".") == string::npos) return true;
					if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dylib") == true) return true;
					if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".so") == true) return true;
				#else
					if (fileName.find(".") == string::npos) return true;
					if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".so") == true) return true;
				#endif
				//
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(folder) == false) {
		Console::println("Error: scanDirData: file does not exist: " + folder);
	} else
	if (FileSystem::getInstance()->isPath(folder) == false) {
		if (listFilter.accept(".", folder) == true) {
			totalFiles.push_back(folder);
		} else {
			Console::println("Error: scanDirData: file exist, but does not match filter: " + folder);
		}
	} else {
		FileSystem::getInstance()->list(folder, files, &listFilter);
		for (auto fileName: files) {
			if (FileSystem::getInstance()->isPath(folder + "/" + fileName) == false) {
				totalFiles.push_back(folder + "/" + fileName);
			} else {
				scanDirBin(folder + "/" + fileName, totalFiles);
			}
		}
	}
}

void processFile(const string& fileName, vector<FileInformation>& fileInformations, const string& archiveFileName, bool binFile) {
	// read content
	vector<uint8_t> content;
	FileSystem::getInstance()->getContent(
		FileSystem::getInstance()->getPathName(fileName),
		FileSystem::getInstance()->getFileName(fileName),
		content
	);

	auto fileNameToUse = fileName;
	// remove prefix if requested
	if (binFile == true && fileName.find_last_of('/') != string::npos) {
		fileNameToUse = StringUtils::substring(fileName, fileName.find_last_of('/') + 1);
	}

	Console::print(archiveFileName + ": Processing file: " + fileNameToUse);

	// append to archive
	ofstream ofs(archiveFileName.c_str(), ofstream::binary | ofstream::app);
	uint64_t fileOffset = ofs.tellp();

	//
	uint64_t bytesCompressed = 0;
	uint8_t compressed = 1;

	// always use compression for now
	if (compressed == 1) {
		// see: https://www.zlib.net/zpipe.c

		#define CHUNK 	16384

		int ret;
		int flush;
		size_t have;
		z_stream strm;
		unsigned char in[CHUNK];
		unsigned char out[CHUNK];

		/* allocate deflate state */
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
		if (ret != Z_OK) {
			Console::println("processFile(): Error compressing file: Aborting");
			return;
		}

		// compress until end of file
		size_t inPosition = 0;
		size_t inBytes = content.size();
		do {
			auto inStartPosition = inPosition;
			for (size_t i = 0; i < CHUNK; i++) {
				if (inPosition == inBytes) break;
				in[i] = content[inPosition];
				inPosition++;
			}
			strm.avail_in = inPosition - inStartPosition;
			flush = inPosition == inBytes?Z_FINISH:Z_NO_FLUSH;
			strm.next_in = in;

			// run deflate() on input until output buffer not full, finish compression if all of source has been read in
			do {
				strm.avail_out = CHUNK;
				strm.next_out = out;
				ret = deflate(&strm, flush); // no bad return value
				assert(ret != Z_STREAM_ERROR); // state not clobbered
				have = CHUNK - strm.avail_out;
				ofs.write((char*)out, have);
				bytesCompressed+= have;
			} while (strm.avail_out == 0);
			assert(strm.avail_in == 0); // all input will be used

			// done when last data in file processed
		} while (flush != Z_FINISH);
		assert(ret == Z_STREAM_END); // stream will be complete

		// clean up and return
		(void) deflateEnd(&strm);
	} else {
		ofs.write((char*)content.data(), content.size());
	}
	ofs.close();

	// store file information
	FileInformation fileInformation;
	fileInformation.name = fileNameToUse;
	fileInformation.bytes = content.size();
	fileInformation.compressed = compressed;
	fileInformation.bytesCompressed = bytesCompressed;
	fileInformation.offset = fileOffset;
	fileInformation.executable = binFile;
	fileInformations.push_back(fileInformation);

	// done
	Console::println(", processed " + to_string(content.size()) + " bytes" + (compressed == 1?", " + to_string(bytesCompressed) + " bytes compressed":""));
}

int main(int argc, char** argv)
{
	Console::println(string("create-installer 1.9.9"));
	Console::println(string("Programmed 2019 by Andreas Drewke, drewke.net."));
	Console::println();

	auto fileNameTime = StringUtils::replace(StringUtils::replace(StringUtils::replace(Time::getAsString(), " ", "-" ), ":", ""), "-", "");

	Properties installerProperties;
	installerProperties.load("resources/installer", "installer.properties");
	for (auto setIdx = 1; true; setIdx++) {
		auto setName = installerProperties.get("set" + to_string(setIdx), "");
		if (setName.empty() == true) break;
		Console::println("Having set: " + to_string(setIdx) + ": " + setName);
		auto setInclude = installerProperties.get("set" + to_string(setIdx) + "_include", "");
		if (setInclude.empty() == true) {
			Console::println("Set: " + to_string(setIdx) + ": missing includes. Skipping.");
			continue;
		}
		//
		string cpu = "x64";
		string os;
		#if defined(__FreeBSD__)
			os = "FreeBSD";
		#elif defined(__HAIKU__)
			os = "Haiku";
		#elif defined(__linux__)
			os = "Linux";
		#elif defined(__APPLE__)
			os = "MacOSX";
		#elif defined(__NetBSD__)
			os = "NetBSD";
		#elif defined(_MSC_VER)
			os = "Windows-MSC";
		#elif defined(_WIN32)
			os = "Windows-MINGW";
		#else
			os = "Unknown";
		#endif
		auto setFileName = os + "-" + cpu + "-" + StringUtils::replace(StringUtils::replace(setName, " - ", "-"), " ", "-") + "-" + fileNameTime + ".ta";
		//
		Console::println("Set: " + to_string(setIdx) + ": set file name: " + setFileName);

		if (FileSystem::getInstance()->fileExists("installer") == false) {
			FileSystem::getInstance()->createPath("installer");
		}

		// reset archive
		{
			ofstream ofs("installer/" + setFileName, ofstream::binary | ofstream::trunc);
			ofs.close();
		}

		//
		vector<FileInformation> fileInformations;
		vector<string> filesData;
		vector<string> filesBin;

		// parse includes definitions
		StringTokenizer t;
		StringTokenizer t2;
		t.tokenize(setInclude, ",");
		while (t.hasMoreTokens() == true) {
			auto setIncludeDefinition = t.nextToken();
			t2.tokenize(setIncludeDefinition, ":");
			string type = t2.hasMoreTokens() == true?t2.nextToken():"";
			string file = t2.hasMoreTokens() == true?t2.nextToken():"";
			if (type.empty() == true || file.empty() == true) {
				Console::println("Set: " + to_string(setIdx) + ": type or file empty. Skipping");
				continue;
			}
			Console::println("Set: " + to_string(setIdx) + ": type = " + type + "; file = " + file);

			// scan files
			if (type == "bin") {
				scanDirBin(installerProperties.get("bin_folder", "") + "/" + file, filesBin);
			} else
			if (type == "data") {
				scanDirData(file, filesData);
			} else {
				Console::println("Set: " + to_string(setIdx) + ": type = " + type + " unsupported!");
			}

			// process files
			Console::println("Set: " + to_string(setIdx) + ": Processing files");
		}

		// add files to archive
		for (auto fileName: filesData) {
			processFile(fileName, fileInformations, "installer/" + setFileName, false);
		}

		// add files to archive
		for (auto fileName: filesBin) {
			processFile(fileName, fileInformations, "installer/" + setFileName, true);
		}

		// add file informations
		{
			ofstream ofs("installer/" + setFileName, ofstream::binary | ofstream::app);
			uint32_t fileInformationOffsetEnd = 0LL;
			uint64_t fileInformationOffset = ofs.tellp();
			for (auto& fileInformation: fileInformations) {
				uint32_t nameSize = fileInformation.name.size();
				ofs.write((char*)&nameSize, sizeof(nameSize));
				for (auto i = 0; i < nameSize; i++) ofs.write(&fileInformation.name[i], 1);
				ofs.write((char*)&fileInformation.bytes, sizeof(fileInformation.bytes));
				ofs.write((char*)&fileInformation.compressed, sizeof(fileInformation.compressed));
				ofs.write((char*)&fileInformation.bytesCompressed, sizeof(fileInformation.bytesCompressed));
				ofs.write((char*)&fileInformation.offset, sizeof(fileInformation.offset));
				ofs.write((char*)&fileInformation.executable, sizeof(fileInformation.executable));
			}
			ofs.write((char*)&fileInformationOffsetEnd, sizeof(fileInformationOffsetEnd));
			ofs.write((char*)&fileInformationOffset, sizeof(fileInformationOffset));
			ofs.close();
		}
	}
}
