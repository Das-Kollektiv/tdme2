#include <tdme/tests/GUITest_init_2.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tests/GUITest.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>

using tdme::tests::GUITest_init_2;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tests::GUITest;
using tdme::utils::MutableString;
using tdme::utils::_Console;

GUITest_init_2::GUITest_init_2(GUITest *GUITest_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, GUITest_this(GUITest_this)
{
	clinit();
	ctor();
}

void GUITest_init_2::onValueChanged(GUIElementNode* node)
{
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(node->getName())->append(u":onValueChanged: "_j)
		->append(static_cast< Object* >(node->getController()->getValue()))->toString()));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITest_init_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* GUITest_init_2::getClass0()
{
	return class_();
}

