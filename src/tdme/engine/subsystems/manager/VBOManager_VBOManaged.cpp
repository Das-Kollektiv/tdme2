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
}
