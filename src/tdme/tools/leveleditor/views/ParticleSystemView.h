// Generated from /tdme/src/tdme/tools/leveleditor/views/ParticleSystemView.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using tdme::tools::shared::views::SharedParticleSystemView;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * Particle System View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::ParticleSystemView
	: public SharedParticleSystemView
{

public:
	typedef SharedParticleSystemView super;
protected:

	/** 
	 * Public constructor
	 * @param pop ups
	 */
	void ctor(PopUps* popUps);

public:
	void onSetEntityData() override;
	void onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* newEntity) override;

public: /* protected */
	LevelEditorEntity* loadParticleSystem(String* name, String* description, String* pathName, String* fileName) /* throws(Exception) */ override;

public:
	void onInitAdditionalScreens() override;

	// Generated
	ParticleSystemView(PopUps* popUps);
protected:
	ParticleSystemView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
