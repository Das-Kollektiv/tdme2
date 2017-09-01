// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java
#include <tdme/engine/fileio/models/DAEReader_determineDisplacementFilename_1.h>

#include <string>

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/StringUtils.h>

using std::wstring;

using tdme::utils::StringUtils;

using tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1;

DAEReader_determineDisplacementFilename_1::DAEReader_determineDisplacementFilename_1(const wstring& finalFilenameCandidate)
{
	this->finalFilenameCandidate = finalFilenameCandidate;
}

bool DAEReader_determineDisplacementFilename_1::accept(const wstring& pathName, const wstring& fileName)
{
	return
		StringUtils::equalsIgnoreCase(fileName, finalFilenameCandidate + L".png") == true ||
		StringUtils::equalsIgnoreCase(fileName, finalFilenameCandidate + L".jpg") == true;
}

