/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2010-2022 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

// Libraries
#include <reactphysics3d/engine/PhysicsCommon.h>

using namespace reactphysics3d;

// Static variables
Logger* PhysicsCommon::mLogger = nullptr;

/// Constructor
/**
 * @param baseMemoryAllocator Pointer to a user custom memory allocator
 */
PhysicsCommon::PhysicsCommon(MemoryAllocator* baseMemoryAllocator)
              : mMemoryManager(baseMemoryAllocator),
                mPhysicsWorlds(mMemoryManager.getHeapAllocator()), mSphereShapes(mMemoryManager.getHeapAllocator()),
                mBoxShapes(mMemoryManager.getHeapAllocator()), mCapsuleShapes(mMemoryManager.getHeapAllocator()),
                mConvexMeshShapes(mMemoryManager.getHeapAllocator()), mConcaveMeshShapes(mMemoryManager.getHeapAllocator()),
                mHeightFieldShapes(mMemoryManager.getHeapAllocator()), mPolyhedronMeshes(mMemoryManager.getHeapAllocator()),
                mTriangleMeshes(mMemoryManager.getHeapAllocator()),
                mProfilers(mMemoryManager.getHeapAllocator()), mDefaultLoggers(mMemoryManager.getHeapAllocator()),
                mBoxShapeHalfEdgeStructure(mMemoryManager.getHeapAllocator(), 6, 8, 24),
                mTriangleShapeHalfEdgeStructure(mMemoryManager.getHeapAllocator(), 2, 3, 6) {

    init();
}

// Destructor
PhysicsCommon::~PhysicsCommon() {

    // Release the allocated memory
    release();
}

/// Initialization
void PhysicsCommon::init() {

    // Initialize the static half-edge structure for the BoxShape collision shape
    initBoxShapeHalfEdgeStructure();

    // Initialize the static half-edge structure for the TriangleShape collision shape
    initTriangleShapeHalfEdgeStructure();
}

// Initialize the static half-edge structure of a BoxShape
void PhysicsCommon::initBoxShapeHalfEdgeStructure() {

    // Vertices
    mBoxShapeHalfEdgeStructure.addVertex(0);
    mBoxShapeHalfEdgeStructure.addVertex(1);
    mBoxShapeHalfEdgeStructure.addVertex(2);
    mBoxShapeHalfEdgeStructure.addVertex(3);
    mBoxShapeHalfEdgeStructure.addVertex(4);
    mBoxShapeHalfEdgeStructure.addVertex(5);
    mBoxShapeHalfEdgeStructure.addVertex(6);
    mBoxShapeHalfEdgeStructure.addVertex(7);

    MemoryAllocator& allocator = mMemoryManager.getHeapAllocator();

    // Faces
    Array<uint> face0(allocator, 4);
    face0.add(0); face0.add(1); face0.add(2); face0.add(3);
    Array<uint> face1(allocator, 4);
    face1.add(1); face1.add(5); face1.add(6); face1.add(2);
    Array<uint> face2(allocator, 4);
    face2.add(4); face2.add(7); face2.add(6); face2.add(5);
    Array<uint> face3(allocator, 4);
    face3.add(4); face3.add(0); face3.add(3); face3.add(7);
    Array<uint> face4(allocator, 4);
    face4.add(4); face4.add(5); face4.add(1); face4.add(0);
    Array<uint> face5(allocator, 4);
    face5.add(2); face5.add(6); face5.add(7); face5.add(3);

    mBoxShapeHalfEdgeStructure.addFace(face0);
    mBoxShapeHalfEdgeStructure.addFace(face1);
    mBoxShapeHalfEdgeStructure.addFace(face2);
    mBoxShapeHalfEdgeStructure.addFace(face3);
    mBoxShapeHalfEdgeStructure.addFace(face4);
    mBoxShapeHalfEdgeStructure.addFace(face5);

    mBoxShapeHalfEdgeStructure.init();
}

// Initialize the static half-edge structure of a TriangleShape
void PhysicsCommon::initTriangleShapeHalfEdgeStructure() {

    // Vertices
    mTriangleShapeHalfEdgeStructure.addVertex(0);
    mTriangleShapeHalfEdgeStructure.addVertex(1);
    mTriangleShapeHalfEdgeStructure.addVertex(2);

    MemoryAllocator& allocator = mMemoryManager.getHeapAllocator();

    // Faces
    Array<uint> face0(allocator, 3);
    face0.add(0); face0.add(1); face0.add(2);
    Array<uint> face1(allocator, 3);
    face1.add(0); face1.add(2); face1.add(1);

    mTriangleShapeHalfEdgeStructure.addFace(face0);
    mTriangleShapeHalfEdgeStructure.addFace(face1);

    mTriangleShapeHalfEdgeStructure.init();
}

// Destroy and release everything that has been allocated
void PhysicsCommon::release() {

    // Destroy the physics worlds
    for (auto it = mPhysicsWorlds.begin(); it != mPhysicsWorlds.end(); ++it) {
        deletePhysicsWorld(*it);
    }
    mPhysicsWorlds.clear();

    // Destroy the sphere shapes
    for (auto it = mSphereShapes.begin(); it != mSphereShapes.end(); ++it) {
        deleteSphereShape(*it);
    }
    mSphereShapes.clear();

    // Destroy the box shapes
    for (auto it = mBoxShapes.begin(); it != mBoxShapes.end(); ++it) {
        deleteBoxShape(*it);
    }
    mBoxShapes.clear();

    // Destroy the capsule shapes
    for (auto it = mCapsuleShapes.begin(); it != mCapsuleShapes.end(); ++it) {
        deleteCapsuleShape(*it);
    }
    mCapsuleShapes.clear();

    // Destroy the convex mesh shapes
    for (auto it = mConvexMeshShapes.begin(); it != mConvexMeshShapes.end(); ++it) {
        deleteConvexMeshShape(*it);
    }
    mConvexMeshShapes.clear();

    // Destroy the heigh-field shapes
    for (auto it = mHeightFieldShapes.begin(); it != mHeightFieldShapes.end(); ++it) {
        deleteHeightFieldShape(*it);
    }
    mHeightFieldShapes.clear();

    // Destroy the concave mesh shapes
    for (auto it = mConcaveMeshShapes.begin(); it != mConcaveMeshShapes.end(); ++it) {
        deleteConcaveMeshShape(*it);
    }
    mConcaveMeshShapes.clear();

    // Destroy the polyhedron mesh
    for (auto it = mPolyhedronMeshes.begin(); it != mPolyhedronMeshes.end(); ++it) {
        deletePolyhedronMesh(*it);
    }
    mPolyhedronMeshes.clear();

    // Destroy the triangle mesh
    for (auto it = mTriangleMeshes.begin(); it != mTriangleMeshes.end(); ++it) {
        deleteTriangleMesh(*it);
    }
    mTriangleMeshes.clear();

    // Destroy the default loggers
    for (auto it = mDefaultLoggers.begin(); it != mDefaultLoggers.end(); ++it) {
        deleteDefaultLogger(*it);
    }
    mDefaultLoggers.clear();

// If profiling is enabled
#ifdef IS_RP3D_PROFILING_ENABLED


    // Destroy the profilers
    for (auto it = mProfilers.begin(); it != mProfilers.end(); ++it) {
        deleteProfiler(*it);
    }
    mProfilers.clear();

#endif

}

// Create and return an instance of PhysicsWorld
/**
 * @param worldSettings The settings of the physics world
 * @return A pointer to the created physics world
 */
PhysicsWorld* PhysicsCommon::createPhysicsWorld(const PhysicsWorld::WorldSettings& worldSettings) {

    Profiler* profiler = nullptr;

#ifdef IS_RP3D_PROFILING_ENABLED


    profiler = createProfiler();

    // Add a destination file for the profiling data
    profiler->addFileDestination("rp3d_profiling_" + worldSettings.worldName + ".txt", Profiler::Format::Text);

#endif

    PhysicsWorld* world = new(mMemoryManager.allocate(MemoryManager::AllocationType::Heap, sizeof(PhysicsWorld))) PhysicsWorld(mMemoryManager, *this, worldSettings, profiler);

    mPhysicsWorlds.add(world);

    return world;
}

// Destroy an instance of PhysicsWorld
/**
 * @param world A pointer to the physics world to destroy
 */
void PhysicsCommon::destroyPhysicsWorld(PhysicsWorld* world) {

   deletePhysicsWorld(world);

   mPhysicsWorlds.remove(world);
}

// Delete an instance of PhysicsWorld
/**
 * @param world A pointer to the physics world to destroy
 */
void PhysicsCommon::deletePhysicsWorld(PhysicsWorld* world) {

   // Call the destructor of the world
   world->~PhysicsWorld();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Heap, world, sizeof(PhysicsWorld));
}

// Create and return a sphere collision shape
/**
 * @param radius The radius of the sphere collision shape
 * @return A pointer to the created sphere shape
 */
SphereShape* PhysicsCommon::createSphereShape(const decimal radius) {

    if (radius <= decimal(0.0)) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when creating a SphereShape: radius must be a positive value",  __FILE__, __LINE__);
    }

    SphereShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(SphereShape))) SphereShape(radius, mMemoryManager.getHeapAllocator());
    mSphereShapes.add(shape);

    return shape;
}

// Destroy a sphere collision shape
/**
 * @param sphereShape A pointer to the sphere collision shape to destroy
 */
void PhysicsCommon::destroySphereShape(SphereShape* sphereShape) {

    deleteSphereShape(sphereShape);

    mSphereShapes.remove(sphereShape);
}

// Delete a sphere collision shape
/**
 * @param sphereShape A pointer to the sphere collision shape to destroy
 */
void PhysicsCommon::deleteSphereShape(SphereShape* sphereShape) {

    // If the shape is still part of some colliders
    if (sphereShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the SphereShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   sphereShape->~SphereShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, sphereShape, sizeof(SphereShape));
}

// Create and return a box collision shape
/**
 * @param halfExtents A vector with the three half-extents of the box shape
 * @return A pointer to the created box shape
 */
BoxShape* PhysicsCommon::createBoxShape(const Vector3& halfExtents) {

    if (halfExtents.x <= decimal(0.0) || halfExtents.y <= decimal(0.0) || halfExtents.z <= decimal(0.0)) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when creating a BoxShape: the half extents must be positive values",  __FILE__, __LINE__);
    }
    BoxShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(BoxShape))) BoxShape(halfExtents, mMemoryManager.getHeapAllocator(), *this);

    mBoxShapes.add(shape);

    return shape;
}

// Destroy a box collision shape
/**
 * @param boxShape A pointer to the box shape to destroy
 */
void PhysicsCommon::destroyBoxShape(BoxShape* boxShape) {

    deleteBoxShape(boxShape);

    mBoxShapes.remove(boxShape);
}

// Delete a box collision shape
/**
 * @param boxShape A pointer to the box shape to destroy
 */
void PhysicsCommon::deleteBoxShape(BoxShape* boxShape) {

    // If the shape is still part of some colliders
    if (boxShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the BoxShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   boxShape->~BoxShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, boxShape, sizeof(BoxShape));
}

// Create and return a capsule shape
/**
 * @param radius The radius of the sphere of the capsule shape
 * @param height The height of the capsule shape (distance betwen the two spheres centers)
 * @return boxShape A pointer to the created capsule shape
 */
CapsuleShape* PhysicsCommon::createCapsuleShape(decimal radius, decimal height) {

    if (radius <= decimal(0.0)) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when creating a CapsuleShape: radius must be a positive value",  __FILE__, __LINE__);
    }

    if (height <= decimal(0.0)) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when creating a CapsuleShape: height must be a positive value",  __FILE__, __LINE__);
    }

    CapsuleShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(CapsuleShape))) CapsuleShape(radius, height, mMemoryManager.getHeapAllocator());

    mCapsuleShapes.add(shape);

    return shape;
}

// Destroy a capsule collision shape
/**
 * @param capsuleShape A pointer to the capsule shape to destroy
 */
void PhysicsCommon::destroyCapsuleShape(CapsuleShape* capsuleShape) {

    deleteCapsuleShape(capsuleShape);

    mCapsuleShapes.remove(capsuleShape);
}

// Delete a capsule collision shape
/**
 * @param capsuleShape A pointer to the capsule shape to destroy
 */
void PhysicsCommon::deleteCapsuleShape(CapsuleShape* capsuleShape) {

    // If the shape is still part of some colliders
    if (capsuleShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the CapsuleShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   capsuleShape->~CapsuleShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, capsuleShape, sizeof(CapsuleShape));
}

// Create and return a convex mesh shape
/**
 * @param polyhedronMesh A pointer to the polyhedron mesh used to create the convex shape
 * @param scaling Scaling factor to scale the polyhedron mesh if necessary
 * @return A pointer to the created convex mesh shape
 */
ConvexMeshShape* PhysicsCommon::createConvexMeshShape(PolyhedronMesh* polyhedronMesh, const Vector3& scaling) {

    ConvexMeshShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(ConvexMeshShape))) ConvexMeshShape(polyhedronMesh, mMemoryManager.getHeapAllocator(), scaling);

    mConvexMeshShapes.add(shape);

    return shape;
}

// Destroy a convex mesh shape
/**
 * @param convexMeshShape A pointer to the convex mesh shape to destroy
 */
void PhysicsCommon::destroyConvexMeshShape(ConvexMeshShape* convexMeshShape) {

    deleteConvexMeshShape(convexMeshShape);

    mConvexMeshShapes.remove(convexMeshShape);
}

// Delete a convex mesh shape
/**
 * @param convexMeshShape A pointer to the convex mesh shape to destroy
 */
void PhysicsCommon::deleteConvexMeshShape(ConvexMeshShape* convexMeshShape) {

    // If the shape is still part of some colliders
    if (convexMeshShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the ConvexMeshShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   convexMeshShape->~ConvexMeshShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, convexMeshShape, sizeof(ConvexMeshShape));
}

// Create and return a height-field shape
/**
 * @param nbGridColumns Number of columns in the grid of the height field
 * @param nbGridRows Number of rows in the grid of the height field
 * @param minHeight Minimum height value of the height field
 * @param maxHeight Maximum height value of the height field
 * @param heightFieldData Pointer to the first height value data (note that values are shared and not copied)
 * @param dataType Data type for the height values (int, float, double)
 * @param upAxis Integer representing the up axis direction (0 for x, 1 for y and 2 for z)
 * @param integerHeightScale Scaling factor used to scale the height values (only when height values type is integer)
 * @return A pointer to the created height field shape
 */
HeightFieldShape* PhysicsCommon::createHeightFieldShape(int nbGridColumns, int nbGridRows, decimal minHeight, decimal maxHeight,
                                         const void* heightFieldData, HeightFieldShape::HeightDataType dataType,
                                         int upAxis, decimal integerHeightScale, const Vector3& scaling) {

    HeightFieldShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(HeightFieldShape))) HeightFieldShape(nbGridColumns, nbGridRows, minHeight, maxHeight,
                                         heightFieldData, dataType, mMemoryManager.getHeapAllocator(), mTriangleShapeHalfEdgeStructure, upAxis, integerHeightScale, scaling);

    mHeightFieldShapes.add(shape);

    return shape;
}

// Destroy a height-field shape
/**
 * @param heightFieldShape A pointer to the height field shape to destroy
 */
void PhysicsCommon::destroyHeightFieldShape(HeightFieldShape* heightFieldShape) {

    deleteHeightFieldShape(heightFieldShape);

    mHeightFieldShapes.remove(heightFieldShape);
}

// Delete a height-field shape
/**
 * @param heightFieldShape A pointer to the height field shape to destroy
 */
void PhysicsCommon::deleteHeightFieldShape(HeightFieldShape* heightFieldShape) {

    // If the shape is still part of some colliders
    if (heightFieldShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the HeightFieldShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   heightFieldShape->~HeightFieldShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, heightFieldShape, sizeof(HeightFieldShape));
}

// Create and return a concave mesh shape
/**
 * @param triangleMesh A pointer to the triangle mesh to use to create the concave mesh shape
 * @param scaling An optional scaling factor to scale the triangle mesh
 * @return A pointer to the created concave mesh shape
 */
ConcaveMeshShape* PhysicsCommon::createConcaveMeshShape(TriangleMesh* triangleMesh, const Vector3& scaling) {

    ConcaveMeshShape* shape = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(ConcaveMeshShape))) ConcaveMeshShape(triangleMesh,
                                                                                                                                            mMemoryManager.getHeapAllocator(), mTriangleShapeHalfEdgeStructure, scaling);

    mConcaveMeshShapes.add(shape);

    return shape;
}

// Destroy a concave mesh shape
/**
 * @param concaveMeshShape A pointer to the concave mesh shape to destroy
 */
void PhysicsCommon::destroyConcaveMeshShape(ConcaveMeshShape* concaveMeshShape) {

    deleteConcaveMeshShape(concaveMeshShape);

    mConcaveMeshShapes.remove(concaveMeshShape);
}

// Delete a concave mesh shape
/**
 * @param concaveMeshShape A pointer to the concave mesh shape to destroy
 */
void PhysicsCommon::deleteConcaveMeshShape(ConcaveMeshShape* concaveMeshShape) {

    // If the shape is still part of some colliders
    if (concaveMeshShape->mColliders.size() > 0) {

        RP3D_LOG("PhysicsCommon", Logger::Level::Error, Logger::Category::PhysicCommon,
                 "Error when destroying the ConcaveMeshShape because it is still used by some colliders",  __FILE__, __LINE__);
    }

   // Call the destructor of the shape
   concaveMeshShape->~ConcaveMeshShape();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, concaveMeshShape, sizeof(ConcaveMeshShape));
}

// Create a polyhedron mesh
/**
 * @param polygonVertexArray A pointer to the polygon vertex array to use to create the polyhedron mesh
 * @return A pointer to the created polyhedron mesh or nullptr if the mesh is not valid
 */
PolyhedronMesh* PhysicsCommon::createPolyhedronMesh(PolygonVertexArray* polygonVertexArray) {

    // Create the polyhedron mesh
    PolyhedronMesh* mesh = PolyhedronMesh::create(polygonVertexArray, mMemoryManager.getPoolAllocator(), mMemoryManager.getHeapAllocator());

    // If the mesh is valid
    if (mesh != nullptr) {

        mPolyhedronMeshes.add(mesh);
    }

    return mesh;
}

// Destroy a polyhedron mesh
/**
 * @param polyhedronMesh A pointer to the polyhedron mesh to destroy
 */
void PhysicsCommon::destroyPolyhedronMesh(PolyhedronMesh* polyhedronMesh) {

    deletePolyhedronMesh(polyhedronMesh);

    mPolyhedronMeshes.remove(polyhedronMesh);
}

// Delete a polyhedron mesh
/**
 * @param polyhedronMesh A pointer to the polyhedron mesh to destroy
 */
void PhysicsCommon::deletePolyhedronMesh(PolyhedronMesh* polyhedronMesh) {

   // Call the destructor of the shape
   polyhedronMesh->~PolyhedronMesh();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, polyhedronMesh, sizeof(PolyhedronMesh));
}

// Create a triangle mesh
/**
 * @return A pointer to the created triangle mesh
 */
TriangleMesh* PhysicsCommon::createTriangleMesh() {

    TriangleMesh* mesh = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(TriangleMesh))) TriangleMesh(mMemoryManager.getHeapAllocator());

    mTriangleMeshes.add(mesh);

    return mesh;
}

// Destroy a triangle mesh
/**
 * @param A pointer to the triangle mesh to destroy
 */
void PhysicsCommon::destroyTriangleMesh(TriangleMesh* triangleMesh) {

    deleteTriangleMesh(triangleMesh);

    mTriangleMeshes.remove(triangleMesh);
}

// Delete a triangle mesh
/**
 * @param A pointer to the triangle mesh to destroy
 */
void PhysicsCommon::deleteTriangleMesh(TriangleMesh* triangleMesh) {

   // Call the destructor of the shape
   triangleMesh->~TriangleMesh();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, triangleMesh, sizeof(TriangleMesh));
}

// Create and return a new logger
/**
 * @return A pointer to the created default logger
 */
DefaultLogger* PhysicsCommon::createDefaultLogger() {

    DefaultLogger* logger = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(DefaultLogger))) DefaultLogger(mMemoryManager.getHeapAllocator());

    mDefaultLoggers.add(logger);

    return logger;
}

// Destroy a logger
/**
 * @param A pointer to the default logger to destroy
 */
void PhysicsCommon::destroyDefaultLogger(DefaultLogger* logger) {

    deleteDefaultLogger(logger);

    mDefaultLoggers.remove(logger);
}

// Delete a logger
/**
 * @param A pointer to the default logger to destroy
 */
void PhysicsCommon::deleteDefaultLogger(DefaultLogger* logger) {

   // Call the destructor of the logger
   logger->~DefaultLogger();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, logger, sizeof(DefaultLogger));
}

// If profiling is enabled
#ifdef IS_RP3D_PROFILING_ENABLED


// Create and return a new profiler
/// Note that you need to use a different profiler for each PhysicsWorld.
Profiler* PhysicsCommon::createProfiler() {

    Profiler* profiler = new (mMemoryManager.allocate(MemoryManager::AllocationType::Pool, sizeof(Profiler))) Profiler();

    mProfilers.add(profiler);

    return profiler;
}

// Destroy a profiler
void PhysicsCommon::destroyProfiler(Profiler* profiler) {

    deleteProfiler(profiler);

    mProfilers.remove(profiler);
}

// Delete a profiler
void PhysicsCommon::deleteProfiler(Profiler* profiler) {

   // Call the destructor of the profiler
   profiler->~Profiler();

   // Release allocated memory
   mMemoryManager.release(MemoryManager::AllocationType::Pool, profiler, sizeof(Profiler));
}
#endif
