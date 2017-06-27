// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/nativewindow/Capabilities.h>
#include <java/lang/Cloneable.h>
#include <com/jogamp/opengl/GLCapabilitiesImmutable.h>

using com::jogamp::nativewindow::Capabilities;
using java::lang::Cloneable;
using com::jogamp::opengl::GLCapabilitiesImmutable;
using com::jogamp::nativewindow::CapabilitiesImmutable;
using com::jogamp::nativewindow::VisualIDHolder_VIDType;
using com::jogamp::opengl::GLProfile;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;


struct default_init_tag;
class com::jogamp::opengl::GLCapabilities
	: public Capabilities
	, public virtual Cloneable
	, public virtual GLCapabilitiesImmutable
{

public:
	typedef Capabilities super;

private:
	int32_t accumAlphaBits {  };
	int32_t accumBlueBits {  };
	int32_t accumGreenBits {  };
	int32_t accumRedBits {  };
	int32_t depthBits {  };
	bool doubleBuffered {  };
	GLProfile* glProfile {  };
	bool hardwareAccelerated {  };
	bool isFBO_ {  };
	bool isPBuffer_ {  };
	int32_t numSamples {  };
	bool sampleBuffers {  };
	String* sampleExtension {  };
	int32_t stencilBits {  };
	bool stereo {  };

protected:
	void ctor(GLProfile* arg0);

public:
	Object* clone() override;
	Object* cloneMutable() override;
	int32_t compareTo(CapabilitiesImmutable* arg0) override;
	virtual GLCapabilities* copyFrom(GLCapabilitiesImmutable* arg0);
	bool equals(Object* arg0) override;
	int32_t getAccumAlphaBits() override;
	int32_t getAccumBlueBits() override;
	int32_t getAccumGreenBits() override;
	int32_t getAccumRedBits() override;
	int32_t getDepthBits() override;
	bool getDoubleBuffered() override;
	GLProfile* getGLProfile() override;
	bool getHardwareAccelerated() override;
	int32_t getNumSamples() override;
	bool getSampleBuffers() override;
	String* getSampleExtension() override;
	int32_t getStencilBits() override;
	bool getStereo() override;
	int32_t hashCode() override;
	bool isFBO() override;
	bool isPBuffer() override;
	virtual void setAccumAlphaBits(int32_t arg0);
	virtual void setAccumBlueBits(int32_t arg0);
	virtual void setAccumGreenBits(int32_t arg0);
	virtual void setAccumRedBits(int32_t arg0);
	virtual void setDepthBits(int32_t arg0);
	virtual void setDoubleBuffered(bool arg0);
	virtual void setFBO(bool arg0);
	virtual void setGLProfile(GLProfile* arg0);
	virtual void setHardwareAccelerated(bool arg0);
	virtual void setNumSamples(int32_t arg0);
	virtual void setPBuffer(bool arg0);
	virtual void setSampleBuffers(bool arg0);
	virtual void setSampleExtension(String* arg0);
	virtual void setStencilBits(int32_t arg0);
	virtual void setStereo(bool arg0);
	String* toString() override;
	StringBuilder* toString(StringBuilder* arg0) override;

	// Generated
	GLCapabilities(GLProfile* arg0);
protected:
	GLCapabilities(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t getAlphaBits();
	virtual int32_t getBlueBits();
	virtual int32_t getGreenBits();
	virtual int32_t getRedBits();
	virtual int32_t getTransparentAlphaValue();
	virtual int32_t getTransparentBlueValue();
	virtual int32_t getTransparentGreenValue();
	virtual int32_t getTransparentRedValue();
	virtual bool isBackgroundOpaque();
	virtual bool isBitmap();
	virtual bool isOnscreen();
	virtual int32_t getVisualID(VisualIDHolder_VIDType* arg0);
	virtual int32_t compareTo(Object* o) override;
	virtual Capabilities* copyFrom(CapabilitiesImmutable* arg0);

public: /* protected */
	virtual StringBuilder* toString(StringBuilder* arg0, bool arg1);

private:
	virtual ::java::lang::Class* getClass0();
};
