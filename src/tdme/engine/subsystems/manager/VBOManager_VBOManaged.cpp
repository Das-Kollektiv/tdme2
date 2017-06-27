// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <Array.h>

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::subsystems::manager::VBOManager;

VBOManager_VBOManaged::VBOManager_VBOManaged(VBOManager *VBOManager_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, VBOManager_this(VBOManager_this)
{
	clinit();
}

VBOManager_VBOManaged::VBOManager_VBOManaged(VBOManager *VBOManager_this, String* id, int32_tArray* vboGlIds) 
	: VBOManager_VBOManaged(VBOManager_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(id,vboGlIds);
}

void VBOManager_VBOManaged::ctor(String* id, int32_tArray* vboGlIds)
{
	super::ctor();
	this->id = id;
	this->vboGlIds = vboGlIds;
	this->referenceCounter = 0;
}

String* VBOManager_VBOManaged::getId()
{
	return id;
}

int32_tArray* VBOManager_VBOManaged::getVBOGlIds()
{
	return vboGlIds;
}

int32_t VBOManager_VBOManaged::getReferenceCounter()
{
	return referenceCounter;
}

bool VBOManager_VBOManaged::decrementReferenceCounter()
{
	referenceCounter--;
	return referenceCounter == 0;
}

void VBOManager_VBOManaged::incrementReferenceCounter()
{
	referenceCounter++;
}

bool VBOManager_VBOManaged::isUploaded()
{
	if (uploaded == false) {
		uploaded = true;
		return false;
	} else {
		return true;
	}
}

String* VBOManager_VBOManaged::toString()
{
	return ::java::lang::StringBuilder().append(u"VBOManaged [id="_j)->append(id)
		->append(u", vboGlIds="_j)
		->append(Arrays::toString(vboGlIds))
		->append(u", referenceCounter="_j)
		->append(referenceCounter)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* VBOManager_VBOManaged::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.VBOManager.VBOManaged", 52);
    return c;
}

java::lang::Class* VBOManager_VBOManaged::getClass0()
{
	return class_();
}

