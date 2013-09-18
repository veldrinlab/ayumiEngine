/**
 * File contains declaration and definition of TextureType enumeration.
 * @file    TextureType.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-13
 */

#ifndef TEXTURETYPE_HPP
#define TEXTURETYPE_HPP

#include <GL/glew.h>

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Enumeration represents all available tetxure resource type.
		 */
		enum TextureType
		{
			UNKNOWN,
			TEXTURE1D = GL_TEXTURE_1D,
			TEXTURE2D = GL_TEXTURE_2D,
			TEXTURE3D = GL_TEXTURE_3D,
			CUBE_MAP = GL_TEXTURE_CUBE_MAP,
			RECTANGLE = GL_TEXTURE_RECTANGLE
		};
	}
}
#endif
