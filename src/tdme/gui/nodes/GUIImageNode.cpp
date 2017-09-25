// Generated from /tdme/src/tdme/gui/nodes/GUIImageNode.java
#include <tdme/gui/nodes/GUIImageNode.h>

#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <Array.h>

using tdme::gui::nodes::GUIImageNode;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::renderer::GUIRenderer;

GUIImageNode::GUIImageNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIImageNode::GUIImageNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& src, GUIColor* effectColorMul, GUIColor* effectColorAdd)  /* throws(GUIParserException) */
	: GUIImageNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn,src,effectColorMul,effectColorAdd);
}

void GUIImageNode::init()
{
	color = (new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	}));
}

void GUIImageNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& src, GUIColor* effectColorMul, GUIColor* effectColorAdd) /* throws(GUIParserException) */
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	init();
	this->texture = GUI::getImage(src);
	this->textureId = Engine::getInstance()->getTextureManager()->addTexture(texture);
	this->effectColorMul = effectColorMul;
	this->effectColorAdd = effectColorAdd;
}

const wstring GUIImageNode::getNodeType()
{
	return L"image";
}

bool GUIImageNode::isContentNode()
{
	return true;
}

int32_t GUIImageNode::getContentWidth()
{
	return (texture != nullptr ? texture->getWidth() : 0) + border->left + border->right+ padding->left+ padding->right;
}

int32_t GUIImageNode::getContentHeight()
{
	return (texture != nullptr ? texture->getHeight() : 0) + border->top + border->bottom+ padding->top+ padding->bottom;
}

void GUIImageNode::dispose()
{
	Engine::getInstance()->getTextureManager()->removeTexture(texture->getId());
	super::dispose();
}

void GUIImageNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	super::render(guiRenderer, floatingNodes);
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	float left = computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->contentAlignmentLeft;
	float top = computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->contentAlignmentTop;
	float width = getContentWidth();
	float height = getContentHeight();
	guiRenderer->bindTexture(textureId);
	guiRenderer->setEffectColorMul(effectColorMul);
	guiRenderer->setEffectColorAdd(effectColorAdd);
	guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*color)[0], (*color)[1], (*color)[2], (*color)[3], 0.0f, 0.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*color)[0], (*color)[1], (*color)[2], (*color)[3], 1.0f, 0.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*color)[0], (*color)[1], (*color)[2], (*color)[3], 1.0f, 1.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*color)[0], (*color)[1], (*color)[2], (*color)[3], 0.0f, 1.0f);
	guiRenderer->render();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIImageNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIImageNode", 27);
    return c;
}

java::lang::Class* GUIImageNode::getClass0()
{
	return class_();
}

