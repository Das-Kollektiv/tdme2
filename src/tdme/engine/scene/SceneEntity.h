#pragma once

#include <string>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/prototype/PrototypeProperties.h>

using std::string;

using tdme::engine::prototype::PrototypeProperties;
using tdme::engine::Transformations;
using tdme::engine::prototype::Prototype;

/**
 * Level Editor Object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::scene::SceneEntity final
	: public PrototypeProperties
{
private:
	string id;
	string description;
	Transformations transformations;
	Prototype* entity { nullptr };
	string reflectionEnvironmentMappingId;

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param description description
	 * @param transformations transformations
	 * @param entity entity
	 */
	SceneEntity(const string& id, const string& description, const Transformations& transformations, Prototype* entity);

	/**
	 * Destructor
	 */
	~SceneEntity();

	/**
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Set id
	 * @param id id
	 */
	inline void setId(const string& id) {
		this->id = id;
	}

	/**
	 * @return description
	 */
	inline const string& getDescription() {
		return description;
	}

	/**
	 * Set description
	 * @param description description
	 */
	inline void setDescription(const string& description) {
		this->description = description;
	}

	/**
	 * @return transformations
	 */
	inline Transformations& getTransformations() {
		return transformations;
	}

	/**
	 * @return entity
	 */
	inline Prototype* getEntity() {
		return entity;
	}

	/**
	 * Set up entity
	 * @param entity entity
	 */
	inline void setEntity(Prototype* entity) {
		this->entity = entity;
	}

	/**
	 * @return reflection environment mapping id
	 */
	inline const string& getReflectionEnvironmentMappingId() {
		return reflectionEnvironmentMappingId;
	}

	/**
	 * @return reflection environment mapping id
	 */
	inline void setReflectionEnvironmentMappingId(const string& reflectionEnvironmentMappingId) {
		this->reflectionEnvironmentMappingId = reflectionEnvironmentMappingId;
	}

	/**
	 * @return merged properties from entity and object
	 */
	PrototypeProperties* getTotalProperties();

};
