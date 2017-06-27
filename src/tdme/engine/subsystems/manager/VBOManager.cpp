// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java
#include <tdme/engine/subsystems/manager/VBOManager.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>

using tdme::engine::subsystems::manager::VBOManager;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

VBOManager::VBOManager(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

VBOManager::VBOManager(GLRenderer* renderer) 
	: VBOManager(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void VBOManager::ctor(GLRenderer* renderer)
{
	super::ctor();
	this->renderer = renderer;
	vbos = new _HashMap();
}

VBOManager_VBOManaged* VBOManager::addVBO(String* vboId, int32_t ids)
{
	auto vboManaged = java_cast< VBOManager_VBOManaged* >(vbos->get(vboId));
	if (vboManaged != nullptr) {
		vboManaged->incrementReferenceCounter();
		return vboManaged;
	}
	auto vboIds = renderer->createBufferObjects(ids);
	vboManaged = new VBOManager_VBOManaged(this, vboId, vboIds);
	vboManaged->incrementReferenceCounter();
	vbos->put(vboManaged->getId(), vboManaged);
	return vboManaged;
}

void VBOManager::removeVBO(String* vboId)
{
	auto vboManaged = java_cast< VBOManager_VBOManaged* >(vbos->get(vboId));
	if (vboManaged != nullptr) {
		if (vboManaged->decrementReferenceCounter()) {
			auto vboIds = vboManaged->getVBOGlIds();
			renderer->disposeBufferObjects(vboIds);
			vbos->remove(vboId);
		}
		return;
	}
	_Console::println(static_cast< Object* >(u"Warning: vbo not managed by vbo manager"_j));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* VBOManager::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.manager.VBOManager", 41);
    return c;
}

java::lang::Class* VBOManager::getClass0()
{
	return class_();
}

