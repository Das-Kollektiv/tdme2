// Generated from /tdme/src/tdme/engine/PartitionNone.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Partition.h>

using tdme::engine::Partition;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * PartitionQuadTree none implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::PartitionNone final
	: public Partition
{

public:
	typedef Partition super;

private:
	_ArrayList* entities {  };
	ArrayListIteratorMultiple* arrayListIteratorMultiple {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

public: /* protected */
	void reset() override;
	void addEntity(Entity* entity) override;
	void updateEntity(Entity* entity) override;
	void removeEntity(Entity* entity) override;

public:
	_ArrayList* getVisibleEntities(Frustum* frustum) override;
	ArrayListIteratorMultiple* getObjectsNearTo(BoundingVolume* cbv) override;
	ArrayListIteratorMultiple* getObjectsNearTo(Vector3* center) override;

	// Generated
	PartitionNone();
protected:
	PartitionNone(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
