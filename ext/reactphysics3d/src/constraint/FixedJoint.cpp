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
#include <reactphysics3d/constraint/FixedJoint.h>
#include <reactphysics3d/systems/ConstraintSolverSystem.h>
#include <reactphysics3d/components/RigidBodyComponents.h>
#include <reactphysics3d/engine/PhysicsWorld.h>

using namespace reactphysics3d;

// Constructor
FixedJoint::FixedJoint(Entity entity, PhysicsWorld& world, const FixedJointInfo& jointInfo)
           : Joint(entity, world) {


    Vector3 anchorPointBody1LocalSpace;
    Vector3 anchorPointBody2LocalSpace;

    const Transform& transform1 = mWorld.mTransformComponents.getTransform(jointInfo.body1->getEntity());
    const Transform& transform2 = mWorld.mTransformComponents.getTransform(jointInfo.body2->getEntity());

    if (jointInfo.isUsingLocalSpaceAnchors) {

        anchorPointBody1LocalSpace = jointInfo.anchorPointBody1LocalSpace;
        anchorPointBody2LocalSpace = jointInfo.anchorPointBody2LocalSpace;
    }
    else {

        // Compute the local-space anchor point for each body
        anchorPointBody1LocalSpace = transform1.getInverse() * jointInfo.anchorPointWorldSpace;
        anchorPointBody2LocalSpace = transform2.getInverse() * jointInfo.anchorPointWorldSpace;
    }

    mWorld.mFixedJointsComponents.setLocalAnchorPointBody1(mEntity, anchorPointBody1LocalSpace);
    mWorld.mFixedJointsComponents.setLocalAnchorPointBody2(mEntity, anchorPointBody2LocalSpace);

	// Store inverse of initial rotation from body 1 to body 2 in body 1 space:
	//
	// q20 = q10 r0 
	// <=> r0 = q10^-1 q20 
	// <=> r0^-1 = q20^-1 q10
	//
	// where:
	//
	// q20 = initial orientation of body 2
	// q10 = initial orientation of body 1
	// r0 = initial rotation rotation from body 1 to body 2
    mWorld.mFixedJointsComponents.setInitOrientationDifferenceInv(mEntity, transform2.getOrientation().getInverse() * transform1.getOrientation());
}

// Return the force (in Newtons) on body 2 required to satisfy the joint constraint in world-space
/**
 * @return The current force (in Newtons) applied on body 2
 */
Vector3 FixedJoint::getReactionForce(decimal timeStep) const {
    assert(timeStep > MACHINE_EPSILON);
    return mWorld.mFixedJointsComponents.getImpulseTranslation(mEntity) / timeStep;
}

// Return the torque (in Newtons * meters) on body 2 required to satisfy the joint constraint in world-space
/**
 * @return The current torque (in Newtons * meters) applied on body 2
 */
Vector3 FixedJoint::getReactionTorque(decimal timeStep) const {
    assert(timeStep > MACHINE_EPSILON);
    return mWorld.mFixedJointsComponents.getImpulseRotation(mEntity) / timeStep;
}

// Return a string representation
std::string FixedJoint::to_string() const {
    return "FixedJoint{ localAnchorPointBody1=" + mWorld.mFixedJointsComponents.getLocalAnchorPointBody1(mEntity).to_string() +
                        ", localAnchorPointBody2=" + mWorld.mFixedJointsComponents.getLocalAnchorPointBody2(mEntity).to_string() +
                        ", initOrientationDifferenceInv=" + mWorld.mFixedJointsComponents.getInitOrientationDifferenceInv(mEntity).to_string() +
                        "}";
}

