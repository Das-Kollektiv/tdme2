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
#include "Sphere.h"

openglframework::VertexBufferObject Sphere::mVBOVertices(GL_ARRAY_BUFFER);
openglframework::VertexBufferObject Sphere::mVBONormals(GL_ARRAY_BUFFER);
openglframework::VertexBufferObject Sphere::mVBOTextureCoords(GL_ARRAY_BUFFER);
openglframework::VertexBufferObject Sphere::mVBOIndices(GL_ELEMENT_ARRAY_BUFFER);
openglframework::VertexArrayObject Sphere::mVAO;
int Sphere::totalNbSpheres = 0;

// Constructor
Sphere::Sphere(float radius, rp3d::CollisionWorld* world,
               const std::string& meshFolderPath)
       : PhysicsObject(meshFolderPath + "sphere.obj"), mRadius(radius) {

    // Compute the scaling matrix
    mScalingMatrix = openglframework::Matrix4(mRadius, 0, 0, 0,
                                              0, mRadius, 0, 0,
                                              0, 0, mRadius, 0,
                                              0, 0, 0, 1);

    // Create the collision shape for the rigid body (sphere shape)
    // ReactPhysics3D will clone this object to create an internal one. Therefore,
    // it is OK if this object is destroyed right after calling RigidBody::addCollisionShape()
    mCollisionShape = new rp3d::SphereShape(mRadius);
    //mCollisionShape->setLocalScaling(rp3d::Vector3(2, 2, 2));

    mPreviousTransform = rp3d::Transform::identity();

    // Create a rigid body corresponding to the sphere in the dynamics world
    mBody = world->createCollisionBody(mPreviousTransform);

    // Add a collision shape to the body and specify the mass of the shape
    mProxyShape = mBody->addCollisionShape(mCollisionShape, rp3d::Transform::identity());

    mTransformMatrix = mTransformMatrix * mScalingMatrix;

    // Create the VBOs and VAO
    if (totalNbSpheres == 0) {
        createVBOAndVAO();
    }

    totalNbSpheres++;
}

// Constructor
Sphere::Sphere(float radius, float mass, reactphysics3d::DynamicsWorld* world,
               const std::string& meshFolderPath)
       : PhysicsObject(meshFolderPath + "sphere.obj"), mRadius(radius) {

    // Compute the scaling matrix
    mScalingMatrix = openglframework::Matrix4(mRadius, 0, 0, 0,
                                              0, mRadius, 0, 0,
                                              0, 0, mRadius, 0,
                                              0, 0, 0, 1);

    // Create the collision shape for the rigid body (sphere shape)
    // ReactPhysics3D will clone this object to create an internal one. Therefore,
    // it is OK if this object is destroyed right after calling RigidBody::addCollisionShape()
    mCollisionShape = new rp3d::SphereShape(mRadius);

    mPreviousTransform = rp3d::Transform::identity();

    // Create a rigid body corresponding to the sphere in the dynamics world
    rp3d::RigidBody* body = world->createRigidBody(mPreviousTransform);

    // Add a collision shape to the body and specify the mass of the shape
    mProxyShape = body->addCollisionShape(mCollisionShape, rp3d::Transform::identity(), mass);

    mBody = body;

    mTransformMatrix = mTransformMatrix * mScalingMatrix;

    // Create the VBOs and VAO
    if (totalNbSpheres == 0) {
        createVBOAndVAO();
    }

    totalNbSpheres++;
}

// Destructor
Sphere::~Sphere() {

    if (totalNbSpheres == 1) {
        // Destroy the mesh
        destroy();

        // Destroy the VBOs and VAO
        mVBOIndices.destroy();
        mVBOVertices.destroy();
        mVBONormals.destroy();
        mVBOTextureCoords.destroy();
        mVAO.destroy();
    }
    delete mCollisionShape;
    totalNbSpheres--;
}

// Render the sphere at the correct position and with the correct orientation
void Sphere::render(openglframework::Shader& shader, const openglframework::Matrix4& worldToCameraMatrix) {

    // Bind the shader
    shader.bind();

    // Set the model to camera matrix
    shader.setMatrix4x4Uniform("localToWorldMatrix", mTransformMatrix);
    shader.setMatrix4x4Uniform("worldToCameraMatrix", worldToCameraMatrix);

    // Set the normal matrix (inverse transpose of the 3x3 upper-left sub matrix of the
    // model-view matrix)
    const openglframework::Matrix4 localToCameraMatrix = worldToCameraMatrix * mTransformMatrix;
    const openglframework::Matrix3 normalMatrix =
                       localToCameraMatrix.getUpperLeft3x3Matrix().getInverse().getTranspose();
    shader.setMatrix3x3Uniform("normalMatrix", normalMatrix, false);

    // Set the vertex color
    openglframework::Color currentColor = mBody->isSleeping() ? mSleepingColor : mColor;
    openglframework::Vector4 color(currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    shader.setVector4Uniform("vertexColor", color, false);

    // Bind the VAO
    mVAO.bind();

    mVBOVertices.bind();

    // Get the location of shader attribute variables
    GLint vertexPositionLoc = shader.getAttribLocation("vertexPosition");
    GLint vertexNormalLoc = shader.getAttribLocation("vertexNormal", false);

    glEnableVertexAttribArray(vertexPositionLoc);
    glVertexAttribPointer(vertexPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, (char*)NULL);

    mVBONormals.bind();

    if (vertexNormalLoc != -1) glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_FALSE, 0, (char*)NULL);
    if (vertexNormalLoc != -1) glEnableVertexAttribArray(vertexNormalLoc);

    // For each part of the mesh
    for (unsigned int i=0; i<getNbParts(); i++) {
        glDrawElements(GL_TRIANGLES, getNbFaces(i) * 3, GL_UNSIGNED_INT, (char*)NULL);
    }

    glDisableVertexAttribArray(vertexPositionLoc);
    if (vertexNormalLoc != -1) glDisableVertexAttribArray(vertexNormalLoc);

    mVBONormals.unbind();
    mVBOVertices.unbind();

    // Unbind the VAO
    mVAO.unbind();

    // Unbind the shader
    shader.unbind();
}

// Create the Vertex Buffer Objects used to render with OpenGL.
/// We create two VBOs (one for vertices and one for indices)
void Sphere::createVBOAndVAO() {

    // Create the VBO for the vertices data
    mVBOVertices.create();
    mVBOVertices.bind();
    size_t sizeVertices = mVertices.size() * sizeof(openglframework::Vector3);
    mVBOVertices.copyDataIntoVBO(sizeVertices, getVerticesPointer(), GL_STATIC_DRAW);
    mVBOVertices.unbind();

    // Create the VBO for the normals data
    mVBONormals.create();
    mVBONormals.bind();
    size_t sizeNormals = mNormals.size() * sizeof(openglframework::Vector3);
    mVBONormals.copyDataIntoVBO(sizeNormals, getNormalsPointer(), GL_STATIC_DRAW);
    mVBONormals.unbind();

    if (hasTexture()) {
        // Create the VBO for the texture co data
        mVBOTextureCoords.create();
        mVBOTextureCoords.bind();
        size_t sizeTextureCoords = mUVs.size() * sizeof(openglframework::Vector2);
        mVBOTextureCoords.copyDataIntoVBO(sizeTextureCoords, getUVTextureCoordinatesPointer(), GL_STATIC_DRAW);
        mVBOTextureCoords.unbind();
    }

    // Create th VBO for the indices data
    mVBOIndices.create();
    mVBOIndices.bind();
    size_t sizeIndices = mIndices[0].size() * sizeof(unsigned int);
    mVBOIndices.copyDataIntoVBO(sizeIndices, getIndicesPointer(), GL_STATIC_DRAW);
    mVBOIndices.unbind();

    // Create the VAO for both VBOs
    mVAO.create();
    mVAO.bind();

    // Bind the VBO of vertices
    mVBOVertices.bind();

    // Bind the VBO of normals
    mVBONormals.bind();

    if (hasTexture()) {
        // Bind the VBO of texture coords
        mVBOTextureCoords.bind();
    }

    // Bind the VBO of indices
    mVBOIndices.bind();

    // Unbind the VAO
    mVAO.unbind();
}

// Set the scaling of the object
void Sphere::setScaling(const openglframework::Vector3& scaling) {

    // Scale the collision shape
    mProxyShape->setLocalScaling(rp3d::Vector3(scaling.x, scaling.y, scaling.z));

    // Scale the graphics object
    mScalingMatrix = openglframework::Matrix4(mRadius * scaling.x, 0, 0, 0,
                                              0, mRadius * scaling.y, 0, 0,
                                              0, 0, mRadius * scaling.z, 0,
                                              0, 0, 0, 1);
}
