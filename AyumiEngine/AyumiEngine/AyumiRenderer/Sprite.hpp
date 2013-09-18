/**
 * File contains declaration of Sprite class.
 * @file    Sprite.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#include "DefinedGeometry.hpp"

#include "../AyumiMath/CommonMath.hpp"
#include "../AyumiResource/Texture.hpp"
#include "../AyumiResource/Shader.hpp"
#include "../AyumiUtils/VertexArrayObject.hpp"
#include "../AyumiUtils/VertexBufferObject.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class represents engine 2D object - Sprite which is used to render 2D images, text and post-process
		 * fullscreen quad to screen. Each Sprite store all nessecary vertex buffers, shaders and parameters.
		 * Sprite objects store name for identification. If it is text(each letter is another Sprite Instance)
		 * all parts have the same name - text itself.
		 */
		class Sprite
		{
		private:
			std::string name;
			AyumiResource::Texture* spriteTexture;
			AyumiResource::Shader* spriteShader;
			AyumiResource::Mesh* spriteMesh; 
			AyumiUtils::VertexArrayObject* spriteVao;
			AyumiUtils::VertexBufferObject* spriteVbo;
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D size;
			float alpha;
			
			void initializeSpriteMesh();
			void initializeSpriteBuffers();
			void multiplyUVCoordinates();
			
		public:
			Sprite();
			Sprite(AyumiResource::Texture* spriteTexture, const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& size, const float alpha);
			~Sprite();

			void initializeSprite(const float offsetX = 0.0f, const float offsetY = 0.0f);
			void attachRenderObjects();
			void detachRenderObjects();
			void setCharsetCoordinates(const float x, const float y);
		
			AyumiMath::Vector3D getPosition() const;
			AyumiMath::Vector3D getSize() const;
			AyumiResource::Texture* getTexture() const;
			AyumiResource::Shader* getShader() const;
			std::string getName() const;
			float getAlpha() const;
			
			void setPosition(const float x, const float y);
			void setSize(const float width, const float height);
			void setShader(AyumiResource::Shader* spriteShader);
			void setTexture(AyumiResource::Texture* spriteTexture);
			void setName(const std::string& name);
			void setAlpha(const float alpha);
		};
	}
}
#endif
