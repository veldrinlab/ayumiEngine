/**
 * File contains declaration of TextureFactory class.
 * @file    TextureFactory.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-02
 */

#ifndef TEXTUREFACTORY_HPP
#define TEXTUREFACTORY_HPP

#include <IL/il.h>
#include <string>
#include <fstream>

#include "Texture.hpp"
#include "TextureType.hpp"

#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represents one of Engine ResourceManager/TextureManager subclass - TextureFactory
		 * which is used by TextureManager to create all supported types of texture:
		 * texture 1d/2d/3d, cube maps and rectangle texture. Class has methods to
		 * load all kind of texture resources and store it in TextureManager class.
		 * It is implementation of simple Factory design pattern.
		 */
		class TextureFactory
		{
		private:
			Texture* createTexture1D(const std::string& name, const std::string& path);
			Texture* createTexture2D(const std::string& name, const std::string& path);
			Texture* createTexture3D(const std::string& name, const std::string& path);
			Texture* createRectangleTexture(const std::string& name, const std::string& path);
			Texture* createCubeMapTexture(const std::string& name, const std::string& path, const std::string& path2,
									const std::string& path3, const std::string& path4, const std::string& path5,
									const std::string& path6);
		public:
			TextureFactory();
			~TextureFactory();

			void initializeFactory();
			Texture* createTextureResource(const std::string& name, const std::string& path, const std::string& path2,
									const std::string& path3, const std::string& path4, const std::string& path5,
									const std::string& path6, const std::string& type);

		};
	}
}
#endif
