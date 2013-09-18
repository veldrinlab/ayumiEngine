/**
 * File contains declaration of ShaderFactory class.
 * @file    ShaderFactory.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-12
 */

#ifndef SHADERFACTORY_HPP
#define SHADERFACTORY_HPP

#include <string>

#include "Shader.hpp"
#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiResource	
	{
		/**
		 * Class represents one of Engine ResourceManager/ShaderManager subclass - ShaderFactory
		 * which is used by ShaderManager to create all supported types of shader programs:
		 * vertex+fragment, vertex+geometry+fragment. Class has methods to load and compile
		 * all kind of shader resources and store it in ShaderManager class. It is implementation of
		 * simple Factory design pattern.
		 */
		class ShaderFactory
		{
		private:
			Shader* createVertexFragmentShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
			Shader* createVertexGeometryFragmentShader(const std::string& names, const std::string& vertPath, const std::string& geomPath, const std::string& fragPath);
			char* loadShaderSource(const char* shaderFileName);

		public:
			ShaderFactory();
			~ShaderFactory();

			Shader* createShaderResource(const std::string& name, const std::string& type, const std::string& vertPath, const std::string& geomPath, const std::string& fragPath);
		};
	}
}
#endif
