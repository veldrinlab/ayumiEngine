/**
 * File contains declaration of TextureManager class.
 * @file    TextureManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-23
 */

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <boost/shared_ptr.hpp>

#include "TextureFactory.hpp"
#include "../AyumiScript.hpp"
#include "../AyumiUtils/Manager.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		typedef boost::shared_ptr<Texture> TextureResource;

		/**
		 * Class represnets one of Engine ResourceManager subclass. TextureManager extends templated Manager pattern.
		 * It is used to load and store Texture objects using AyumiScript. It can load any format that is supported
		 * by Devil library and translate it to any texture type that is descriped in Engine documentation. It use
		 * TextureFactory to load supported resources.
		 */
		class TextureManager : public AyumiUtils::Manager<std::string,TextureResource>
		{
		private:
			TextureFactory* textureFactory;
			AyumiScript* resourceScript;
			
			void prepareResourceScript();
			void registerResource(const std::string& name, const std::string& path, const std::string& type);
			void registerResource(const std::string& name, const std::string& path, const std::string& path2,
									const std::string& path3,const std::string& path4, const std::string& path5,
									const std::string& path6, const std::string& type);
			void releaseResource(const std::string& name);
			void clearResources();
		public:
			TextureManager(const char* scriptFileName);
			~TextureManager();

			void initializeResources();
			void updateResources(const std::string& scriptPath);
		};
	}
}
#endif
