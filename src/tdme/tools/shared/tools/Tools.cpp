// Generated from /tdme/src/tdme/tools/shared/tools/Tools.java
#include <tdme/tools/shared/tools/Tools.h>

#include <string>

#include <java/lang/Float.h>
#include <java/lang/Integer.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Locale.h>
#include <java/util/StringTokenizer.h>
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
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::wstring;
using std::to_wstring;

using tdme::tools::shared::tools::Tools;
using java::lang::Float;
using java::lang::Integer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Locale;
using java::util::StringTokenizer;
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
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
typedef ::SubArray< ::tdme::engine::Light, ::java::lang::ObjectArray > LightArray;
}  // namespace engine
}  // namespace tdme

Tools::Tools(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Tools::Tools()
	: Tools(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Engine* Tools::osEngine;

Transformations* Tools::oseLookFromRotations;

float Tools::oseScale;

String* Tools::formatFloat(float value)
{
	clinit();
	wstring floatString = to_wstring(value);
	return new String(floatString);
}

String* Tools::formatVector3(Vector3* value)
{
	clinit();
	return ::java::lang::StringBuilder().append(formatFloat(value->getX()))->append(u", "_j)
		->append(formatFloat(value->getY()))
		->append(u", "_j)
		->append(formatFloat(value->getZ()))->toString();
}

String* Tools::formatColor4(Color4* value)
{
	clinit();
	return ::java::lang::StringBuilder().append(formatFloat(value->getRed()))->append(u", "_j)
		->append(formatFloat(value->getGreen()))
		->append(u", "_j)
		->append(formatFloat(value->getBlue()))
		->append(u", "_j)
		->append(formatFloat(value->getAlpha()))->toString();
}

void Tools::convertToArray(String* text, int32_t length, floatArray* array) /* throws(NumberFormatException) */
{
	clinit();
	auto i = 0;
	auto t = new StringTokenizer(text, u","_j);
	while (t->hasMoreTokens() && i < length) {
		(*array)[i++] = Float::parseFloat(t->nextToken());
	}
}

Vector3* Tools::convertToVector3(String* text) /* throws(NumberFormatException) */
{
	clinit();
	auto v = new Vector3();
	convertToArray(text, 3, v->getArray());
	return v;
}

Vector4* Tools::convertToVector4(String* text) /* throws(NumberFormatException) */
{
	clinit();
	auto v = new Vector4();
	convertToArray(text, 4, v->getArray());
	return v;
}

Color4* Tools::convertToColor4(String* text) /* throws(NumberFormatException) */
{
	clinit();
	auto color = new Color4();
	convertToArray(text, 4, color->getArray());
	return color;
}

float Tools::convertToFloat(String* text) /* throws(NumberFormatException) */
{
	clinit();
	return Float::parseFloat(text);
}

int32_t Tools::convertToInt(String* text) /* throws(NumberFormatException) */
{
	clinit();
	return Integer::parseInt(text);
}

int32_t Tools::convertToIntSilent(String* text)
{
	clinit();
	try {
		return Integer::parseInt(text);
	} catch (_Exception& exception) {
		return -1;
	}
}

void Tools::setDefaultLight(Light* light)
{
	clinit();
	light->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light->getPosition()->set(0.0f, 20000.0f, 0.0f, 1.0f);
	light->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light->getPosition()->getArray()));
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
}

void Tools::oseInit()
{
	clinit();
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
	clinit();
	osEngine->dispose();
}

void Tools::oseThumbnail(LevelEditorEntity* model)
{
	clinit();
	Tools::setupEntity(model, osEngine, oseLookFromRotations, oseScale);
	osEngine->getSceneColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	osEngine->display();
	// osEngine->makeScreenshot(u"tmp"_j, model->getThumbnail());
	osEngine->getSceneColor()->set(0.8f, 0.0f, 0.0f, 1.0f);
	osEngine->display();
	// osEngine->makeScreenshot(u"tmp"_j, ::java::lang::StringBuilder().append(u"selected_"_j)->append(model->getThumbnail())->toString());
	osEngine->reset();
}

float Tools::computeMaxAxisDimension(BoundingVolume* modelBoundingVolume)
{
	clinit();
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
	clinit();
	auto ground = new Model(u"ground"_j, u"ground"_j, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto groundMaterial = new Material(u"ground"_j);
	groundMaterial->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	ground->getMaterials()->put(u"ground"_j, groundMaterial);
	auto groundGroup = new Group(ground, nullptr, u"ground"_j, u"ground"_j);
	auto groupFacesEntityGround = new FacesEntity(groundGroup, u"ground group faces entity ground"_j);
	groupFacesEntityGround->setMaterial(groundMaterial);
	vector<FacesEntity*> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntityGround);
	vector<Vector3*> groundVertices;
	groundVertices.push_back(new Vector3(-width, y, -depth));
	groundVertices.push_back(new Vector3(-width, y, +depth));
	groundVertices.push_back(new Vector3(+width, y, +depth));
	groundVertices.push_back(new Vector3(+width, y, -depth));
	vector<Vector3*> groundNormals;
	groundNormals.push_back(new Vector3(0.0f, 1.0f, 0.0f));
	vector<TextureCoordinate*> groundTextureCoordinates;
	groundTextureCoordinates.push_back(new TextureCoordinate(0.0f, 0.0f));
	groundTextureCoordinates.push_back(new TextureCoordinate(0.0f, 1.0f));
	groundTextureCoordinates.push_back(new TextureCoordinate(1.0f, 1.0f));
	groundTextureCoordinates.push_back(new TextureCoordinate(1.0f, 0.0f));
	vector<Face*> groundFacesGround;
	groundFacesGround.push_back(new Face(groundGroup, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	groundFacesGround.push_back(new Face(groundGroup, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	groupFacesEntityGround->setFaces(groundFacesGround);
	groundGroup->setVertices(groundVertices);
	groundGroup->setNormals(groundNormals);
	groundGroup->setTextureCoordinates(groundTextureCoordinates);
	groundGroup->setFacesEntities(groupFacesEntities);
	ground->getGroups()->put(u"ground"_j, groundGroup);
	ground->getSubGroups()->put(u"ground"_j, groundGroup);
	ModelHelper::prepareForIndexedRendering(ground);
	return ground;
}

void Tools::setupEntity(LevelEditorEntity* entity, Engine* engine, Transformations* lookFromRotations, float scale)
{
	clinit();
	if (entity == nullptr)
		return;

	BoundingBox* entityBoundingBox = nullptr;
	if (entity->getType() == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		entityBoundingBox = new BoundingBox(new Vector3(-0.5f, 0.0f, -0.5f), new Vector3(0.5f, 3.0f, 0.5f));
		auto particleSystemObject = Level::createParticleSystem(entity->getParticleSystem(), u"model"_j, true);
		if (particleSystemObject != nullptr) {
			engine->addEntity(particleSystemObject);
		}
	} else {
		entityBoundingBox = entity->getModel()->getBoundingBox();
		auto modelObject = new Object3D(u"model"_j, entity->getModel());
		modelObject->setDynamicShadowingEnabled(true);
		engine->addEntity(modelObject);
	}
	auto ground = createGroundModel((entityBoundingBox->getMax()->getX() - entityBoundingBox->getMin()->getX()) * 1.0f, (entityBoundingBox->getMax()->getZ() - entityBoundingBox->getMin()->getZ()) * 1.0f, entityBoundingBox->getMin()->getY() - MathTools::EPSILON);
	auto groundObject = new Object3D(u"ground"_j, ground);
	groundObject->setEnabled(false);
	engine->addEntity(groundObject);
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto boundingVolume = entity->getBoundingVolumeAt(i);
		if (boundingVolume->getModel() == nullptr)
			continue;

		auto modelBoundingVolumeObject = new Object3D(::java::lang::StringBuilder().append(u"model_bv."_j)->append(i)->toString(), boundingVolume->getModel());
		modelBoundingVolumeObject->setEnabled(false);
		engine->addEntity(modelBoundingVolumeObject);
	}
	for (auto light : *engine->getLights()) light->setEnabled(false);
	auto light0 = engine->getLightAt(0);
	light0->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light0->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getPosition()->set(entityBoundingBox->getMin()->getX() + ((entityBoundingBox->getMax()->getX() - entityBoundingBox->getMin()->getX()) / 2.0f), entityBoundingBox->getMin()->getY() + ((entityBoundingBox->getMax()->getY() - entityBoundingBox->getMin()->getY()) / 2.0f), -entityBoundingBox->getMin()->getZ() * 4.0f, 1.0f);
	light0->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light0->getPosition()->getArray()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto dimension = entityBoundingBox->getMax()->clone()->sub(entityBoundingBox->getMin());
	auto maxAxisDimension = computeMaxAxisDimension(entityBoundingBox);
	auto cam = engine->getCamera();
	cam->setZNear(maxAxisDimension / 5000.0f);
	cam->setZFar(maxAxisDimension);
	auto lookAt = entityBoundingBox->getMin()->clone()->add(dimension->clone()->scale(0.5f));
	cam->getLookAt()->set(lookAt);
	auto lookAtToFromVector = new Vector3(0.0f, 0.0f, +(maxAxisDimension * 1.2f));
	auto lookAtToFromVectorTransformed = new Vector3();
	auto lookAtToFromVectorScaled = new Vector3();
	auto upVector = new Vector3();
	lookFromRotations->getTransformationsMatrix()->multiply(lookAtToFromVector, lookAtToFromVectorTransformed);
	lookAtToFromVectorScaled->set(lookAtToFromVectorTransformed)->scale(scale);
	lookFromRotations->getRotations()->get(2)->getQuaternion()->multiply(new Vector3(0.0f, 1.0f, 0.0f), upVector);
	auto lookFrom = lookAt->clone()->add(lookAtToFromVectorScaled);
	cam->getLookFrom()->set(lookFrom);
	cam->getUpVector()->set(upVector);
}

String* Tools::getRelativeResourcesFileName(String* gameRoot, String* fileName)
{
	clinit();
	fileName = fileName->replace(u'\\', u'/');
	auto cutFileNameIdx = -1;
	if (cutFileNameIdx == -1) {
		cutFileNameIdx = fileName->lastIndexOf(u"/resources/"_j);
		if (cutFileNameIdx != -1) {
			fileName = fileName->substring(cutFileNameIdx + 1);
		}
	}
	if (cutFileNameIdx == -1) {
		cutFileNameIdx = fileName->lastIndexOf(u"resources/"_j);
		if (cutFileNameIdx != -1) {
			fileName = fileName->substring(cutFileNameIdx);
		}
	}
	return fileName;
}

String* Tools::getGameRootPath(String* fileName)
{
	clinit();
	fileName = fileName->replace(u'\\', u'/');
	auto filesRootIdx = -1;
	if (filesRootIdx == -1) {
		filesRootIdx = fileName->lastIndexOf(u"/resources/"_j);
		if (filesRootIdx != -1)
			fileName = fileName->substring(0, filesRootIdx);

	}
	if (filesRootIdx == -1) {
		filesRootIdx = fileName->lastIndexOf(u"resources/"_j);
		if (filesRootIdx != -1)
			fileName = fileName->substring(0, filesRootIdx);

	}
	return fileName;
}

String* Tools::getPath(String* fileName)
{
	clinit();
	return _FileSystem::getInstance()->getPathName(fileName);
}

String* Tools::getFileName(String* fileName)
{
	clinit();
	return _FileSystem::getInstance()->getFileName(fileName);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Tools::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.tools.Tools", 29);
    return c;
}

void Tools::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		osEngine = nullptr;
		oseLookFromRotations = nullptr;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Tools::getClass0()
{
	return class_();
}

