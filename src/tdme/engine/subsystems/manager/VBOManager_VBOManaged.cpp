// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>

#include <string>

#include <java/util/Arrays.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <Array.h>

using std::wstring;

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::subsystems::manager::VBOManager;

VBOManager_VBOManaged::VBOManager_VBOManaged(const wstring& id, int32_tArray* vboGlIds)
{
	this->id = id;
	this->vboGlIds = vboGlIds;
	this->referenceCounter = 0;
}

const wstring& VBOManager_VBOManaged::getId()
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
