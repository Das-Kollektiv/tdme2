// Generated from /tdme/src/tdme/tools/shared/views/EntityDisplayView.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

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
 * Entity display view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityDisplayView
	: public virtual Object
{

public:
	typedef Object super;

private:
	static StringArray* MODEL_BOUNDINGVOLUME_IDS;
	Engine* engine {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	bool displayGroundPlate {  };
	bool displayShadowing {  };
	bool displayBoundingVolume {  };
protected:

	/** 
	 * Public constructor
	 * @param entity display sub screen controller
	 */
	void ctor(EntityDisplaySubScreenController* entityDisplaySubScreenController);

public:

	/** 
	 * @return display ground plate
	 */
	virtual bool isDisplayGroundPlate();

	/** 
	 * Set up ground plate visibility
	 * @param ground plate visible
	 */
	virtual void setDisplayGroundPlate(bool groundPlate);

	/** 
	 * @return display shadowing
	 */
	virtual bool isDisplayShadowing();

	/** 
	 * Set up shadow rendering
	 * @param shadow rendering
	 */
	virtual void setDisplayShadowing(bool shadowing);

	/** 
	 * @return display bounding volume
	 */
	virtual bool isDisplayBoundingVolume();

	/** 
	 * Set up bounding volume visibility
	 * @param bounding volume
	 */
	virtual void setDisplayBoundingVolume(bool displayBoundingVolume);

	/** 
	 * Display
	 * @param entity
	 */
	virtual void display(LevelEditorEntity* entity);

	// Generated
	EntityDisplayView(EntityDisplaySubScreenController* entityDisplaySubScreenController);
protected:
	EntityDisplayView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
