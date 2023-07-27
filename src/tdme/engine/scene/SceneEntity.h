#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::Transform;

/**
 * Scene entity definition
 * @author Andreas Drewke
 */
class tdme::engine::scene::SceneEntity final
	: public BaseProperties
{
private:
	Transform transform;
	Prototype* prototype { nullptr };
	string reflectionEnvironmentMappingId;

public:
	// forbid class copy
	FORBID_CLASS_COPY(SceneEntity)

	/**
	 * Public constructor
	 * @param id id
	 * @param description description
	 * @param transform transform
	 * @param prototype prototype
	 */
	SceneEntity(const string& id, const string& description, const Transform& transform, Prototype* prototype);

	/**
	 * Destructor
	 */
	~SceneEntity();

	/**
	 * @return id
	 */
	inline const string& getId() {
		return name;
	}

	/**
	 * Set id
	 * @param id id
	 */
	inline void setId(const string& id) {
		this->name = name;
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
	 * @return transform
	 */
	inline Transform& getTransform() {
		return transform;
	}

	/**
	 * @return prototype
	 */
	inline Prototype* getPrototype() {
		return prototype;
	}

	/**
	 * Set up prototype
	 * @param prototype prototype
	 */
	inline void setPrototype(Prototype* prototype) {
		this->prototype = prototype;
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
	const BaseProperties* getTotalProperties();

};
