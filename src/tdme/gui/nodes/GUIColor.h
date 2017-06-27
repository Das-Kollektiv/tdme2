// Generated from /tdme/src/tdme/gui/nodes/GUIColor.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/engine/model/Color4Base.h>

using tdme::engine::model::Color4Base;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::model::Color4;
using java::lang::Object;
using tdme::gui::nodes::GUIColor;

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

namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Color4Base, ::java::lang::ObjectArray > Color4BaseArray;
}  // namespace model
}  // namespace engine

namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUIColor, ::tdme::engine::model::Color4BaseArray > GUIColorArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;
using tdme::engine::model::Color4BaseArray;
using tdme::gui::nodes::GUIColorArray;

struct default_init_tag;

/** 
 * GUI color
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIColor final
	: public Color4Base
{

public:
	typedef Color4Base super;
	static GUIColor* WHITE;
	static GUIColor* BLACK;
	static GUIColor* RED;
	static GUIColor* GREEN;
	static GUIColor* BLUE;
	static GUIColor* TRANSPARENT;
	static GUIColor* EFFECT_COLOR_MUL;
	static GUIColor* EFFECT_COLOR_ADD;

private:
	static GUIColorArray* COLOR_INSTANCES;
	static StringArray* COLOR_NAMES;
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 */
	void ctor(Color4* color);

	/** 
	 * Public constructor
	 */
	void ctor(float r, float g, float b, float a);

	/** 
	 * Public constructor
	 */
	void ctor(floatArray* color);

	/** 
	 * Public constructor
	 * @param color text
	 */
	void ctor(String* colorString) /* throws(GUIParserException) */;

public:
	String* toString() override;

	// Generated
	GUIColor();
	GUIColor(Color4* color);
	GUIColor(float r, float g, float b, float a);
	GUIColor(floatArray* color);
	GUIColor(String* colorString);
protected:
	GUIColor(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
