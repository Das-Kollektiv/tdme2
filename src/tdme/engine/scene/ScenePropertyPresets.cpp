#include <tdme/engine/scene/ScenePropertyPresets.h>

#include <stdlib.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Color4;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLight;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

ScenePropertyPresets* ScenePropertyPresets::instance = nullptr;

ScenePropertyPresets::ScenePropertyPresets(const string& pathName, const string& fileName)
{
}

ScenePropertyPresets::~ScenePropertyPresets() {
}

ScenePropertyPresets* ScenePropertyPresets::getInstance()
{
	if (instance == nullptr) {
		try {
			instance = new ScenePropertyPresets("resources/engine/tools/sceneeditor/gd", "presets.xml");
		} catch (Exception& exception) {
			Console::println(string(" ScenePropertyPresets::getInstance(): An error occurred: "));
			Console::print(string(exception.what()));
			Application::exit(1);
		}
	}
	return instance;
}

void ScenePropertyPresets::setDefaultSceneProperties(Scene* scene)
{
	for (auto sceneProperty: scenePropertiesPreset) {
		scene->addProperty(sceneProperty->getName(), sceneProperty->getValue());
	}
}

const vector<TiXmlElement*> ScenePropertyPresets::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}
