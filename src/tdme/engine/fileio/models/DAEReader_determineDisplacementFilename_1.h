
#pragma once

#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FilenameFilter.h>

using std::string;

using tdme::utils::FilenameFilter;

class tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1
	: public virtual FilenameFilter
{

public:
	bool accept(const string& pathName, const string& fileName) override;
	DAEReader_determineDisplacementFilename_1(const string& finalFilenameCandidate);

private:
	string finalFilenameCandidate;
};
