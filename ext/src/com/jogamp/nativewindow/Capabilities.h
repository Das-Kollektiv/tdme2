// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <com/jogamp/nativewindow/CapabilitiesImmutable.h>
#include <java/lang/Cloneable.h>

using java::lang::Object;
using com::jogamp::nativewindow::CapabilitiesImmutable;
using java::lang::Cloneable;
using com::jogamp::nativewindow::VisualIDHolder_VIDType;
using java::lang::String;
using java::lang::StringBuilder;


struct default_init_tag;
class com::jogamp::nativewindow::Capabilities
	: public virtual Object
	, public virtual CapabilitiesImmutable
	, public virtual Cloneable
{

public:
	typedef Object super;

public: /* protected */
	static String* CSEP;
	static String* ESEP;

private:
	int32_t alphaBits {  };
	bool backgroundOpaque {  };
	int32_t blueBits {  };
	int32_t greenBits {  };
	bool isBitmap_ {  };

public: /* protected */
	static String* na_str;

private:
	bool onscreen {  };
	int32_t redBits {  };
	int32_t transparentValueAlpha {  };
	int32_t transparentValueBlue {  };
	int32_t transparentValueGreen {  };
	int32_t transparentValueRed {  };

protected:
	void ctor();

public:
	Object* clone() override;
	Object* cloneMutable() override;
	virtual int32_t compareTo(CapabilitiesImmutable* arg0);
	virtual Capabilities* copyFrom(CapabilitiesImmutable* arg0);
	bool equals(Object* arg0) override;
	int32_t getAlphaBits() override;
	int32_t getBlueBits() override;
	int32_t getGreenBits() override;
	int32_t getRedBits() override;
	int32_t getTransparentAlphaValue() override;
	int32_t getTransparentBlueValue() override;
	int32_t getTransparentGreenValue() override;
	int32_t getTransparentRedValue() override;
	int32_t getVisualID(VisualIDHolder_VIDType* arg0) override;
	int32_t hashCode() override;
	bool isBackgroundOpaque() override;
	bool isBitmap() override;
	bool isOnscreen() override;

public: /* protected */
	virtual StringBuilder* onoffScreenToString(StringBuilder* arg0);

public:
	virtual void setAlphaBits(int32_t arg0);
	virtual void setBackgroundOpaque(bool arg0);
	virtual void setBitmap(bool arg0);
	virtual void setBlueBits(int32_t arg0);
	virtual void setGreenBits(int32_t arg0);
	virtual void setOnscreen(bool arg0);
	virtual void setRedBits(int32_t arg0);
	virtual void setTransparentAlphaValue(int32_t arg0);
	virtual void setTransparentBlueValue(int32_t arg0);
	virtual void setTransparentGreenValue(int32_t arg0);
	virtual void setTransparentRedValue(int32_t arg0);

public: /* protected */
	String* toHexString(int32_t arg0);

public:
	String* toString() override;
	StringBuilder* toString(StringBuilder* arg0) override;

public: /* protected */
	virtual StringBuilder* toString(StringBuilder* arg0, bool arg1);

	// Generated

public:
	Capabilities();
protected:
	Capabilities(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
