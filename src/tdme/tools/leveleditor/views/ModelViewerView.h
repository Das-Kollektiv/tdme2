#pragma once

#include <string>

#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using std::wstring;

using tdme::tools::shared::views::SharedModelViewerView;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::PopUps;

/** 
 * Model viewer view
 * @author Andreas Drewke
 * @version $Id$ 
 */
class tdme::tools::leveleditor::views::ModelViewerView
	: public SharedModelViewerView
{
public:
	void onSetEntityData() override;
	void onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity) override;
	void onInitAdditionalScreens() override;

public: /* protected */
	LevelEditorEntity* loadModel(const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName, const Vector3& pivot) /* throws(Exception) */ override;

public:
	/**
	 * Public constructor
	 * @param pop ups view
	 */
	ModelViewerView(PopUps* popUps);
};
