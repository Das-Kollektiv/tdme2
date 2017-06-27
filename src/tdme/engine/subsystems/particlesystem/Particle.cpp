// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/Particle.java
#include <tdme/engine/subsystems/particlesystem/Particle.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::Particle;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

Particle::Particle(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Particle::Particle()
	: Particle(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Particle::ctor()
{
	super::ctor();
	init();
}

void Particle::init()
{
	active = false;
	velocity = new Vector3();
	position = new Vector3();
	color = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	colorAdd = new Color4(0.0f, 0.0f, 0.0f, 0.0f);
}

String* Particle::toString()
{
	return ::java::lang::StringBuilder().append(u"Particle [active="_j)->append(active)
		->append(u", velocity="_j)
		->append(static_cast< Object* >(velocity))
		->append(u", position="_j)
		->append(static_cast< Object* >(position))
		->append(u", mass="_j)
		->append(mass)
		->append(u", lifeTimeMax="_j)
		->append(lifeTimeMax)
		->append(u", lifeTimeCurrent="_j)
		->append(lifeTimeCurrent)
		->append(u", color="_j)
		->append(static_cast< Object* >(color))
		->append(u", colorAdd="_j)
		->append(static_cast< Object* >(colorAdd))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Particle::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.Particle", 46);
    return c;
}

java::lang::Class* Particle::getClass0()
{
	return class_();
}

