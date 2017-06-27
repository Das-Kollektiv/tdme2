// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java
#include <tdme/engine/fileio/models/DAEReader_determineDisplacementFilename_1.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1;
using java::lang::String;
using java::lang::StringBuilder;

DAEReader_determineDisplacementFilename_1::DAEReader_determineDisplacementFilename_1(String* finalFilenameCandidate)
	: super(*static_cast< ::default_init_tag* >(0))
	, finalFilenameCandidate(finalFilenameCandidate)
{
	clinit();
	ctor();
}

bool DAEReader_determineDisplacementFilename_1::accept(File* dir, String* name)
{
	return name->equalsIgnoreCase(::java::lang::StringBuilder().append(finalFilenameCandidate)->append(u".png"_j)->toString()) || name->equalsIgnoreCase(::java::lang::StringBuilder().append(finalFilenameCandidate)->append(u".tga"_j)->toString()) || name->equalsIgnoreCase(::java::lang::StringBuilder().append(finalFilenameCandidate)->append(u".jpg"_j)->toString());
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DAEReader_determineDisplacementFilename_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* DAEReader_determineDisplacementFilename_1::getClass0()
{
	return class_();
}

