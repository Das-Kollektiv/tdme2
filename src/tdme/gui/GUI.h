#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/application/ApplicationInputEventsHandler.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Time.h>

using std::map;
using std::set;
using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::application::ApplicationInputEventsHandler;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::Time;

/** 
 * GUI
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUI final
	: public virtual ApplicationInputEventsHandler
{
private:
	GUIRenderer* guiRenderer {  };
	Engine* engine {  };
	map<string, GUIScreenNode*> screens {  };
	static map<string, GUIFont*> fontCache;
	static map<string, Texture*> imageCache;
	GUIColor foccussedBorderColor;
	vector<GUIElementNode*> focusableNodes {  };
	vector<GUIScreenNode*> focusableScreenNodes {  };
	GUIElementNode* focussedNode {  };
	GUIColor unfocussedNodeBorderLeftColor;
	GUIColor unfocussedNodeBorderRightColor;
	GUIColor unfocussedNodeBorderTopColor;
	GUIColor unfocussedNodeBorderBottomColor;
	vector<GUIMouseEvent> mouseEvents {  };
	vector<GUIKeyboardEvent> keyboardEvents {  };
	vector<GUIScreenNode*> renderScreens {  };
	int32_t width {  };
	int32_t height {  };
	int32_t mouseButtonLast { };
	map<string, set<string>> mouseMovedEventNodeIdsLast;
	map<string, set<string>> mousePressedEventNodeIds;
	map<string, set<string>> mouseDraggingEventNodeIds;
	map<string, bool> mouseIsDragging;

public:

	/** 
	 * @return width
	 */
	int32_t getWidth();

	/** 
	 * @return height
	 */
	int32_t getHeight();

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Reshape
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

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
	 * @param fileName file name
	 * @return
	 */
	static GUIFont* getFont(const string& fileName);

	/** 
	 * Get image
	 * @param fileName file name
	 * @return
	 */
	static Texture* getImage(const string& fileName);

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

private:

	/** 
	 * Determine focussed nodes
	 */
	void determineFocussedNodes();

public:

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

private:

	/** 
	 * Handle mouse event for given node
	 * @param node node
	 * @param event event
	 * @param mouseMovedEventNodeIds mouse moved event nodes ids
	 * @param mousePressedEventNodeIds mouse pressed event node ids
	 */
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event, set<string>& mouseMovedEventNodeIds, set<string>& mousePressedEventNodeIds);

	/**
	 * Handle mouse event for given node
	 * @param event event
	 */
	void handleKeyboardEvent(GUIKeyboardEvent* event);

public:
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

private:

	/** 
	 * Fake mouse moved event
	 */
	void fakeMouseMovedEvent();

	/**
	 *
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

};
