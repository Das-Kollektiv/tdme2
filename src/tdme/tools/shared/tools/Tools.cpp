#include <tdme/tools/shared/tools/Tools.h>

#include <array>
#include <string>

#include <java/lang/String.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/leveleditor/logic/Level.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Exception.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::array;
using std::wstring;
using std::to_wstring;

using tdme::tools::shared::tools::Tools;
using java::lang::String;
using java::util::Locale;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::PartitionNone;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::leveleditor::logic::Level;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::utils::_Exception;
using tdme::utils::Float;
using tdme::utils::Integer;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

Engine* Tools::osEngine = nullptr;

Transformations* Tools::oseLookFromRotations = nullptr;

float Tools::oseScale = 0.75f;

String* Tools::formatFloat(float value)
{
	wstring floatString = to_wstring(value);
	return new String(floatString);
}

String* Tools::formatVector3(Vector3* value)
{
	return new String(
		formatFloat(value->getX())->getCPPWString() +
		L", " +
		formatFloat(value->getY())->getCPPWString() +
		L", " +
		formatFloat(value->getZ())->getCPPWString()
	);
}

String* Tools::formatColor4(Color4* value)
{
	return new String(
		formatFloat(value->getRed())->getCPPWString() +
		L", " +
		formatFloat(value->getGreen())->getCPPWString() +
		L", " +
		formatFloat(value->getBlue())->getCPPWString() +
		L", " +
		formatFloat(value->getAlpha())->getCPPWString()
	);
}

void Tools::convertToArray(String* text, array<float, 3>* array) /* throws(NumberFormatException) */
{
	auto i = 0;
	StringTokenizer t;
	t.tokenize(text->getCPPWString(), L",");
	while (t.hasMoreTokens() && i < array->size()) {
		(*array)[i++] = Float::parseFloat(t.nextToken());
	}
}

void Tools::convertToArray(String* text, array<float, 4>* array) /* throws(NumberFormatException) */
{
	auto i = 0;
	StringTokenizer t;
	t.tokenize(text->getCPPWString(), L",");
	while (t.hasMoreTokens() && i < array->size()) {
		(*array)[i++] = Float::parseFloat(t.nextToken());
	}
}

Vector3* Tools::convertToVector3(String* text) /* throws(NumberFormatException) */
{
	auto v = new Vector3();
	convertToArray(text, v->getArray());
	return v;
}

Vector4* Tools::convertToVector4(String* text) /* throws(NumberFormatException) */
{
	auto v = new Vector4();
	convertToArray(text, v->getArray());
	return v;
}

Color4* Tools::convertToColor4(String* text) /* throws(NumberFormatException) */
{
	auto color = new Color4();
	convertToArray(text, color->getArray());
	return color;
}

float Tools::convertToFloat(String* text) /* throws(NumberFormatException) */
{
	return Float::parseFloat(text->getCPPWString());
}

int32_t Tools::convertToInt(String* text) /* throws(NumberFormatException) */
{
	return Integer::parseInt(text->getCPPWString());
}

int32_t Tools::convertToIntSilent(String* text)
{
	try {
		return Integer::parseInt(text->getCPPWString());
	} catch (_Exception& exception) {
		return -1;
	}
}

void Tools::setDefaultLight(Light* light)
{
	light->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getPosition()->set(0.0f, 20000.0f, 0.0f, 1.0f);
	light->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light->getPosition()));
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
}

void Tools::oseInit()
{
	osEngine = Engine::createOffScreenInstance(128, 128);
	osEngine->setPartition(new PartitionNone());
	setDefaultLight(osEngine->getLightAt(0));
	oseScale = 0.75f;
	oseLookFromRotations = new Transformations();
	oseLookFromRotations->getRotations()->add(new Rotation(-45.0f, new Vector3(0.0f, 1.0f, 0.0f)));
	oseLookFromRotations->getRotations()->add(new Rotation(-45.0f, new Vector3(1.0f, 0.0f, 0.0f)));
	oseLookFromRotations->getRotations()->add(new Rotation(0.0f, new Vector3(0.0f, 0.0f, 1.0f)));
	oseLookFromRotations->update();
}

void Tools::oseDispose()
{
	osEngine->dispose();
}

void Tools::oseThumbnail(LevelEditorEntity* model)
{
	Tools::setupEntity(model, osEngine, oseLookFromRotations, oseScale);
	osEngine->getSceneColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	osEngine->display();
	// osEngine->makeScreenshot(u"tmp"_j, model->getThumbnail());
	osEngine->getSceneColor()->set(0.8f, 0.0f, 0.0f, 1.0f);
	osEngine->display();
	// osEngine->makeScreenshot(u"tmp"_j, L"selected_" + model->getThumbnail());
	osEngine->reset();
}

float Tools::computeMaxAxisDimension(BoundingVolume* modelBoundingVolume)
{
	auto maxAxisDimension = 0.0f;
	auto dimension = new Vector3(modelBoundingVolume->computeDimensionOnAxis(new Vector3(1.0f, 0.0f, 0.0f)), modelBoundingVolume->computeDimensionOnAxis(new Vector3(0.0f, 1.0f, 0.0f)), modelBoundingVolume->computeDimensionOnAxis(new Vector3(0.0f, 0.0f, 1.0f)));
	if (dimension->getX() > maxAxisDimension)
		maxAxisDimension = dimension->getX();

	if (dimension->getY() > maxAxisDimension)
		maxAxisDimension = dimension->getY();

	if (dimension->getZ() > maxAxisDimension)
		maxAxisDimension = dimension->getZ();

	return maxAxisDimension;
}

Model* Tools::createGroundModel(float width, float depth, float y)
{
	auto ground = new Model(L"ground", L"ground", Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto groundMaterial = new Material(L"ground");
	groundMaterial->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*ground->getMaterials())[L"ground"] = groundMaterial;
	auto groundGroup = new Group(ground, nullptr, L"ground", L"ground");
	vector<Vector3> groundVertices;
	groundVertices.push_back(Vector3(-width, y, -depth));
	groundVertices.push_back(Vector3(-width, y, +depth));
	groundVertices.push_back(Vector3(+width, y, +depth));
	groundVertices.push_back(Vector3(+width, y, -depth));
	vector<Vector3> groundNormals;
	groundNormals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	vector<TextureCoordinate> groundTextureCoordinates;
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 1.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(1.0f, 1.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(1.0f, 0.0f));
	vector<Face> groundFacesGround;
	groundFacesGround.push_back(Face(groundGroup, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	groundFacesGround.push_back(Face(groundGroup, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity groupFacesEntityGround(groundGroup, L"ground group faces entity ground");
	groupFacesEntityGround.setMaterial(groundMaterial);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntityGround.setFaces(&groundFacesGround);
	groupFacesEntities.push_back(groupFacesEntityGround);
	groundGroup->setVertices(&groundVertices);
	groundGroup->setNormals(&groundNormals);
	groundGroup->setTextureCoordinates(&groundTextureCoordinates);
	groundGroup->setFacesEntities(&groupFacesEntities);
	(*ground->getGroups())[L"ground"] = groundGroup;
	(*ground->getSubGroups())[L"ground"] = groundGroup;
	ModelHelper::prepareForIndexedRendering(ground);
	return ground;
}

void Tools::setupEntity(LevelEditorEntity* entity, Engine* engine, Transformations* lookFromRotations, float scale)
{
	if (entity == nullptr)
		return;

	BoundingBox* entityBoundingBox = nullptr;
	if (entity->getType() == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		entityBoundingBox = new BoundingBox(new Vector3(-0.5f, 0.0f, -0.5f), new Vector3(0.5f, 3.0f, 0.5f));
		auto particleSystemObject = Level::createParticleSystem(entity->getParticleSystem(), L"model", true);
		if (particleSystemObject != nullptr) {
			engine->addEntity(particleSystemObject);
		}
	} else {
		entityBoundingBox = entity->getModel()->getBoundingBox();
		auto modelObject = new Object3D(L"model", entity->getModel());
		modelObject->setDynamicShadowingEnabled(true);
		engine->addEntity(modelObject);
	}
	auto ground = createGroundModel((entityBoundingBox->getMax()->getX() - entityBoundingBox->getMin()->getX()) * 1.0f, (entityBoundingBox->getMax()->getZ() - entityBoundingBox->getMin()->getZ()) * 1.0f, entityBoundingBox->getMin()->getY() - MathTools::EPSILON);
	auto groundObject = new Object3D(L"ground", ground);
	groundObject->setEnabled(false);
	engine->addEntity(groundObject);
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto boundingVolume = entity->getBoundingVolumeAt(i);
		if (boundingVolume->getModel() == nullptr)
			continue;

		auto modelBoundingVolumeObject = new Object3D(
			L"model_bv." + to_wstring(i),
			boundingVolume->getModel());
		modelBoundingVolumeObject->setEnabled(false);
		engine->addEntity(modelBoundingVolumeObject);
	}
	for (auto lightIdx = 0; lightIdx < engine->getLightCount(); lightIdx++) engine->getLightAt(lightIdx)->setEnabled(false);
	auto light0 = engine->getLightAt(0);
	light0->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light0->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getPosition()->set(entityBoundingBox->getMin()->getX() + ((entityBoundingBox->getMax()->getX() - entityBoundingBox->getMin()->getX()) / 2.0f), entityBoundingBox->getMin()->getY() + ((entityBoundingBox->getMax()->getY() - entityBoundingBox->getMin()->getY()) / 2.0f), -entityBoundingBox->getMin()->getZ() * 4.0f, 1.0f);
	light0->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light0->getPosition()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto dimension = entityBoundingBox->getMax()->clone2().sub(entityBoundingBox->getMin());
	auto maxAxisDimension = computeMaxAxisDimension(entityBoundingBox);
	auto cam = engine->getCamera();
	cam->setZNear(maxAxisDimension / 5000.0f);
	cam->setZFar(maxAxisDimension);
	auto lookAt = entityBoundingBox->getMin()->clone2().add(dimension->clone2().scale(0.5f));
	cam->getLookAt()->set(lookAt);
	auto lookAtToFromVector = new Vector3(0.0f, 0.0f, +(maxAxisDimension * 1.2f));
	auto lookAtToFromVectorTransformed = new Vector3();
	auto lookAtToFromVectorScaled = new Vector3();
	auto upVector = new Vector3();
	lookFromRotations->getTransformationsMatrix()->multiply(lookAtToFromVector, lookAtToFromVectorTransformed);
	lookAtToFromVectorScaled->set(lookAtToFromVectorTransformed)->scale(scale);
	lookFromRotations->getRotations()->get(2)->getQuaternion()->multiply(new Vector3(0.0f, 1.0f, 0.0f), upVector);
	auto lookFrom = lookAt->clone2().add(lookAtToFromVectorScaled);
	cam->getLookFrom()->set(lookFrom);
	cam->getUpVector()->set(upVector);
}

const wstring Tools::getRelativeResourcesFileName(const wstring& gameRoot, const wstring& fileName)
{
	auto newFileName = StringUtils::replace(fileName, L'\\', L'/');
	auto cutFileNameIdx = -1;
	if (cutFileNameIdx == -1) {
		cutFileNameIdx = fileName.rfind(L"/resources/");
		if (cutFileNameIdx != -1) {
			newFileName = StringUtils::substring(fileName, cutFileNameIdx + 1);
		}
	}
	if (cutFileNameIdx == -1) {
		cutFileNameIdx = fileName.rfind(L"resources/");
		if (cutFileNameIdx != -1) {
			newFileName = StringUtils::substring(fileName, cutFileNameIdx);
		}
	}
	return newFileName;
}

const wstring Tools::getGameRootPath(const wstring& fileName)
{
	auto newFileName = StringUtils::replace(fileName, L'\\', L'/');
	auto filesRootIdx = -1;
	if (filesRootIdx == -1) {
		filesRootIdx = fileName.rfind(L"/resources/");
		if (filesRootIdx != -1)
			newFileName = StringUtils::substring(fileName, 0, filesRootIdx);

	}
	if (filesRootIdx == -1) {
		filesRootIdx = fileName.rfind(L"resources/");
		if (filesRootIdx != -1)
			newFileName = StringUtils::substring(fileName, 0, filesRootIdx);

	}
	return newFileName;
}

const wstring Tools::getPath(const wstring& fileName)
{
	return _FileSystem::getInstance()->getPathName(fileName);
}

const wstring Tools::getFileName(const wstring& fileName)
{
	return _FileSystem::getInstance()->getFileName(fileName);
}
