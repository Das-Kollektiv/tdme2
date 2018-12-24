#include <fstream>
#include <string>
#include <vector>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/FilenameFilter.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::FilenameFilter;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

struct FileInformation {
	string name;
	uint64_t bytes;
	uint8_t compressed;
	uint64_t bytesCompressed;
	uint64_t offset;
};

void scanDir(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FilenameFilter {
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
				// meta
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tmm") == true) return true;
				// level
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tl") == true) return true;
				// xml
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".xml") == true) return true;
				// images
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".png") == true) return true;
				// fonts
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".fnt") == true) return true;
				//
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(folder, files, &listFilter);

	for (auto fileName: files) {
		if (FileSystem::getInstance()->isPath(folder + "/" + fileName) == false) {
			totalFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, totalFiles);
		}
	}
}

void processFile(const string& fileName, vector<FileInformation>& fileInformations) {
	Console::print("Processing file: " + fileName);

	// read content
	vector<uint8_t> content;
	FileSystem::getInstance()->getContent(
		FileSystem::getInstance()->getPathName(fileName),
		FileSystem::getInstance()->getFileName(fileName),
		content
	);

	// append to archive
	ofstream ofs("archive.ta", ofstream::binary | ofstream::app);
	uint64_t fileOffset = ofs.tellp();
	ofs.write((char*)content.data(), content.size());
	ofs.close();

	// store file information
	FileInformation fileInformation;
	fileInformation.name = fileName;
	fileInformation.bytes = content.size();
	fileInformation.compressed = 0;
	fileInformation.bytesCompressed = 0;
	fileInformation.offset = fileOffset;
	fileInformations.push_back(fileInformation);

	// done
	Console::println(", processed " + to_string(content.size()) + " bytes");
}

int main(int argc, char** argv)
{
	Console::println(string("archive 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();

	if (argc != 1) {
		Console::println("Usage: archive");
		exit(0);
	}

	// scan files
	Console::println("Scanning files");
	vector<string> files;
	scanDir("resources", files);
	scanDir("shader", files);

	// processing
	Console::println("Processing files");

	// reset archive
	{
		ofstream ofs("archive.ta", ofstream::binary | ofstream::trunc);
		ofs.close();
	}

	// add files to archive
	vector<FileInformation> fileInformations;
	for (auto fileName: files) {
		processFile(fileName, fileInformations);
	}

	// add file informations
	{
		ofstream ofs("archive.ta", ofstream::binary | ofstream::app);
		uint64_t fileInformationOffsetEnd = 0LL;
		uint64_t fileInformationOffset = ofs.tellp();
		for (auto& fileInformation: fileInformations) {
			uint32_t nameSize = fileInformation.name.size();
			ofs.write((char*)&nameSize, sizeof(nameSize));
			for (auto i = 0; i < nameSize; i++) ofs.write(&fileInformation.name[i], 1);
			ofs.write((char*)&fileInformation.bytes, sizeof(fileInformation.bytes));
			ofs.write((char*)&fileInformation.compressed, sizeof(fileInformation.compressed));
			ofs.write((char*)&fileInformation.bytesCompressed, sizeof(fileInformation.bytesCompressed));
			ofs.write((char*)&fileInformation.offset, sizeof(fileInformation.offset));
		}
		ofs.write((char*)&fileInformationOffsetEnd, sizeof(fileInformationOffsetEnd));
		ofs.write((char*)&fileInformationOffset, sizeof(fileInformationOffset));
		ofs.close();
	}
}
