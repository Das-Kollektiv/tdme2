#pragma once

#include <string>

#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>

using std::string;

using tdme::tools::shared::views::SharedModelEditorView;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;

/** 
 * Model viewer view
 * @author Andreas Drewke
 * @version $Id$ 
 */
class tdme::tools::leveleditor::views::ModelEditorView
	: public SharedModelEditorView
{
public:
	void onSetEntityData() override;
	void onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity) override;
	void onInitAdditionalScreens() override;

private:
	LevelEditorEntity* loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */ override;

public:
	/**
	 * Public constructor
	 * @param pop ups view
	 */
	ModelEditorView(PopUps* popUps);
};
