#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>

#include <string>

#include <tdme/engine/subsystems/manager/VBOManager.h>

using std::string;

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;

VBOManager_VBOManaged::VBOManager_VBOManaged(const string& id, vector<int32_t>& vboIds)
{
	this->id = id;
	this->vboIds = vboIds;
	this->referenceCounter = 0;
}

const string& VBOManager_VBOManaged::getId()
{
	return id;
}

vector<int32_t>* VBOManager_VBOManaged::getVBOIds()
{
	return &vboIds;
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
