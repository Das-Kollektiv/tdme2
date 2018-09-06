#pragma once

#include <map>
#include <set>
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
#include <tdme/gui/nodes/GUIScreenNode_SizeConstraints.h>

using std::map;
using std::set;
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
using tdme::gui::events::GUIMouseOverListener;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode_SizeConstraints;
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
	friend class tdme::gui::GUI;
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
	map<string, GUINode*> tickNodesById {  };
	vector<GUINode*> floatingNodes {  };
	vector<GUIActionListener*> actionListener {  };
	vector<GUIChangeListener*> changeListener {  };
	vector<GUIMouseOverListener*> mouseOverListener {  };
	GUIInputEventHandler* inputEventHandler {  };
	vector<GUINode*> childControllerNodes {  };
	GUIScreenNode_SizeConstraints sizeConstraints {  };

	bool mouseEventProcessedByFloatingNode {  };
	bool visible {  };
	bool popUp {  };

	map<string, GUIEffect*> effects {  };
	int32_t guiEffectOffsetX {  };
	int32_t guiEffectOffsetY {  };

	bool reshapeRequested { false };

public:

	/** 
	 * @return GUI
	 */
	GUI* getGUI();

	/** 
	 * Set GUI
	 * @param gui gui
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
	 * @param visible visible
	 */
	void setVisible(bool visible);

	/** 
	 * @return is pop up
	 */
	bool isPopUp();

	/** 
	 * Set pop up
	 * @param popUp pop up
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
	 * @param guiEffectOffsetX gui effect offset X
	 */
	void setGUIEffectOffsetX(int32_t guiEffectOffsetX);

	/** 
	 * @return GUI effect offset Y 
	 */
	int32_t getGUIEffectOffsetY();

	/** 
	 * Set GUI effect offset Y
	 * @param guiEffectOffsetY gui effect offset Y
	 */
	void setGUIEffectOffsetY(int32_t guiEffectOffsetY);

protected:
	bool isContentNode() override;

	/**
	 * @return node type
	 */
	const string getNodeType() override;

	/**
	 * Constructor
	 * @param id id
	 * @param flow flow
	 * @param overflowX overflow x
	 * @param overflowY overflow y
	 * @param alignments alignments
	 * @param requestedConstraints requested constraints
	 * @param backgroundColor background color
	 * @param backgroundImage background image
	 * @param backgroundImageScale9Grid background image scale 9 grid
	 * @param border border
	 * @param padding padding
	 * @param sizeConstraints size constraints
	 * @param showOn show on
	 * @param hideOn hide on
	 * @param scrollable scrollable
	 * @param popUp pop up
	 */
	GUIScreenNode(
		const string& id,
		GUINode_Flow* flow,
		GUIParentNode_Overflow* overflowX,
		GUIParentNode_Overflow* overflowY,
		const GUINode_Alignments& alignments,
		const GUINode_RequestedConstraints& requestedConstraints,
		const GUIColor& backgroundColor,
		const string& backgroundImage,
		const GUINode_Scale9Grid& backgroundImageScale9Grid,
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUIScreenNode_SizeConstraints& sizeConstraints,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		bool scrollable,
		bool popUp
	) throw(GUIParserException);

	/**
	 * Destructor
	 */
	~GUIScreenNode();

private:
	/**
	 * Add node
	 * @param node node
	 * @return success
	 */
	bool addNode(GUINode* node);

	/**
	 * Add node
	 * @param node node
	 * @return success
	 */
	bool removeNode(GUINode* node);

	/**
	 * Calls registered tick nodes controller tick method
	 */
	void tick();

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
	 * @param node node
	 */
	void layout(GUINode* node);

	/** 
	 * Set screen size
	 * @param width width
	 * @param height height
	 */
	void setScreenSize(int32_t width, int32_t height);

	/** 
	 * Get GUI node by id
	 * @param nodeId nodeId
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
	 * @param guiRenderer gui renderer
	 */
	void render(GUIRenderer* guiRenderer);

	/** 
	 * Render floating nodes
	 * @param guiRenderer gui renderer
	 */
	void renderFloatingNodes(GUIRenderer* guiRenderer);

	/** 
	 * Determine focussed nodes
	 * @param parentNode parent node
	 * @param focusableNodes focusable nodes
	 */
	void determineFocussedNodes(GUIParentNode* parentNode, vector<GUIElementNode*>& focusableNodes);

	// overriden methods
	void determineMouseEventNodes(GUIMouseEvent* event, set<string>& eventNodeIds) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;

	/** 
	 * Add action listener
	 * @param listener listener
	 */
	void addActionListener(GUIActionListener* listener);

	/** 
	 * Remove action listener
	 * @param listener listener
	 */
	void removeActionListener(GUIActionListener* listener);

	/** 
	 * @return input event handler
	 */
	GUIInputEventHandler* getInputEventHandler();

	/** 
	 * Set input event handler 
	 * @param inputEventHandler input event handler
	 */
	void setInputEventHandler(GUIInputEventHandler* inputEventHandler);

	/** 
	 * Delegate action performed
	 * @param type type
	 * @param node node
	 */
	void delegateActionPerformed(GUIActionListener_Type* type, GUIElementNode* node);

	/** 
	 * Add change listener
	 * @param listener listener
	 */
	void addChangeListener(GUIChangeListener* listener);

	/** 
	 * Remove change listener
	 * @param listener listener
	 */
	void removeChangeListener(GUIChangeListener* listener);

	/** 
	 * Delegate value changed
	 * @param node node
	 */
	void delegateValueChanged(GUIElementNode* node);

	/**
	 * Add mouse over listener
	 * @param listener listener
	 */
	void addMouseOverListener(GUIMouseOverListener* listener);

	/**
	 * Remove mouse over listener
	 * @param listener listener
	 */
	void removeMouseOverListener(GUIMouseOverListener* listener);

	/**
	 * Delegate mouse over event
	 * @param node node
	 */
	void delegateMouseOver(GUIElementNode* node);

	/**
	 * Add tick node, registered node controllers will have a tick once per frame
	 * @param
	 */
	void addTickNode(GUINode* node);

	/**
	 * Remove tick node
	 */
	void removeTickNode(GUINode* node);

	/** 
	 * Get values
	 * @param values values
	 */
	void getValues(map<string, MutableString>& values);

	/** 
	 * Set values
	 * @param values values
	 */
	void setValues(const map<string, MutableString>& values);

	/** 
	 * Add effect that will be removed if finished
	 * @param id id
	 * @param effect effect
	 * @return success
	 */
	bool addEffect(const string& id, GUIEffect* effect);

	/** 
	 * Get effect
	 * @param id id
	 * @return effect or null
	 */
	GUIEffect* getEffect(const string& id);

	/** 
	 * Remove effect
	 * @param id id
	 * @return success
	 */
	bool removeEffect(const string& id);

private:
	/**
	 * Initializes this screen
	 */
	void init();

public:
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;

	/**
	 * Create size constraints
	 * @param minWidth min width
	 * @param minHeight min height
	 * @param maxWidth max width
	 * @param maxHeight max height
	 */
	static GUIScreenNode_SizeConstraints createSizeConstraints(const string& minWidth, const string& minHeight, const string& maxWidth, const string& maxHeight);
};
