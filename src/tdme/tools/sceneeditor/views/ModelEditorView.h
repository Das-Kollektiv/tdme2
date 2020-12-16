#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/sceneeditor/views/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>

using std::string;

using tdme::tools::shared::views::SharedModelEditorView;
using tdme::math::Vector3;
using tdme::engine::prototype::Prototype;
using tdme::tools::shared::views::PopUps;

/**
 * Model editor view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::sceneeditor::views::ModelEditorView final: public SharedModelEditorView
{
public:
	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	ModelEditorView(PopUps* popUps);

	// overridden methods
	virtual void onSetPrototypeData() override;
	virtual void onLoadModel(Prototype* oldEntity, Prototype* entity) override;
	virtual void onInitAdditionalScreens() override;

private:
	// overridden methods
	virtual Prototype* loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) override;

};
