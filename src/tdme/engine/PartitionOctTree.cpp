// Generated from /tdme/src/tdme/engine/PartitionOctTree.java
#include <tdme/engine/PartitionOctTree.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/PartitionOctTree_reset_1.h>
#include <tdme/engine/PartitionOctTree_reset_2.h>
#include <tdme/engine/PartitionOctTree_reset_3.h>
#include <tdme/engine/PartitionOctTree_reset_4.h>
#include <tdme/engine/PartitionOctTree_reset_5.h>
#include <tdme/engine/PartitionOctTree_reset_6.h>
#include <tdme/engine/PartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>
#include <tdme/utils/Key.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>

using tdme::engine::PartitionOctTree;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::PartitionOctTree_reset_1;
using tdme::engine::PartitionOctTree_reset_2;
using tdme::engine::PartitionOctTree_reset_3;
using tdme::engine::PartitionOctTree_reset_4;
using tdme::engine::PartitionOctTree_reset_5;
using tdme::engine::PartitionOctTree_reset_6;
using tdme::engine::PartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::Key;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

PartitionOctTree::PartitionOctTree(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PartitionOctTree::PartitionOctTree() 
	: PartitionOctTree(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void PartitionOctTree::init()
{
	treeRoot = nullptr;
}

constexpr float PartitionOctTree::PARTITION_SIZE_MIN;

constexpr float PartitionOctTree::PARTITION_SIZE_MID;

constexpr float PartitionOctTree::PARTITION_SIZE_MAX;

void PartitionOctTree::ctor()
{
	super::ctor();
	init();
	this->key = new Key();
	this->entityIterator = new ArrayListIteratorMultiple();
	this->boundingBox = new BoundingBox();
	this->halfExtension = new Vector3();
	this->sideVector = new Vector3(1.0f, 0.0f, 0.0f);
	this->upVector = new Vector3(0.0f, 1.0f, 0.0f);
	this->forwardVector = new Vector3(0.0f, 0.0f, 1.0f);
	reset();
}

void PartitionOctTree::reset()
{
	this->entityPartitionNodesPool = new PartitionOctTree_reset_1(this);
	this->boundingBoxPool = new PartitionOctTree_reset_2(this);
	this->partitionTreeNodePool = new PartitionOctTree_reset_3(this);
	this->subNodesPool = new PartitionOctTree_reset_4(this);
	this->partitionEntitiesPool = new PartitionOctTree_reset_5(this);
	this->keyPool = new PartitionOctTree_reset_6(this);
	this->entityPartitionNodes = new _HashMap();
	this->visibleEntities = new _ArrayList();
	this->treeRoot = new PartitionOctTree_PartitionTreeNode();
	this->treeRoot->partitionSize = -1;
	this->treeRoot->x = -1;
	this->treeRoot->y = -1;
	this->treeRoot->z = -1;
	this->treeRoot->parent = nullptr;
	this->treeRoot->bv = nullptr;
	this->treeRoot->subNodes = new _ArrayList();
	this->treeRoot->subNodesByCoordinate = new _HashMap();
	this->treeRoot->partitionEntities = nullptr;
}

PartitionOctTree_PartitionTreeNode* PartitionOctTree::createPartition(PartitionOctTree_PartitionTreeNode* parent, int32_t x, int32_t y, int32_t z, float partitionSize)
{
	auto node = java_cast< PartitionOctTree_PartitionTreeNode* >(partitionTreeNodePool->allocate());
	node->partitionSize = partitionSize;
	node->x = x;
	node->y = y;
	node->z = z;
	node->parent = parent;
	node->bv = java_cast< BoundingBox* >(boundingBoxPool->allocate());
	node->bv->getMin()->set(x * partitionSize, y * partitionSize, z * partitionSize);
	node->bv->getMax()->set(x * partitionSize + partitionSize, y * partitionSize + partitionSize, z * partitionSize + partitionSize);
	node->bv->update();
	node->subNodes = nullptr;
	node->subNodesByCoordinate = nullptr;
	node->partitionEntities = nullptr;
	if (parent->subNodes == nullptr) {
		parent->subNodes = java_cast< _ArrayList* >(subNodesPool->allocate());
	}
	parent->subNodes->add(node);
	if (parent == treeRoot) {
		auto key = java_cast< Key* >(keyPool->allocate());
		key->reset();
		key->append(node->x);
		key->append(u","_j);
		key->append(node->y);
		key->append(u","_j);
		key->append(node->z);
		parent->subNodesByCoordinate->put(key, node);
	}
	if (partitionSize > PARTITION_SIZE_MIN) {
		for (auto _y = 0; _y < 2; _y++) 
						for (auto _x = 0; _x < 2; _x++) 
								for (auto _z = 0; _z < 2; _z++) {
					createPartition(node, static_cast< int32_t >(((x * partitionSize) / (partitionSize / 2.0f))) + _x, static_cast< int32_t >(((y * partitionSize) / (partitionSize / 2.0f))) + _y, static_cast< int32_t >(((z * partitionSize) / (partitionSize / 2.0f))) + _z, partitionSize / 2.0f);
				}


	} else {
		node->partitionEntities = java_cast< _ArrayList* >(partitionEntitiesPool->allocate());
	}
	return node;
}

void PartitionOctTree::addEntity(Entity* entity)
{
	auto thisEntityPartitions = java_cast< _ArrayList* >(entityPartitionNodes->get(entity->getId()));
	if (thisEntityPartitions != nullptr && thisEntityPartitions->isEmpty() == false) {
		removeEntity(entity);
	}
	auto boundingBox = entity->getBoundingBoxTransformed();
	auto minXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getX() / PARTITION_SIZE_MAX));
	auto minYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getY() / PARTITION_SIZE_MAX));
	auto minZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMin()->getZ() / PARTITION_SIZE_MAX));
	auto maxXPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getX() / PARTITION_SIZE_MAX));
	auto maxYPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getY() / PARTITION_SIZE_MAX));
	auto maxZPartition = static_cast< int32_t >(Math::floor(boundingBox->getMax()->getZ() / PARTITION_SIZE_MAX));
	for (auto yPartition = minYPartition; yPartition <= maxYPartition; yPartition++) 
				for (auto xPartition = minXPartition; xPartition <= maxXPartition; xPartition++) 
						for (auto zPartition = minZPartition; zPartition <= maxZPartition; zPartition++) {
				key->reset();
				key->append(xPartition);
				key->append(u","_j);
				key->append(yPartition);
				key->append(u","_j);
				key->append(zPartition);
				auto node = java_cast< PartitionOctTree_PartitionTreeNode* >(treeRoot->subNodesByCoordinate->get(key));
				if (node == nullptr) {
					node = createPartition(treeRoot, xPartition, yPartition, zPartition, PARTITION_SIZE_MAX);
				}
			}


	addToPartitionTree(entity, boundingBox);
}

void PartitionOctTree::updateEntity(Entity* entity)
{
	addEntity(entity);
}

void PartitionOctTree::removeEntity(Entity* entity)
{
	auto objectPartitionsVector = java_cast< _ArrayList* >(entityPartitionNodes->remove(entity->getId()));
	if (objectPartitionsVector == nullptr || objectPartitionsVector->isEmpty() == true) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"PartitionOctTree::removeEntity(): '"_j)->append(entity->getId())
			->append(u"' not registered"_j)->toString()));
		return;
	}
	while (objectPartitionsVector->size() > 0) {
		auto lastIdx = objectPartitionsVector->size() - 1;
		auto partitionTreeNode = java_cast< PartitionOctTree_PartitionTreeNode* >(objectPartitionsVector->get(lastIdx));
		auto partitionObjects = partitionTreeNode->partitionEntities;
		partitionObjects->remove(static_cast< Object* >(entity));
		objectPartitionsVector->remove(lastIdx);
		if (partitionObjects->isEmpty() == true) {
			auto rootPartitionTreeNode = partitionTreeNode->parent->parent;
			if (isPartitionNodeEmpty(rootPartitionTreeNode) == true) {
				removePartitionNode(rootPartitionTreeNode);
				treeRoot->subNodes->remove(static_cast< Object* >(rootPartitionTreeNode));
				key->reset();
				key->append(rootPartitionTreeNode->x);
				key->append(u","_j);
				key->append(rootPartitionTreeNode->y);
				key->append(u","_j);
				key->append(rootPartitionTreeNode->z);
				keyPool->release(java_cast< Key* >(treeRoot->subNodesByCoordinate->getKey(key)));
				treeRoot->subNodesByCoordinate->remove(key);
			}
		}
	}
	entityPartitionNodesPool->release(objectPartitionsVector);
}

bool PartitionOctTree::isPartitionNodeEmpty(PartitionOctTree_PartitionTreeNode* node)
{
	if (node->partitionEntities != nullptr) {
		return node->partitionEntities->size() == 0;
	} else {
		for (auto i = 0; i < node->subNodes->size(); i++) {
			if (isPartitionNodeEmpty(java_cast< PartitionOctTree_PartitionTreeNode* >(node->subNodes->get(i))) == false)
				return false;

		}
		return true;
	}
}

void PartitionOctTree::removePartitionNode(PartitionOctTree_PartitionTreeNode* node)
{
	if (node->partitionEntities != nullptr) {
		if (node->partitionEntities->size() > 0) {
			_Console::println(static_cast< Object* >(u"PartitionOctTree::removePartitionNode(): partition has objects attached!!!"_j));
			node->partitionEntities->clear();
		}
		partitionEntitiesPool->release(node->partitionEntities);
		node->partitionEntities = nullptr;
	} else {
		for (auto i = 0; i < node->subNodes->size(); i++) {
			auto subNode = java_cast< PartitionOctTree_PartitionTreeNode* >(node->subNodes->get(i));
			removePartitionNode(subNode);
		}
		node->subNodes->clear();
		subNodesPool->release(node->subNodes);
		node->subNodes = nullptr;
	}
	boundingBoxPool->release(node->bv);
	node->bv = nullptr;
	partitionTreeNodePool->release(node);
}

int32_t PartitionOctTree::doPartitionTreeLookUpVisibleObjects(Frustum* frustum, PartitionOctTree_PartitionTreeNode* node, _ArrayList* visibleEntities)
{
	auto lookUps = 1;
	if (frustum->isVisible(node->bv) == false) {
		return lookUps;
	}
	if (node->partitionEntities != nullptr) {
		for (auto i = 0; i < node->partitionEntities->size(); i++) {
			auto entity = java_cast< Entity* >(node->partitionEntities->get(i));
			auto hasEntity = false;
			for (auto j = 0; j < visibleEntities->size(); j++) {
				if (java_cast< Entity* >(visibleEntities->get(j)) == entity) {
					hasEntity = true;
					break;
				}
			}
			if (hasEntity == true)
				continue;

			lookUps++;
			if (frustum->isVisible(entity->getBoundingBoxTransformed()) == false)
				continue;

			visibleEntities->add(entity);
		}
		return lookUps;
	} else if (node->subNodes != nullptr) {
		for (auto i = 0; i < node->subNodes->size(); i++) {
			lookUps += doPartitionTreeLookUpVisibleObjects(frustum, java_cast< PartitionOctTree_PartitionTreeNode* >(node->subNodes->get(i)), visibleEntities);
		}
		return lookUps;
	}
	return lookUps;
}

_ArrayList* PartitionOctTree::getVisibleEntities(Frustum* frustum)
{
	visibleEntities->clear();
	auto lookUps = 0;
	for (auto i = 0; i < treeRoot->subNodes->size(); i++) {
		lookUps += doPartitionTreeLookUpVisibleObjects(frustum, java_cast< PartitionOctTree_PartitionTreeNode* >(treeRoot->subNodes->get(i)), visibleEntities);
	}
	return visibleEntities;
}

void PartitionOctTree::addToPartitionTree(PartitionOctTree_PartitionTreeNode* node, Entity* entity, BoundingBox* cbv)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(node->bv, cbv) == false) {
		return;
	}
	if (node->partitionEntities != nullptr) {
		node->partitionEntities->add(entity);
		auto objectPartitionNodesVector = java_cast< _ArrayList* >(entityPartitionNodes->get(entity->getId()));
		if (objectPartitionNodesVector == nullptr) {
			objectPartitionNodesVector = java_cast< _ArrayList* >(entityPartitionNodesPool->allocate());
			entityPartitionNodes->put(entity->getId(), objectPartitionNodesVector);
		}
		objectPartitionNodesVector->add(node);
	} else if (node->subNodes != nullptr) {
		for (auto i = 0; i < node->subNodes->size(); i++) {
			addToPartitionTree(java_cast< PartitionOctTree_PartitionTreeNode* >(node->subNodes->get(i)), entity, cbv);
		}
	}
}

void PartitionOctTree::addToPartitionTree(Entity* entity, BoundingBox* cbv)
{
	for (auto i = 0; i < treeRoot->subNodes->size(); i++) {
		addToPartitionTree(java_cast< PartitionOctTree_PartitionTreeNode* >(treeRoot->subNodes->get(i)), entity, cbv);
	}
}

int32_t PartitionOctTree::doPartitionTreeLookUpNearEntities(PartitionOctTree_PartitionTreeNode* node, BoundingBox* cbv, ArrayListIteratorMultiple* entityIterator)
{
	if (CollisionDetection::doCollideAABBvsAABBFast(cbv, node->bv) == false) {
		return 1;
	}
	if (node->partitionEntities != nullptr) {
		entityIterator->addArrayList(node->partitionEntities);
		return 1;
	} else {
		auto lookUps = 1;
		for (auto i = 0; i < node->subNodes->size(); i++) {
			lookUps += doPartitionTreeLookUpNearEntities(java_cast< PartitionOctTree_PartitionTreeNode* >(node->subNodes->get(i)), cbv, entityIterator);
		}
		return lookUps;
	}
}

ArrayListIteratorMultiple* PartitionOctTree::getObjectsNearTo(BoundingVolume* cbv)
{
	auto center = cbv->getCenter();
	halfExtension->set(cbv->computeDimensionOnAxis(sideVector) + 0.2f, cbv->computeDimensionOnAxis(upVector) + 0.2f, cbv->computeDimensionOnAxis(forwardVector) + 0.2f)->scale(0.5f);
	boundingBox->getMin()->set(center);
	boundingBox->getMin()->sub(halfExtension);
	boundingBox->getMax()->set(center);
	boundingBox->getMax()->add(halfExtension);
	boundingBox->update();
	entityIterator->clear();
	auto lookUps = 0;
	for (auto i = 0; i < treeRoot->subNodes->size(); i++) {
		lookUps += doPartitionTreeLookUpNearEntities(java_cast< PartitionOctTree_PartitionTreeNode* >(treeRoot->subNodes->get(i)), boundingBox, entityIterator);
	}
	return entityIterator;
}

ArrayListIteratorMultiple* PartitionOctTree::getObjectsNearTo(Vector3* center)
{
	halfExtension->set(0.2f, 0.2f, 0.2f)->scale(0.5f);
	boundingBox->getMin()->set(center);
	boundingBox->getMin()->sub(halfExtension);
	boundingBox->getMax()->set(center);
	boundingBox->getMax()->add(halfExtension);
	boundingBox->update();
	entityIterator->clear();
	auto lookUps = 0;
	for (auto i = 0; i < treeRoot->subNodes->size(); i++) {
		lookUps += doPartitionTreeLookUpNearEntities(java_cast< PartitionOctTree_PartitionTreeNode* >(treeRoot->subNodes->get(i)), boundingBox, entityIterator);
	}
	return entityIterator;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionOctTree::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.PartitionOctTree", 28);
    return c;
}

java::lang::Class* PartitionOctTree::getClass0()
{
	return class_();
}

