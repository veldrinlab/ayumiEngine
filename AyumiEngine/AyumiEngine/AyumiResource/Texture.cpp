/**
 * File contains declaration of Texture class.
 * @file    Texture.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-09
 */

#include "Texture.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Set object default values.
		 */
		Texture::Texture()
		{
			resourceType = TEXTURE;
			type = UNKNOWN;
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	name is texture resource name.
		 * @param	filePath is texture resource file path.
		 */
		Texture::Texture(const char* name, const char* filePath)
		{
			resourcePath = filePath;
			resourceName = name;
			resourceType = TEXTURE;
			type = UNKNOWN;
		}

		/**
		 * Class copy constructor.
		 * @param	texture is copy source object.
		 */
		Texture::Texture(const Texture& texture)
		{
			resourcePath = texture.resourcePath;
			resourceName = texture.resourceName;
			resourceType = TEXTURE;
			type = texture.getType();
			this->texture = texture.texture;
		}

		/**
		 * Class destructor, free allocated memory. Delete texture.
		 */
		Texture::~Texture()
		{
			glDeleteTextures(1,&texture);
		}

		/**
		 * Setter of private texture id member.
		 * @param	texture is texture id.
		 */
		void Texture::setTexture(const GLuint texture)
		{
			this->texture = texture;
		}

		/**
		 * Setter of private texture type enumeration.
		 * @param	type is new texture type enumeration.
		 */
		void Texture::setTextureType(const TextureType& type)
		{
			this->type = type;
		}

		/**
		 * Accessor to texture variable.
		 * @return	value of texture variable.
		 */
		GLuint* Texture::getTexture() 
		{
			return &texture;
		}

		/**
		 * Accessor to texture type member.
		 * @return	texture type enumeration.
		 */
		TextureType Texture::getType() const
		{
			return type;
		}
	}
}
