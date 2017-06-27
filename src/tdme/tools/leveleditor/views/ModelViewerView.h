// Generated from /tdme/src/tdme/tools/leveleditor/views/ModelViewerView.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using tdme::tools::shared::views::SharedModelViewerView;
using java::lang::String;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * Model viewer view
 * @author Andreas Drewke
 * @version $Id$ 
 */
class tdme::tools::leveleditor::views::ModelViewerView
	: public SharedModelViewerView
{

public:
	typedef SharedModelViewerView super;
protected:

	/** 
	 * Public constructor
	 * @param pop ups view
	 */
	void ctor(PopUps* popUps);

public:
	void onSetEntityData() override;
	void onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity) override;
	void onInitAdditionalScreens() override;

public: /* protected */
	LevelEditorEntity* loadModel(String* name, String* description, String* pathName, String* fileName, Vector3* pivot) /* throws(Exception) */ override;

	// Generated

public:
	ModelViewerView(PopUps* popUps);
protected:
	ModelViewerView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
