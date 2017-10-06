
#pragma once

#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FilenameFilter.h>

using std::wstring;

using tdme::utils::FilenameFilter;

class tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1
	: public virtual FilenameFilter
{

public:
	bool accept(const wstring& pathName, const wstring& fileName) override;
	DAEReader_determineDisplacementFilename_1(const wstring& finalFilenameCandidate);

private:
	wstring finalFilenameCandidate;
};
