// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderPointsPool.java
#include <tdme/engine/subsystems/object/TransparentRenderPointsPool.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/QuickSort.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>

using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using java::lang::ClassCastException;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::math::Vector3;
using tdme::utils::QuickSort;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

TransparentRenderPointsPool::TransparentRenderPointsPool(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TransparentRenderPointsPool::TransparentRenderPointsPool(int32_t pointsMax) 
	: TransparentRenderPointsPool(*static_cast< ::default_init_tag* >(0))
{
	ctor(pointsMax);
}

void TransparentRenderPointsPool::init()
{
	transparentRenderPoints = nullptr;
	poolIdx = 0;
}

void TransparentRenderPointsPool::ctor(int32_t pointsMax)
{
	super::ctor();
	init();
	transparentRenderPoints = new _ArrayList();
	for (auto i = 0; i < pointsMax; i++) {
		auto point = new TransparentRenderPoint();
		point->acquired = false;
		point->point = new Vector3();
		point->color = new Color4();
		transparentRenderPoints->add(point);
	}
}

void TransparentRenderPointsPool::addPoint(Vector3* point, Color4* color, float distanceFromCamera)
{
	if (poolIdx >= transparentRenderPoints->size()) {
		_Console::println(static_cast< Object* >(u"TransparentRenderPointsPool::createTransparentRenderPoint(): Too many transparent render points"_j));
		return;
	}
	auto transparentRenderPoint = java_cast< TransparentRenderPoint* >(transparentRenderPoints->get(poolIdx++));
	transparentRenderPoint->acquired = true;
	transparentRenderPoint->point->set(point);
	transparentRenderPoint->color->set(static_cast< Color4Base* >(color));
	transparentRenderPoint->distanceFromCamera = distanceFromCamera;
}

void TransparentRenderPointsPool::merge(TransparentRenderPointsPool* pool2)
{
	for (auto _i = pool2->transparentRenderPoints->iterator(); _i->hasNext(); ) {
		TransparentRenderPoint* point = java_cast< TransparentRenderPoint* >(_i->next());
		{
			if (point->acquired == false)
				break;

			if (poolIdx >= transparentRenderPoints->size()) {
				_Console::println(static_cast< Object* >(u"TransparentRenderPointsPool::merge(): Too many transparent render points"_j));
				break;
			}
			auto transparentRenderPoint = java_cast< TransparentRenderPoint* >(transparentRenderPoints->get(poolIdx++));
			transparentRenderPoint->acquired = true;
			transparentRenderPoint->point->set(point->point);
			transparentRenderPoint->color->set(static_cast< Color4Base* >(point->color));
			transparentRenderPoint->distanceFromCamera = point->distanceFromCamera;
		}
	}
}

void TransparentRenderPointsPool::reset()
{
	poolIdx = 0;
	for (auto _i = transparentRenderPoints->iterator(); _i->hasNext(); ) {
		TransparentRenderPoint* point = java_cast< TransparentRenderPoint* >(_i->next());
		{
			point->acquired = false;
		}
	}
}

_ArrayList* TransparentRenderPointsPool::getTransparentRenderPoints()
{
	return transparentRenderPoints;
}

void TransparentRenderPointsPool::sort()
{
	QuickSort::sort(transparentRenderPoints);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderPointsPool::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.TransparentRenderPointsPool", 57);
    return c;
}

java::lang::Class* TransparentRenderPointsPool::getClass0()
{
	return class_();
}

