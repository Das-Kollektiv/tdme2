#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::application::InputEventHandler;
using tdme::engine::Engine;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Time;

template<typename T, typename U>
static T required_dynamic_cast(U u)
{
	auto t = dynamic_cast<T>(u);
	if (t == nullptr) {
		throw ExceptionBase("required_dynamic_cast did fail");
	}
	return t;
}

/**
 * GUI module class
 * @author Andreas Drewke
 */
class tdme::gui::GUI final: public virtual InputEventHandler
{
	friend class tdme::gui::nodes::GUIScreenNode;

private:
	STATIC_DLL_IMPEXT static bool disableTabFocusControl;

	GUIRenderer* guiRenderer { nullptr };
	Engine* engine { nullptr };
	unordered_map<string, GUIScreenNode*> screens;
	GUIColor foccussedBorderColor;
	vector<GUIElementNode*> focusableNodes;
	vector<GUIScreenNode*> focusableScreenNodes;
	string focussedNodeScreenId;
	string focussedNodeNodeId;
	GUIColor unfocussedNodeBorderLeftColor;
	GUIColor unfocussedNodeBorderRightColor;
	GUIColor unfocussedNodeBorderTopColor;
	GUIColor unfocussedNodeBorderBottomColor;
	vector<GUIMouseEvent> mouseEvents;
	vector<GUIKeyboardEvent> keyboardEvents;
	vector<GUIScreenNode*> renderScreens;
	int width;
	int height;
	int lastMouseButton;
	int64_t lastEventTime { -1LL };
	bool tooltipShown { false };
	GUIMouseEvent lastMouseEvent;

	unordered_map<string, unordered_set<string>> mouseOutCandidateEventNodeIds;
	unordered_map<string, unordered_set<string>> mouseOutClickCandidateEventNodeIds;
	unordered_map<string, unordered_set<string>> mousePressedEventNodeIds;
	unordered_map<string, unordered_set<string>> mouseDraggingEventNodeIds;
	unordered_map<string, bool> mouseIsDragging;

	bool altDown { false };
	bool controlDown { false };
	bool shiftDown { false };

	/**
	 * Determine focussed nodes
	 */
	void determineFocussedNodes();

	/**
	 * Handle mouse event for given node
	 * @param node node
	 * @param event event
	 * @param mouseOutCandidateEventNodeIds mouse out candidate event node ids
	 * @param mouseOutClickCandidateEventNodeIds mouse out click candidate event node ids
	 * @param mousePressedEventNodeIds mouse pressed event node ids
	 * @param floatingNodes check if to gather floating nodes only
	 */
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event, const unordered_set<string>& mouseOutCandidateEventNodeIds, const unordered_set<string>& mouseOutClickCandidateEventNodeIds, unordered_set<string>& mousePressedEventNodeIds, bool floatingNodes);

	/**
	 * Handle mouse event for given node
	 * @param event event
	 */
	void handleKeyboardEvent(GUIKeyboardEvent* event);

	/**
	 * Reshape screen
	 * @param screenNode screen node
	 */
	void reshapeScreen(GUIScreenNode* screenNode);

	/**
	 * Fake mouse moved event
	 */
	void fakeMouseMovedEvent();

	/**
	 * Fake a keyboard modifier event
	 */
	void fakeKeyboardModifierEvent();

	/**
	 * Render screens change
	 */
	void applyRenderScreensChange();

public:
	static constexpr int64_t TOOLTIP_TIME { 250LL };

	/**
	 * @return is focus control by TAB key disabled
	 */
	inline static bool isDisableTabFocusControl() {
		return disableTabFocusControl;
	}

	/**
	 * Set focus control by TAB key disabled
	 * @param disableTabFocusControl disable TAB focus control
	 */
	inline static void setDisableTabFocusControl(bool disableTabFocusControl) {
		GUI::disableTabFocusControl = disableTabFocusControl;
	}

	/**
	 * Public constructor
	 * @param engine engine
	 * @param guiRenderer gui renderer
	 */
	GUI(Engine* engine, GUIRenderer* guiRenderer);

	/**
	 * Destructor
	 */
	~GUI();

	/**
	 * @return width
	 */
	inline int getWidth() {
		return width;
	}

	/**
	 * @return height
	 */
	inline int getHeight() {
		return height;
	}

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Reshape
	 * @param width width
	 * @param height height
	 */
	void reshape(int width, int height);

	/**
	 * Dispose
	 */
	void dispose();

	/**
	 * @return mouse events
	 */
	inline vector<GUIMouseEvent>& getMouseEvents() {
		return mouseEvents;
	}

	/**
	 * @return keyboard events
	 */
	inline vector<GUIKeyboardEvent>& getKeyboardEvents() {
		return keyboardEvents;
	}

	/**
	 * Get screen
	 * @param id id
	 * @return screen
	 */
	inline GUIScreenNode* getScreen(const string& id) {
		auto screensIt = screens.find(id);
		if (screensIt == screens.end()) {
			return nullptr;
		}
		return screensIt->second;
	}

	/**
	 * Add screen
	 * @param id id
	 * @param screen gui
	 */
	void addScreen(const string& id, GUIScreenNode* screen);

	/**
	 * Removes an screen
	 * @param id id
	 */
	void removeScreen(const string& id);

	/**
	 * Removes all screens and caches
	 */
	void reset();

	/**
	 * Reset render screens
	 */
	void resetRenderScreens();

	/**
	 * Returns if given screen is beeing rendered
	 * @param screenId screenId
	 */
	inline bool hasRenderScreen(const string& screenId) {
		for (auto renderScreen: renderScreens) {
			if (renderScreen->getId() == screenId) return true;
		}
		return false;
	}

	/**
	 * Add render screen
	 * @param screenId screenId
	 */
	void addRenderScreen(const string& screenId);

	/**
	 * Remove render screen
	 * @param screenId screenId
	 */
	void removeRenderScreen(const string& screenId);

	/**
	 * @return focussed border color
	 */
	inline GUIColor& getFoccussedBorderColor() {
		return foccussedBorderColor;
	}

	/**
	 * Invalidate focussed node
	 */
	void invalidateFocussedNode();

	/**
	 * @return focussed node
	 */
	GUIElementNode* getFocussedNode();

	/**
	 * Unfocus current focussed node
	 */
	void unfocusNode();

	/**
	 * Focus current focussed node
	 */
	void focusNode();

	/**
	 * Set focussed node
	 * @param newFoccussedNode foccussed node
	 */
	void setFoccussedNode(GUIElementNode* newFoccussedNode);

	/**
	 * Focus next node
	 */
	void focusNextNode();

	/**
	 * Focus next node
	 */
	void focusPreviousNode();

	/**
	 * Add node that is a possible mouse out candidate as it received a mouse over
	 * @param node element node
	 */
	inline void addMouseOutCandidateNode(GUINode* node) {
		mouseOutCandidateEventNodeIds[node->getScreenNode()->getId()].insert(node->getId());
	}

	/**
	 * Add node that is a possible mouse click out candidate as it received a mouse click
	 * @param node element node
	 */
	inline void addMouseOutClickCandidateNode(GUINode* node) {
		mouseOutClickCandidateEventNodeIds[node->getScreenNode()->getId()].insert(node->getId());
	}

	/**
	 * Render GUIs
	 */
	void render();

	/**
	 * Reports if node has currently mouse interaction like dragging or pressing
	 * @param node node
	 * @return if node has currently mouse interaction
	 */
	bool isHavingMouseInteraction(GUINode* node);

	/**
	 * On char
	 * @param key key
	 * @param x x
	 * @param y y
	 */

	void onChar(int key, int x, int y) override;
	/**
	 * On key down
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 * @param repeat repeat event
	 */
	void onKeyDown (int key, int keyCode, int x, int y, bool repeat) override;

	/**
	 * On key up
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 */
	void onKeyUp(int key, int keyCode, int x, int y) override;

	/**
	 * On mouse dragged
	 * @param x x
	 * @param y y
	 */
	void onMouseDragged(int x, int y) override;

	/**
	 * On mouse moved
	 * @param x x
	 * @param y y
	 */
	void onMouseMoved(int x, int y) override;

	/**
	 * On mouse moved
	 * @param button button
	 * @param state state
	 * @param x x
	 * @param y y
	 */
	void onMouseButton(int button, int state, int x, int y) override;

	/**
	 * On mouse wheel
	 * @param button button
	 * @param direction direction
	 * @param x x
	 * @param y y
	 */
	void onMouseWheel(int button, int direction, int x, int y) override;

	/**
	 * Handle screen events
	 * @param clearEvents clear events
	 */
	void handleEvents(bool clearEvents = true);

};
