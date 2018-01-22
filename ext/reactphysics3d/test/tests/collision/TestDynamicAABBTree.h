/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2010-2016 Daniel Chappuis                                       *
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

#ifndef TEST_DYNAMIC_AABB_TREE_H
#define TEST_DYNAMIC_AABB_TREE_H

// Libraries
#include "Test.h"
#include "collision/broadphase/DynamicAABBTree.h"
#include <vector>

/// Reactphysics3D namespace
namespace reactphysics3d {

class TestOverlapCallback : public DynamicAABBTreeOverlapCallback {

    public :

        std::vector<int> mOverlapNodes;

        // Called when a overlapping node has been found during the call to
        // DynamicAABBTree:reportAllShapesOverlappingWithAABB()
        virtual void notifyOverlappingNode(int nodeId) override {
            mOverlapNodes.push_back(nodeId);
        }

        void reset() {
            mOverlapNodes.clear();
        }

        bool isOverlapping(int nodeId) const {
            return std::find(mOverlapNodes.begin(), mOverlapNodes.end(), nodeId) != mOverlapNodes.end();
        }
};

class DynamicTreeRaycastCallback : public DynamicAABBTreeRaycastCallback {

    public:

        std::vector<int> mHitNodes;

        // Called when the AABB of a leaf node is hit by a ray
        virtual decimal raycastBroadPhaseShape(int32 nodeId, const Ray& ray) override {
            mHitNodes.push_back(nodeId);
            return 1.0;
        }

        void reset() {
            mHitNodes.clear();
        }

        bool isHit(int nodeId) const {
            return std::find(mHitNodes.begin(), mHitNodes.end(), nodeId) != mHitNodes.end();
        }
};

// Class TestDynamicAABBTree
/**
 * Unit test for the dynamic AABB tree
 */
class TestDynamicAABBTree : public Test {

    private :

        // ---------- Atributes ---------- //

        TestOverlapCallback mOverlapCallback;
        DynamicTreeRaycastCallback mRaycastCallback;

    public :

        // ---------- Methods ---------- //

        /// Constructor
        TestDynamicAABBTree(const std::string& name): Test(name)  {


        }

        /// Run the tests
        void run() {

            testBasicsMethods();
            testOverlapping();
            testRaycast();

        }

        void testBasicsMethods() {

            // ------------ Create tree ---------- //

            // Dynamic AABB Tree
            DynamicAABBTree tree;
			
#ifdef IS_PROFILING_ACTIVE
			/// Pointer to the profiler
			Profiler* profiler = new Profiler();
			tree.setProfiler(profiler);
#endif

            int object1Data = 56;
            int object2Data = 23;
            int object3Data = 13;
            int object4Data = 7;

            // First object
            AABB aabb1 = AABB(Vector3(-6, 4, -3), Vector3(4, 8, 3));
            int object1Id = tree.addObject(aabb1, &object1Data);

            // Second object
            AABB aabb2 = AABB(Vector3(5, 2, -3), Vector3(10, 7, 3));
            int object2Id = tree.addObject(aabb2, &object2Data);

            // Third object
            AABB aabb3 = AABB(Vector3(-5, 1, -3), Vector3(-2, 3, 3));
            int object3Id = tree.addObject(aabb3, &object3Data);

            // Fourth object
            AABB aabb4 = AABB(Vector3(0, -4, -3), Vector3(3, -2, 3));
            int object4Id = tree.addObject(aabb4, &object4Data);

            // ----------- Tests ----------- //

            // Test root AABB
            AABB rootAABB = tree.getRootAABB();
            test(rootAABB.getMin().x == -6);
            test(rootAABB.getMin().y == -4);
            test(rootAABB.getMin().z == -3);
            test(rootAABB.getMax().x == 10);
            test(rootAABB.getMax().y == 8);
            test(rootAABB.getMax().z == 3);

            // Test data stored at the nodes of the tree
            test(*(int*)(tree.getNodeDataPointer(object1Id)) == object1Data);
            test(*(int*)(tree.getNodeDataPointer(object2Id)) == object2Data);
            test(*(int*)(tree.getNodeDataPointer(object3Id)) == object3Data);
            test(*(int*)(tree.getNodeDataPointer(object4Id)) == object4Data);

#ifdef IS_PROFILING_ACTIVE
			delete profiler;
#endif
        }

        void testOverlapping() {

            // ------------- Create tree ----------- //

            // Dynamic AABB Tree
            DynamicAABBTree tree;

#ifdef IS_PROFILING_ACTIVE
			/// Pointer to the profiler
			Profiler* profiler = new Profiler();
			tree.setProfiler(profiler);
#endif

            int object1Data = 56;
            int object2Data = 23;
            int object3Data = 13;
            int object4Data = 7;

            // First object
            AABB aabb1 = AABB(Vector3(-6, 4, -3), Vector3(4, 8, 3));
            int object1Id = tree.addObject(aabb1, &object1Data);

            // Second object
            AABB aabb2 = AABB(Vector3(5, 2, -3), Vector3(10, 7, 3));
            int object2Id = tree.addObject(aabb2, &object2Data);

            // Third object
            AABB aabb3 = AABB(Vector3(-5, 1, -3), Vector3(-2, 3, 3));
            int object3Id = tree.addObject(aabb3, &object3Data);

            // Fourth object
            AABB aabb4 = AABB(Vector3(0, -4, -3), Vector3(3, -2, 3));
            int object4Id = tree.addObject(aabb4, &object4Data);

            // ---------- Tests ---------- //

            // AABB overlapping nothing
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-10, 12, -4), Vector3(10, 50, 4)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping everything
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-15, -15, -4), Vector3(15, 15, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 1 and 3
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-4, 2, -4), Vector3(-1, 7, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 3 and 4
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-6, -5, -2), Vector3(2, 2, 0)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 2
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(5, -10, -2), Vector3(7, 10, 9)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // ---- Update the object AABBs with the initial AABBs (no reinsertion) ----- //

            tree.updateObject(object1Id, aabb1, Vector3::zero(), false);
            tree.updateObject(object2Id, aabb2, Vector3::zero(), false);
            tree.updateObject(object3Id, aabb3, Vector3::zero(), false);
            tree.updateObject(object4Id, aabb4, Vector3::zero(), false);

            // AABB overlapping nothing
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-10, 12, -4), Vector3(10, 50, 4)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping everything
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-15, -15, -4), Vector3(15, 15, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 1 and 3
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-4, 2, -4), Vector3(-1, 7, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 3 and 4
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-6, -5, -2), Vector3(2, 2, 0)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 2
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(5, -10, -2), Vector3(7, 10, 9)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // ---- Update the object AABBs with the initial AABBs (with reinsertion) ----- //

            tree.updateObject(object1Id, aabb1, Vector3::zero(), true);
            tree.updateObject(object2Id, aabb2, Vector3::zero(), true);
            tree.updateObject(object3Id, aabb3, Vector3::zero(), true);
            tree.updateObject(object4Id, aabb4, Vector3::zero(), true);

            // AABB overlapping nothing
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-10, 12, -4), Vector3(10, 50, 4)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping everything
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-15, -15, -4), Vector3(15, 15, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 1 and 3
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-4, 2, -4), Vector3(-1, 7, 4)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 3 and 4
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-6, -5, -2), Vector3(2, 2, 0)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping object 2
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(5, -10, -2), Vector3(7, 10, 9)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // ---- Move objects 2 and 3 ----- //

            AABB newAABB2(Vector3(-7, 10, -3), Vector3(1, 13, 3));
            tree.updateObject(object2Id, newAABB2, Vector3::zero());

            AABB newAABB3(Vector3(7, -6, -3), Vector3(9, 1, 3));
            tree.updateObject(object3Id, newAABB3, Vector3::zero());

            // AABB overlapping object 3
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(6, -10, -2), Vector3(8, 5, 3)), mOverlapCallback);
            test(!mOverlapCallback.isOverlapping(object1Id));
            test(!mOverlapCallback.isOverlapping(object2Id));
            test(mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

            // AABB overlapping objects 1, 2
            mOverlapCallback.reset();
            tree.reportAllShapesOverlappingWithAABB(AABB(Vector3(-8, 5, -3), Vector3(-2, 11, 3)), mOverlapCallback);
            test(mOverlapCallback.isOverlapping(object1Id));
            test(mOverlapCallback.isOverlapping(object2Id));
            test(!mOverlapCallback.isOverlapping(object3Id));
            test(!mOverlapCallback.isOverlapping(object4Id));

#ifdef IS_PROFILING_ACTIVE
			delete profiler;
#endif
        }

        void testRaycast() {

            // ------------- Create tree ----------- //

            // Dynamic AABB Tree
            DynamicAABBTree tree;

#ifdef IS_PROFILING_ACTIVE
			/// Pointer to the profiler
			Profiler* profiler = new Profiler();
			tree.setProfiler(profiler);
#endif

            int object1Data = 56;
            int object2Data = 23;
            int object3Data = 13;
            int object4Data = 7;

            // First object
            AABB aabb1 = AABB(Vector3(-6, 4, -3), Vector3(4, 8, 3));
            int object1Id = tree.addObject(aabb1, &object1Data);

            // Second object
            AABB aabb2 = AABB(Vector3(5, 2, -3), Vector3(10, 7, 3));
            int object2Id = tree.addObject(aabb2, &object2Data);

            // Third object
            AABB aabb3 = AABB(Vector3(-5, 1, -3), Vector3(-2, 3, 3));
            int object3Id = tree.addObject(aabb3, &object3Data);

            // Fourth object
            AABB aabb4 = AABB(Vector3(0, -4, -3), Vector3(3, -2, 3));
            int object4Id = tree.addObject(aabb4, &object4Data);

            // ---------- Tests ---------- //

            // Ray with no hits
            mRaycastCallback.reset();
            Ray ray1(Vector3(4.5, -10, -5), Vector3(4.5, 10, -5));
            tree.raycast(ray1, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1
            mRaycastCallback.reset();
            Ray ray2(Vector3(-1, -20, -2), Vector3(-1, 20, -2));
            tree.raycast(ray2, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1 and 2
            mRaycastCallback.reset();
            Ray ray3(Vector3(-7, 6, -2), Vector3(8, 6, -2));
            tree.raycast(ray3, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 3
            mRaycastCallback.reset();
            Ray ray4(Vector3(-7, 2, 0), Vector3(-1, 2, 0));
            tree.raycast(ray4, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // ---- Update the object AABBs with the initial AABBs (no reinsertion) ----- //

            tree.updateObject(object1Id, aabb1, Vector3::zero(), false);
            tree.updateObject(object2Id, aabb2, Vector3::zero(), false);
            tree.updateObject(object3Id, aabb3, Vector3::zero(), false);
            tree.updateObject(object4Id, aabb4, Vector3::zero(), false);

            // Ray with no hits
            mRaycastCallback.reset();
            tree.raycast(ray1, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1
            mRaycastCallback.reset();
            tree.raycast(ray2, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1 and 2
            mRaycastCallback.reset();
            tree.raycast(ray3, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 3
            mRaycastCallback.reset();
            tree.raycast(ray4, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // ---- Update the object AABBs with the initial AABBs (with reinsertion) ----- //

            tree.updateObject(object1Id, aabb1, Vector3::zero(), true);
            tree.updateObject(object2Id, aabb2, Vector3::zero(), true);
            tree.updateObject(object3Id, aabb3, Vector3::zero(), true);
            tree.updateObject(object4Id, aabb4, Vector3::zero(), true);

            // Ray with no hits
            mRaycastCallback.reset();
            tree.raycast(ray1, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1
            mRaycastCallback.reset();
            tree.raycast(ray2, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 1 and 2
            mRaycastCallback.reset();
            tree.raycast(ray3, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 3
            mRaycastCallback.reset();
            tree.raycast(ray4, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // ---- Move objects 2 and 3 ----- //

            AABB newAABB2(Vector3(-7, 10, -3), Vector3(1, 13, 3));
            tree.updateObject(object2Id, newAABB2, Vector3::zero());

            AABB newAABB3(Vector3(7, -6, -3), Vector3(9, 1, 3));
            tree.updateObject(object3Id, newAABB3, Vector3::zero());

            // Ray that hits object 1, 2
            Ray ray5(Vector3(-4, -5, 0), Vector3(-4, 12, 0));
            mRaycastCallback.reset();
            tree.raycast(ray5, mRaycastCallback);
            test(mRaycastCallback.isHit(object1Id));
            test(mRaycastCallback.isHit(object2Id));
            test(!mRaycastCallback.isHit(object3Id));
            test(!mRaycastCallback.isHit(object4Id));

            // Ray that hits object 3 and 4
            Ray ray6(Vector3(11, -3, 1), Vector3(-2, -3, 1));
            mRaycastCallback.reset();
            tree.raycast(ray6, mRaycastCallback);
            test(!mRaycastCallback.isHit(object1Id));
            test(!mRaycastCallback.isHit(object2Id));
            test(mRaycastCallback.isHit(object3Id));
            test(mRaycastCallback.isHit(object4Id));

#ifdef IS_PROFILING_ACTIVE
			delete profiler;
#endif
        }
 };

}

#endif
