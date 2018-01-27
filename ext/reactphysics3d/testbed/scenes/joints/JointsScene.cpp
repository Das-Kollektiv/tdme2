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

// Libraries
#include "JointsScene.h"
#include <cmath>

// Namespaces
using namespace openglframework;
using namespace jointsscene;

// Constructor
JointsScene::JointsScene(const std::string& name, EngineSettings& settings)
      : SceneDemo(name, settings, SCENE_RADIUS) {

    // Compute the radius and the center of the scene
    openglframework::Vector3 center(0, 5, 0);

    // Set the center of the scene
    setScenePosition(center, SCENE_RADIUS);

    // Gravity vector in the dynamics world
    rp3d::Vector3 gravity(0, rp3d::decimal(-9.81), 0);

    // Create the dynamics world for the physics simulation
    mPhysicsWorld = new rp3d::DynamicsWorld(gravity);

#ifdef IS_PROFILING_ACTIVE

    mPhysicsWorld->setProfilerName(name + "_profiler");

#endif

    // Create the Ball-and-Socket joint
    createBallAndSocketJoints();

    // Create the Slider joint
    createSliderJoint();

    // Create the Hinge joint
    createPropellerHingeJoint();

    // Create the Fixed joint
    createFixedJoints();

    // Create the floor
    createFloor();

    // Get the physics engine parameters
    mEngineSettings.isGravityEnabled = getDynamicsWorld()->isGravityEnabled();
    rp3d::Vector3 gravityVector = getDynamicsWorld()->getGravity();
    mEngineSettings.gravity = openglframework::Vector3(gravityVector.x, gravityVector.y, gravityVector.z);
    mEngineSettings.isSleepingEnabled = getDynamicsWorld()->isSleepingEnabled();
    mEngineSettings.sleepLinearVelocity = getDynamicsWorld()->getSleepLinearVelocity();
    mEngineSettings.sleepAngularVelocity = getDynamicsWorld()->getSleepAngularVelocity();
    mEngineSettings.nbPositionSolverIterations = getDynamicsWorld()->getNbIterationsPositionSolver();
    mEngineSettings.nbVelocitySolverIterations = getDynamicsWorld()->getNbIterationsVelocitySolver();
    mEngineSettings.timeBeforeSleep = getDynamicsWorld()->getTimeBeforeSleep();
}

// Destructor
JointsScene::~JointsScene() {

    // Destroy the joints
    getDynamicsWorld()->destroyJoint(mSliderJoint);
    getDynamicsWorld()->destroyJoint(mPropellerHingeJoint);
    getDynamicsWorld()->destroyJoint(mFixedJoint1);
    getDynamicsWorld()->destroyJoint(mFixedJoint2);
    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES-1; i++) {
        getDynamicsWorld()->destroyJoint(mBallAndSocketJoints[i]);
    }

    // Destroy all the rigid bodies of the scene
    getDynamicsWorld()->destroyRigidBody(mSliderJointBottomBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mSliderJointTopBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mPropellerBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mFixedJointBox1->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mFixedJointBox2->getRigidBody());
    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES; i++) {
        getDynamicsWorld()->destroyRigidBody(mBallAndSocketJointChainBoxes[i]->getRigidBody());
    }

    delete mSliderJointBottomBox;
    delete mSliderJointTopBox;
    delete mPropellerBox;
    delete mFixedJointBox1;
    delete mFixedJointBox2;
    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES; i++) {
        delete mBallAndSocketJointChainBoxes[i];
    }

    // Destroy the floor
    getDynamicsWorld()->destroyRigidBody(mFloor->getRigidBody());
    delete mFloor;

    // Destroy the dynamics world
    delete getDynamicsWorld();
}

// Update the physics world (take a simulation step)
void JointsScene::updatePhysics() {

    // Update the motor speed of the Slider Joint (to move up and down)
    double motorSpeed = 2.0 * std::cos(static_cast<double>(mEngineSettings.elapsedTime) * 1.5);
    mSliderJoint->setMotorSpeed(rp3d::decimal(motorSpeed));

    SceneDemo::updatePhysics();
}

// Reset the scene
void JointsScene::reset() {

    openglframework::Vector3 positionBox(0, 15, 5);
    openglframework::Vector3 boxDimension(1, 1, 1);

    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES; i++) {

        // Initial position and orientation of the rigid body
        rp3d::Vector3 initPosition(positionBox.x, positionBox.y, positionBox.z);
        rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
        rp3d::Transform transform(initPosition, initOrientation);

        // Create a box and a corresponding rigid in the dynamics world
        mBallAndSocketJointChainBoxes[i]->setTransform(transform);

        positionBox.y -= boxDimension.y + 0.5f;
    }

    // --------------- Slider Joint --------------- //

    // Position of the box
    openglframework::Vector3 positionBox1(0, 2.1f, 0);
    rp3d::Vector3 initPosition(positionBox1.x, positionBox1.y, positionBox1.z);
    rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transformBottomBox(initPosition, initOrientation);

    // Create a box and a corresponding rigid in the dynamics world
    mSliderJointBottomBox->setTransform(transformBottomBox);

    // Position of the box
    openglframework::Vector3 positionBox2(0, 4.2f, 0);
    initPosition = rp3d::Vector3(positionBox2.x, positionBox2.y, positionBox2.z);
    initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transformTopBox(initPosition, initOrientation);

    // Create a box and a corresponding rigid in the dynamics world
    mSliderJointTopBox->setTransform(transformTopBox);

    // --------------- Propeller Hinge joint --------------- //

    // Position of the box
    positionBox1 = openglframework::Vector3(0, 7, 0);
    initPosition = rp3d::Vector3(positionBox1.x, positionBox1.y, positionBox1.z);
    initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transformHingeBox(initPosition, initOrientation);

    // Create a box and a corresponding rigid in the dynamics world
    mPropellerBox->setTransform(transformHingeBox);

    // --------------- Fixed joint --------------- //

    // Position of the box
    positionBox1 = openglframework::Vector3(5, 7, 0);
    initPosition = rp3d::Vector3(positionBox1.x, positionBox1.y, positionBox1.z);
    initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transformFixedBox1(initPosition, initOrientation);

    // Create a box and a corresponding rigid in the dynamics world
    mFixedJointBox1->setTransform(transformFixedBox1);

    // Position of the box
    positionBox2 = openglframework::Vector3(-5, 7, 0);
    initPosition = rp3d::Vector3(positionBox2.x, positionBox2.y, positionBox2.z);
    initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transformFixedBox2(initPosition, initOrientation);

    // Create a box and a corresponding rigid in the dynamics world
    mFixedJointBox2->setTransform(transformFixedBox2);
}

// Create the boxes and joints for the Ball-and-Socket joint example
void JointsScene::createBallAndSocketJoints() {

    // --------------- Create the boxes --------------- //

    rp3d::Vector3 positionBox(0, 15, 5);
    openglframework::Vector3 boxDimension(1, 1, 1);
    const float boxMass = 0.5f;

    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES; i++) {

        // Create a box and a corresponding rigid in the dynamics world
        mBallAndSocketJointChainBoxes[i] = new Box(boxDimension, boxMass,
                                                   getDynamicsWorld(), mMeshFolderPath);
        mBallAndSocketJointChainBoxes[i]->setTransform(rp3d::Transform(positionBox, rp3d::Quaternion::identity()));

        // Set the box color
        mBallAndSocketJointChainBoxes[i]->setColor(mDemoColors[i % mNbDemoColors]);
        mBallAndSocketJointChainBoxes[i]->setSleepingColor(mRedColorDemo);

        // The fist box cannot move (static body)
        if (i == 0) {
            mBallAndSocketJointChainBoxes[i]->getRigidBody()->setType(rp3d::BodyType::STATIC);
        }

        // Add some angular velocity damping
        mBallAndSocketJointChainBoxes[i]->getRigidBody()->setAngularDamping(rp3d::decimal(0.2));

        // Change the material properties of the rigid body
        rp3d::Material& material = mBallAndSocketJointChainBoxes[i]->getRigidBody()->getMaterial();
        material.setBounciness(rp3d::decimal(0.4));

		mPhysicsObjects.push_back(mBallAndSocketJointChainBoxes[i]);

        positionBox.y -= boxDimension.y + 0.5f;
    }

    // --------------- Create the joints --------------- //

    for (int i=0; i<NB_BALLSOCKETJOINT_BOXES-1; i++) {

        // Create the joint info object
        rp3d::RigidBody* body1 = mBallAndSocketJointChainBoxes[i]->getRigidBody();
        rp3d::RigidBody* body2 = mBallAndSocketJointChainBoxes[i+1]->getRigidBody();
        rp3d::Vector3 body1Position = body1->getTransform().getPosition();
        rp3d::Vector3 body2Position = body2->getTransform().getPosition();
        const rp3d::Vector3 anchorPointWorldSpace = 0.5 * (body1Position + body2Position);
        rp3d::BallAndSocketJointInfo jointInfo(body1, body2, anchorPointWorldSpace);

        // Create the joint in the dynamics world
        mBallAndSocketJoints[i] = dynamic_cast<rp3d::BallAndSocketJoint*>(
                    getDynamicsWorld()->createJoint(jointInfo));
    }
}

/// Create the boxes and joint for the Slider joint example
void JointsScene::createSliderJoint() {

    // --------------- Create the first box --------------- //

    // Position of the box
    rp3d::Vector3 positionBox1(0, 2.1f, 0);

    // Create a box and a corresponding rigid in the dynamics world
    openglframework::Vector3 box1Dimension(2, 4, 2);
    mSliderJointBottomBox = new Box(box1Dimension , BOX_MASS, getDynamicsWorld(), mMeshFolderPath);
    mSliderJointBottomBox->setTransform(rp3d::Transform(positionBox1, rp3d::Quaternion::identity()));

    // Set the box color
    mSliderJointBottomBox->setColor(mBlueColorDemo);
    mSliderJointBottomBox->setSleepingColor(mRedColorDemo);

    // The fist box cannot move
    mSliderJointBottomBox->getRigidBody()->setType(rp3d::BodyType::STATIC);

    // Change the material properties of the rigid body
    rp3d::Material& material1 = mSliderJointBottomBox->getRigidBody()->getMaterial();
    material1.setBounciness(0.4f);
	mPhysicsObjects.push_back(mSliderJointBottomBox);

    // --------------- Create the second box --------------- //

    // Position of the box
    rp3d::Vector3 positionBox2(0, 4.2f, 0);

    // Create a box and a corresponding rigid in the dynamics world
    openglframework::Vector3 box2Dimension(1.5f, 4, 1.5f);
    mSliderJointTopBox = new Box(box2Dimension, BOX_MASS, getDynamicsWorld(), mMeshFolderPath);
    mSliderJointTopBox->setTransform(rp3d::Transform(positionBox2, rp3d::Quaternion::identity()));

    // Set the box color
    mSliderJointTopBox->setColor(mOrangeColorDemo);
    mSliderJointTopBox->setSleepingColor(mRedColorDemo);

    // Change the material properties of the rigid body
    rp3d::Material& material2 = mSliderJointTopBox->getRigidBody()->getMaterial();
    material2.setBounciness(0.4f);
	mPhysicsObjects.push_back(mSliderJointTopBox);

    // --------------- Create the joint --------------- //

    // Create the joint info object
    rp3d::RigidBody* body1 = mSliderJointBottomBox->getRigidBody();
    rp3d::RigidBody* body2 = mSliderJointTopBox->getRigidBody();
    const rp3d::Vector3& body1Position = body1->getTransform().getPosition();
    const rp3d::Vector3& body2Position = body2->getTransform().getPosition();
    const rp3d::Vector3 anchorPointWorldSpace = rp3d::decimal(0.5) * (body2Position + body1Position);
    const rp3d::Vector3 sliderAxisWorldSpace = (body2Position - body1Position);
    rp3d::SliderJointInfo jointInfo(body1, body2, anchorPointWorldSpace, sliderAxisWorldSpace,
                                    rp3d::decimal(-1.7), rp3d::decimal(1.7));
    jointInfo.isMotorEnabled = true;
    jointInfo.motorSpeed = 0.0;
    jointInfo.maxMotorForce = 10000.0;
    jointInfo.isCollisionEnabled = false;

    // Create the joint in the dynamics world
    mSliderJoint = dynamic_cast<rp3d::SliderJoint*>(getDynamicsWorld()->createJoint(jointInfo));
}

/// Create the boxes and joint for the Hinge joint example
void JointsScene::createPropellerHingeJoint() {

    // --------------- Create the propeller box --------------- //

    // Position of the box
    rp3d::Vector3 positionBox1(0, 7, 0);

    // Create a box and a corresponding rigid in the dynamics world
    openglframework::Vector3 boxDimension(10, 1, 1);
    mPropellerBox = new Box(boxDimension, BOX_MASS, getDynamicsWorld(), mMeshFolderPath);
    mPropellerBox->setTransform(rp3d::Transform(positionBox1, rp3d::Quaternion::identity()));

    // Set the box color
    mPropellerBox->setColor(mYellowColorDemo);
    mPropellerBox->setSleepingColor(mRedColorDemo);

    // Change the material properties of the rigid body
    rp3d::Material& material = mPropellerBox->getRigidBody()->getMaterial();
    material.setBounciness(rp3d::decimal(0.4));
	mPhysicsObjects.push_back(mPropellerBox);

    // --------------- Create the Hinge joint --------------- //

    // Create the joint info object
    rp3d::RigidBody* body1 = mPropellerBox->getRigidBody();
    rp3d::RigidBody* body2 = mSliderJointTopBox->getRigidBody();
    const rp3d::Vector3& body1Position = body1->getTransform().getPosition();
    const rp3d::Vector3& body2Position = body2->getTransform().getPosition();
    const rp3d::Vector3 anchorPointWorldSpace = 0.5 * (body2Position + body1Position);
    const rp3d::Vector3 hingeAxisWorldSpace(0, 1, 0);
    rp3d::HingeJointInfo jointInfo(body1, body2, anchorPointWorldSpace, hingeAxisWorldSpace);
    jointInfo.isMotorEnabled = true;
    jointInfo.motorSpeed = - rp3d::decimal(0.5) * PI;
    jointInfo.maxMotorTorque = rp3d::decimal(60.0);
    jointInfo.isCollisionEnabled = false;

    // Create the joint in the dynamics world
    mPropellerHingeJoint = dynamic_cast<rp3d::HingeJoint*>(getDynamicsWorld()->createJoint(jointInfo));
}

/// Create the boxes and joints for the fixed joints
void JointsScene::createFixedJoints() {

    // --------------- Create the first box --------------- //

    // Position of the box
    rp3d::Vector3 positionBox1(5, 7, 0);

    // Create a box and a corresponding rigid in the dynamics world
    openglframework::Vector3 boxDimension(1.5, 1.5, 1.5);
    mFixedJointBox1 = new Box(boxDimension, BOX_MASS, getDynamicsWorld(), mMeshFolderPath);
    mFixedJointBox1->setTransform(rp3d::Transform(positionBox1, rp3d::Quaternion::identity()));

    // Set the box color
    mFixedJointBox1->setColor(mPinkColorDemo);
    mFixedJointBox1->setSleepingColor(mRedColorDemo);

    // Change the material properties of the rigid body
    rp3d::Material& material1 = mFixedJointBox1->getRigidBody()->getMaterial();
    material1.setBounciness(rp3d::decimal(0.4));
	mPhysicsObjects.push_back(mFixedJointBox1);

    // --------------- Create the second box --------------- //

    // Position of the box
    rp3d::Vector3 positionBox2(-5, 7, 0);

    // Create a box and a corresponding rigid in the dynamics world
    mFixedJointBox2 = new Box(boxDimension, BOX_MASS, getDynamicsWorld(), mMeshFolderPath);
    mFixedJointBox2->setTransform(rp3d::Transform(positionBox2, rp3d::Quaternion::identity()));

    // Set the box color
    mFixedJointBox2->setColor(mBlueColorDemo);
    mFixedJointBox2->setSleepingColor(mRedColorDemo);

    // Change the material properties of the rigid body
    rp3d::Material& material2 = mFixedJointBox2->getRigidBody()->getMaterial();
    material2.setBounciness(rp3d::decimal(0.4));
	mPhysicsObjects.push_back(mFixedJointBox2);

    // --------------- Create the first fixed joint --------------- //

    // Create the joint info object
    rp3d::RigidBody* body1 = mFixedJointBox1->getRigidBody();
    rp3d::RigidBody* propellerBody = mPropellerBox->getRigidBody();
    const rp3d::Vector3 anchorPointWorldSpace1(5, 7, 0);
    rp3d::FixedJointInfo jointInfo1(body1, propellerBody, anchorPointWorldSpace1);
    jointInfo1.isCollisionEnabled = false;

    // Create the joint in the dynamics world
    mFixedJoint1 = dynamic_cast<rp3d::FixedJoint*>(getDynamicsWorld()->createJoint(jointInfo1));

    // --------------- Create the second fixed joint --------------- //

    // Create the joint info object
    rp3d::RigidBody* body2 = mFixedJointBox2->getRigidBody();
    const rp3d::Vector3 anchorPointWorldSpace2(-5, 7, 0);
    rp3d::FixedJointInfo jointInfo2(body2, propellerBody, anchorPointWorldSpace2);
    jointInfo2.isCollisionEnabled = false;

    // Create the joint in the dynamics world
    mFixedJoint2 = dynamic_cast<rp3d::FixedJoint*>(getDynamicsWorld()->createJoint(jointInfo2));
}

// Create the floor
void JointsScene::createFloor() {

    // Create the floor
    rp3d::Vector3 floorPosition(0, 0, 0);
    mFloor = new Box(FLOOR_SIZE, FLOOR_MASS, getDynamicsWorld(), mMeshFolderPath);

    // Set the box color
    mFloor->setColor(mGreyColorDemo);
    mFloor->setSleepingColor(mGreyColorDemo);

    // The floor must be a static rigid body
    mFloor->getRigidBody()->setType(rp3d::BodyType::STATIC);

    // Change the material properties of the rigid body
    rp3d::Material& material = mFloor->getRigidBody()->getMaterial();
    material.setBounciness(rp3d::decimal(0.3));
	mPhysicsObjects.push_back(mFloor);
}
