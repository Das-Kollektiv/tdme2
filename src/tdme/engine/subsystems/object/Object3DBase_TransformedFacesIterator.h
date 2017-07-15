// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DBase.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Iterator.h>
#include <java/lang/Iterable.h>
#include <tdme/math/Vector3.h>
#include <ObjectArray.h>
#include <SubArray.h>

using java::lang::Object;
using java::util::Iterator;
using java::lang::Iterable;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::math::Vector3Array;

struct default_init_tag;

/** 
 * Transformed faces iterator
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator
	: public virtual Object
	, public virtual Iterator
	, public virtual Iterable
{

public:
	typedef Object super;

private:
	Object3DBase* object3DBase {  };
	Vector3Array* vertices {  };
	Matrix4x4* matrix {  };
	int32_t faceCount {  };
	int32_t faceIdxTotal {  };
	int32_t faceIdx {  };
	int32_t object3DGroupIdx {  };
	int32_t facesEntityIdx {  };
protected:

	/** 
	 * Protected constructor
	 */
	void ctor(Object3DBase* object3DBase);

private:

	/** 
	 * Reset
	 */
	void reset();

public:
	Iterator* iterator() override;
	bool hasNext() override;
	Vector3Array* next() override;
	void remove() override;

	// Generated

public: /* protected */
	Object3DBase_TransformedFacesIterator(Object3DBase* object3DBase);
protected:
	Object3DBase_TransformedFacesIterator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class Object3DBase;
};
