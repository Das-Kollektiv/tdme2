#include <tdme/engine/fileio/scenes/SceneWriter.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

#include <ext/rapidjson/document.h>
#include <ext/rapidjson/stringbuffer.h>
#include <ext/rapidjson/writer.h>

using std::string;

using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::Color4;
using tdme::engine::model::RotationOrder;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

using rapidjson::Document;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

void SceneWriter::write(const string& pathName, const string& fileName, Scene* scene)
{
	scene->setFileName((pathName.empty() == false?pathName + "/":"") + fileName);
	auto sceneLibrary = scene->getLibrary();
	Document jDocument;
	jDocument.SetObject();
	auto& jAllocator = jDocument.GetAllocator();
	jDocument.AddMember("version", Value("1.99", jAllocator), jAllocator);
	jDocument.AddMember("ro", Value(scene->getRotationOrder()->getName(), jAllocator), jAllocator);
	// lights
	{
		Value jLights;
		jLights.SetArray();
		auto i = 0;
		for (auto light: scene->getLights()) {
			Value jLight;
			jLight.SetObject();
			jLight.AddMember("id", Value(i), jAllocator);
			jLight.AddMember("ar", Value(light->getAmbient().getRed()), jAllocator);
			jLight.AddMember("ag", Value(light->getAmbient().getGreen()), jAllocator);
			jLight.AddMember("ab", Value(light->getAmbient().getBlue()), jAllocator);
			jLight.AddMember("aa", Value(light->getAmbient().getAlpha()), jAllocator);
			jLight.AddMember("dr", Value(light->getDiffuse().getRed()), jAllocator);
			jLight.AddMember("dg", Value(light->getDiffuse().getGreen()), jAllocator);
			jLight.AddMember("db", Value(light->getDiffuse().getBlue()), jAllocator);
			jLight.AddMember("da", Value(light->getDiffuse().getAlpha()), jAllocator);
			jLight.AddMember("sr", Value(light->getSpecular().getRed()), jAllocator);
			jLight.AddMember("sg", Value(light->getSpecular().getGreen()), jAllocator);
			jLight.AddMember("sb", Value(light->getSpecular().getBlue()), jAllocator);
			jLight.AddMember("sa", Value(light->getSpecular().getAlpha()), jAllocator);
			jLight.AddMember("px", Value(light->getPosition().getX()), jAllocator);
			jLight.AddMember("py", Value(light->getPosition().getY()), jAllocator);
			jLight.AddMember("pz", Value(light->getPosition().getZ()), jAllocator);
			jLight.AddMember("pw", Value(light->getPosition().getW()), jAllocator);
			jLight.AddMember("sdx", Value(light->getSpotDirection().getX()), jAllocator);
			jLight.AddMember("sdy", Value(light->getSpotDirection().getY()), jAllocator);
			jLight.AddMember("sdz", Value(light->getSpotDirection().getZ()), jAllocator);
			jLight.AddMember("se", Value(light->getSpotExponent()), jAllocator);
			jLight.AddMember("sco", Value(light->getSpotCutOff()), jAllocator);
			jLight.AddMember("ca", Value(light->getConstantAttenuation()), jAllocator);
			jLight.AddMember("la", Value(light->getLinearAttenuation()), jAllocator);
			jLight.AddMember("qa", Value(light->getQuadraticAttenuation()), jAllocator);
			jLight.AddMember("e", Value(light->isEnabled()), jAllocator);
			jLights.PushBack(jLight, jAllocator);
			i++;
		}
		jDocument.AddMember("lights", jLights, jAllocator);
	}
	// scene library
	{
		Value jSceneLibrary;
		jSceneLibrary.SetArray();
		for (auto prototype: sceneLibrary->getPrototypes()) {
			Value jPrototype;
			jPrototype.SetObject();
			if (prototype->isEmbedded() == true) {
				Value jEmbeddedPrototype;
				jEmbeddedPrototype.SetObject();
				PrototypeWriter::write(
					jDocument,
					jEmbeddedPrototype,
					prototype
				);
				jPrototype.AddMember("type", Value(prototype->getType()->getName(), jAllocator), jAllocator);
				jPrototype.AddMember("entity", jEmbeddedPrototype, jAllocator);
			}
			jPrototype.AddMember("id", Value().SetInt(prototype->getId()), jAllocator);
			jPrototype.AddMember("e", Value(prototype->isEmbedded()), jAllocator);
			jPrototype.AddMember("pf", Value(prototype->getFileName(), jAllocator), jAllocator);
			jSceneLibrary.PushBack(jPrototype, jAllocator);
		}
		jDocument.AddMember("models", jSceneLibrary, jAllocator);
	}
	// scene properties
	{
		Value jSceneProperties;
		jSceneProperties.SetArray();
		for (auto i = 0; i < scene->getPropertyCount(); i++) {
			auto sceneProperty = scene->getPropertyAt(i);
			Value jSceneProperty;
			jSceneProperty.SetObject();
			jSceneProperty.AddMember("name", Value(sceneProperty->getName(), jAllocator), jAllocator);
			jSceneProperty.AddMember("value", Value(sceneProperty->getValue(), jAllocator), jAllocator);
			jSceneProperties.PushBack(jSceneProperty, jAllocator);
		}
		jDocument.AddMember("properties", jSceneProperties, jAllocator);
	}
	// entities
	{
		Value jEntities;
		jEntities.SetArray();
		for (auto sceneEntity: scene->getEntities()) {
			Value jEntity;
			jEntity.SetObject();
			const auto& transform = sceneEntity->getTransform();
			const auto& translation = transform.getTranslation();
			const auto& scale = transform.getScale();
			const auto& rotationAroundXAxis = transform.getRotation(scene->getRotationOrder()->getAxisXIndex());
			const auto& rotationAroundYAxis = transform.getRotation(scene->getRotationOrder()->getAxisYIndex());
			const auto& rotationAroundZAxis = transform.getRotation(scene->getRotationOrder()->getAxisZIndex());
			jEntity.AddMember("id", Value(sceneEntity->getId(), jAllocator), jAllocator);
			jEntity.AddMember("descr", Value(sceneEntity->getDescription(), jAllocator), jAllocator);;
			jEntity.AddMember("mid", Value(sceneEntity->getPrototype()->getId()), jAllocator);
			jEntity.AddMember("tx", Value(translation.getX()), jAllocator);
			jEntity.AddMember("ty", Value(translation.getY()), jAllocator);
			jEntity.AddMember("tz", Value(translation.getZ()), jAllocator);
			jEntity.AddMember("sx", Value(scale.getX()), jAllocator);
			jEntity.AddMember("sy", Value(scale.getY()), jAllocator);
			jEntity.AddMember("sz", Value(scale.getZ()), jAllocator);
			jEntity.AddMember("rx", Value(rotationAroundXAxis.getAngle()), jAllocator);
			jEntity.AddMember("ry", Value(rotationAroundYAxis.getAngle()), jAllocator);
			jEntity.AddMember("rz", Value(rotationAroundZAxis.getAngle()), jAllocator);
			jEntity.AddMember("r", Value(sceneEntity->getReflectionEnvironmentMappingId(), jAllocator), jAllocator);
			Value jEntityProperties;
			jEntityProperties.SetArray();
			for (auto sceneEntityProperty: sceneEntity->getProperties()) {
				Value jSceneEntityProperty;
				jSceneEntityProperty.SetObject();
				jSceneEntityProperty.AddMember("name", Value(sceneEntityProperty->getName(), jAllocator), jAllocator);
				jSceneEntityProperty.AddMember("value", Value(sceneEntityProperty->getValue(), jAllocator), jAllocator);
				jEntityProperties.PushBack(jSceneEntityProperty, jAllocator);
			}
			jEntity.AddMember("properties", jEntityProperties, jAllocator);
			jEntities.PushBack(jEntity, jAllocator);
		}
		jDocument.AddMember("objects", jEntities, jAllocator);
		jDocument.AddMember("objects_eidx", Value(scene->getEntityIdx()), jAllocator);
	}
	// sky
	{
		Value jSkyShaderParameters;
		jSkyShaderParameters.SetObject();
		for (const auto& shaderParameterName: Engine::getShaderParameterNames("sky")) {
			jSkyShaderParameters.AddMember(Value(shaderParameterName, jAllocator), Value(scene->getSkyShaderParameters().getShaderParameter(shaderParameterName).toString(), jAllocator), jAllocator);
		}
		jDocument.AddMember("skyshader", jSkyShaderParameters, jAllocator);
	}
	//
	jDocument.AddMember("gui", Value(scene->getGUIFileName(), jAllocator), jAllocator);

	//
	StringBuffer strbuf;
	Writer<StringBuffer> writer(strbuf);
	jDocument.Accept(writer);

	//
	FileSystem::getInstance()->setContentFromString(pathName, fileName, strbuf.GetString());
}
