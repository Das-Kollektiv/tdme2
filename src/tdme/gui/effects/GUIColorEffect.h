#pragma once

#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;

/** 
 * GUI color effect
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIColorEffect
	: public GUIEffect
{

private:
	GUIColor colorAddStart {  };
	GUIColor colorAddEnd {  };
	GUIColor colorMulStart {  };
	GUIColor colorMulEnd {  };
	GUIColor colorAdd {  };
	GUIColor colorMul {  };

public:

	/** 
	 * @return color add start
	 */
	inline virtual const GUIColor& getColorAddStart() const {
		return colorAddStart;
	}

	/** 
	 * Set color add start
	 * @param colorAddStart color add start
	 */
	inline virtual void setColorAddStart(const GUIColor& colorAddStart) {
		this->colorAddStart = colorAddStart;
	}

	/**
	 * @return color add end
	 */
	inline virtual const GUIColor& getColorAddEnd() const {
		return colorAddEnd;
	}

	/**
	 * Set color add end
	 * @param colorAddEnd color add end
	 */
	inline virtual void setColorAddEnd(const GUIColor& colorAddEnd) {
		this->colorAddEnd = colorAddEnd;
	}

	/** 
	 * @return color mul start
	 */
	inline virtual const GUIColor& getColorMulStart() const {
		return colorMulStart;
	}

	/** 
	 * Set color mul start
	 * @param colorMulStart color mul start
	 */
	inline virtual void setColorMulStart(const GUIColor& colorMulStart) {
		this->colorMulStart = colorMulStart;
	}

	/**
	 * @return color mul end
	 */
	inline virtual const GUIColor& getColorMulEnd() const {
		return colorMulEnd;
	}

	/**
	 * Set color mul end
	 * @param colorMulEnd color mul end
	 */
	inline virtual void setColorMulEnd(const GUIColor& colorMulEnd) {
		this->colorMulEnd = colorMulEnd;
	}

	// overriden methods
	void apply(GUIRenderer* guiRenderer) override;

	/**
	 * Public constructor
	 */
	GUIColorEffect();

private:
	/**
	 * Init
	 */
	void init();

};
