// Generated from /tdme/src/tdme/tools/shared/files/ModelMetaDataFileExport.java
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>

#include <java/io/File.h>
#include <java/io/FileInputStream.h>
#include <java/io/FileOutputStream.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
#include <java/io/OutputStream.h>
#include <java/io/PrintStream.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Iterable.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <org/json/JSONArray.h>
#include <org/json/JSONException.h>
#include <org/json/JSONObject.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::tools::shared::files::ModelMetaDataFileExport;
using java::io::File;
using java::io::FileInputStream;
using java::io::FileOutputStream;
using java::io::IOException;
using java::io::InputStream;
using java::io::OutputStream;
using java::io::PrintStream;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Iterable;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using org::json::JSONArray;
using org::json::JSONException;
using org::json::JSONObject;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}
ModelMetaDataFileExport::ModelMetaDataFileExport(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelMetaDataFileExport::ModelMetaDataFileExport()
	: ModelMetaDataFileExport(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void ModelMetaDataFileExport::copyFile(File* source, File* dest) /* throws(IOException) */
{
	clinit();
	InputStream* is = nullptr;
	OutputStream* os = nullptr;
	{
		auto finally0 = finally([&] {
			if (is != nullptr)
				try {
					is->close();
				} catch (IOException* ioe) {
				}

			if (os != nullptr)
				try {
					os->close();
				} catch (IOException* ioe) {
				}

		});
		{
			is = new FileInputStream(source);
			os = new FileOutputStream(dest);
			auto buffer = new int8_tArray(1024);
			int32_t length;
			while ((length = is->read(buffer)) > 0) {
				os->write(buffer, 0, length);
			}
		}
	}

}

void ModelMetaDataFileExport::export_(String* pathName, String* fileName, LevelEditorEntity* entity) /* throws(Exception) */
{
	clinit();
	FileOutputStream* fos = nullptr;
	PrintStream* fops = nullptr;
	{
		auto finally1 = finally([&] {
			if (fops != nullptr)
				fops->close();

			if (fos != nullptr)
				try {
					fos->close();
				} catch (IOException* ioe) {
					throw ioe;
				}

		});
		try {
			auto entityFileName = (new File(pathName, fileName))->getCanonicalPath();
			entity->setEntityFileName(entityFileName);
			auto jEntityRoot = exportToJSON(entity);
			fos = new FileOutputStream(entityFileName);
			fops = new PrintStream(static_cast< OutputStream* >(fos));
			fops->print(jEntityRoot->toString(2));
		} catch (JSONException* je) {
			je->printStackTrace();
			throw je;
		} catch (IOException* ioe) {
			ioe->printStackTrace();
			throw ioe;
		}
	}
}

JSONObject* ModelMetaDataFileExport::exportToJSON(LevelEditorEntity* entity) /* throws(Exception) */
{
	clinit();
	auto jEntityRoot = new JSONObject();
	if (entity->getType() == LevelEditorEntity_EntityType::MODEL && entity->getFileName() != nullptr) {
		auto modelPathName = Tools::getPath(entity->getFileName());
		auto modelFileName = ::java::lang::StringBuilder().append(Tools::getFileName(entity->getFileName()))->append((entity->getFileName()->endsWith(u".tm"_j) == false ? u".tm"_j : u""_j))->toString();
		TMWriter::write(entity->getModel(), modelPathName, modelFileName);
		jEntityRoot->put(u"file"_j, static_cast< Object* >(::java::lang::StringBuilder().append(modelPathName)->append(u"/"_j)
			->append(modelFileName)->toString()));
		try {
			auto thumbnail = ::java::lang::StringBuilder().append(modelFileName)->append(u".png"_j)->toString();
			jEntityRoot->put(u"thumbnail"_j, static_cast< Object* >(thumbnail));
			copyFile(new File(u"./tmp"_j, entity->getThumbnail()), new File(Tools::getPath(entity->getFileName()), thumbnail));
		} catch (IOException* ioe) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileExport::export(): Could not copy thumbnail for '"_j)->append(entity->getFileName())
				->append(u"'"_j)->toString()));
		}
	}
	jEntityRoot->put(u"version"_j, static_cast< Object* >(u"0.99"_j));
	jEntityRoot->put(u"type"_j, static_cast< Object* >(entity->getType()));
	jEntityRoot->put(u"name"_j, static_cast< Object* >(entity->getName()));
	jEntityRoot->put(u"descr"_j, static_cast< Object* >(entity->getDescription()));
	jEntityRoot->put(u"px"_j, static_cast< double >(entity->getPivot()->getX()));
	jEntityRoot->put(u"py"_j, static_cast< double >(entity->getPivot()->getY()));
	jEntityRoot->put(u"pz"_j, static_cast< double >(entity->getPivot()->getZ()));
	if (entity->getType() == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		auto particleSystem = entity->getParticleSystem();
		auto jParticleSystem = new JSONObject();
		jParticleSystem->put(u"t"_j, static_cast< Object* >(particleSystem->getType()->toString()));
		{
			auto v = particleSystem->getType();
			if ((v == LevelEditorEntityParticleSystem_Type::NONE)) {
{
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM)) {
{
					auto jObjectParticleSystem = new JSONObject();
					if (particleSystem->getObjectParticleSystem()->getModelFile() != nullptr && particleSystem->getObjectParticleSystem()->getModelFile()->length() > 0) {
						auto modelPathName = Tools::getPath(particleSystem->getObjectParticleSystem()->getModelFile());
						auto modelFileName = Tools::getFileName(::java::lang::StringBuilder().append(particleSystem->getObjectParticleSystem()->getModelFile())->append((particleSystem->getObjectParticleSystem()->getModelFile()->endsWith(u".tm"_j) == false ? u".tm"_j : u""_j))->toString());
						TMWriter::write(particleSystem->getObjectParticleSystem()->getModel(), modelPathName, modelFileName);
						particleSystem->getObjectParticleSystem()->setModelFile(::java::lang::StringBuilder().append(modelPathName)->append(u"/"_j)
							->append(modelFileName)->toString());
					}
					jObjectParticleSystem->put(u"mc"_j, particleSystem->getObjectParticleSystem()->getMaxCount());
					jObjectParticleSystem->put(u"sx"_j, static_cast< double >(particleSystem->getObjectParticleSystem()->getScale()->getX()));
					jObjectParticleSystem->put(u"sy"_j, static_cast< double >(particleSystem->getObjectParticleSystem()->getScale()->getY()));
					jObjectParticleSystem->put(u"sz"_j, static_cast< double >(particleSystem->getObjectParticleSystem()->getScale()->getZ()));
					jObjectParticleSystem->put(u"mf"_j, static_cast< Object* >(particleSystem->getObjectParticleSystem()->getModelFile()));
					jObjectParticleSystem->put(u"ae"_j, particleSystem->getObjectParticleSystem()->isAutoEmit());
					jParticleSystem->put(u"ops"_j, static_cast< Object* >(jObjectParticleSystem));
					goto end_switch0;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)) {
{
					auto jPointParticleSystem = new JSONObject();
					jPointParticleSystem->put(u"mp"_j, particleSystem->getPointParticleSystem()->getMaxPoints());
					jPointParticleSystem->put(u"ae"_j, particleSystem->getPointParticleSystem()->isAutoEmit());
					jParticleSystem->put(u"pps"_j, static_cast< Object* >(jPointParticleSystem));
					goto end_switch0;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Type::NONE) || (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) || (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM) || ((v != LevelEditorEntityParticleSystem_Type::NONE) && (v != LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) && (v != LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM)))) {
{
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileExport::export(): unknown particle system type '"_j)->append(static_cast< Object* >(particleSystem->getType()))
						->append(u"'"_j)->toString()));
					goto end_switch0;;
				}			}
end_switch0:;
		}

		jParticleSystem->put(u"e"_j, static_cast< Object* >(particleSystem->getEmitter()->toString()));
		{
			auto v = particleSystem->getEmitter();
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE)) {
{
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER)) {
{
					auto jPointParticleEmitter = new JSONObject();
					auto emitter = particleSystem->getPointParticleEmitter();
					jPointParticleEmitter->put(u"c"_j, emitter->getCount());
					jPointParticleEmitter->put(u"lt"_j, emitter->getLifeTime());
					jPointParticleEmitter->put(u"ltrnd"_j, emitter->getLifeTimeRnd());
					jPointParticleEmitter->put(u"m"_j, static_cast< double >(emitter->getMass()));
					jPointParticleEmitter->put(u"mrnd"_j, static_cast< double >(emitter->getMassRnd()));
					jPointParticleEmitter->put(u"px"_j, static_cast< double >(emitter->getPosition()->getX()));
					jPointParticleEmitter->put(u"py"_j, static_cast< double >(emitter->getPosition()->getY()));
					jPointParticleEmitter->put(u"pz"_j, static_cast< double >(emitter->getPosition()->getZ()));
					jPointParticleEmitter->put(u"vx"_j, static_cast< double >(emitter->getVelocity()->getX()));
					jPointParticleEmitter->put(u"vy"_j, static_cast< double >(emitter->getVelocity()->getY()));
					jPointParticleEmitter->put(u"vz"_j, static_cast< double >(emitter->getVelocity()->getZ()));
					jPointParticleEmitter->put(u"vrndx"_j, static_cast< double >(emitter->getVelocityRnd()->getX()));
					jPointParticleEmitter->put(u"vrndy"_j, static_cast< double >(emitter->getVelocityRnd()->getY()));
					jPointParticleEmitter->put(u"vrndz"_j, static_cast< double >(emitter->getVelocityRnd()->getZ()));
					jPointParticleEmitter->put(u"csr"_j, static_cast< double >(emitter->getColorStart()->getRed()));
					jPointParticleEmitter->put(u"csg"_j, static_cast< double >(emitter->getColorStart()->getGreen()));
					jPointParticleEmitter->put(u"csb"_j, static_cast< double >(emitter->getColorStart()->getBlue()));
					jPointParticleEmitter->put(u"csa"_j, static_cast< double >(emitter->getColorStart()->getAlpha()));
					jPointParticleEmitter->put(u"cer"_j, static_cast< double >(emitter->getColorEnd()->getRed()));
					jPointParticleEmitter->put(u"ceg"_j, static_cast< double >(emitter->getColorEnd()->getGreen()));
					jPointParticleEmitter->put(u"ceb"_j, static_cast< double >(emitter->getColorEnd()->getBlue()));
					jPointParticleEmitter->put(u"cea"_j, static_cast< double >(emitter->getColorEnd()->getAlpha()));
					jParticleSystem->put(u"ppe"_j, static_cast< Object* >(jPointParticleEmitter));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER)) {
{
					auto jBoundingBoxParticleEmitter = new JSONObject();
					auto emitter = particleSystem->getBoundingBoxParticleEmitters();
					jBoundingBoxParticleEmitter->put(u"c"_j, emitter->getCount());
					jBoundingBoxParticleEmitter->put(u"lt"_j, emitter->getLifeTime());
					jBoundingBoxParticleEmitter->put(u"ltrnd"_j, emitter->getLifeTimeRnd());
					jBoundingBoxParticleEmitter->put(u"m"_j, static_cast< double >(emitter->getMass()));
					jBoundingBoxParticleEmitter->put(u"mrnd"_j, static_cast< double >(emitter->getMassRnd()));
					jBoundingBoxParticleEmitter->put(u"vx"_j, static_cast< double >(emitter->getVelocity()->getX()));
					jBoundingBoxParticleEmitter->put(u"vy"_j, static_cast< double >(emitter->getVelocity()->getY()));
					jBoundingBoxParticleEmitter->put(u"vz"_j, static_cast< double >(emitter->getVelocity()->getZ()));
					jBoundingBoxParticleEmitter->put(u"vrndx"_j, static_cast< double >(emitter->getVelocityRnd()->getX()));
					jBoundingBoxParticleEmitter->put(u"vrndy"_j, static_cast< double >(emitter->getVelocityRnd()->getY()));
					jBoundingBoxParticleEmitter->put(u"vrndz"_j, static_cast< double >(emitter->getVelocityRnd()->getZ()));
					jBoundingBoxParticleEmitter->put(u"csr"_j, static_cast< double >(emitter->getColorStart()->getRed()));
					jBoundingBoxParticleEmitter->put(u"csg"_j, static_cast< double >(emitter->getColorStart()->getGreen()));
					jBoundingBoxParticleEmitter->put(u"csb"_j, static_cast< double >(emitter->getColorStart()->getBlue()));
					jBoundingBoxParticleEmitter->put(u"csa"_j, static_cast< double >(emitter->getColorStart()->getAlpha()));
					jBoundingBoxParticleEmitter->put(u"cer"_j, static_cast< double >(emitter->getColorEnd()->getRed()));
					jBoundingBoxParticleEmitter->put(u"ceg"_j, static_cast< double >(emitter->getColorEnd()->getGreen()));
					jBoundingBoxParticleEmitter->put(u"ceb"_j, static_cast< double >(emitter->getColorEnd()->getBlue()));
					jBoundingBoxParticleEmitter->put(u"cea"_j, static_cast< double >(emitter->getColorEnd()->getAlpha()));
					jBoundingBoxParticleEmitter->put(u"ocx"_j, static_cast< double >(emitter->getObbCenter()->getX()));
					jBoundingBoxParticleEmitter->put(u"ocy"_j, static_cast< double >(emitter->getObbCenter()->getY()));
					jBoundingBoxParticleEmitter->put(u"ocz"_j, static_cast< double >(emitter->getObbCenter()->getZ()));
					jBoundingBoxParticleEmitter->put(u"ohex"_j, static_cast< double >(emitter->getObbHalfextension()->getX()));
					jBoundingBoxParticleEmitter->put(u"ohey"_j, static_cast< double >(emitter->getObbHalfextension()->getY()));
					jBoundingBoxParticleEmitter->put(u"ohez"_j, static_cast< double >(emitter->getObbHalfextension()->getZ()));
					jBoundingBoxParticleEmitter->put(u"oa0x"_j, static_cast< double >(emitter->getObbAxis0()->getX()));
					jBoundingBoxParticleEmitter->put(u"oa0y"_j, static_cast< double >(emitter->getObbAxis0()->getY()));
					jBoundingBoxParticleEmitter->put(u"oa0z"_j, static_cast< double >(emitter->getObbAxis0()->getZ()));
					jBoundingBoxParticleEmitter->put(u"oa1x"_j, static_cast< double >(emitter->getObbAxis1()->getX()));
					jBoundingBoxParticleEmitter->put(u"oa1y"_j, static_cast< double >(emitter->getObbAxis1()->getY()));
					jBoundingBoxParticleEmitter->put(u"oa1z"_j, static_cast< double >(emitter->getObbAxis1()->getZ()));
					jBoundingBoxParticleEmitter->put(u"oa2x"_j, static_cast< double >(emitter->getObbAxis2()->getX()));
					jBoundingBoxParticleEmitter->put(u"oa2y"_j, static_cast< double >(emitter->getObbAxis2()->getY()));
					jBoundingBoxParticleEmitter->put(u"oa2z"_j, static_cast< double >(emitter->getObbAxis2()->getZ()));
					jParticleSystem->put(u"bbpe"_j, static_cast< Object* >(jBoundingBoxParticleEmitter));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER)) {
{
					auto jCircleParticleEmitter = new JSONObject();
					auto emitter = particleSystem->getCircleParticleEmitter();
					jCircleParticleEmitter->put(u"c"_j, emitter->getCount());
					jCircleParticleEmitter->put(u"lt"_j, emitter->getLifeTime());
					jCircleParticleEmitter->put(u"ltrnd"_j, emitter->getLifeTimeRnd());
					jCircleParticleEmitter->put(u"m"_j, static_cast< double >(emitter->getMass()));
					jCircleParticleEmitter->put(u"mrnd"_j, static_cast< double >(emitter->getMassRnd()));
					jCircleParticleEmitter->put(u"vx"_j, static_cast< double >(emitter->getVelocity()->getX()));
					jCircleParticleEmitter->put(u"vy"_j, static_cast< double >(emitter->getVelocity()->getY()));
					jCircleParticleEmitter->put(u"vz"_j, static_cast< double >(emitter->getVelocity()->getZ()));
					jCircleParticleEmitter->put(u"vrndx"_j, static_cast< double >(emitter->getVelocityRnd()->getX()));
					jCircleParticleEmitter->put(u"vrndy"_j, static_cast< double >(emitter->getVelocityRnd()->getY()));
					jCircleParticleEmitter->put(u"vrndz"_j, static_cast< double >(emitter->getVelocityRnd()->getZ()));
					jCircleParticleEmitter->put(u"csr"_j, static_cast< double >(emitter->getColorStart()->getRed()));
					jCircleParticleEmitter->put(u"csg"_j, static_cast< double >(emitter->getColorStart()->getGreen()));
					jCircleParticleEmitter->put(u"csb"_j, static_cast< double >(emitter->getColorStart()->getBlue()));
					jCircleParticleEmitter->put(u"csa"_j, static_cast< double >(emitter->getColorStart()->getAlpha()));
					jCircleParticleEmitter->put(u"cer"_j, static_cast< double >(emitter->getColorEnd()->getRed()));
					jCircleParticleEmitter->put(u"ceg"_j, static_cast< double >(emitter->getColorEnd()->getGreen()));
					jCircleParticleEmitter->put(u"ceb"_j, static_cast< double >(emitter->getColorEnd()->getBlue()));
					jCircleParticleEmitter->put(u"cea"_j, static_cast< double >(emitter->getColorEnd()->getAlpha()));
					jCircleParticleEmitter->put(u"cx"_j, static_cast< double >(emitter->getCenter()->getX()));
					jCircleParticleEmitter->put(u"cy"_j, static_cast< double >(emitter->getCenter()->getY()));
					jCircleParticleEmitter->put(u"cz"_j, static_cast< double >(emitter->getCenter()->getZ()));
					jCircleParticleEmitter->put(u"r"_j, static_cast< double >(emitter->getRadius()));
					jCircleParticleEmitter->put(u"a0x"_j, static_cast< double >(emitter->getAxis0()->getX()));
					jCircleParticleEmitter->put(u"a0y"_j, static_cast< double >(emitter->getAxis0()->getY()));
					jCircleParticleEmitter->put(u"a0z"_j, static_cast< double >(emitter->getAxis0()->getZ()));
					jCircleParticleEmitter->put(u"a1x"_j, static_cast< double >(emitter->getAxis1()->getX()));
					jCircleParticleEmitter->put(u"a1y"_j, static_cast< double >(emitter->getAxis1()->getY()));
					jCircleParticleEmitter->put(u"a1z"_j, static_cast< double >(emitter->getAxis1()->getZ()));
					jParticleSystem->put(u"cpe"_j, static_cast< Object* >(jCircleParticleEmitter));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY)) {
{
					auto jCircleParticleEmitterPlaneVelocity = new JSONObject();
					auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
					jCircleParticleEmitterPlaneVelocity->put(u"c"_j, emitter->getCount());
					jCircleParticleEmitterPlaneVelocity->put(u"lt"_j, emitter->getLifeTime());
					jCircleParticleEmitterPlaneVelocity->put(u"ltrnd"_j, emitter->getLifeTimeRnd());
					jCircleParticleEmitterPlaneVelocity->put(u"m"_j, static_cast< double >(emitter->getMass()));
					jCircleParticleEmitterPlaneVelocity->put(u"mrnd"_j, static_cast< double >(emitter->getMassRnd()));
					jCircleParticleEmitterPlaneVelocity->put(u"v"_j, static_cast< double >(emitter->getVelocity()));
					jCircleParticleEmitterPlaneVelocity->put(u"vrnd"_j, static_cast< double >(emitter->getVelocityRnd()));
					jCircleParticleEmitterPlaneVelocity->put(u"csr"_j, static_cast< double >(emitter->getColorStart()->getRed()));
					jCircleParticleEmitterPlaneVelocity->put(u"csg"_j, static_cast< double >(emitter->getColorStart()->getGreen()));
					jCircleParticleEmitterPlaneVelocity->put(u"csb"_j, static_cast< double >(emitter->getColorStart()->getBlue()));
					jCircleParticleEmitterPlaneVelocity->put(u"csa"_j, static_cast< double >(emitter->getColorStart()->getAlpha()));
					jCircleParticleEmitterPlaneVelocity->put(u"cer"_j, static_cast< double >(emitter->getColorEnd()->getRed()));
					jCircleParticleEmitterPlaneVelocity->put(u"ceg"_j, static_cast< double >(emitter->getColorEnd()->getGreen()));
					jCircleParticleEmitterPlaneVelocity->put(u"ceb"_j, static_cast< double >(emitter->getColorEnd()->getBlue()));
					jCircleParticleEmitterPlaneVelocity->put(u"cea"_j, static_cast< double >(emitter->getColorEnd()->getAlpha()));
					jCircleParticleEmitterPlaneVelocity->put(u"cx"_j, static_cast< double >(emitter->getCenter()->getX()));
					jCircleParticleEmitterPlaneVelocity->put(u"cy"_j, static_cast< double >(emitter->getCenter()->getY()));
					jCircleParticleEmitterPlaneVelocity->put(u"cz"_j, static_cast< double >(emitter->getCenter()->getZ()));
					jCircleParticleEmitterPlaneVelocity->put(u"r"_j, static_cast< double >(emitter->getRadius()));
					jCircleParticleEmitterPlaneVelocity->put(u"a0x"_j, static_cast< double >(emitter->getAxis0()->getX()));
					jCircleParticleEmitterPlaneVelocity->put(u"a0y"_j, static_cast< double >(emitter->getAxis0()->getY()));
					jCircleParticleEmitterPlaneVelocity->put(u"a0z"_j, static_cast< double >(emitter->getAxis0()->getZ()));
					jCircleParticleEmitterPlaneVelocity->put(u"a1x"_j, static_cast< double >(emitter->getAxis1()->getX()));
					jCircleParticleEmitterPlaneVelocity->put(u"a1y"_j, static_cast< double >(emitter->getAxis1()->getY()));
					jCircleParticleEmitterPlaneVelocity->put(u"a1z"_j, static_cast< double >(emitter->getAxis1()->getZ()));
					jParticleSystem->put(u"cpeev"_j, static_cast< Object* >(jCircleParticleEmitterPlaneVelocity));
					goto end_switch1;;
				}			}
			if ((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)) {
{
					auto jSphereParticleEmitter = new JSONObject();
					auto emitter = particleSystem->getSphereParticleEmitter();
					jSphereParticleEmitter->put(u"c"_j, emitter->getCount());
					jSphereParticleEmitter->put(u"lt"_j, emitter->getLifeTime());
					jSphereParticleEmitter->put(u"ltrnd"_j, emitter->getLifeTimeRnd());
					jSphereParticleEmitter->put(u"m"_j, static_cast< double >(emitter->getMass()));
					jSphereParticleEmitter->put(u"mrnd"_j, static_cast< double >(emitter->getMassRnd()));
					jSphereParticleEmitter->put(u"vx"_j, static_cast< double >(emitter->getVelocity()->getX()));
					jSphereParticleEmitter->put(u"vy"_j, static_cast< double >(emitter->getVelocity()->getY()));
					jSphereParticleEmitter->put(u"vz"_j, static_cast< double >(emitter->getVelocity()->getZ()));
					jSphereParticleEmitter->put(u"vrndx"_j, static_cast< double >(emitter->getVelocityRnd()->getX()));
					jSphereParticleEmitter->put(u"vrndy"_j, static_cast< double >(emitter->getVelocityRnd()->getY()));
					jSphereParticleEmitter->put(u"vrndz"_j, static_cast< double >(emitter->getVelocityRnd()->getZ()));
					jSphereParticleEmitter->put(u"csr"_j, static_cast< double >(emitter->getColorStart()->getRed()));
					jSphereParticleEmitter->put(u"csg"_j, static_cast< double >(emitter->getColorStart()->getGreen()));
					jSphereParticleEmitter->put(u"csb"_j, static_cast< double >(emitter->getColorStart()->getBlue()));
					jSphereParticleEmitter->put(u"csa"_j, static_cast< double >(emitter->getColorStart()->getAlpha()));
					jSphereParticleEmitter->put(u"cer"_j, static_cast< double >(emitter->getColorEnd()->getRed()));
					jSphereParticleEmitter->put(u"ceg"_j, static_cast< double >(emitter->getColorEnd()->getGreen()));
					jSphereParticleEmitter->put(u"ceb"_j, static_cast< double >(emitter->getColorEnd()->getBlue()));
					jSphereParticleEmitter->put(u"cea"_j, static_cast< double >(emitter->getColorEnd()->getAlpha()));
					jSphereParticleEmitter->put(u"cx"_j, static_cast< double >(emitter->getCenter()->getX()));
					jSphereParticleEmitter->put(u"cy"_j, static_cast< double >(emitter->getCenter()->getY()));
					jSphereParticleEmitter->put(u"cz"_j, static_cast< double >(emitter->getCenter()->getZ()));
					jSphereParticleEmitter->put(u"r"_j, static_cast< double >(emitter->getRadius()));
					jParticleSystem->put(u"spe"_j, static_cast< Object* >(jSphereParticleEmitter));
					goto end_switch1;;
				}			}
			if (((v == LevelEditorEntityParticleSystem_Emitter::NONE) || (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) || (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) || (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) || ((v != LevelEditorEntityParticleSystem_Emitter::NONE) && (v != LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) && (v != LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) && (v != LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER)))) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelMetaDataFileExport::export(): unknown particle system emitter '"_j)->append(static_cast< Object* >(particleSystem->getEmitter()))
					->append(u"'"_j)->toString()));
			}
end_switch1:;
		}

		jEntityRoot->put(u"ps"_j, static_cast< Object* >(jParticleSystem));
	}
	auto jBoundingVolumes = new JSONArray();
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto entityBoundingVolume = entity->getBoundingVolumeAt(i);
		auto bv = entityBoundingVolume->getBoundingVolume();
		if (bv == nullptr)
			continue;

		auto jBoundingVolume = new JSONObject();
		if (bv == nullptr) {
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"none"_j));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		} else if (dynamic_cast< Sphere* >(bv) != nullptr) {
			auto sphere = java_cast< Sphere* >(bv);
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"sphere"_j));
			jBoundingVolume->put(u"cx"_j, static_cast< double >(sphere->getCenter()->getX()));
			jBoundingVolume->put(u"cy"_j, static_cast< double >(sphere->getCenter()->getY()));
			jBoundingVolume->put(u"cz"_j, static_cast< double >(sphere->getCenter()->getZ()));
			jBoundingVolume->put(u"r"_j, static_cast< double >(sphere->getRadius()));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		} else if (dynamic_cast< Capsule* >(bv) != nullptr) {
			auto capsule = java_cast< Capsule* >(bv);
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"capsule"_j));
			jBoundingVolume->put(u"ax"_j, static_cast< double >(capsule->getA()->getX()));
			jBoundingVolume->put(u"ay"_j, static_cast< double >(capsule->getA()->getY()));
			jBoundingVolume->put(u"az"_j, static_cast< double >(capsule->getA()->getZ()));
			jBoundingVolume->put(u"bx"_j, static_cast< double >(capsule->getB()->getX()));
			jBoundingVolume->put(u"by"_j, static_cast< double >(capsule->getB()->getY()));
			jBoundingVolume->put(u"bz"_j, static_cast< double >(capsule->getB()->getZ()));
			jBoundingVolume->put(u"r"_j, static_cast< double >(capsule->getRadius()));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		} else if (dynamic_cast< BoundingBox* >(bv) != nullptr) {
			auto aabb = java_cast< BoundingBox* >(bv);
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"aabb"_j));
			jBoundingVolume->put(u"mix"_j, static_cast< double >(aabb->getMin()->getX()));
			jBoundingVolume->put(u"miy"_j, static_cast< double >(aabb->getMin()->getY()));
			jBoundingVolume->put(u"miz"_j, static_cast< double >(aabb->getMin()->getZ()));
			jBoundingVolume->put(u"max"_j, static_cast< double >(aabb->getMax()->getX()));
			jBoundingVolume->put(u"may"_j, static_cast< double >(aabb->getMax()->getY()));
			jBoundingVolume->put(u"maz"_j, static_cast< double >(aabb->getMax()->getZ()));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		} else if (dynamic_cast< OrientedBoundingBox* >(bv) != nullptr) {
			auto obb = java_cast< OrientedBoundingBox* >(bv);
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"obb"_j));
			jBoundingVolume->put(u"cx"_j, static_cast< double >(obb->getCenter()->getX()));
			jBoundingVolume->put(u"cy"_j, static_cast< double >(obb->getCenter()->getY()));
			jBoundingVolume->put(u"cz"_j, static_cast< double >(obb->getCenter()->getZ()));
			jBoundingVolume->put(u"a0x"_j, static_cast< double >((*obb->getAxes())[0]->getX()));
			jBoundingVolume->put(u"a0y"_j, static_cast< double >((*obb->getAxes())[0]->getY()));
			jBoundingVolume->put(u"a0z"_j, static_cast< double >((*obb->getAxes())[0]->getZ()));
			jBoundingVolume->put(u"a1x"_j, static_cast< double >((*obb->getAxes())[1]->getX()));
			jBoundingVolume->put(u"a1y"_j, static_cast< double >((*obb->getAxes())[1]->getY()));
			jBoundingVolume->put(u"a1z"_j, static_cast< double >((*obb->getAxes())[1]->getZ()));
			jBoundingVolume->put(u"a2x"_j, static_cast< double >((*obb->getAxes())[2]->getX()));
			jBoundingVolume->put(u"a2y"_j, static_cast< double >((*obb->getAxes())[2]->getY()));
			jBoundingVolume->put(u"a2z"_j, static_cast< double >((*obb->getAxes())[2]->getZ()));
			jBoundingVolume->put(u"hex"_j, static_cast< double >(obb->getHalfExtension()->getX()));
			jBoundingVolume->put(u"hey"_j, static_cast< double >(obb->getHalfExtension()->getY()));
			jBoundingVolume->put(u"hez"_j, static_cast< double >(obb->getHalfExtension()->getZ()));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		} else if (dynamic_cast< ConvexMesh* >(bv) != nullptr) {
			auto mesh = java_cast< ConvexMesh* >(bv);
			jBoundingVolume->put(u"type"_j, static_cast< Object* >(u"convexmesh"_j));
			jBoundingVolume->put(u"file"_j, static_cast< Object* >(entityBoundingVolume->getModelMeshFile()));
			auto jMeshTriangles = new JSONArray();
			auto triangleIdx = 0;
			for (auto triangle : *mesh->getTriangles()) {
				auto jMeshTriangleVertices = new JSONArray();
				auto vertexIdx = 0;
				for (auto vertex : *triangle->getVertices()) {
					auto jMeshTriangleVertex = new JSONArray();
					for (auto vcIdx = 0; vcIdx < 3; vcIdx++) {
						jMeshTriangleVertex->put(vcIdx, static_cast< double >((*vertex->getArray())[vcIdx]));
					}
					jMeshTriangleVertices->put(vertexIdx++, static_cast< Object* >(jMeshTriangleVertex));
				}
				jMeshTriangles->put(triangleIdx++, static_cast< Object* >(jMeshTriangleVertices));
			}
			jBoundingVolume->put(u"t"_j, static_cast< Object* >(jMeshTriangles));
			jBoundingVolumes->put(static_cast< Object* >(jBoundingVolume));
		}
	}
	jEntityRoot->put(u"bvs"_j, static_cast< Object* >(jBoundingVolumes));
	auto jModelProperties = new JSONArray();
	for (auto _i = entity->getProperties()->iterator(); _i->hasNext(); ) {
		PropertyModelClass* modelProperty = java_cast< PropertyModelClass* >(_i->next());
		{
			auto jObjectProperty = new JSONObject();
			jObjectProperty->put(u"name"_j, static_cast< Object* >(modelProperty->getName()));
			jObjectProperty->put(u"value"_j, static_cast< Object* >(modelProperty->getValue()));
			jModelProperties->put(static_cast< Object* >(jObjectProperty));
		}
	}
	jEntityRoot->put(u"properties"_j, static_cast< Object* >(jModelProperties));
	return jEntityRoot;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelMetaDataFileExport::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.files.ModelMetaDataFileExport", 47);
    return c;
}

java::lang::Class* ModelMetaDataFileExport::getClass0()
{
	return class_();
}

