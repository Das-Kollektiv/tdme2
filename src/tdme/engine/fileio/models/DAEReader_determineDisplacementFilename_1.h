// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/FilenameFilter.h>

using java::lang::Object;
using java::io::FilenameFilter;
using java::io::File;
using java::lang::String;
using tdme::engine::fileio::models::DAEReader_AuthoringTool;
using tdme::engine::fileio::models::DAEReader;


struct default_init_tag;
class tdme::engine::fileio::models::DAEReader_determineDisplacementFilename_1
	: public virtual Object
	, public virtual FilenameFilter
{

public:
	typedef Object super;
	bool accept(String* dir, String* name) override;

	// Generated
	DAEReader_determineDisplacementFilename_1(String* finalFilenameCandidate);
	static ::java::lang::Class *class_();
	String* finalFilenameCandidate;

private:
	virtual ::java::lang::Class* getClass0();
	friend class DAEReader;
	friend class DAEReader_AuthoringTool;
};
