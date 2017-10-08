#pragma once

#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI tabs controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabsController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	vector<GUINode*> childControllerNodes {  };
	MutableString* tabContentNodeId {  };
protected:

	/** 
	 * Constructor
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * Unselect all tab nodes
	 */
	void unselect();

	/** 
	 * Set tab content selected
	 * @param id
	 */
	void setTabContentSelected(const wstring& id);

public:
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

public: /* protected */
	GUITabsController(GUINode* node);

protected:
	GUITabsController(const ::default_init_tag&);

private:
	void init();
};
