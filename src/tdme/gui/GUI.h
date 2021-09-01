#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
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
using tdme::engine::fileio::textures::Texture;
using tdme::engine::Engine;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::filesystem::FileSystemException;
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
 * @version $Id$
 */
class tdme::gui::GUI final: public virtual InputEventHandler
{
	friend class tdme::gui::elements::GUIDropDownController;
	friend class tdme::gui::elements::GUIMenuHeaderItemController;
	friend class tdme::gui::nodes::GUIElementController;
	friend class tdme::gui::nodes::GUIHorizontalScrollbarInternalController;
	friend class tdme::gui::nodes::GUIVerticalScrollbarInternalController;

private:
	static unordered_map<string, GUIFont*>* fontCache;
	static unordered_map<string, Texture*>* imageCache;

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
	int mouseButtonLast;
	unordered_map<string, unordered_set<string>> mouseOutCandidateEventNodeIds;
	unordered_map<string, unordered_set<string>> mouseOutClickCandidateEventNodeIds;
	unordered_map<string, unordered_set<string>> mousePressedEventNodeIds;
	unordered_map<string, unordered_set<string>> mouseDraggingEventNodeIds;
	unordered_map<string, bool> mouseIsDragging;

	bool altDown { false };
	bool controlDown { false };
	bool shiftDown { false };

	/**
	 * Add node that is a possible mouse out candidate as it received a mouse over
	 * @param node element node
	 */
	void addMouseOutCandidateElementNode(GUINode* node);

	/**
	 * Add node that is a possible mouse click out candidate as it received a mouse click
	 * @param node element node
	 */
	void addMouseOutClickCandidateElementNode(GUINode* node);

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

public:
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
	int getWidth();

	/**
	 * @return height
	 */
	int getHeight();

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
	 * Lock mouse events
	 */
	void lockEvents();

	/**
	 * Unlock events
	 */
	void unlockEvents();

	/**
	 * @return mouse events
	 */
	vector<GUIMouseEvent>& getMouseEvents();

	/**
	 * @return keyboard events
	 */
	vector<GUIKeyboardEvent>& getKeyboardEvents();

	/**
	 * Get font
	 * @param applicationRootPath application root path
	 * @param fileName file name
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return font
	 */
	static GUIFont* getFont(const string& applicationRootPath, const string& fileName);

	/**
	 * Get image
	 * @param applicationRootPath application root path
	 * @param fileName file name
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return texture
	 */
	static Texture* getImage(const string& applicationRootPath, const string& fileName);

	/**
	 * Get screen
	 * @param id id
	 * @return screen
	 */
	GUIScreenNode* getScreen(const string& id);

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
	bool hasRenderScreen(const string& screenId);

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
	GUIColor& getFoccussedBorderColor();

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

	void onChar(unsigned int key, int x, int y) override;
	/**
	 * On key down
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	void onKeyDown (unsigned char key, int x, int y) override;

	/**
	 * On key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	void onKeyUp(unsigned char key, int x, int y) override;

	/**
	 * On special key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	void onSpecialKeyDown (int key, int x, int y) override;

	/**
	 * On special key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	void onSpecialKeyUp(int key, int x, int y) override;

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
	 */
	void handleEvents();

};
