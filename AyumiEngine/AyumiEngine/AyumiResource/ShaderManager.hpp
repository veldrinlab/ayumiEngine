/**
 * File contains declaration of ShaderManager class.
 * @file    ShaderManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-12
 */

#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <boost/shared_ptr.hpp>

#include "ShaderFactory.hpp"
#include "../AyumiScript.hpp"
#include "../AyumiUtils/Manager.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		typedef boost::shared_ptr<Shader> ShaderResource;

		/**
		 * Class represnets one of Engine ResourceManager subclass.  ShaderManager extends templated Manager pattern.
		 * It is used to load and store Shader objects. It support loading of classic vertex and fragment shader and
		 * building shader program. It use ShaderFactory to load supported resources. 
		 */
		class ShaderManager : public AyumiUtils::Manager<std::string,ShaderResource>
		{
		private:
			ShaderFactory* shaderFactory;
			AyumiScript* resourceScript;

			void prepareResourceScript();
			void registerResource(const std::string& name, const std::string& type, const std::string& vertPath, const std::string& fragPath);
			void registerResource(const std::string& name, const std::string& type, const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);
			void releaseResource(const std::string& name);
			void clearResources();
		public:
			ShaderManager(const char* scriptFileName);
			~ShaderManager();

			void initializeResources();
			void updateResources(const std::string& scriptPath);
		};
	}
}
#endif
