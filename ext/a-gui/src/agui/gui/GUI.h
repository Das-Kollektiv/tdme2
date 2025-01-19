#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <agui/agui.h>

#include <agui/gui/fwd-agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/misc/GUITiming.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/gui/textures/fwd-agui.h>
#include <agui/gui/vbos/fwd-agui.h>
#include <agui/gui/GUIEventHandler.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/RTTI.h>
#include <agui/utilities/Time.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

// namespaces
namespace agui {
namespace gui {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::misc::GUITiming;
	using ::agui::gui::nodes::GUIColor;
	using ::agui::gui::nodes::GUIElementNode;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUIScreenNode;
	using ::agui::gui::renderer::GUIRenderer;
	using ::agui::gui::renderer::GUIRendererBackend;
	using ::agui::gui::renderer::GUIShader;
	using ::agui::gui::textures::GUITextureManager;
	using ::agui::gui::vbos::GUIVBOManager;
	using ::agui::gui::GUIEventHandler;
	using ::agui::utilities::Console;
	using ::agui::utilities::Exception;
	using ::agui::utilities::RTTI;
	using ::agui::utilities::Time;
}
}

template<typename T, typename U>
static T required_dynamic_cast(U u)
{
	auto t = dynamic_cast<T>(u);
	if (t == nullptr) {
		::agui::utilities::Console::printLine("required_dynamic_cast: unable to perform required dynamic cast @\n\n" + ::agui::utilities::RTTI::backtrace());
		throw ::agui::utilities::ExceptionBase("required_dynamic_cast did fail");

	}
	return t;
}

#define MOUSE_CURSOR_DISABLED 0
#define MOUSE_CURSOR_ENABLED 1
#define MOUSE_CURSOR_NORMAL 1
#define MOUSE_CURSOR_HAND 2

/**
 * GUI module class
 * @author Andreas Drewke
 */
class agui::gui::GUI final: public virtual GUIEventHandler
{
	friend class agui::gui::nodes::GUIScreenNode;

private:
	AGUI_STATIC_DLL_IMPEXT static bool disableTabFocusControl;

	static GUIApplication* application;
	static GUIRendererBackend* rendererBackend;
	static unique_ptr<GUIRenderer> renderer;
	static unique_ptr<GUITextureManager> textureManager;
	static unique_ptr<GUIVBOManager> vboManager;
	static unique_ptr<GUIShader> shader;

	GUITiming timing;
	unordered_map<string, GUIScreenNode*> screens;
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
	 * Fake a keyboard modifier event
	 */
	void fakeKeyboardModifierEvent();

	/**
	 * Render screens change
	 */
	void unsetMouseStates();

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
	 * @return application
	 */
	static inline GUIApplication* getApplication() {
		return application;
	}

	/**
	 * @return renderer backend
	 */
	static inline GUIRendererBackend* getRendererBackend() {
		return rendererBackend;
	}

	/**
	 * @return renderer
	 */
	static inline GUIRenderer* getRenderer() {
		return renderer.get();
	}

	/**
	 * @return texture manager
	 */
	static inline GUITextureManager* getTextureManager() {
		return textureManager.get();
	}

	/**
	 * @return VBO manager
	 */
	static inline GUIVBOManager* getVBOManager() {
		return vboManager.get();
	}

	/**
	 * @return GUI shader
	 */
	static inline GUIShader* getShader() {
		return shader.get();
	}

	// forbid class copy
	FORBID_CLASS_COPY(GUI)

	/**
	 * Public constructor
	 * @param application application
	 * @param rendererBackend renderer backend
	 * @param width width
	 * @param height height
	 */
	GUI(GUIApplication* application, GUIRendererBackend* rendererBackend, int width, int height);

	/**
	 * Destructor
	 */
	~GUI();

	/**
	 * @return timing
	 */
	inline GUITiming* getTiming() {
		return &timing;
	}

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
	 * @param screenIdx screen index or -1 to push to the end
	 */
	void addRenderScreen(const string& screenId, int screenIdx = -1);

	/**
	 * Remove render screen
	 * @param screenId screenId
	 */
	void removeRenderScreen(const string& screenId);

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
	 * @param modifiers modifiers
	 */
	void onKeyDown (int key, int keyCode, int x, int y, bool repeat, int modifiers) override;

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

	/**
	 * Register mouse dragging
	 * @param node node
	 */
	void startMouseDragging(GUINode* node) {
		mouseIsDragging[node->screenNode->getId()] = true;
		mousePressedEventNodeIds[node->screenNode->getId()].insert(node->getId());
		mouseDraggingEventNodeIds[node->screenNode->getId()].insert(node->getId());
	}

	/**
	 * Get scaled x from unscaled x
	 * @param screenNode screen node
	 * @param x x
	 * @return scaled x
	 */
	inline int getScaledX(GUIScreenNode* screenNode, int x) {
		return (float)x * (float)screenNode->getScreenWidth() / (float)width + screenNode->getGUIEffectOffsetX();
	}

	/**
	 * Get scaled y from unscaled y
	 * @param screenNode screen node
	 * @param y y
	 * @return scaled y
	 */
	inline int getScaledY(GUIScreenNode* screenNode, int y) {
		return (float)y * (float)screenNode->getScreenHeight() / (float)height + screenNode->getGUIEffectOffsetY();
	}

};
