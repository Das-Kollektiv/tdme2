// Generated from /tdme/src/tdme/audio/decoder/AudioDecoderException.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;


struct default_init_tag;

/** 
 * Audio decoder exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::decoder::AudioDecoderException final
	: public Exception
{

public:
	typedef Exception super;
protected:

	/** 
	 * Public constructor
	 * @param message
	 */
	void ctor(String* message);

	// Generated

public:
	AudioDecoderException(String* message);
protected:
	AudioDecoderException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
