	// Generated from /tdme/src/tdme/gui/GUI.java
#include <tdme/gui/GUI.h>

#include <string>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Iterator.h>
#include <java/util/concurrent/locks/ReentrantLock.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/gui/GUI_1.h>
#include <tdme/gui/GUI_2.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>

using std::wstring;
using std::string;
using std::to_string;
using std::to_wstring;

using tdme::gui::GUI;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::Object;
using java::lang::String;
using java::lang::System;
using java::util::Iterator;
using java::util::concurrent::locks::ReentrantLock;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::gui::GUI_1;
using tdme::gui::GUI_2;
using tdme::gui::GUIParserException;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUI::GUI(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUI::GUI(Engine* engine, GUIRenderer* guiRenderer) 
	: GUI(*static_cast< ::default_init_tag* >(0))
{
	ctor(engine,guiRenderer);
}

void GUI::init()
{
	foccussedBorderColor = nullptr;
	focusableNodes = new _ArrayList();
	focusableScreenNodes = new _ArrayList();
	unfocussedNodeBorderLeftColor = nullptr;
	unfocussedNodeBorderRightColor = nullptr;
	unfocussedNodeBorderTopColor = nullptr;
	unfocussedNodeBorderBottomColor = nullptr;
	mouseEventsPool = new GUI_1(this);
	mouseEvents = new _ArrayList();
	keyboardEventsPool = new GUI_2(this);
	keyboardEvents = new _ArrayList();
	eventsMutex = new ReentrantLock();
	renderScreens = new _ArrayList();
	mouseButtonLast = 0;
}

_HashMap* GUI::fontCache;

_HashMap* GUI::imageCache;

void GUI::ctor(Engine* engine, GUIRenderer* guiRenderer)
{
	super::ctor();
	init();
	this->engine = engine;
	this->guiRenderer = guiRenderer;
	this->screens = new _HashMap();
	this->width = 0;
	this->height = 0;
	try {
		this->foccussedBorderColor = new GUIColor(u"#8080FF"_j);
	} catch (GUIParserException* gpe) {
	}
}

int32_t GUI::getWidth()
{
	return width;
}

int32_t GUI::getHeight()
{
	return height;
}

void GUI::initialize()
{
}

void GUI::reshape(int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
}

void GUI::dispose()
{
	reset();
}

void GUI::lockEvents()
{
	eventsMutex->lock();
}

void GUI::unlockEvents()
{
	eventsMutex->unlock();
}

_ArrayList* GUI::getMouseEvents()
{
	return mouseEvents;
}

_ArrayList* GUI::getKeyboardEvents()
{
	return keyboardEvents;
}

GUIFont* GUI::getFont(String* fileName)
{
	clinit();
	String* canonicalFile = _FileSystem::getInstance()->getCanonicalPath(u"."_j, fileName);
	String* path = _FileSystem::getInstance()->getPathName(canonicalFile);
	String* file = _FileSystem::getInstance()->getFileName(canonicalFile);
	String* key = nullptr;
	/*try {*/
		key = canonicalFile;
	/*} catch (IOException* ioe) {
		ioe->printStackTrace();
		return nullptr;
	}*/
	auto font = java_cast< GUIFont* >(fontCache->get(key));
	if (font == nullptr) {
		try {
			font = GUIFont::parse(path, file);
		} catch (Exception* exception) {
			exception->printStackTrace();
			return nullptr;
		}
		fontCache->put(key, font);
	}
	return font;
}

Texture* GUI::getImage(String* fileName)
{
	clinit();
	// TODO: fix me, proper get path, filename
	String* canonicalFile = _FileSystem::getInstance()->getCanonicalPath(u"."_j, fileName);
	String* path = _FileSystem::getInstance()->getPathName(canonicalFile);
	String* file = _FileSystem::getInstance()->getFileName(canonicalFile);
	String* key = nullptr;
	/*try {*/
		key = canonicalFile;
	/*} catch (IOException* ioe) {
		ioe->printStackTrace();
		return nullptr;
	}
	*/
	auto image = java_cast< Texture* >(imageCache->get(key));
	if (image == nullptr) {
		try {
			image = TextureLoader::loadTexture(path, file);
		} catch (Exception* exception) {
			exception->printStackTrace();
			return nullptr;
		}
		imageCache->put(key, image);
	}
	return image;
}

GUIScreenNode* GUI::getScreen(String* id)
{
	return java_cast< GUIScreenNode* >(screens->get(id));
}

void GUI::addScreen(String* id, GUIScreenNode* screen)
{
	screens->put(id, screen);
}

void GUI::removeScreen(String* id)
{
	auto screen = java_cast< GUIScreenNode* >(screens->remove(id));
	if (screen != nullptr) {
		screen->dispose();
	}
}

void GUI::reset()
{
	Iterator* screenKeys = screens->getKeysIterator();
	auto entitiesToRemove = new _ArrayList();
	while (screenKeys->hasNext()) {
		auto screen = java_cast< String* >(screenKeys->next());
		entitiesToRemove->add(screen);
	}
	for (auto i = 0; i < entitiesToRemove->size(); i++) {
		removeScreen(java_cast< String* >(entitiesToRemove->get(i)));
	}
	fontCache->clear();
	imageCache->clear();
}

void GUI::resetRenderScreens()
{
	for (auto i = 0; i < renderScreens->size(); i++) {
		java_cast< GUIScreenNode* >(renderScreens->get(i))->setGUI(nullptr);
	}
	renderScreens->clear();
}

void GUI::addRenderScreen(String* screenId)
{
	auto screen = java_cast< GUIScreenNode* >(screens->get(screenId));
	if (screen == nullptr)
		return;

	screen->setGUI(this);
	renderScreens->add(screen);
}

GUIColor* GUI::getFoccussedBorderColor()
{
	return foccussedBorderColor;
}

void GUI::invalidateFocussedNode()
{
	unfocusNode();
	focussedNode = nullptr;
}

void GUI::determineFocussedNodes()
{
	focusableNodes->clear();
	focusableScreenNodes->clear();
	for (auto i = renderScreens->size() - 1; i >= 0; i--) {
		auto screen = java_cast< GUIScreenNode* >(renderScreens->get(i));
		if (screen->isVisible() == false)
			continue;

		focusableScreenNodes->add(screen);
		if (screen->isPopUp() == true)
			break;

	}
	for (auto i = focusableScreenNodes->size() - 1; i >= 0; i--) {
		auto screen = java_cast< GUIScreenNode* >(focusableScreenNodes->get(i));
		screen->determineFocussedNodes(screen, focusableNodes);
	}
}

GUIElementNode* GUI::getFocussedNode()
{
	return this->focussedNode;
}

void GUI::unfocusNode()
{
	if (focussedNode != nullptr) {
		focussedNode->getActiveConditions()->remove(GUIElementNode::CONDITION_FOCUS);
		focussedNode->getBorder()->topColor = unfocussedNodeBorderTopColor;
		focussedNode->getBorder()->leftColor = unfocussedNodeBorderLeftColor;
		focussedNode->getBorder()->bottomColor = unfocussedNodeBorderBottomColor;
		focussedNode->getBorder()->rightColor = unfocussedNodeBorderRightColor;
		if (focussedNode->getController() != nullptr)
			focussedNode->getController()->onFocusLost();

	}
}

void GUI::focusNode()
{
	if (focussedNode != nullptr) {
		focussedNode->getActiveConditions()->add(GUIElementNode::CONDITION_FOCUS);
		unfocussedNodeBorderTopColor = focussedNode->getBorder()->topColor;
		unfocussedNodeBorderLeftColor = focussedNode->getBorder()->leftColor;
		unfocussedNodeBorderBottomColor = focussedNode->getBorder()->bottomColor;
		unfocussedNodeBorderRightColor = focussedNode->getBorder()->rightColor;
		focussedNode->getBorder()->topColor = foccussedBorderColor;
		focussedNode->getBorder()->leftColor = foccussedBorderColor;
		focussedNode->getBorder()->bottomColor = foccussedBorderColor;
		focussedNode->getBorder()->rightColor = foccussedBorderColor;
		if (focussedNode->getController() != nullptr)
			focussedNode->getController()->onFocusGained();

	}
}

void GUI::setFoccussedNode(GUIElementNode* newFoccussedNode)
{
	if (this->focussedNode == newFoccussedNode) {
		return;
	}
	unfocusNode();
	this->focussedNode = newFoccussedNode;
	focusNode();
	determineFocussedNodes();
}

void GUI::focusNextNode()
{
	determineFocussedNodes();
	unfocusNode();
	if (focusableNodes->size() > 0) {
		auto focussedNodeIdx = -1;
		for (auto i = 0; i < focusableNodes->size(); i++) {
			if (focussedNode == java_cast< GUIElementNode* >(focusableNodes->get(i))) {
				focussedNodeIdx = i;
			}
		}
		auto focussedNextNodeIdx = (focussedNodeIdx + 1) % focusableNodes->size();
		focussedNode = java_cast< GUIElementNode* >(focusableNodes->get(focussedNextNodeIdx));
		focusNode();
		focussedNode->scrollToNodeX();
		focussedNode->scrollToNodeY();
	}
}

void GUI::focusPreviousNode()
{
	determineFocussedNodes();
	unfocusNode();
	if (focusableNodes->size() > 0) {
		auto focussedNodeIdx = -1;
		for (auto i = 0; i < focusableNodes->size(); i++) {
			if (focussedNode == java_cast< GUIElementNode* >(focusableNodes->get(i))) {
				focussedNodeIdx = i;
			}
		}
		auto focussedPreviousNodeIdx = (focussedNodeIdx - 1) % focusableNodes->size();
		if (focussedPreviousNodeIdx < 0)
			focussedPreviousNodeIdx += focusableNodes->size();

		focussedNode = java_cast< GUIElementNode* >(focusableNodes->get(focussedPreviousNodeIdx));
		focusNode();
		focussedNode->scrollToNodeX();
		focussedNode->scrollToNodeY();
	}
}

void GUI::render()
{
	if (renderScreens->isEmpty() == true)
		return;

	if (focussedNode == nullptr) {
		focusNextNode();
	}
	guiRenderer->setGUI(this);
	engine->initGUIMode();
	guiRenderer->initRendering();
	for (auto i = 0; i < renderScreens->size(); i++) {
		auto screen = java_cast< GUIScreenNode* >(renderScreens->get(i));
		if (screen->isVisible() == false)
			continue;

		if (screen->getScreenWidth() != width || screen->getScreenHeight() != height) {
			screen->setScreenSize(width, height);
			screen->layout();
		}
		screen->setConditionsMet();
		screen->tick();
		screen->render(guiRenderer);
	}
	for (auto i = 0; i < renderScreens->size(); i++) {
		auto screen = java_cast< GUIScreenNode* >(renderScreens->get(i));
		if (screen->isVisible() == false)
			continue;

		screen->renderFloatingNodes(guiRenderer);
	}
	guiRenderer->doneRendering();
	engine->doneGUIMode();
}

void GUI::handleEvents(GUINode* node)
{
	for (auto i = 0; i < mouseEvents->size(); i++) {
		auto event = java_cast< GUIMouseEvent* >(mouseEvents->get(i));
		if (event->isProcessed() == true)
			continue;

		event->setX(event->getX() + node->getScreenNode()->getGUIEffectOffsetX());
		event->setY(event->getY() + node->getScreenNode()->getGUIEffectOffsetY());
		node->handleMouseEvent(event);
	}
	for (auto i = 0; i < keyboardEvents->size(); i++) {
		auto event = java_cast< GUIKeyboardEvent* >(keyboardEvents->get(i));
		if (event->isProcessed() == true)
			continue;

		switch (event->getKeyCode()) {
			case (GUIKeyboardEvent::KEYCODE_TAB):
				{
					if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
						focusNextNode();
					}
					event->setProcessed(true);
					break;
				}
			case (GUIKeyboardEvent::KEYCODE_TAB_SHIFT):
				{
					if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
						focusPreviousNode();
					}
					event->setProcessed(true);
					break;
				}
			default:
				{
					break;
				}
		}

		if (event->isProcessed() == true) {
			continue;
		}
		if (focussedNode != nullptr) {
			focussedNode->handleKeyboardEvent(event);
		}
	}
}

void GUI::handleEvents()
{
	lockEvents();
	for (auto i = renderScreens->size() - 1; i >= 0; i--) {
		auto screen = java_cast< GUIScreenNode* >(renderScreens->get(i));
		if (screen->isVisible() == false)
			continue;

		auto floatingNodes = screen->getFloatingNodes();
		for (auto j = 0; j < floatingNodes->size(); j++) {
			auto floatingNode = java_cast< GUINode* >(floatingNodes->get(j));
			handleEvents(floatingNode);
		}
		if (screen->isPopUp() == true)
			break;

	}
	for (auto i = renderScreens->size() - 1; i >= 0; i--) {
		auto screen = java_cast< GUIScreenNode* >(renderScreens->get(i));
		if (screen->isVisible() == false)
			continue;

		handleEvents(screen);
		if (screen->getInputEventHandler() != nullptr) {
			screen->getInputEventHandler()->handleInputEvents();
		}
		if (screen->isPopUp() == true)
			break;

	}
	mouseEvents->clear();
	mouseEventsPool->reset();
	keyboardEvents->clear();
	keyboardEventsPool->reset();
	unlockEvents();
}

void GUI::onKeyDown (unsigned char key, int x, int y) {
	fakeMouseMovedEvent();
	lockEvents();
	auto guiKeyboardEvent = java_cast< GUIKeyboardEvent* >(keyboardEventsPool->allocate());
	guiKeyboardEvent->setTime(System::currentTimeMillis());
	guiKeyboardEvent->setType(GUIKeyboardEvent_Type::KEY_PRESSED);
	guiKeyboardEvent->setKeyCode(GUIKeyboardEvent::getKeyCodeFromChar(key));
	guiKeyboardEvent->setKeyChar(key);
	guiKeyboardEvent->setMetaDown(false);
	guiKeyboardEvent->setControlDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_CTRL) == KEYBOARD_MODIFIER_CTRL);
	guiKeyboardEvent->setAltDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_ALT) == KEYBOARD_MODIFIER_ALT);
	guiKeyboardEvent->setShiftDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_SHIFT) == KEYBOARD_MODIFIER_SHIFT);
	guiKeyboardEvent->setProcessed(false);
	keyboardEvents->add(guiKeyboardEvent);
	unlockEvents();
}

void GUI::onKeyUp(unsigned char key, int x, int y) {
	fakeMouseMovedEvent();
	lockEvents();
	auto guiKeyboardEvent = java_cast< GUIKeyboardEvent* >(keyboardEventsPool->allocate());
	guiKeyboardEvent->setTime(System::currentTimeMillis());
	guiKeyboardEvent->setType(GUIKeyboardEvent_Type::KEY_RELEASED);
	guiKeyboardEvent->setKeyCode(GUIKeyboardEvent::getKeyCodeFromChar(key));
	guiKeyboardEvent->setKeyChar(key);
	guiKeyboardEvent->setMetaDown(false);
	guiKeyboardEvent->setControlDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_CTRL) == KEYBOARD_MODIFIER_CTRL);
	guiKeyboardEvent->setAltDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_ALT) == KEYBOARD_MODIFIER_ALT);
	guiKeyboardEvent->setShiftDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_SHIFT) == KEYBOARD_MODIFIER_SHIFT);
	guiKeyboardEvent->setProcessed(false);
	keyboardEvents->add(guiKeyboardEvent);
	unlockEvents();
}

void GUI::onSpecialKeyDown (int key, int x, int y) {
	fakeMouseMovedEvent();
	lockEvents();
	auto guiKeyboardEvent = java_cast< GUIKeyboardEvent* >(keyboardEventsPool->allocate());
	guiKeyboardEvent->setTime(System::currentTimeMillis());
	guiKeyboardEvent->setType(GUIKeyboardEvent_Type::KEY_PRESSED);
	guiKeyboardEvent->setKeyCode(key);
	guiKeyboardEvent->setKeyChar(-1);
	guiKeyboardEvent->setMetaDown(false);
	guiKeyboardEvent->setControlDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_CTRL) == KEYBOARD_MODIFIER_CTRL);
	guiKeyboardEvent->setAltDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_ALT) == KEYBOARD_MODIFIER_ALT);
	guiKeyboardEvent->setShiftDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_SHIFT) == KEYBOARD_MODIFIER_SHIFT);
	guiKeyboardEvent->setProcessed(false);
	keyboardEvents->add(guiKeyboardEvent);
	unlockEvents();
}

void GUI::onSpecialKeyUp(int key, int x, int y) {
	fakeMouseMovedEvent();
	lockEvents();
	auto guiKeyboardEvent = java_cast< GUIKeyboardEvent* >(keyboardEventsPool->allocate());
	guiKeyboardEvent->setTime(System::currentTimeMillis());
	guiKeyboardEvent->setType(GUIKeyboardEvent_Type::KEY_RELEASED);
	guiKeyboardEvent->setKeyCode(key);
	guiKeyboardEvent->setKeyChar(-1);
	guiKeyboardEvent->setMetaDown(false);
	guiKeyboardEvent->setControlDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_CTRL) == KEYBOARD_MODIFIER_CTRL);
	guiKeyboardEvent->setAltDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_ALT) == KEYBOARD_MODIFIER_ALT);
	guiKeyboardEvent->setShiftDown((ApplicationInputEventsHandler::getKeyboardModifiers() &  KEYBOARD_MODIFIER_SHIFT) == KEYBOARD_MODIFIER_SHIFT);
	guiKeyboardEvent->setProcessed(false);
	keyboardEvents->add(guiKeyboardEvent);
	unlockEvents();
}

void GUI::onMouseDragged(int x, int y) {
	lockEvents();
	auto guiMouseEvent = java_cast< GUIMouseEvent* >(mouseEventsPool->allocate());
	guiMouseEvent->setTime(System::currentTimeMillis());
	guiMouseEvent->setType(GUIMouseEvent_Type::MOUSE_DRAGGED);
	guiMouseEvent->setX(x);
	guiMouseEvent->setY(y);
	guiMouseEvent->setButton(mouseButtonLast);
	/*
	guiMouseEvent->setWheelX((*event->getRotation())[0] * event->getRotationScale());
	guiMouseEvent->setWheelY((*event->getRotation())[1] * event->getRotationScale());
	guiMouseEvent->setWheelZ((*event->getRotation())[2] * event->getRotationScale());
	*/
	guiMouseEvent->setProcessed(false);
	mouseEvents->add(guiMouseEvent);
	unlockEvents();
}

void GUI::onMouseMoved(int x, int y) {
	lockEvents();
	auto guiMouseEvent = java_cast< GUIMouseEvent* >(mouseEventsPool->allocate());
	guiMouseEvent->setTime(System::currentTimeMillis());
	guiMouseEvent->setType(GUIMouseEvent_Type::MOUSE_MOVED);
	guiMouseEvent->setX(x);
	guiMouseEvent->setY(y);
	guiMouseEvent->setButton(0);
	/*
	guiMouseEvent->setWheelX((*event->getRotation())[0] * event->getRotationScale());
	guiMouseEvent->setWheelY((*event->getRotation())[1] * event->getRotationScale());
	guiMouseEvent->setWheelZ((*event->getRotation())[2] * event->getRotationScale());
	*/
	guiMouseEvent->setProcessed(false);
	mouseEvents->add(guiMouseEvent);
	unlockEvents();
}

void GUI::onMouseButton(int button, int state, int x, int y) {
	lockEvents();
	mouseButtonLast = button + 1;
	auto guiMouseEvent = java_cast< GUIMouseEvent* >(mouseEventsPool->allocate());
	guiMouseEvent->setTime(System::currentTimeMillis());
	guiMouseEvent->setType(state == MOUSE_BUTTON_DOWN?GUIMouseEvent_Type::MOUSE_PRESSED:GUIMouseEvent_Type::MOUSE_RELEASED);
	guiMouseEvent->setX(x);
	guiMouseEvent->setY(y);
	guiMouseEvent->setButton(mouseButtonLast);
	/*
	guiMouseEvent->setWheelX((*event->getRotation())[0] * event->getRotationScale());
	guiMouseEvent->setWheelY((*event->getRotation())[1] * event->getRotationScale());
	guiMouseEvent->setWheelZ((*event->getRotation())[2] * event->getRotationScale());
	*/
	guiMouseEvent->setProcessed(false);
	mouseEvents->add(guiMouseEvent);
	unlockEvents();
}

/*
void GUI::mouseWheelMoved(MouseEvent* event)
{
	lockEvents();
	auto guiMouseEvent = java_cast< GUIMouseEvent* >(mouseEventsPool->allocate());
	guiMouseEvent->setTime(System::currentTimeMillis());
	guiMouseEvent->setType(GUIMouseEvent_Type::MOUSE_WHEEL_MOVED);
	guiMouseEvent->setX(event->getX());
	guiMouseEvent->setY(event->getY());
	guiMouseEvent->setButton(0);
	guiMouseEvent->setWheelX((*event->getRotation())[0] * event->getRotationScale());
	guiMouseEvent->setWheelY((*event->getRotation())[1] * event->getRotationScale());
	guiMouseEvent->setWheelZ((*event->getRotation())[2] * event->getRotationScale());
	guiMouseEvent->setProcessed(false);
	mouseEvents->add(guiMouseEvent);
	unlockEvents();
}
*/

void GUI::fakeMouseMovedEvent()
{
	lockEvents();
	auto guiMouseEvent = java_cast< GUIMouseEvent* >(mouseEventsPool->allocate());
	guiMouseEvent->setTime(System::currentTimeMillis());
	guiMouseEvent->setType(GUIMouseEvent_Type::MOUSE_MOVED);
	guiMouseEvent->setX(-10000);
	guiMouseEvent->setY(-10000);
	guiMouseEvent->setButton(0);
	guiMouseEvent->setWheelX(0.0f);
	guiMouseEvent->setWheelY(0.0f);
	guiMouseEvent->setWheelZ(0.0f);
	guiMouseEvent->setProcessed(false);
	mouseEvents->add(guiMouseEvent);
	unlockEvents();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUI::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.GUI", 12);
    return c;
}

void GUI::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		fontCache = new _HashMap();
		imageCache = new _HashMap();
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* GUI::getClass0()
{
	return class_();
}

