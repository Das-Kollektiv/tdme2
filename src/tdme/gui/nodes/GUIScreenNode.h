#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using std::map;
using std::string;
using std::vector;

using tdme::gui::nodes::GUIParentNode;
using tdme::gui::GUI;
using tdme::gui::effects::GUIEffect;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::MutableString;

/** 
 * GUI Screen Node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIScreenNode final
	: public GUIParentNode
{
	friend class tdme::gui::GUIParser;
	friend class GUIElementNode;
	friend class GUINode;
	friend class GUIParentNode;

private:
	GUI* gui {  };
	int32_t nodeCounter {  };
	int32_t screenWidth {  };
	int32_t screenHeight {  };
	map<string, GUINode*> nodesById {  };
	vector<GUINode*> floatingNodes {  };
	vector<GUIActionListener*> actionListener {  };
	vector<GUIChangeListener*> changeListener {  };
	GUIInputEventHandler* inputEventHandler {  };
	vector<GUINode*> childControllerNodes {  };

private:
	bool mouseEventProcessedByFloatingNode {  };
	bool visible {  };
	bool popUp {  };

private:
	map<string, GUIEffect*> effects {  };
	int32_t guiEffectOffsetX {  };
	int32_t guiEffectOffsetY {  };

public:

	/** 
	 * @return GUI
	 */
	GUI* getGUI();

	/** 
	 * Set GUI
	 * @param gui
	 */
	void setGUI(GUI* gui);

	/** 
	 * @return screen width
	 */
	int32_t getScreenWidth();

	/** 
	 * @return screen height
	 */
	int32_t getScreenHeight();

	/** 
	 * @return is visible
	 */
	bool isVisible();

	/** 
	 * Set visible
	 * @param visible
	 */
	void setVisible(bool visible);

	/** 
	 * @return is pop up
	 */
	bool isPopUp();

	/** 
	 * Set pop up
	 * @param pop up
	 */
	void setPopUp(bool popUp);

	/** 
	 * @return floating nodes
	 */
	vector<GUINode*>* getFloatingNodes();

	/** 
	 * @return GUI effect offset X
	 */
	int32_t getGUIEffectOffsetX();

	/** 
	 * Set GUI effect offset X
	 * @param gui effect offset X
	 */
	void setGUIEffectOffsetX(int32_t guiEffectOffsetX);

	/** 
	 * @return GUI effect offset Y 
	 */
	int32_t getGUIEffectOffsetY();

	/** 
	 * Set GUI effect offset Y
	 * @param gui effect offset Y
	 */
	void setGUIEffectOffsetY(int32_t guiEffectOffsetY);

protected:
	bool isContentNode() override;

	/**
	 * @return node type
	 */
	const string getNodeType() override;

	GUIScreenNode(const string& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, const GUINode_Alignments& alignments, const GUINode_RequestedConstraints& requestedConstraints, const GUIColor& backgroundColor, const GUINode_Border& border, const GUINode_Padding& padding, const GUINodeConditions& showOn, const GUINodeConditions& hideOn, bool scrollable, bool popUp) throw(GUIParserException);

private:
	/**
	 * Add node
	 * @param node
	 * @return success
	 */
	bool addNode(GUINode* node);

	/**
	 * Add node
	 * @param node
	 * @return success
	 */
	bool removeNode(GUINode* node);

public:

	/** 
	 * @return content width
	 */
	int32_t getContentWidth() override;

	/** 
	 * @return content height
	 */
	int32_t getContentHeight() override;

	/** 
	 * Layout
	 */
	void layout() override;

	/** 
	 * Layout node content (e.g. child nodes or content)
	 * this does also does call layouted nodes post layout method
	 * @param node
	 */
	void layout(GUINode* node);

	/** 
	 * Set screen size
	 * @param width
	 * @param height
	 */
	void setScreenSize(int32_t width, int32_t height);

	/** 
	 * Get GUI node by id
	 * @param nodeId
	 * @return GUI node or null
	 */
	GUINode* getNodeById(const string& nodeId);

	/** 
	 * Allocate node id
	 * @return node id
	 */
	const string allocateNodeId();

	/** 
	 * Render screen
	 * @param gui renderer
	 */
	void render(GUIRenderer* guiRenderer);

	/** 
	 * Render floating nodes
	 * @param gui renderer
	 */
	void renderFloatingNodes(GUIRenderer* guiRenderer);

	/** 
	 * Determine focussed nodes
	 * @param parent node
	 * @param focusable nodes
	 */
	void determineFocussedNodes(GUIParentNode* parentNode, vector<GUIElementNode*>& focusableNodes);
	void handleMouseEvent(GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;

	/** 
	 * Add action listener
	 * @param listener
	 */
	void addActionListener(GUIActionListener* listener);

	/** 
	 * Remove action listener
	 * @param listener
	 */
	void removeActionListener(GUIActionListener* listener);

	/** 
	 * @return input event handler
	 */
	GUIInputEventHandler* getInputEventHandler();

	/** 
	 * Set input event handler 
	 * @param input event handler
	 */
	void setInputEventHandler(GUIInputEventHandler* inputEventHandler);

	/** 
	 * Delegate action performed
	 * @param node
	 */
	void delegateActionPerformed(GUIActionListener_Type* type, GUIElementNode* node);

	/** 
	 * Add change listener
	 * @param listener
	 */
	void addChangeListener(GUIChangeListener* listener);

	/** 
	 * Remove change listener
	 * @param listener
	 */
	void removeChangeListener(GUIChangeListener* listener);

	/** 
	 * Delegate value changed
	 * @param node
	 */
	void delegateValueChanged(GUIElementNode* node);

	/** 
	 * Get values
	 * @param values
	 */
	void getValues(map<string, MutableString*>* values);

	/** 
	 * Set values
	 * @param values
	 */
	void setValues(map<string, MutableString*>* values);

	/** 
	 * Add effect that will be removed if finished
	 * @param id
	 * @param effect
	 * @return success
	 */
	bool addEffect(const string& id, GUIEffect* effect);

	/** 
	 * Get effect
	 * @param id
	 * @return effect or null
	 */
	GUIEffect* getEffect(const string& id);

	/** 
	 * Remove effect
	 * @param id
	 * @return success
	 */
	bool removeEffect(const string& id);

private:
	void init();

public:
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;
};
