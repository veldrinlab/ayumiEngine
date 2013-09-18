/**
 * File contains definition of Sprite class.
 * @file    Sprite.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#include "Sprite.hpp"

using namespace std;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class default constructor. Create geometry data and set default values.
		 */
		Sprite::Sprite()
		{
			spriteMesh = new Mesh("Sprite","null");
			spriteVao = new VertexArrayObject();
			spriteVbo = new VertexBufferObject();
			spriteTexture = nullptr;
			position.set(0.0f,0.0f,0.0f);
			size.set(0.0f,0.0f,0.0f);
			alpha = 1.0f;
		}

		/**
		 * Class constructor with initialize parameters. Create geometry data and set postion/size and texture data.
		 * @param	spriteTexture is pointer to Sprite Texture resource from ResourceManager.
		 * @param	position is sprite position on screen.
		 * @param	size is sprite scale.
		 * @param	alpha is sprite alpha channel value for blending operations.
		 */
		Sprite::Sprite(Texture* spriteTexture, const Vector3D& position, const Vector3D& size, const float alpha)
		{
			spriteMesh = new Mesh("Sprite","null");
			spriteVao = new VertexArrayObject();
			spriteVbo = new VertexBufferObject();
			
			this->spriteTexture = spriteTexture;
			setPosition(position[0],position[1]);
			setSize(size[0],size[1]);
			this->alpha = alpha;
		}

		/**
		 * Class destructor, free allocated memory. Release sprite geometry buffers.
		 */
		Sprite::~Sprite()
		{
			delete spriteMesh;
			delete spriteVao;
			delete spriteVbo;
		}

		/**
		 * Method is used to initialize Sprite object. Call few private methods to initialize Sprite geometry,
		 * tetxure coordinates and configure buffers with Sprite shader.
		 * @param	offsetX is sprite UV coordinates x axis offset. Default is 0.0.
		 * @param	offsetY is sprite UV coordinates y axis offset. Default is 0.0.
		 */
		void Sprite::initializeSprite(const float offsetX, const float offsetY)
		{
			initializeSpriteMesh();
			multiplyUVCoordinates();
			setCharsetCoordinates(offsetX,offsetY);
			initializeSpriteBuffers();
		}

		/**
		 * Method is used to bind VAO and Sprite shader.
		 */
		void Sprite::attachRenderObjects()
		{
			spriteVao->bindVertexArray();
			spriteShader->bindShader();
		}

		/**
		 * Method is used to unbind VAO and Sprite shader.
		 */
		void Sprite::detachRenderObjects()
		{
			spriteShader->unbindShader();
			spriteVao->unbindVertexArray();
		}

		/**
		 * Method is used to configure Sprite texture coordinates to match defined font char.
		 * @param	x is vertical position of char in font charset.
		 * @param	y is horizontal position of char in font charset.
		 */
		void Sprite::setCharsetCoordinates(const float x, const float y)
		{
			for(int i = 0; i < spriteMesh->getVerticesAmount(); ++i)
			{
				spriteMesh->getVertices()[i].u += x;
				spriteMesh->getVertices()[i].v += y;	
			}
		}

		/**
		 * Accessor to private sprite position member.
		 * @return	sprite postion vector.
		 */
		Vector3D Sprite::getPosition() const
		{
			return position;
		}

		/**
		 * Accessor to private sprite size member.
		 * @return	sprite size vector.
		 */
		Vector3D Sprite::getSize() const
		{
			return size;
		}

		/**
		 * Accessor to private sprite texture member.
		 * @return	pointer to sprite texture.
		 */
		Texture* Sprite::getTexture() const
		{
			return spriteTexture;
		}

		/**
		 * Accessor to private sprite shader member.
		 * @return	pointer to sprite shader.
		 */
		Shader* Sprite::getShader() const
		{
			return spriteShader;
		}

		/**
		 * Accessor to private sprite name member.
		 * @return	sprite name string.
		 */
		string Sprite::getName() const
		{
			return name;
		}

		/**
		 * Accessor to private sprite alpha channel member.
		 * @return	sprite postion vector.
		 */
		float Sprite::getAlpha() const
		{
			return alpha;
		}

		/**
		 * Setter for private position vector member.
		 * @param	x is position vector x value.
		 * @param	y is position vector y value.
		 */
		void Sprite::setPosition(const float x, const float y)
		{
			position.set(x,y,0.0f);
		}

		/**
		 * Setter for private size vector member.
		 * @param	width is size vector x value.
		 * @param	height is size vector y value.
		 */
		void Sprite::setSize(const float width, const float height)
		{
			size.set(width,height,0.0f);
		}

		/**
		 * Setter for private shader member.
		 * @param	spriteShader is pointer to shader resource.
		 */
		void Sprite::setShader(Shader* spriteShader)
		{
			this->spriteShader = spriteShader;
		}

		/**
		 * Setter for private texture member.
		 * @param	spriteTexture is pointer to texture resource.
		 */
		void Sprite::setTexture(Texture* spriteTexture)
		{
			this->spriteTexture = spriteTexture;
		}

		/**
		 * Setter for private name member.
		 * @param	name is sprite name string.
		 */
		void Sprite::setName(const string& name)
		{
			this->name = name;
		}

		/**
		 * Setter for private alpha color member.
		 * @param	alpha is sprite alpha color value
		 */
		void Sprite::setAlpha(const float alpha)
		{
			this->alpha = alpha;
		}

		/**
		 * Private method which is used to initialize sprite geometry mesh.
		 */
		void Sprite::initializeSpriteMesh()
		{
			spriteMesh->setVerticesAmount(quadVertexAmount);
			spriteMesh->setTrianglesAmount(quadTriangleAmount);
			spriteMesh->initializeDataArrays();

			for(int i = 0, iterator = 0, iterator2 = 0; i < quadVertexAmount; ++i)
			{
				spriteMesh->getVertices()[i].x = quadVertices[iterator];
				spriteMesh->getVertices()[i].nx = quadNormals[iterator++];
				spriteMesh->getVertices()[i].y = quadVertices[iterator];
				spriteMesh->getVertices()[i].ny = quadNormals[iterator++];
				spriteMesh->getVertices()[i].z = quadVertices[iterator];
				spriteMesh->getVertices()[i].nz = quadNormals[iterator++];
				spriteMesh->getVertices()[i].u = quadUV[iterator2++];
				spriteMesh->getVertices()[i].v = quadUV[iterator2++];
			}

			for(int i = 0; i < quadTriangleAmount*3; ++i)
				spriteMesh->setIndex(i,quadIndices[i]);
		}

		/**
		 * Private method which is used to initialize sprite vertex buffers and configure render shader.
		 */
		void Sprite::initializeSpriteBuffers()
		{
			spriteVao->bindVertexArray();
		
			spriteVbo->initializeBufferObject(*spriteMesh);
			spriteVbo->vertexPosition = glGetAttribLocation(spriteShader->getShaderProgram(), "vertex" );
			spriteVbo->normalPosition = glGetAttribLocation(spriteShader->getShaderProgram(), "normal" );
			spriteVbo->texCoordPosition = glGetAttribLocation(spriteShader->getShaderProgram(), "texCoord" );
			spriteVbo->tangentPosition = glGetAttribLocation(spriteShader->getShaderProgram(), "tangent" );

			glVertexAttribPointer(spriteVbo->vertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + 0);
			glVertexAttribPointer(spriteVbo->normalPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*3);
			glVertexAttribPointer(spriteVbo->texCoordPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*6);
			glVertexAttribPointer(spriteVbo->tangentPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<>), reinterpret_cast<const GLubyte *>(0) + sizeof(float)*8);

			spriteVbo->bindBufferObject();
		}

		/**
		 * Private method which is used to set texture coordinates based on sprite size because of using 
		 * rectangle textures.
		 */
		void Sprite::multiplyUVCoordinates()
		{
			for(int i = 0; i < spriteMesh->getVerticesAmount(); ++i)
			{
				spriteMesh->getVertices()[i].u *= size.x();
				spriteMesh->getVertices()[i].v *= size.y();
			}
		}
	}
}
