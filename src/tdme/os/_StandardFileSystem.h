// Generated from /tdme/src/tdme/os/_StandardFileSystem.java

#pragma once

#include <string>
#include <vector>

#include <java/io/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/fwd-tdme.h>

using std::wstring;
using std::vector;

using tdme::os::_FileSystemInterface;
using tdme::utils::FilenameFilter;

class tdme::os::_StandardFileSystem final
	: public _FileSystemInterface
{

public:
	const wstring getFileName(const wstring& path, const wstring& fileName) throw (_FileSystemException) override;
	void list(const wstring& pathName, vector<wstring>* files, FilenameFilter* filter = nullptr) throw (_FileSystemException) override;
	bool isPath(const wstring& pathName) throw (_FileSystemException) override;
	bool fileExists(const wstring& fileName) throw (_FileSystemException) override;
	const wstring getContentAsString(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) override;
	void setContentFromString(const wstring& pathName, const wstring& fileName, const wstring& content) throw (_FileSystemException) override;
	void getContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (_FileSystemException) override;
	void setContent(const wstring& pathName, const wstring& fileName, vector<uint8_t>* content) throw (_FileSystemException) override;
	void getContentAsStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (_FileSystemException) override;
	void setContentFromStringArray(const wstring& pathName, const wstring& fileName, vector<wstring>* content) throw (_FileSystemException) override;
	const wstring getCanonicalPath(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) override;
	const wstring getCurrentWorkingPathName() throw (_FileSystemException) override;
	const wstring getPathName(const wstring& fileName) throw (_FileSystemException) override;
	const wstring getFileName(const wstring& fileName) throw (_FileSystemException) override;
	void createPath(const wstring& pathName) throw (_FileSystemException) override;
	void removePath(const wstring& pathName) throw (_FileSystemException) override;
	void removeFile(const wstring& pathName, const wstring& fileName) throw (_FileSystemException) override;
	_StandardFileSystem();
};
