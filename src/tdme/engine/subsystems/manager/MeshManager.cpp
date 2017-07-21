// Generated from /tdme/src/tdme/engine/subsystems/manager/MeshManager.java
#include <tdme/engine/subsystems/manager/MeshManager.h>

#include <map>
#include <string>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/utils/_Console.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::manager::MeshManager;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

MeshManager::MeshManager(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

MeshManager::MeshManager() 
	: MeshManager(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void MeshManager::ctor()
{
	super::ctor();
}

Object3DGroupMesh* MeshManager::getMesh(String* meshId)
{
	auto meshManagedIt = meshes.find(meshId->getCPPWString());
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		meshManaged->incrementReferenceCounter();
		return meshManaged->getMesh();
	}
	return nullptr;
}

void MeshManager::addMesh(String* meshId, Object3DGroupMesh* mesh)
{
	auto meshManaged = new MeshManager_MeshManaged(this, meshId, mesh);
	meshManaged->incrementReferenceCounter();
	meshes[meshManaged->getId()->getCPPWString()] = meshManaged;
}

void MeshManager::removeMesh(String* meshId)
{
	auto meshManagedIt = meshes.find(meshId->getCPPWString());
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		if (meshManaged->decrementReferenceCounter()) {
			meshes.erase(meshManagedIt);
		}
		return;
	}
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Warning: mesh not managed by mesh manager: "_j)->append(meshId)->toString()));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MeshManager::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.MeshManager", 42);
    return c;
}

java::lang::Class* MeshManager::getClass0()
{
	return class_();
}

