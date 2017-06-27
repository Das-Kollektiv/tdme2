// Generated from /tdme/src/tdme/engine/subsystems/manager/TextureManager.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::TextureManager;


struct default_init_tag;

/** 
 * Managed texture entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::TextureManager_TextureManaged
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	String* id {  };
	int32_t glId {  };
	int32_t referenceCounter {  };
protected:

	/** 
	 * Protected constructor
	 * @param id
	 * @param gl id
	 */
	void ctor(String* id, int32_t glId);

private:

	/** 
	 * @return texture id
	 */
	String* getId();

	/** 
	 * @return texture open gl id
	 */
	int32_t getGlId();

	/** 
	 * @return reference counter
	 */
	int32_t getReferenceCounter();

	/** 
	 * decrement reference counter
	 * @return if reference counter = 0
	 */
	bool decrementReferenceCounter();

	/** 
	 * increment reference counter
	 */
	void incrementReferenceCounter();

	// Generated
	TextureManager_TextureManaged(TextureManager *TextureManager_this, String* id, int32_t glId);
protected:
	TextureManager_TextureManaged(TextureManager *TextureManager_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	TextureManager *TextureManager_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class TextureManager;
};
