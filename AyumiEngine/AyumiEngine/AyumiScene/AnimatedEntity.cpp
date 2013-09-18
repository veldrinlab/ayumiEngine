/**
 * File contains definition of AnimatedEntity class.
 * @file	AnimatedEntityEntity.Cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-24
 */

#include "AnimatedEntity.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	entityName is animated entity name.
		 * @param	meshName is animated entity mesh resource id.
		 * @param	materialName is animated entity material resource id.
		 */
		AnimatedEntity::AnimatedEntity(const string& entityName, const string& meshName, const string& materialName) : SceneEntity(entityName,meshName,materialName)
		{

		}

		/**
		 * Class constructor, free allocated memeory. Delete created vertex buffers collection.
		 */
		AnimatedEntity::~AnimatedEntity()
		{
			delete [] entityGeometry.geomteryVbo;
			entityGeometry.geomteryVbo = nullptr;
		}

		/**
		 * Method is used to initialize animated entity. Initialize base class data and set
		 * animation to defautl state.
		 */
		void AnimatedEntity::initializeAnimatedEntity()
		{
			initializeSceneEntity();
			setAnimation(STAND);
		}

		/**
		 * Method is used to update animation state. Update current animation and configure 
		 * vertex buffers data. Animation interpolation is made in vertex shader.
		 * @param	elapsedTime is time between two frames.
		 */
		void AnimatedEntity::updateAnimation(const float elapsedTime)
		{
			animationState.currentTime += elapsedTime;

			if(animationState.currentTime > (1.0 / animationState.framePerSecond))
			{
				animationState.currentFrame = animationState.nextFrame;
				animationState.nextFrame++;

				if(animationState.nextFrame > animationState.endFrame)
					animationState.nextFrame = animationState.startFrame;

				animationState.currentTime = 0.0f;
				animationState.interpolatonValue = 0.0f;
			}

			if(animationState.currentFrame > (198 - 1))
				animationState.currentFrame = 0;

			if(animationState.nextFrame> (198 - 1))
				animationState.nextFrame = 0;

			animationState.interpolatonValue +=  elapsedTime;
			configureGeometryAttributes();	
		}

		/**
		 * Method is used to set and configrue animation state.
		 * @param	type is enum of new animation state.
		 */
		void AnimatedEntity::setAnimation(AnimationType type)
		{
			if((type < STAND) || (type > MAX_ANIMATIONS))
				type = STAND;

			animationState.startFrame = animationList[type].firstFrame;
			animationState.endFrame = animationList[type].lastFrame;
			animationState.currentFrame = animationList[type].firstFrame;
			animationState.nextFrame = animationList[type].firstFrame + 1;
			animationState.framePerSecond = animationList[type].framePerSecond;
			animationState.type = type;
			animationState.interpolatonValue = 0.0f;
			animationState.currentTime = 0.0f;
		}

		/**
		 * Method is used to set geometry data of AnimatedEntity. Create EntityGeometry struct of VAO/VBO and Bounding
		 * Volumes based on poniter to entity geometry mesh object.
		 * @param	geometryMesh is pointer to scene eneity geometry mesh object.
		 */
		void AnimatedEntity::setGeometryData(AyumiResource::Mesh* geometryMesh)
		{
			entityGeometry.geometryMesh = geometryMesh;
			entityGeometry.geometryVao = new VertexArrayObject();
			entityGeometry.geomteryVbo = new VertexBufferObject[198];
			entityGeometry.geometryBox = new BoundingBox(geometryMesh[0]);
			entityGeometry.geometrySphere = new BoundingSphere(geometryMesh[0],entityState.position);

			for(int i = 0; i < 198; ++i)
				entityGeometry.geomteryVbo[i].initializeBufferObject(entityGeometry.geometryMesh[i]);
		}

		/**
		 * Method is used to configure animated scene entity geometry buffers attributes. Create AnimatedEntity
		 * VAO and initialize VBO. In this case we need to configure current and next frame buffers to do interpolation
		 * in vertex shader.
		 */
		void AnimatedEntity::configureGeometryAttributes()
		{
			entityGeometry.geometryVao->bindVertexArray();

			entityGeometry.geomteryVbo[animationState.currentFrame].vertexPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(), "vertex" );
			entityGeometry.geomteryVbo[animationState.currentFrame].normalPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(), "normal" );
			entityGeometry.geomteryVbo[animationState.currentFrame].texCoordPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(), "texCoord" );
			entityGeometry.geomteryVbo[animationState.currentFrame].tangentPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(), "tangent" );

			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.currentFrame].vertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + 0);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.currentFrame].normalPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*3);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.currentFrame].texCoordPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*6);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.currentFrame].tangentPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*8);

			entityGeometry.geomteryVbo[animationState.currentFrame].bindBufferObject();

			entityGeometry.geomteryVbo[animationState.nextFrame].vertexPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"vertex2");
			entityGeometry.geomteryVbo[animationState.nextFrame].normalPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"normal2");
			entityGeometry.geomteryVbo[animationState.nextFrame].texCoordPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"texCoord2");
			entityGeometry.geomteryVbo[animationState.nextFrame].tangentPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"tangent2");

			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.nextFrame].vertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + 0);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.nextFrame].normalPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*3);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.nextFrame].texCoordPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*6);
			glVertexAttribPointer(entityGeometry.geomteryVbo[animationState.nextFrame].tangentPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*8);

			entityGeometry.geomteryVbo[animationState.nextFrame].bindBufferObject();
			entityMaterial.entityShader->setUniformf("interpolate",animationState.interpolatonValue);
		}
	}
}