// Generated from /tdme/src/tdme/tests/EngineTest.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Application;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::Transformations;
using tdme::engine::model::Model;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;

/** 
 * Engine test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::EngineTest final
	: public virtual Object, public Application
{

public:
	typedef Object super;

private:
	Engine* engine {  };
	Engine* osEngine {  };
	CollisionResponse* collision {  };
	_ArrayList* players {  };
	_ArrayList* playersBoundingVolumeModel {  };
	BoundingVolume* playerBoundingVolume {  };
	Model* playerBoundingVolumeModel {  };
	_ArrayList* playerBoundingVolumesTransformed {  };
	Object3D* cube {  };
	Model* cubeBoundingVolumeModel {  };
	BoundingVolume* cubeBoundingVolume {  };
	BoundingVolume* cubeBoundingVolumeTransformed {  };
	BoundingVolume* barrelBoundingVolume {  };
	BoundingVolume* barrelBoundingVolumeTransformed {  };
	Transformations* circleTransformations {  };

public: /* package */
	Entity* entityClicked {  };

private:
	int32_tArray* mouseClicked_ {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyW {  };
	bool keyA {  };
	bool keyS {  };
	bool keyD {  };

public:

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);
protected:

	/** 
	 * Engine test
	 * @param gl window
	 */
	void ctor();

private:

	/** 
	 * Create wall model
	 * @return
	 */
	Model* createWallModel();

public:
	void display();

private:

	/** 
	 * Do player control
	 * @param idx
	 * @param key left
	 * @param key right
	 * @param key up
	 */
	void doPlayerControl(int32_t idx, bool keyLeft, bool keyRight, bool keyUp);

public:
	void dispose();
	void initialize() ;
	void reshape(int32_t width, int32_t height);

	// Generated
	EngineTest();
protected:
	EngineTest(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
