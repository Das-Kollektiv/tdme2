// Generated from /tdme/src/tdme/engine/fileio/models/ModelFileIOException.java
#include <tdme/engine/fileio/models/ModelFileIOException.h>

using tdme::engine::fileio::models::ModelFileIOException;

ModelFileIOException::ModelFileIOException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelFileIOException::ModelFileIOException(String* msg) 
	: ModelFileIOException(*static_cast< ::default_init_tag* >(0))
{
	ctor(msg);
}

void ModelFileIOException::ctor(String* msg)
{
	super::ctor(msg);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelFileIOException::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.models.ModelFileIOException", 46);
    return c;
}

java::lang::Class* ModelFileIOException::getClass0()
{
	return class_();
}

