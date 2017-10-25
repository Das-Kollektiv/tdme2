#include <tdme/engine/fileio/models/DAEReader_determineDisplacementFilename_1.h>

#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/StringUtils.h>

using std::string;

using tdme::utils::StringUtils;

using tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1;

DAEReader_determineDisplacementFilename_1::DAEReader_determineDisplacementFilename_1(const string& finalFilenameCandidate)
{
	this->finalFilenameCandidate = finalFilenameCandidate;
}

bool DAEReader_determineDisplacementFilename_1::accept(const string& pathName, const string& fileName)
{
	return
		StringUtils::equalsIgnoreCase(fileName, finalFilenameCandidate + ".png") == true ||
		StringUtils::equalsIgnoreCase(fileName, finalFilenameCandidate + ".jpg") == true;
}

