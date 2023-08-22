#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeImposterLOD.h>
#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::make_unique;
using std::map;
using std::remove;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeImposterLOD;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypePhysics;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::math::Vector3;
using tdme::utilities::UniquePtrSequenceIterator;

/**
 * Prototype definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::Prototype final
	: public BaseProperties
{
	friend class tdme::engine::scene::SceneLibrary;
	friend class Prototype_Type;

public:
	static constexpr int ID_NONE { -1 };

private:
	int id;
	Prototype_Type* type { nullptr };
	bool embedded { true };
	string fileName;
	string modelFileName;
	string thumbnail;
	unique_ptr<Model> model;
	bool entityHierachy { false };
	bool scriptHandlingHID { false };
	string script;
	unique_ptr<PrototypeLODLevel> lodLevel2;
	unique_ptr<PrototypeLODLevel> lodLevel3;
	unique_ptr<PrototypeImposterLOD> imposterLOD;
	vector<unique_ptr<PrototypeBoundingVolume>> boundingVolumes;
	unique_ptr<PrototypePhysics> physics;
	vector<unique_ptr<PrototypeParticleSystem>> particleSystems;
	bool terrainMesh { false };
	bool renderGroups { false };
	string shaderId { "default"};
	bool contributesShadows { true };
	bool receivesShadows { true };
	EntityShaderParameters shaderParameters;
	map<string, PrototypeAudio*> soundsById;
	vector<unique_ptr<PrototypeAudio>> sounds;
	int32_t environmentMapRenderPassMask { Entity::RENDERPASS_ALL - Entity::RENDERPASS_WATER };
	int64_t environmentMapTimeRenderUpdateFrequency { 0LL };
	unique_ptr<PrototypeTerrain> terrain;
	unique_ptr<PrototypeDecal> decal;

	/**
	 * Set Id
	 * @param id id
	 */
	inline void setId(int id) {
		this->id = id;
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(Prototype)

	/**
	 * Creates a prototype
	 * @param id id
	 * @param prototypType prototype type
	 * @param name name
	 * @param description description
	 * @param fileName file name
	 * @param modelFileName model file name
	 * @param thumbnail thumbnail PNG data
	 * @param model model
	 */
	Prototype(int id, Prototype_Type* prototypeType, const string& name, const string& description, const string& fileName, const string& modelFileName, const string& thumbnail, Model* model);

	/**
	 * Destructor
	 */
	virtual ~Prototype();

	/**
	 * @return id
	 */
	inline int getId() {
		return id;
	}

	/**
	 * @return type
	 */
	inline Prototype_Type* getType() {
		return type;
	}

	/**
	 * @return if this prototype is embedded into a tscene file
	 */
	inline bool isEmbedded() {
		return embedded;
	}

	/**
	 * Set embedded
	 * @param embedded embedded
	 */
	inline void setEmbedded(bool embedded) {
		this->embedded = embedded;
	}

	/**
	 * @return prototype file name including relative path
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/**
	 * Set up prototype file name including relative path
	 * @param fileName prototype file name including relative path
	 */
	inline void setFileName(const string& fileName) {
		this->fileName = fileName;
	}

	/**
	 * @return model file name
	 */
	inline const string& getModelFileName() {
		return modelFileName;
	}

	/**
	 * Set model file name
	 * @param fileName file name
	 */
	inline void setModelFileName(const string& fileName) {
		this->modelFileName = fileName;
	}

	/**
	 * @return thumbnail base 64 PNG data
	 */
	inline const string& getThumbnail() {
		return thumbnail;
	}

	/**
	 * Set thumbnail base 64 PNG data
	 * @param thumbnail thumbnail Base 64 PNG data
	 */
	inline void setThumbnail(const string& thumbnail) {
		this->thumbnail = thumbnail;
	}

	/**
	 * @return model
	 */
	inline Model* getModel() {
		return model.get();
	}

	/**
	 * Set model
	 * @param model model
	 */
	void setModel(Model* model);

	/**
	 * Unset model without deleting current one
	 * @return model
	 */
	inline Model* unsetModel() {
		return model.release();
	}

	/**
	 * @return script attached to prototype
	 */
	inline bool hasScript() {
		return script.empty() == false;
	}

	/**
	 * @return prototype script name
	 */
	inline const string& getScript() {
		return script;
	}

	/**
	 * Set up prototype script
	 * @param fileName script file name
	 */
	inline void setScript(const string& fileName) {
		this->script = fileName;
	}

	/**
	 * @return is entity hierarchy
	 */
	inline bool isEntityHierarchy() {
		return entityHierachy;
	}

	/**
	 * Set entity hierarchy
	 * @param entityHierarchy entity hierarchy
	 */
	inline void setEntityHierarchy(bool entityHierarchy) {
		this->entityHierachy = entityHierarchy;
	}

	/**
	 * @return script is handling HID (input)
	 */
	inline bool isScriptHandlingHID() {
		return scriptHandlingHID;
	}

	/**
	 * Set script is handling HID (input)
	 * @param scriptHandlingHID script handling HID
	 */
	inline void setScriptHandlingHID(bool scriptHandlingHID) {
		this->scriptHandlingHID = scriptHandlingHID;
	}

	/**
	 * @return bounding volumes iterator
	 */
	inline UniquePtrSequenceIterator<PrototypeBoundingVolume> getBoundingVolumes() {
		return UniquePtrSequenceIterator<PrototypeBoundingVolume>(&boundingVolumes[0], &boundingVolumes[boundingVolumes.size()]);
	}

	/**
	 * @return bounding volume count
	 */
	inline int getBoundingVolumeCount() {
		return boundingVolumes.size();
	}

	/**
	 * Get bounding volume at given index
	 * @param idx index
	 * @return prototype bounding volume
	 */
	inline PrototypeBoundingVolume* getBoundingVolume(int idx) {
		return idx >= 0 && idx < boundingVolumes.size()?boundingVolumes[idx].get():nullptr;
	}

	/**
	 * Add bounding volume
	 * @param prototypeBoundingVolume prototype bounding volume
	 */
	void addBoundingVolume(PrototypeBoundingVolume* prototypeBoundingVolume);

	/**
	 * Remove bounding volume at given index
	 * @param idx index
	 */
	void removeBoundingVolume(int idx);

	/**
	 * Get bounding volumes primitibves to be added to physics engine
	 * @return bounding volume primitives
	 */
	inline const vector<BoundingVolume*> getBoundingVolumesPrimitives() {
		vector<BoundingVolume*> boundingVolumePrimitives;
		for (const auto& boundingVolume: boundingVolumes) {
			if (boundingVolume->getBoundingVolume() != nullptr) {
				boundingVolumePrimitives.push_back(boundingVolume->getBoundingVolume());
			}
		}
		return boundingVolumePrimitives;
	}

	/**
	 * @return physics
	 */
	inline PrototypePhysics* getPhysics() {
		return physics.get();
	}

	/**
	 * @return LOD level 2
	 */
	inline PrototypeLODLevel* getLODLevel2() {
		return lodLevel2.get();
	}

	/**
	 * Set LOD level 2
	 * @param lodLevel LOD level settings
	 */
	void setLODLevel2(PrototypeLODLevel* lodLevel);

	/**
	 * @return LOD level 3
	 */
	inline PrototypeLODLevel* getLODLevel3() {
		return lodLevel3.get();
	}

	/**
	 * Set LOD level 3
	 * @param lodLevel LOD level settings
	 */
	void setLODLevel3(PrototypeLODLevel* lodLevel);

	/**
	 * Remove LOD level
	 * @param lodLevel LOD level
	 */
	void removeLODLevel(int lodLevel);

	/**
	 * @return imposter LOD
	 */
	inline PrototypeImposterLOD* getImposterLOD() {
		return imposterLOD.get();
	}

	/**
	 * Set imposter LOD
	 * @param imposterLOD imposter LOD
	 */
	void setImposterLOD(PrototypeImposterLOD* imposterLOD);

	/**
	 * @return particle systems iterator
	 */
	inline UniquePtrSequenceIterator<PrototypeParticleSystem> getParticleSystems() {
		return UniquePtrSequenceIterator<PrototypeParticleSystem>(&particleSystems[0], &particleSystems[particleSystems.size()]);
	}

	/**
	 * @return particle systems count
	 */
	inline int getParticleSystemsCount() {
		return particleSystems.size();
	}

	/**
	 * Get particle system at given index
	 * @param idx particle system index
	 * @return prototype particle system
	 */
	inline PrototypeParticleSystem* getParticleSystemAt(int idx) {
		if (idx < 0 || idx >= particleSystems.size()) return nullptr;
		return particleSystems[idx].get();
	}

	/**
	 * Add particle system
	 */
	inline PrototypeParticleSystem* addParticleSystem() {
		particleSystems.push_back(make_unique<PrototypeParticleSystem>());
		return particleSystems[particleSystems.size() - 1].get();
	}

	/**
	 * Remove particle system at given index
	 * @param idx particle system index
	 * @return success
	 */
	inline bool removeParticleSystemAt(int idx) {
		if (idx < 0 || idx >= particleSystems.size()) return false;
		const auto& particleSystem = particleSystems[idx];
		particleSystems.erase(remove(particleSystems.begin(), particleSystems.end(), particleSystem), particleSystems.end());
		return true;
	}

	/**
	 * @return if entity contributes to shadows
	 */
	inline bool isContributesShadows() {
		return contributesShadows;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline void setContributesShadows(bool contributesShadows) {
		this->contributesShadows = contributesShadows;
	}

	/**
	 * @return if entity receives shadows
	 */
	inline bool isReceivesShadows() {
		return receivesShadows;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline void setReceivesShadows(bool receivesShadows) {
		this->receivesShadows = receivesShadows;
	}

	/**
	 * Is terrain mesh
	 * @return terrain mesh
	 */
	inline bool isTerrainMesh() {
		return terrainMesh;
	}

	/**
	 * Set terrain mesh
	 * @param terrainMesh terrain mesh
	 */
	inline void setTerrainMesh(bool terrainMesh) {
		this->terrainMesh = terrainMesh;
	}

	/**
	 * Is using render groups
	 * @return render groups enabled
	 */
	inline bool isRenderGroups() {
		return renderGroups;
	}

	/**
	 * Set using render groups
	 * @param renderGroups use render groups
	 */
	inline void setRenderGroups(bool renderGroups) {
		this->renderGroups = renderGroups;
	}

	/**
	 * Get shader
	 * @return shader id
	 */
	inline const string& getShader() {
		return shaderId;
	}

	/**
	 * Set shader
	 * @param id shader id
	 */
	inline void setShader(const string& id) {
		this->shaderId = id;
		shaderParameters.setShader(id);
	}

	/**
	 * Get shader parameters
	 * @return shader parameters
	 */
	inline const EntityShaderParameters& getShaderParameters() {
		return shaderParameters;
	}

	/**
	 * Set shader parameters
	 * @param parameters shader parameters
	 */
	inline void setShaderParameters(EntityShaderParameters& parameters) {
		shaderParameters = parameters;
	}

	/**
	 * @return sounds iterator
	 */
	inline UniquePtrSequenceIterator<PrototypeAudio> getSounds() {
		return UniquePtrSequenceIterator<PrototypeAudio>(&sounds[0], &sounds[sounds.size()]);
	}

	/**
	 * @return sound count
	 */
	inline int getSoundCount() {
		return sounds.size();
	}

	/**
	 * Get sound at given index
	 * @param idx index
	 * @return prototype sound
	 */
	inline PrototypeAudio* getSoundAt(int idx) {
		return idx >= 0 && idx < sounds.size()?sounds[idx].get():nullptr;
	}

	/**
	 * Returns sound of given sound id
	 */
	inline PrototypeAudio* getSound(const string& id) {
		auto soundIt = soundsById.find(id);
		if (soundIt == soundsById.end()) return nullptr;
		return soundIt->second;
	}

	/**
	 * Add sound with given id
	 * @param id id
	 * @return prototype audio
	 */
	PrototypeAudio* addSound(const string& id);

	/**
	 * Remove sound of given sound id
	 * @param id id
	 */
	inline void removeSound(const string& id) {
		auto soundIt = soundsById.find(id);
		if (soundIt == soundsById.end()) return;
		auto sound = soundIt->second;
		for (auto i = 0; i < sounds.size(); i++) {
			if (sounds[i].get() == sound) {
				sounds.erase(sounds.begin() + i);
				break;
			}
		}
		soundsById.erase(soundIt);
	}

	/**
	 * Renames sound of given sound id with new id
	 * @param id existing id
	 * @param id new id
	 * @return success
	 */
	inline bool renameSound(const string& id, const string& newId) {
		auto soundIt = soundsById.find(id);
		if (soundIt == soundsById.end()) return false;
		auto sound = soundIt->second;
		sound->setId(newId);
		soundsById.erase(soundIt);
		soundsById[newId] = sound;
		return true;
	}

	/**
	 * @return environment map render pass mask
	 */
	inline int getEnvironmentMapRenderPassMask() {
		return environmentMapRenderPassMask;
	}

	/**
	 * Set up environment render pass mask
	 * @param renderPassMask render pass mask
	 */
	inline void setEnvironmentMapRenderPassMask(int renderPassMask) {
		this->environmentMapRenderPassMask = renderPassMask;
	}

	/**
	 * @return environment map render update time frequency in milliseconds
	 */
	inline int64_t getEnvironmentMapTimeRenderUpdateFrequency() {
		return environmentMapTimeRenderUpdateFrequency;
	}

	/**
	 * Set up environment map render update time frequency
	 * @param frequency frequency in milliseconds
	 */
	inline void setEnvironmentMapTimeRenderUpdateFrequency(int64_t frequency) {
		environmentMapTimeRenderUpdateFrequency = frequency;
	}

	/**
	 * @return terrain definitions
	 */
	inline PrototypeTerrain* getTerrain() {
		return terrain.get();
	}

	/**
	 * @return decal definitions
	 */
	inline PrototypeDecal* getDecal() {
		return decal.get();
	}

};
