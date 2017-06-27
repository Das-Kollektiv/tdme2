// Generated from /tdme/src/tdme/engine/subsystems/manager/MeshManager.java
#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>

using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::object::Object3DGroupMesh;

MeshManager_MeshManaged::MeshManager_MeshManaged(MeshManager *MeshManager_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, MeshManager_this(MeshManager_this)
{
	clinit();
}

MeshManager_MeshManaged::MeshManager_MeshManaged(MeshManager *MeshManager_this, String* id, Object3DGroupMesh* mesh) 
	: MeshManager_MeshManaged(MeshManager_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(id,mesh);
}

void MeshManager_MeshManaged::ctor(String* id, Object3DGroupMesh* mesh)
{
	super::ctor();
	this->id = id;
	this->mesh = mesh;
	this->referenceCounter = 0;
}

String* MeshManager_MeshManaged::getId()
{
	return id;
}

Object3DGroupMesh* MeshManager_MeshManaged::getMesh()
{
	return mesh;
}

int32_t MeshManager_MeshManaged::getReferenceCounter()
{
	return referenceCounter;
}

bool MeshManager_MeshManaged::decrementReferenceCounter()
{
	referenceCounter--;
	return referenceCounter == 0;
}

void MeshManager_MeshManaged::incrementReferenceCounter()
{
	referenceCounter++;
}

String* MeshManager_MeshManaged::toString()
{
	return ::java::lang::StringBuilder().append(u"MeshManaged [id="_j)->append(id)
		->append(u", mesh="_j)
		->append(static_cast< Object* >(mesh))
		->append(u", referenceCounter="_j)
		->append(referenceCounter)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MeshManager_MeshManaged::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.MeshManager.MeshManaged", 54);
    return c;
}

java::lang::Class* MeshManager_MeshManaged::getClass0()
{
	return class_();
}

