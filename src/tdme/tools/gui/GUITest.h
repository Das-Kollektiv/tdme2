#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/gui/fwd-tdme.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;


/**
 * GUI Test
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::gui::GUITest final
	: public virtual Application, public virtual GUIActionListener, public virtual GUIChangeListener
{
private:
	string screenFileName;
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };

public:
	/**
	 * Public constructor
	 * @param screenFileName screen file name
	 */
	GUITest(const string& screenFileName);

	/**
	 * Public destructor
	 */
	~GUITest();

	void initialize() override;
	void dispose() override;
	void reshape(int width, int height) override;
	void display() override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onValueChanged(GUIElementNode* node) override;

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);
};
