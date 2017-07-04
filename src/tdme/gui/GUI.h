// Generated from /tdme/src/tdme/gui/GUI.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/ApplicationInputEventsHandler.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::util::concurrent::locks::ReentrantLock;
using tdme::engine::Engine;
using tdme::engine::ApplicationInputEventsHandler;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * GUI
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUI final
	: public virtual Object, public virtual ApplicationInputEventsHandler
{

public:
	typedef Object super;

private:
	GUIRenderer* guiRenderer {  };
	Engine* engine {  };
	_HashMap* screens {  };
	static _HashMap* fontCache;
	static _HashMap* imageCache;
	GUIColor* foccussedBorderColor {  };
	_ArrayList* focusableNodes {  };
	_ArrayList* focusableScreenNodes {  };
	GUIElementNode* focussedNode {  };
	GUIColor* unfocussedNodeBorderLeftColor {  };
	GUIColor* unfocussedNodeBorderRightColor {  };
	GUIColor* unfocussedNodeBorderTopColor {  };
	GUIColor* unfocussedNodeBorderBottomColor {  };
	Pool* mouseEventsPool {  };
	_ArrayList* mouseEvents {  };
	Pool* keyboardEventsPool {  };
	_ArrayList* keyboardEvents {  };
	ReentrantLock* eventsMutex {  };
	_ArrayList* renderScreens {  };
	int32_t width {  };
	int32_t height {  };
	int32_t mouseButtonLast { };
protected:

	/** 
	 * Constructor
	 * @param engine 
	 * @param GUI renderer
	 */
	void ctor(Engine* engine, GUIRenderer* guiRenderer);

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
	 * @param width
	 * @param height
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
	_ArrayList* getMouseEvents();

	/** 
	 * @return keyboard events
	 */
	_ArrayList* getKeyboardEvents();

	/** 
	 * Get font
	 * @param file name
	 * @return
	 */
	static GUIFont* getFont(String* fileName);

	/** 
	 * Get image
	 * @param file name
	 * @return
	 */
	static Texture* getImage(String* fileName);

	/** 
	 * Get screen
	 * @param id
	 * @return screen
	 */
	GUIScreenNode* getScreen(String* id);

	/** 
	 * Add screen
	 * @param id
	 * @param gui
	 */
	void addScreen(String* id, GUIScreenNode* screen);

	/** 
	 * Removes an screen
	 * @param id
	 */
	void removeScreen(String* id);

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
	 * @param screenId
	 */
	void addRenderScreen(String* screenId);

	/** 
	 * @return focussed border color
	 */
	GUIColor* getFoccussedBorderColor();

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
	 * @param foccussed node
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

private:

	/** 
	 * Handle events for given node
	 * @param node
	 */
	void handleEvents(GUINode* node);

public:
	/**
	 * On key down
	 * @param key
	 * @param x
	 * @param y
	 */
	void onKeyDown (unsigned char key, int x, int y) override;

	/**
	 * On key up
	 * @param key
	 * @param x
	 * @param y
	 */
	void onKeyUp(unsigned char key, int x, int y) override;

	/**
	 * On special key up
	 * @param key
	 * @param x
	 * @param y
	 */
	void onSpecialKeyDown (int key, int x, int y) override;

	/**
	 * On special key up
	 * @param key
	 * @param x
	 * @param y
	 */
	void onSpecialKeyUp(int key, int x, int y) override;

	/**
	 * On mouse dragged
	 * @param x
	 * @param y
	 */
	void onMouseDragged(int x, int y) override;

	/**
	 * On mouse moved
	 * @param x
	 * @param y
	 */
	void onMouseMoved(int x, int y) override;

	/**
	 * On mouse moved
	 * @param button
	 * @param state
	 * @param x
	 * @param y
	 */
	void onMouseButton(int button, int state, int x, int y) override;

	/** 
	 * Handle screen events
	 */
	void handleEvents();

private:

	/** 
	 * Fake mouse moved event
	 */
	void fakeMouseMovedEvent();

public:

	// Generated
	GUI(Engine* engine, GUIRenderer* guiRenderer);
protected:
	GUI(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class GUI_1;
	friend class GUI_2;
};
