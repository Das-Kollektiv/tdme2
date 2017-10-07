
#pragma once

#include <string>
#include <vector>

#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/fwd-tdme.h>

using std::wstring;
using std::vector;

using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::FilenameFilter;

class tdme::os::filesystem::StandardFileSystem final
	: public FileSystemInterface
{

public:
	const wstring getFileName(const wstring& path, const wstring& fileName) throw (FileSystemException) override;
	void list(const wstring& pathName, vector<wstring>* files, FilenameFilter* filter = nullptr) throw (FileSystemException) override;
	bool isPath(const wstring& pathName) throw (FileSystemException) override;
	bool fileExists(const wstring& fileName) throw (FileSystemException) override;
	const wstring getContentAsString(const wstring& pathName, const wstring& fileName) throw (FileSystemException) override;
	void setContentFromString(const wstring& pathName, const wstring& fileName, const wstring& content) throw (FileSystemException) override;
	void getContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (FileSystemException) override;
	void setContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (FileSystemException) override;
	void getContentAsStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (FileSystemException) override;
	void setContentFromStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (FileSystemException) override;
	const wstring getCanonicalPath(const wstring& pathName, const wstring& fileName) throw (FileSystemException) override;
	const wstring getCurrentWorkingPathName() throw (FileSystemException) override;
	const wstring getPathName(const wstring& fileName) throw (FileSystemException) override;
	const wstring getFileName(const wstring& fileName) throw (FileSystemException) override;
	void createPath(const wstring& pathName) throw (FileSystemException) override;
	void removePath(const wstring& pathName) throw (FileSystemException) override;
	void removeFile(const wstring& pathName, const wstring& fileName) throw (FileSystemException) override;
	StandardFileSystem();
};
