/**
 * File contains declaration of Texture class.
 * @file    Texture.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-09
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Resource.hpp"
#include "TextureType.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represents one of basic Engine resource - Texture resource. Texture is bacis
		 * element of all 3D engine and games, where it is used in geometry mesh mapping. In Engine,
		 * textures are used in Entity Materials, 2D Sprites, Canvas and post-process effects.
		 */
		class Texture : public Resource
		{
		protected:
			GLuint texture;
			TextureType type;
		public:
			Texture();
			Texture(const char* name, const char* filePath);
			Texture(const Texture& resource);
			~Texture();

			void setTexture(const GLuint texture);
			void setTextureType(const TextureType& type);
			
			GLuint* getTexture();
			TextureType getType() const;
		};
	}
}
#endif
