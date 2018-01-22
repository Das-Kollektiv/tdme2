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

#ifndef TEST_AABB_H
#define TEST_AABB_H

// Libraries
#include "reactphysics3d.h"

/// Reactphysics3D namespace
namespace reactphysics3d {


// Class TestAABB
/**
 * Unit test for the AABB class.
 */
class TestAABB : public Test {

    private :

        // ---------- Atributes ---------- //

        AABB mAABB1;
        AABB mAABB2;
        AABB mAABB3;
        AABB mAABB4;

    public :

        // ---------- Methods ---------- //

        /// Constructor
        TestAABB(const std::string& name) : Test(name) {

            mAABB1.setMin(Vector3(-10, -10, -10));
            mAABB1.setMax(Vector3(10, 10, 10));

            // AABB2 intersect with AABB1
            mAABB2.setMin(Vector3(-5, 4, -30));
            mAABB2.setMax(Vector3(-2, 20, 30));

            // AABB3 contains AABB1
            mAABB3.setMin(Vector3(-25, -25, -25));
            mAABB3.setMax(Vector3(25, 25, 25));

            // AABB4 does not collide with AABB1
            mAABB4.setMin(Vector3(-40, -40, -40));
            mAABB4.setMax(Vector3(-15, -25, -12));
        }

        /// Destructor
        virtual ~TestAABB() {

        }

        /// Run the tests
        void run() {
            testBasicMethods();
            testMergeMethods();
            testIntersection();
        }

        void testBasicMethods() {

            // -------- Test constructors -------- //
            AABB aabb1;
            AABB aabb2(Vector3(-3, -5, -8), Vector3(65, -1, 56));
            Vector3 trianglePoints[] = {
                Vector3(-5, 7, 23), Vector3(45, -34, -73), Vector3(-12, 98, 76)
            };
            AABB aabb3 = AABB::createAABBForTriangle(trianglePoints);

            test(aabb1.getMin().x == 0);
            test(aabb1.getMin().y == 0);
            test(aabb1.getMin().z == 0);
            test(aabb1.getMax().x == 0);
            test(aabb1.getMax().y == 0);
            test(aabb1.getMax().z == 0);

            test(aabb2.getMin().x == -3);
            test(aabb2.getMin().y == -5);
            test(aabb2.getMin().z == -8);
            test(aabb2.getMax().x == 65);
            test(aabb2.getMax().y == -1);
            test(aabb2.getMax().z == 56);

            test(aabb3.getMin().x == -12);
            test(aabb3.getMin().y == -34);
            test(aabb3.getMin().z == -73);
            test(aabb3.getMax().x == 45);
            test(aabb3.getMax().y == 98);
            test(aabb3.getMax().z == 76);

            // -------- Test inflate() -------- //
            AABB aabbInflate(Vector3(-3, 4, 8), Vector3(-1, 6, 32));
            aabbInflate.inflate(1, 2, 3);
            test(approxEqual(aabbInflate.getMin().x, -4, 0.00001));
            test(approxEqual(aabbInflate.getMin().y, 2, 0.00001));
            test(approxEqual(aabbInflate.getMin().z, 5, 0.00001));
            test(approxEqual(aabbInflate.getMax().x, 0, 0.00001));
            test(approxEqual(aabbInflate.getMax().y, 8, 0.00001));
            test(approxEqual(aabbInflate.getMax().z, 35, 0.00001));

            // -------- Test getExtent() --------- //

            test(approxEqual(mAABB1.getExtent().x, 20));
            test(approxEqual(mAABB1.getExtent().y, 20));
            test(approxEqual(mAABB1.getExtent().z, 20));

            test(approxEqual(mAABB2.getExtent().x, 3));
            test(approxEqual(mAABB2.getExtent().y, 16));
            test(approxEqual(mAABB2.getExtent().z, 60));

            test(approxEqual(mAABB3.getExtent().x, 50));
            test(approxEqual(mAABB3.getExtent().y, 50));
            test(approxEqual(mAABB3.getExtent().z, 50));

            // -------- Test getCenter() -------- //

            test(mAABB1.getCenter().x == 0);
            test(mAABB1.getCenter().y == 0);
            test(mAABB1.getCenter().z == 0);

            test(approxEqual(mAABB2.getCenter().x, -3.5));
            test(approxEqual(mAABB2.getCenter().y, 12));
            test(approxEqual(mAABB2.getCenter().z, 0));

            // -------- Test setMin(), setMax(), getMin(), getMax() -------- //

            AABB aabb5;
            aabb5.setMin(Vector3(-12, 34, 6));
            aabb5.setMax(Vector3(-3, 56, 20));

            test(aabb5.getMin().x == -12);
            test(aabb5.getMin().y == 34);
            test(aabb5.getMin().z == 6);
            test(aabb5.getMax().x == -3);
            test(aabb5.getMax().y == 56);
            test(aabb5.getMax().z == 20);

            // -------- Test assignment operator -------- //

            AABB aabb6;
            aabb6 = aabb2;

            test(aabb6.getMin().x == -3);
            test(aabb6.getMin().y == -5);
            test(aabb6.getMin().z == -8);
            test(aabb6.getMax().x == 65);
            test(aabb6.getMax().y == -1);
            test(aabb6.getMax().z == 56);

            // -------- Test getVolume() -------- //

            test(approxEqual(mAABB1.getVolume(), 8000));
            test(approxEqual(mAABB2.getVolume(), 2880));
        }

        void testMergeMethods() {

            AABB aabb1(Vector3(-45, 7, -2), Vector3(23, 8, 1));
            AABB aabb2(Vector3(-15, 6, 23), Vector3(-5, 9, 45));

            // -------- Test mergeTwoAABBs() -------- //

            AABB aabb3;
            aabb3.mergeTwoAABBs(aabb1, mAABB1);

            test(aabb3.getMin().x == -45);
            test(aabb3.getMin().y == -10);
            test(aabb3.getMin().z == -10);
            test(aabb3.getMax().x == 23);
            test(aabb3.getMax().y == 10);
            test(aabb3.getMax().z == 10);

            AABB aabb4;
            aabb4.mergeTwoAABBs(aabb1, aabb2);

            test(aabb4.getMin().x == -45);
            test(aabb4.getMin().y == 6);
            test(aabb4.getMin().z == -2);
            test(aabb4.getMax().x == 23);
            test(aabb4.getMax().y == 9);
            test(aabb4.getMax().z == 45);

            // -------- Test mergeWithAABB() -------- //

            aabb1.mergeWithAABB(mAABB1);

            test(aabb1.getMin().x == -45);
            test(aabb1.getMin().y == -10);
            test(aabb1.getMin().z == -10);
            test(aabb1.getMax().x == 23);
            test(aabb1.getMax().y == 10);
            test(aabb1.getMax().z == 10);

            aabb2.mergeWithAABB(mAABB1);

            test(aabb2.getMin().x == -15);
            test(aabb2.getMin().y == -10);
            test(aabb2.getMin().z == -10);
            test(aabb2.getMax().x == 10);
            test(aabb2.getMax().y == 10);
            test(aabb2.getMax().z == 45);
        }

        void testIntersection() {

            // -------- Test contains(AABB) -------- //
            test(!mAABB1.contains(mAABB2));
            test(mAABB3.contains(mAABB1));
            test(!mAABB1.contains(mAABB3));
            test(!mAABB1.contains(mAABB4));
            test(!mAABB4.contains(mAABB1));

            // -------- Test contains(Vector3) -------- //
            test(mAABB1.contains(Vector3(0, 0, 0)));
            test(mAABB1.contains(Vector3(-5, 6, 9)));
            test(mAABB1.contains(Vector3(-9, -4, -9)));
            test(mAABB1.contains(Vector3(9, 4, 7)));
            test(!mAABB1.contains(Vector3(-11, -4, -9)));
            test(!mAABB1.contains(Vector3(1, 12, -9)));
            test(!mAABB1.contains(Vector3(1, 8, -13)));
            test(!mAABB1.contains(Vector3(-14, 82, -13)));

            // -------- Test testCollision() -------- //
            test(mAABB1.testCollision(mAABB2));
            test(mAABB2.testCollision(mAABB1));
            test(mAABB1.testCollision(mAABB3));
            test(mAABB3.testCollision(mAABB1));
            test(!mAABB1.testCollision(mAABB4));
            test(!mAABB4.testCollision(mAABB1));

            // -------- Test testCollisionTriangleAABB() -------- //

            AABB aabb(Vector3(100, 100, 100), Vector3(200, 200, 200));
            Vector3 trianglePoints[] = {
                Vector3(-2, 4, 6), Vector3(20, -34, -73), Vector3(-12, 98, 76)
            };
            test(mAABB1.testCollisionTriangleAABB(trianglePoints));
            test(!aabb.testCollisionTriangleAABB(trianglePoints));

            // -------- Test testRayIntersect() -------- //

            Ray ray1(Vector3(-20, 4, -7), Vector3(20, 4, -7));
            Ray ray2(Vector3(-20, 11, -7), Vector3(20, 11, -7));
            Ray ray3(Vector3(0, 15, 0), Vector3(0, -15, 0));
            Ray ray4(Vector3(0, -15, 0), Vector3(0, 15, 0));
            Ray ray5(Vector3(-3, 4, 8), Vector3(-7, 9, 4));
            Ray ray6(Vector3(-4, 6, -100), Vector3(-4, 6, -9));
            Ray ray7(Vector3(-4, 6, -100), Vector3(-4, 6, -11), 0.6);
            Ray ray8(Vector3(-403, -432, -100), Vector3(134, 643, 23));

            test(mAABB1.testRayIntersect(ray1));
            test(!mAABB1.testRayIntersect(ray2));
            test(mAABB1.testRayIntersect(ray3));
            test(mAABB1.testRayIntersect(ray4));
            test(mAABB1.testRayIntersect(ray5));
            test(mAABB1.testRayIntersect(ray6));
            test(!mAABB1.testRayIntersect(ray7));
            test(!mAABB1.testRayIntersect(ray8));
        }
 };

}

#endif
