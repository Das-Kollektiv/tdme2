#include <tdme/engine/fileio/prototypes/PrototypeReader.h>

#include <string>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeTransformFilter.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Type.h>
#include <tdme/engine/prototype/PrototypePhysics.h>
#include <tdme/engine/prototype/PrototypePhysics_BodyType.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Base64EncDec.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain.h>

#include <rapidjson/document.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeTransformFilter;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_ObjectParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_Type;
using tdme::engine::prototype::PrototypePhysics;
using tdme::engine::prototype::PrototypePhysics_BodyType;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::EntityShaderParameters;
using tdme::engine::LODObject3D;
using tdme::engine::Rotation;
using tdme::engine::ShaderParameter;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Base64EncDec;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;
using tdme::utilities::Terrain;

using rapidjson::Document;
using rapidjson::Value;

vector<string> PrototypeReader::extensions = {"tenvmap", "tmodel", "tparticle", "tterrain", "ttrigger"};

const vector<string>& PrototypeReader::getPrototypeExtensions() {
	return extensions;
}

bool PrototypeReader::readThumbnail(const string& pathName, const string& fileName, vector<uint8_t>& pngData) {
	try {
		auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);

		Document jPrototypeRoot;
		jPrototypeRoot.Parse(jsonContent.c_str());

		string thumbnail = jPrototypeRoot.FindMember("thumbnail") != jPrototypeRoot.MemberEnd()?jPrototypeRoot["thumbnail"].GetString():"";
		if (thumbnail.empty() == true) return false;

		Base64EncDec::decode(thumbnail, pngData);

		return true;
	} catch (Exception& exception) {
		Console::println("PrototypeReader::readThumbnail(): An error occurred: " + pathName + "/" + fileName + ": " + exception.what());
		return false;
	}
}

Prototype* PrototypeReader::read(int id, const string& pathName, const string& fileName, PrototypeTransformFilter* transformFilter)
{
	auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);

	Document jPrototypeRoot;
	jPrototypeRoot.Parse(jsonContent.c_str());

	auto prototype = read(id, pathName, jPrototypeRoot, transformFilter);
	prototype->setFileName((pathName.empty() == false?pathName + "/":"") + fileName);
	return prototype;
}

Prototype* PrototypeReader::read(int id, const string& pathName, Value& jPrototypeRoot, PrototypeTransformFilter* transformFilter)
{
	//
	Prototype* prototype;
	auto pivot = Vector3(
		static_cast<float>(jPrototypeRoot["px"].GetFloat()),
		static_cast<float>(jPrototypeRoot["py"].GetFloat()),
		static_cast<float>(jPrototypeRoot["pz"].GetFloat())
	);
	auto prototypeType = Prototype_Type::valueOf((jPrototypeRoot["type"].GetString()));
	auto thumbnail = jPrototypeRoot.FindMember("thumbnail") != jPrototypeRoot.MemberEnd()?jPrototypeRoot["thumbnail"].GetString():"";
	auto name = (jPrototypeRoot["name"].GetString());
	auto description = (jPrototypeRoot["descr"].GetString());
	string modelFileName = "";
	string modelPathName = "";
	if (jPrototypeRoot.FindMember("file") != jPrototypeRoot.MemberEnd()) {
		modelFileName = jPrototypeRoot["file"].GetString();
	}
	BaseProperties properties(name, description);
	auto jProperties = jPrototypeRoot["properties"].GetArray();
	for (auto i = 0; i < jProperties.Size(); i++) {
		auto& jProperty = jProperties[i];
		properties.addProperty(
			(jProperty["name"].GetString()),
			(jProperty["value"].GetString())
		);
	}
	if (transformFilter != nullptr && transformFilter->filterEmptyTransform(properties) == true) {
		prototypeType = Prototype_Type::EMPTY;
	}
	Model* model = nullptr;
	if (prototypeType == Prototype_Type::EMPTY) {
		model = ModelReader::read("resources/engine/models", "empty.tm");
	} else
	if (modelFileName.length() > 0) {
		modelPathName = getResourcePathName(pathName, modelFileName);
		model = ModelReader::read(
			modelPathName,
			FileSystem::getInstance()->getFileName(modelFileName)
		);
	}
	prototype = new Prototype(
		id,
		prototypeType,
		name,
		description,
		string(),
		modelFileName.length() > 0?modelPathName + "/" + FileSystem::getInstance()->getFileName(modelFileName):"",
		thumbnail,
		model,
		pivot
	);
	//
	for (auto i = 0; i < properties.getPropertyCount(); i++) {
		auto property = properties.getPropertyByIndex(i);
		prototype->addProperty(property->getName(), property->getValue());
	}
	if (jPrototypeRoot.FindMember("bv") != jPrototypeRoot.MemberEnd()) {
		auto boundingVolume = parseBoundingVolume(
			0,
			prototype,
			pathName,
			jPrototypeRoot["bv"]
		);
		if (boundingVolume->getBoundingVolume() != nullptr) prototype->addBoundingVolume(0, boundingVolume);
	} else
	if (jPrototypeRoot.FindMember("bvs") != jPrototypeRoot.MemberEnd()) {
		auto jBoundingVolumes = jPrototypeRoot["bvs"].GetArray();
		auto bvIdx = 0;
		for (auto i = 0; i < jBoundingVolumes.Size(); i++) {
			auto boundingVolume = parseBoundingVolume(bvIdx, prototype, pathName, jBoundingVolumes[i]);
			if (boundingVolume->getBoundingVolume() != nullptr) prototype->addBoundingVolume(bvIdx++, boundingVolume);
		}
	}
	if (jPrototypeRoot.FindMember("p") != jPrototypeRoot.MemberEnd() && prototype->getPhysics() != nullptr) {
		auto physics = prototype->getPhysics();
		auto& jPhysics = jPrototypeRoot["p"];
		physics->setType(PrototypePhysics_BodyType::valueOf(jPhysics["type"].GetString()));
		physics->setMass(static_cast<float>(jPhysics["mass"].GetFloat()));
		physics->setRestitution(static_cast<float>(jPhysics["restitution"].GetFloat()));
		physics->setFriction(static_cast<float>(jPhysics["friction"].GetFloat()));
		physics->setInertiaTensor(
			Vector3(
				static_cast<float>(jPhysics["itx"].GetFloat()),
				static_cast<float>(jPhysics["ity"].GetFloat()),
				static_cast<float>(jPhysics["itz"].GetFloat())
			)
		);
	}
	if (jPrototypeRoot.FindMember("sd") != jPrototypeRoot.MemberEnd()) {
		for (auto& jSound: jPrototypeRoot["sd"].GetArray()) {
			auto id = jSound["i"].GetString();
			auto sound = prototype->addSound(id);
			if (sound == nullptr) continue;
			sound->setAnimation(jSound["a"].GetString());
			sound->setFileName(jSound["file"].GetString());
			sound->setGain(static_cast<float>(jSound["g"].GetFloat()));
			sound->setPitch(static_cast<float>(jSound["p"].GetFloat()));
			sound->setOffset(static_cast<float>(jSound["o"].GetInt()));
			sound->setLooping(jSound["l"].GetBool());
			sound->setFixed(jSound["f"].GetBool());
		}
	}
	if (prototypeType == Prototype_Type::MODEL) {
		prototype->setTerrainMesh(jPrototypeRoot["tm"].GetBool());
		if (jPrototypeRoot.FindMember("ll2") != jPrototypeRoot.MemberEnd()) prototype->setLODLevel2(parseLODLevel(pathName, jPrototypeRoot["ll2"]));
		if (jPrototypeRoot.FindMember("ll3") != jPrototypeRoot.MemberEnd()) prototype->setLODLevel3(parseLODLevel(pathName, jPrototypeRoot["ll3"]));
	} else
	if (prototypeType == Prototype_Type::PARTICLESYSTEM) {
		if (jPrototypeRoot.FindMember("ps") != jPrototypeRoot.MemberEnd()) {
			prototype->addParticleSystem();
			parseParticleSystem(prototype->getParticleSystemAt(0), pathName, jPrototypeRoot["ps"]);
		} else
		if (jPrototypeRoot.FindMember("pss") != jPrototypeRoot.MemberEnd()) {
			auto jParticleSystems = jPrototypeRoot["pss"].GetArray();
			for (auto i = 0; i < jParticleSystems.Size(); i++) {
				prototype->addParticleSystem();
				parseParticleSystem(prototype->getParticleSystemAt(prototype->getParticleSystemsCount() - 1), pathName, jParticleSystems[i]);
			}
		}
	}
	if (jPrototypeRoot.FindMember("ds") != jPrototypeRoot.MemberEnd()) {
		prototype->setContributesShadows(jPrototypeRoot["ds"].GetBool());
		prototype->setReceivesShadows(jPrototypeRoot["ds"].GetBool());
	} else
	if (jPrototypeRoot.FindMember("cs") != jPrototypeRoot.MemberEnd() && jPrototypeRoot.FindMember("rs") != jPrototypeRoot.MemberEnd()) {
		prototype->setContributesShadows(jPrototypeRoot["cs"].GetBool());
		prototype->setReceivesShadows(jPrototypeRoot["rs"].GetBool());
	}
	prototype->setRenderGroups(jPrototypeRoot.FindMember("rg") != jPrototypeRoot.MemberEnd()?jPrototypeRoot["rg"].GetBool():false);
	prototype->setShader(jPrototypeRoot.FindMember("s") != jPrototypeRoot.MemberEnd()?jPrototypeRoot["s"].GetString():"default");
	prototype->setDistanceShader(jPrototypeRoot.FindMember("sds") != jPrototypeRoot.MemberEnd()?jPrototypeRoot["sds"].GetString():"default");
	prototype->setDistanceShaderDistance(jPrototypeRoot.FindMember("sdsd") != jPrototypeRoot.MemberEnd()?static_cast<float>(jPrototypeRoot["sdsd"].GetFloat()):10000.0f);
	if (jPrototypeRoot.FindMember("sps") != jPrototypeRoot.MemberEnd()) {
		Value& jShaderParameters = jPrototypeRoot["sps"];
		EntityShaderParameters shaderParameters;
		shaderParameters.setShader(prototype->getShader());
		for (auto jShaderParameterIt = jShaderParameters.MemberBegin(); jShaderParameterIt != jShaderParameters.MemberEnd(); ++jShaderParameterIt) {
			shaderParameters.setShaderParameter(jShaderParameterIt->name.GetString(), string(jShaderParameterIt->value.GetString()));
		}
		prototype->setShaderParameters(shaderParameters);
	}
	if (jPrototypeRoot.FindMember("spds") != jPrototypeRoot.MemberEnd()) {
		Value& jDistanceShaderParameters = jPrototypeRoot["spds"];
		EntityShaderParameters distanceShaderParameters;
		distanceShaderParameters.setShader(prototype->getDistanceShader());
		for (auto jDistanceShaderParameterIt = jDistanceShaderParameters.MemberBegin(); jDistanceShaderParameterIt != jDistanceShaderParameters.MemberEnd(); ++jDistanceShaderParameterIt) {
			distanceShaderParameters.setShaderParameter(jDistanceShaderParameterIt->name.GetString(), string(jDistanceShaderParameterIt->value.GetString()));
		}
		prototype->setDistanceShaderParameters(distanceShaderParameters);
	}
	if (prototype->getType() == Prototype_Type::ENVIRONMENTMAPPING) {
		prototype->setEnvironmentMapRenderPassMask(jPrototypeRoot["emrpm"].GetInt());
		prototype->setEnvironmentMapTimeRenderUpdateFrequency(jPrototypeRoot["emtf"].GetInt64());
	}
	//
	if (prototype->getModel() != nullptr) ModelTools::prepareForShader(prototype->getModel(), prototype->getShader());

	//
	if (prototype->getType() == Prototype_Type::TERRAIN) {
		auto terrain = prototype->getTerrain();
		Value& jTerrain = jPrototypeRoot["t"];
		{
			terrain->setWidth(jTerrain["w"].GetFloat());
			terrain->setDepth(jTerrain["d"].GetFloat());
			Value jTerrainValues = jTerrain["t"].GetArray(); // TODO: how to avoid this copy???
			for (auto i = 0; i < jTerrainValues.Size(); i++) terrain->getHeightVector().push_back(jTerrainValues[i].GetFloat());
		}
		{
			auto jWaterPositionMapsArray = jTerrain["W"].GetArray();
			for (auto i = 0; i < jWaterPositionMapsArray.Size(); i++) {
				auto waterPositionMapIdx = terrain->allocateWaterPositionMapIdx();
				auto& jWaterPositionMap = jWaterPositionMapsArray[i];
				auto& jWaterPositionMapData = jWaterPositionMap["w"];
				terrain->setWaterPositionMapHeight(waterPositionMapIdx, jWaterPositionMap["h"].GetFloat());
				for (auto jWaterPositionMapDataIt = jWaterPositionMapData.MemberBegin(); jWaterPositionMapDataIt != jWaterPositionMapData.MemberEnd(); ++jWaterPositionMapDataIt) {
					auto z = Integer::parseInt(jWaterPositionMapDataIt->name.GetString());
					auto xArray = jWaterPositionMapDataIt->value.GetArray();
					for (auto j = 0; j < xArray.Size(); j++) {
						auto x = xArray[j].GetFloat();
						terrain->getWaterPositionMap(waterPositionMapIdx)[z].insert(x);
					}
				}
			}
		}
		{
			auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();
			Terrain::createFoliageMaps(terrain->getWidth(), terrain->getDepth(), foliageMaps);
			auto& jFoliage = jTerrain["f"];
			for (auto jFoliagePrototypeIt = jFoliage.MemberBegin(); jFoliagePrototypeIt != jFoliage.MemberEnd(); ++jFoliagePrototypeIt) {
				auto& jFoliagePrototype = jFoliage[jFoliagePrototypeIt->name.GetString()];
				auto jFoliagePrototypePartitions = jFoliagePrototype["t"].GetArray();


				//
				Prototype* foliagePrototype = nullptr;
				try {
					auto foliagePrototypeFileName = jFoliagePrototype["f"].GetString();
					foliagePrototype = PrototypeReader::read(
						getResourcePathName(pathName, foliagePrototypeFileName),
						FileSystem::getInstance()->getFileName(foliagePrototypeFileName)
					);
				} catch (Exception& exception) {
					Console::println(string("PrototypeReader::read(): An error occurred: ") + exception.what());
					continue;
				}

				//
				auto foliagePrototypeIndex = prototype->getTerrain()->getFoliagePrototypeIndex(foliagePrototype);

				//
				for (auto foliagePrototypePartitionIdx = 0; foliagePrototypePartitionIdx < jFoliagePrototypePartitions.Size(); foliagePrototypePartitionIdx++) {
					auto jFoliagePrototypePartitionTransformations = jFoliagePrototypePartitions[foliagePrototypePartitionIdx].GetArray();
					auto& foliagePrototypePartitionTransformations = foliageMaps[foliagePrototypePartitionIdx][foliagePrototypeIndex];
					for (auto jFoliagePrototypePartitionTransformationsIdx = 0; jFoliagePrototypePartitionTransformationsIdx < jFoliagePrototypePartitionTransformations.Size(); jFoliagePrototypePartitionTransformationsIdx++) {
						Value& jFoliagePrototypeTransformations = jFoliagePrototypePartitionTransformations[jFoliagePrototypePartitionTransformationsIdx];
						Transformations foliagePrototypeTransformations;
						foliagePrototypeTransformations.setTranslation(
							Vector3(
								jFoliagePrototypeTransformations["tx"].GetFloat(),
								jFoliagePrototypeTransformations["ty"].GetFloat(),
								jFoliagePrototypeTransformations["tz"].GetFloat()
							)
						);
						foliagePrototypeTransformations.addRotation(Rotation::Z_AXIS, jFoliagePrototypeTransformations["rz"].GetFloat());
						foliagePrototypeTransformations.addRotation(Rotation::Y_AXIS, jFoliagePrototypeTransformations["ry"].GetFloat());
						foliagePrototypeTransformations.addRotation(Rotation::X_AXIS, jFoliagePrototypeTransformations["rx"].GetFloat());
						foliagePrototypeTransformations.setScale(
							Vector3(
								jFoliagePrototypeTransformations["sx"].GetFloat(),
								jFoliagePrototypeTransformations["sy"].GetFloat(),
								jFoliagePrototypeTransformations["sz"].GetFloat()
							)
						);
						foliagePrototypeTransformations.update();
						foliagePrototypePartitionTransformations.push_back(foliagePrototypeTransformations);
					}
				}
			}
		}
		{
			auto jBrushesArray = jTerrain["b"].GetArray();
			for (auto i = 0; i < jBrushesArray.Size(); i++) {
				auto& jBrush = jBrushesArray[i];
				auto brush = terrain->addBrush();
				brush->setFileName(jBrush["f"].GetString());
				brush->setSize(jBrush["s"].GetFloat());
				brush->setDensity(jBrush["d"].GetFloat());
				auto jPrototypeArray = jBrush["p"].GetArray();
				for (auto i = 0; i < jPrototypeArray.Size(); i++) {
					auto& jPrototype = jPrototypeArray[i];
					auto prototype = brush->addPrototype();
					prototype->setFileName(jPrototype["f"].GetString());
					prototype->setCount(jPrototype["c"].GetFloat());
					prototype->setNormalAlign(jPrototype["n"].GetBool());
					prototype->setRotationXMin(jPrototype["xi"].GetFloat());
					prototype->setRotationXMax(jPrototype["xa"].GetFloat());
					prototype->setRotationYMin(jPrototype["yi"].GetFloat());
					prototype->setRotationYMax(jPrototype["ya"].GetFloat());
					prototype->setRotationZMin(jPrototype["zi"].GetFloat());
					prototype->setRotationZMax(jPrototype["za"].GetFloat());
					prototype->setScaleMin(jPrototype["si"].GetFloat());
					prototype->setScaleMax(jPrototype["sa"].GetFloat());
					prototype->setHeightMin(jPrototype["hi"].GetFloat());
					prototype->setHeightMax(jPrototype["ha"].GetFloat());
					prototype->setSlopeMin(jPrototype["li"].GetFloat());
					prototype->setSlopeMax(jPrototype["la"].GetFloat());
				}
			}
		}
	}

	//
	return prototype;
}

const string PrototypeReader::getResourcePathName(const string& pathName, const string& fileName) {
	string modelFile = FileSystem::getInstance()->getCanonicalPath(
		StringTools::startsWith(FileSystem::getInstance()->getPathName(fileName), "/") == true?
			FileSystem::getInstance()->getPathName(fileName):
			pathName + "/" +  FileSystem::getInstance()->getPathName(fileName),
		FileSystem::getInstance()->getFileName(fileName)
	);
	auto applicationRoot = Tools::getApplicationRootPathName(pathName);
	auto modelRelativeFileName = Tools::getRelativeResourcesFileName(applicationRoot, modelFile);
	auto resourcePathName = (applicationRoot.empty() == false?applicationRoot + "/":"") + Tools::getPathName(modelRelativeFileName);
	return resourcePathName;
}

PrototypeBoundingVolume* PrototypeReader::parseBoundingVolume(int idx, Prototype* prototype, const string& pathName, Value& jBv)
{
	auto prototypeBoundingVolume = new PrototypeBoundingVolume(idx, prototype);
	BoundingVolume* bv;
	auto bvTypeString = (jBv["type"].GetString());
	if (StringTools::equalsIgnoreCase(bvTypeString, "none") == true) {
		prototypeBoundingVolume->setupNone();
	} else
	if (StringTools::equalsIgnoreCase(bvTypeString, "sphere") == true) {
		prototypeBoundingVolume->setupSphere(
			Vector3(
				static_cast<float>(jBv["cx"].GetFloat()),
				static_cast<float>(jBv["cy"].GetFloat()),
				static_cast<float>(jBv["cz"].GetFloat())
			),
			static_cast<float>(jBv["r"].GetFloat())
		);
	} else
	if (StringTools::equalsIgnoreCase(bvTypeString, "capsule") == true) {
		prototypeBoundingVolume->setupCapsule(
			Vector3(
				static_cast<float>(jBv["ax"].GetFloat()),
				static_cast<float>(jBv["ay"].GetFloat()),
				static_cast<float>(jBv["az"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["bx"].GetFloat()),
				static_cast<float>(jBv["by"].GetFloat()),
				static_cast<float>(jBv["bz"].GetFloat())
			),
			static_cast<float>(jBv["r"].GetFloat())
		);
	} else
	if (StringTools::equalsIgnoreCase(bvTypeString, "aabb") == true) {
		prototypeBoundingVolume->setupAabb(
			Vector3(
				static_cast<float>(jBv["mix"].GetFloat()),
				static_cast<float>(jBv["miy"].GetFloat()),
				static_cast<float>(jBv["miz"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["max"].GetFloat()),
				static_cast<float>(jBv["may"].GetFloat()),
				static_cast<float>(jBv["maz"].GetFloat())
			)
		);
	} else
	if (StringTools::equalsIgnoreCase(bvTypeString, "obb") == true) {
		prototypeBoundingVolume->setupObb(
			Vector3(
				static_cast<float>(jBv["cx"].GetFloat()),
				static_cast<float>(jBv["cy"].GetFloat()),
				static_cast<float>(jBv["cz"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["a0x"].GetFloat()),
				static_cast<float>(jBv["a0y"].GetFloat()),
				static_cast<float>(jBv["a0z"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["a1x"].GetFloat()),
				static_cast<float>(jBv["a1y"].GetFloat()),
				static_cast<float>(jBv["a1z"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["a2x"].GetFloat()),
				static_cast<float>(jBv["a2y"].GetFloat()),
				static_cast<float>(jBv["a2z"].GetFloat())
			),
			Vector3(
				static_cast<float>(jBv["hex"].GetFloat()),
				static_cast<float>(jBv["hey"].GetFloat()),
				static_cast<float>(jBv["hez"].GetFloat())
			)
		);
	} else
	if (StringTools::equalsIgnoreCase(bvTypeString, "convexmesh") == true) {
		try {
			string data = jBv.FindMember("data") != jBv.MemberEnd()?jBv["data"].GetString():string();
			if (data.empty() == false) {
				vector<uint8_t> tmData;
				Base64EncDec::decode(data, tmData);
				prototypeBoundingVolume->setupConvexMesh(tmData);
			} else {
				string fileName = jBv["file"].GetString();
				prototypeBoundingVolume->setupConvexMesh(
					getResourcePathName(pathName, fileName),
					Tools::getFileName(fileName)
				);
			}
		} catch (Exception& exception) {
			Console::print(string("PrototypeReader::parseBoundingVolume(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}
	if (jBv.FindMember("g") != jBv.MemberEnd()) prototypeBoundingVolume->setGenerated(jBv["g"].GetBool());
	return prototypeBoundingVolume;
}

PrototypeLODLevel* PrototypeReader::parseLODLevel(const string& pathName, Value& jLodLevel) {
	auto lodType = static_cast<LODObject3D::LODLevelType>(jLodLevel["t"].GetInt());
	PrototypeLODLevel* lodLevel = new PrototypeLODLevel(
		lodType,
		lodType == LODObject3D::LODLEVELTYPE_MODEL?jLodLevel["f"].GetString():"",
		nullptr,
		static_cast<float>(jLodLevel["d"].GetFloat())
	);
	if (lodType == LODObject3D::LODLEVELTYPE_MODEL) {
		auto modelFileName = lodLevel->getFileName();
		auto modelPathName = getResourcePathName(pathName, modelFileName);
		lodLevel->setModel(
			ModelReader::read(
				modelPathName,
				FileSystem::getInstance()->getFileName(modelFileName)
			)
		);
		lodLevel->setFileName(modelPathName + "/" + FileSystem::getInstance()->getFileName(modelFileName));
	}
	lodLevel->setColorAdd(
		Color4(
			static_cast<float>(jLodLevel["car"].GetFloat()),
			static_cast<float>(jLodLevel["cag"].GetFloat()),
			static_cast<float>(jLodLevel["cab"].GetFloat()),
			static_cast<float>(jLodLevel["caa"].GetFloat())
		)
	);
	lodLevel->setColorMul(
		Color4(
			static_cast<float>(jLodLevel["cmr"].GetFloat()),
			static_cast<float>(jLodLevel["cmg"].GetFloat()),
			static_cast<float>(jLodLevel["cmb"].GetFloat()),
			static_cast<float>(jLodLevel["cma"].GetFloat())
		)
	);
	return lodLevel;
}

void PrototypeReader::parseParticleSystem(PrototypeParticleSystem* particleSystem, const string& pathName, Value& jParticleSystem) {
	particleSystem->setType(PrototypeParticleSystem_Type::valueOf((jParticleSystem["t"].GetString())));
	{
		auto v = particleSystem->getType();
		if (v == PrototypeParticleSystem_Type::NONE) {
			// no op
		} else
		if (v == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
			auto& jObjectParticleSystem = jParticleSystem["ops"];
			auto objectParticleSystem = particleSystem->getObjectParticleSystem();
			objectParticleSystem->setMaxCount(jObjectParticleSystem["mc"].GetInt());
			objectParticleSystem->setScale(
				Vector3(
					static_cast<float>(jObjectParticleSystem["sx"].GetFloat()),
					static_cast<float>(jObjectParticleSystem["sy"].GetFloat()),
					static_cast<float>(jObjectParticleSystem["sz"].GetFloat())
				)
			);
			objectParticleSystem->setAutoEmit(jObjectParticleSystem["ae"].GetBool());
			try {
				auto particleModelFile = (jObjectParticleSystem["mf"].GetString());
				auto particleModelPath = getResourcePathName(pathName, particleModelFile);
				objectParticleSystem->setModelFile(
					particleModelPath + "/" + Tools::getFileName(particleModelFile)
				);
			} catch (Exception& exception) {
				Console::print(string("PrototypeReader::doImport(): An error occurred: "));
				Console::println(string(exception.what()));
			}
		} else
		if (v == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
			auto pointParticleSystem = particleSystem->getPointParticleSystem();
			auto& jPointParticleSystem = jParticleSystem["pps"];
			pointParticleSystem->setMaxPoints(jPointParticleSystem["mp"].GetInt());
			if (jPointParticleSystem.FindMember("ps") != jPointParticleSystem.MemberEnd()) pointParticleSystem->setPointSize(static_cast<float>(jPointParticleSystem["ps"].GetFloat()));
			if (jPointParticleSystem.FindMember("t") != jPointParticleSystem.MemberEnd()) {
				try {
					auto particleTextureFileName = jPointParticleSystem["t"].GetString();
					auto particleTexturePathName = getResourcePathName(pathName, particleTextureFileName);
					auto particleTransparencyTextureFileName = string(jPointParticleSystem.FindMember("tt") != jPointParticleSystem.MemberEnd()?jPointParticleSystem["tt"].GetString():"");
					auto particleTransparencyTexturePathName = particleTransparencyTextureFileName.size() == 0?string():getResourcePathName(pathName, particleTransparencyTextureFileName);
					pointParticleSystem->setTextureFileName(
						particleTexturePathName + "/" + Tools::getFileName(particleTextureFileName),
						particleTransparencyTextureFileName.size() == 0?string():particleTransparencyTexturePathName + "/" + Tools::getFileName(particleTransparencyTextureFileName)
					);
					if (jPointParticleSystem.FindMember("ths") != jPointParticleSystem.MemberEnd()) pointParticleSystem->setTextureHorizontalSprites(jPointParticleSystem["ths"].GetInt());
					if (jPointParticleSystem.FindMember("tvs") != jPointParticleSystem.MemberEnd()) pointParticleSystem->setTextureVerticalSprites(jPointParticleSystem["tvs"].GetInt());
					if (jPointParticleSystem.FindMember("fps") != jPointParticleSystem.MemberEnd()) pointParticleSystem->setTextureSpritesFPS(jPointParticleSystem["fps"].GetFloat());
				} catch (Exception& exception) {
					Console::print(string("PrototypeReader::doImport(): An error occurred: "));
					Console::println(string(exception.what()));
				}
			}
			pointParticleSystem->setAutoEmit(jPointParticleSystem["ae"].GetBool());
		} else
		if (v == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
			auto fogParticleSystem = particleSystem->getFogParticleSystem();
			auto& jFogParticleSystem = jParticleSystem["fps"];
			fogParticleSystem->setMaxPoints(jFogParticleSystem["mp"].GetInt());
			if (jFogParticleSystem.FindMember("ps") != jFogParticleSystem.MemberEnd()) fogParticleSystem->setPointSize(static_cast<float>(jFogParticleSystem["ps"].GetFloat()));
			if (jFogParticleSystem.FindMember("t") != jFogParticleSystem.MemberEnd()) {
				try {
					auto particleTextureFileName = jFogParticleSystem["t"].GetString();
					auto particleTexturePathName = getResourcePathName(pathName, particleTextureFileName);
					auto particleTransparencyTextureFileName = jFogParticleSystem.FindMember("tt") != jFogParticleSystem.MemberEnd()?string():jFogParticleSystem["tt"].GetString();
					auto particleTransparencyTexturePathName = particleTransparencyTextureFileName.size() == 0?string():getResourcePathName(pathName, particleTransparencyTextureFileName);
					fogParticleSystem->setTextureFileName(
						particleTexturePathName + "/" + Tools::getFileName(particleTextureFileName),
						particleTransparencyTextureFileName.size() == 0?string():particleTransparencyTexturePathName + "/" + Tools::getFileName(particleTransparencyTextureFileName)
					);
					if (jFogParticleSystem.FindMember("ths") != jFogParticleSystem.MemberEnd()) fogParticleSystem->setTextureHorizontalSprites(jFogParticleSystem["ths"].GetInt());
					if (jFogParticleSystem.FindMember("tvs") != jFogParticleSystem.MemberEnd()) fogParticleSystem->setTextureVerticalSprites(jFogParticleSystem["tvs"].GetInt());
					if (jFogParticleSystem.FindMember("fps") != jFogParticleSystem.MemberEnd()) fogParticleSystem->setTextureSpritesFPS(jFogParticleSystem["fps"].GetFloat());
				} catch (Exception& exception) {
					Console::print(string("PrototypeReader::doImport(): An error occurred: "));
					Console::println(string(exception.what()));
				}
			}
		} else {
			Console::println(
				string(
					 "PrototypeWriter::export(): unknown particle system type '" +
					 particleSystem->getType()->getName() +
					 "'"
				 )
			 );
		}
	}

	particleSystem->setEmitter(PrototypeParticleSystem_Emitter::valueOf((jParticleSystem["e"].GetString())));
	{
		auto v = particleSystem->getEmitter();
		if (v == PrototypeParticleSystem_Emitter::NONE) {
			// no op
		} else
		if (v == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			auto& jPointParticleEmitter = jParticleSystem["ppe"];
			auto emitter = particleSystem->getPointParticleEmitter();
			emitter->setCount(jPointParticleEmitter["c"].GetInt());
			emitter->setLifeTime(jPointParticleEmitter["lt"].GetInt());
			emitter->setLifeTimeRnd(jPointParticleEmitter["ltrnd"].GetInt());
			emitter->setMass(static_cast<float>(jPointParticleEmitter["m"].GetFloat()));
			emitter->setMassRnd(static_cast<float>(jPointParticleEmitter["mrnd"].GetFloat()));
			emitter->setPosition(
				Vector3(
					static_cast<float>(jPointParticleEmitter["px"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["py"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["pz"].GetFloat())
				)
			);
			emitter->setVelocity(
				Vector3(
					static_cast<float>(jPointParticleEmitter["vx"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["vy"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["vz"].GetFloat())
				)
			);
			emitter->setVelocityRnd(
				Vector3(
					static_cast<float>(jPointParticleEmitter["vrndx"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["vrndy"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["vrndz"].GetFloat())
				)
			);
			emitter->setColorStart(
				Color4(
					static_cast<float>(jPointParticleEmitter["csr"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["csg"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["csb"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["csa"].GetFloat())
				)
			);
			emitter->setColorEnd(
				Color4(
					static_cast<float>(jPointParticleEmitter["cer"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["ceg"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["ceb"].GetFloat()),
					static_cast<float>(jPointParticleEmitter["cea"].GetFloat())
				)
			);
		} else
		if (v == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			auto& jBoundingBoxParticleEmitter = jParticleSystem["bbpe"];
			auto emitter = particleSystem->getBoundingBoxParticleEmitters();
			emitter->setCount(jBoundingBoxParticleEmitter["c"].GetInt());
			emitter->setLifeTime(jBoundingBoxParticleEmitter["lt"].GetInt());
			emitter->setLifeTimeRnd(jBoundingBoxParticleEmitter["ltrnd"].GetInt());
			emitter->setMass(static_cast<float>(jBoundingBoxParticleEmitter["m"].GetFloat()));
			emitter->setMassRnd(static_cast<float>(jBoundingBoxParticleEmitter["mrnd"].GetFloat()));
			emitter->setVelocity(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["vx"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["vy"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["vz"].GetFloat())
				)
			);
			emitter->setVelocityRnd(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["vrndx"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["vrndy"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["vrndz"].GetFloat())
				)
			);
			emitter->setColorStart(
				Color4(
					static_cast<float>(jBoundingBoxParticleEmitter["csr"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["csg"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["csb"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["csa"].GetFloat())
				)
			);
			emitter->setColorEnd(
				Color4(
					static_cast<float>(jBoundingBoxParticleEmitter["cer"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ceg"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ceb"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["cea"].GetFloat())
				)
			);
			emitter->setObbCenter(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["ocx"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ocy"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ocz"].GetFloat())
				)
			);
			emitter->setObbHalfextension(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["ohex"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ohey"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["ohez"].GetFloat())
				)
			);
			emitter->setObbAxis0(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["oa0x"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa0y"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa0z"].GetFloat())
				)
			);
			emitter->setObbAxis1(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["oa1x"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa1y"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa1z"].GetFloat())
				)
			);
			emitter->setObbAxis2(
				Vector3(
					static_cast<float>(jBoundingBoxParticleEmitter["oa2x"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa2y"].GetFloat()),
					static_cast<float>(jBoundingBoxParticleEmitter["oa2z"].GetFloat())
				)
			);
		} else
		if (v == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			auto& jCircleParticleEmitter = jParticleSystem["cpe"];
			auto emitter = particleSystem->getCircleParticleEmitter();
			emitter->setCount(jCircleParticleEmitter["c"].GetInt());
			emitter->setLifeTime(jCircleParticleEmitter["lt"].GetInt());
			emitter->setLifeTimeRnd(jCircleParticleEmitter["ltrnd"].GetInt());
			emitter->setMass(static_cast<float>(jCircleParticleEmitter["m"].GetFloat()));
			emitter->setMassRnd(static_cast<float>(jCircleParticleEmitter["mrnd"].GetFloat()));
			emitter->setVelocity(
				Vector3(
					static_cast<float>(jCircleParticleEmitter["vx"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["vy"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["vz"].GetFloat())
				)
			);
			emitter->setVelocityRnd(
				Vector3(
					static_cast<float>(jCircleParticleEmitter["vrndx"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["vrndy"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["vrndz"].GetFloat())
				)
			);
			emitter->setColorStart(
				Color4(
					static_cast<float>(jCircleParticleEmitter["csr"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["csg"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["csb"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["csa"].GetFloat())
				)
			);
			emitter->setColorEnd(
				Color4(
					static_cast<float>(jCircleParticleEmitter["cer"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["ceg"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["ceb"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["cea"].GetFloat())
				)
			);
			emitter->setCenter(
				Vector3(
					static_cast<float>(jCircleParticleEmitter["cx"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["cy"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["cz"].GetFloat())
				)
			);
			emitter->setRadius(static_cast<float>(jCircleParticleEmitter["r"].GetFloat()));
			emitter->setAxis0(
				Vector3(
					static_cast<float>(jCircleParticleEmitter["a0x"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["a0y"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["a0z"].GetFloat())
				)
			);
			emitter->setAxis1(
				Vector3(
					static_cast<float>(jCircleParticleEmitter["a1x"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["a1y"].GetFloat()),
					static_cast<float>(jCircleParticleEmitter["a1z"].GetFloat())
				)
			);
		} else
		if (v == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			auto& jCircleParticleEmitterPlaneVelocity = jParticleSystem["cpeev"];
			auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
			emitter->setCount(jCircleParticleEmitterPlaneVelocity["c"].GetInt());
			emitter->setLifeTime(jCircleParticleEmitterPlaneVelocity["lt"].GetInt());
			emitter->setLifeTimeRnd(jCircleParticleEmitterPlaneVelocity["ltrnd"].GetInt());
			emitter->setMass(static_cast<float>(jCircleParticleEmitterPlaneVelocity["m"].GetFloat()));
			emitter->setMassRnd(static_cast<float>(jCircleParticleEmitterPlaneVelocity["mrnd"].GetFloat()));
			emitter->setVelocity(static_cast<float>(jCircleParticleEmitterPlaneVelocity["v"].GetFloat()));
			emitter->setVelocityRnd(static_cast<float>(jCircleParticleEmitterPlaneVelocity["vrnd"].GetFloat()));
			emitter->setColorStart(
				Color4(
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["csr"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["csg"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["csb"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["csa"].GetFloat())
				)
			);
			emitter->setColorEnd(
				Color4(
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["cer"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["ceg"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["ceb"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["cea"].GetFloat())
				)
			);
			emitter->setCenter(
				Vector3(
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["cx"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["cy"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["cz"].GetFloat())
				)
			);
			emitter->setRadius(static_cast<float>(jCircleParticleEmitterPlaneVelocity["r"].GetFloat()));
			emitter->setAxis0(
				Vector3(
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a0x"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a0y"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a0z"].GetFloat())
				)
			);
			emitter->setAxis1(
				Vector3(
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a1x"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a1y"].GetFloat()),
					static_cast<float>(jCircleParticleEmitterPlaneVelocity["a1z"].GetFloat())
				)
			);
		} else
		if (v == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			auto& jSphereParticleEmitter = jParticleSystem["spe"];
			auto emitter = particleSystem->getSphereParticleEmitter();
			emitter->setCount(jSphereParticleEmitter["c"].GetInt());
			emitter->setLifeTime(jSphereParticleEmitter["lt"].GetInt());
			emitter->setLifeTimeRnd(jSphereParticleEmitter["ltrnd"].GetInt());
			emitter->setMass(static_cast<float>(jSphereParticleEmitter["m"].GetFloat()));
			emitter->setMassRnd(static_cast<float>(jSphereParticleEmitter["mrnd"].GetFloat()));
			emitter->setVelocity(
				Vector3(
					static_cast<float>(jSphereParticleEmitter["vx"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["vy"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["vz"].GetFloat())
				)
			);
			emitter->setVelocityRnd(
				Vector3(
					static_cast<float>(jSphereParticleEmitter["vrndx"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["vrndy"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["vrndz"].GetFloat())
				)
			);
			emitter->setColorStart(
				Color4(
					static_cast<float>(jSphereParticleEmitter["csr"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["csg"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["csb"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["csa"].GetFloat())
				)
			);
			emitter->setColorEnd(
				Color4(
					static_cast<float>(jSphereParticleEmitter["cer"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["ceg"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["ceb"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["cea"].GetFloat())
				)
			);
			emitter->setCenter(
				Vector3(
					static_cast<float>(jSphereParticleEmitter["cx"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["cy"].GetFloat()),
					static_cast<float>(jSphereParticleEmitter["cz"].GetFloat())
				)
			);
			emitter->setRadius(static_cast<float>(jSphereParticleEmitter["r"].GetFloat()));
		} else {
			Console::println(
				"PrototypeWriter::export(): unknown particle system emitter '" +
				particleSystem->getEmitter()->getName() +
				"'"
			 );
		}
	}
}
