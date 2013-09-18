/**
 * File contains definition of ShaderFactory class.
 * @file    ShaderFactory.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#include "ShaderFactory.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Nothing to do.
		 */
		ShaderFactory::ShaderFactory()
		{

		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		ShaderFactory::~ShaderFactory()
		{

		}

		/**
		 * Method is used to create shader resource. It implement Factory Method, depends on resource name
		 * factory choose creating method.
		 * @param	name is resource name.
		 * @param	type is name of resource type.
		 * @param	vertPath is resource vertex shader file path.
		 * @param	geomPath is resource geometry shader file path.
		 * @param	fragPath is resource fragment shader file path.
		 * @return	loaded and created shader resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Shader* ShaderFactory::createShaderResource(const string& name, const string& type, const string& vertPath, const string& geomPath, const string& fragPath)
		{
			Shader* shaderResource = nullptr;

			if(type == "VertexFragment")
				shaderResource = createVertexFragmentShader(name,vertPath,fragPath);
			else if(type == "VertexGeometryFragment")
				shaderResource = createVertexGeometryFragmentShader(name,vertPath,geomPath,fragPath);
			else
			{
				Logger::getInstance()->saveLog(Log<string>("Undefined shader type requested!"));
				shaderResource = nullptr;
			}

			return shaderResource;
		}

		/**
		 * Method is used to create Shader object. Create Vertex and Fragment shaders, validate it, compile
		 * and create shader program.
		 * @param	name is shader name.
		 * @param	vertPath is source code of Vertex Shader.
		 * @param	fragPath is source code of Fragment Shader.
		 * @return	loaded and created shader resource, or nullptr when and logger error type is
		 *			not supported.
		 */	
		Shader* ShaderFactory::createVertexFragmentShader(const string& name, const string& vertPath, const string& fragPath)
		{
			Shader* shaderResource = nullptr;

			shaderResource = new Shader(name.c_str());
			shaderResource->setVertexPath(vertPath.c_str());
			shaderResource->setFragmentPath(fragPath.c_str());

			shaderResource->createVertexShader();
			shaderResource->createFragmentShader();
			
			const char* vertexShaderSource = loadShaderSource(vertPath.c_str());
			const char* fragmentShaderSource = loadShaderSource(fragPath.c_str());

			if(vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
			{
				Logger::getInstance()->saveLog(Log<string>("Shader loading error detected: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
			
			glShaderSource(shaderResource->getShaderVertex(),1,&vertexShaderSource,0);
			glShaderSource(shaderResource->getShaderFragment(),1,&fragmentShaderSource,0);	
			glCompileShader(shaderResource->getShaderVertex());
			glCompileShader(shaderResource->getShaderFragment());
			shaderResource->createShaderProgram();
			glAttachShader(shaderResource->getShaderProgram(),shaderResource->getShaderVertex());
			glAttachShader(shaderResource->getShaderProgram(),shaderResource->getShaderFragment());
			glLinkProgram(shaderResource->getShaderProgram());

			delete vertexShaderSource;
			delete fragmentShaderSource;

			return shaderResource;
		}

		/**
		 * Method is used to create Shader object. Create Vertex, Geometry and Fragment shaders, validate it, compile
		 * and create shader program.
		 * @param	name is shader name.
		 * @param	vertPath is source code of Vertex Shader.
		 * @param	geomPath is source code of Geometry Shader.
		 * @param	fragPath is source code of Fragment Shader.
		 * @return	loaded and created shader resource, or nullptr when and logger error type is
		 *			not supported.
		 */	
		Shader* ShaderFactory::createVertexGeometryFragmentShader(const string& name, const string& vertPath, const string& geomPath, const string& fragPath)
		{
			Shader* shaderResource = nullptr;
			
			shaderResource = new Shader(name.c_str());
			shaderResource->setVertexPath(vertPath.c_str());
			shaderResource->setGeometryPath(geomPath.c_str());
			shaderResource->setFragmentPath(fragPath.c_str());

			shaderResource->createVertexShader();
			shaderResource->createGeometryShader();
			shaderResource->createFragmentShader();
			
			const char* vertexShaderSource = loadShaderSource(vertPath.c_str());
			const char* geometryShaderSource = loadShaderSource(geomPath.c_str());
			const char* fragmentShaderSource = loadShaderSource(fragPath.c_str());

			if(vertexShaderSource == nullptr || geometryShaderSource == nullptr || fragmentShaderSource == nullptr)
			{
				Logger::getInstance()->saveLog(Log<string>("Shader loading error detected: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
			
			glShaderSource(shaderResource->getShaderVertex(),1,&vertexShaderSource,0);
			glShaderSource(shaderResource->getShaderGeometry(),1,&geometryShaderSource,0);
			glShaderSource(shaderResource->getShaderFragment(),1,&fragmentShaderSource,0);
			glCompileShader(shaderResource->getShaderVertex());
			glCompileShader(shaderResource->getShaderGeometry());
			glCompileShader(shaderResource->getShaderFragment());
			shaderResource->createShaderProgram();
			glAttachShader(shaderResource->getShaderProgram(),shaderResource->getShaderVertex());
			glAttachShader(shaderResource->getShaderProgram(),shaderResource->getShaderGeometry());
			glAttachShader(shaderResource->getShaderProgram(),shaderResource->getShaderFragment());
			glLinkProgram(shaderResource->getShaderProgram());

			delete vertexShaderSource;
			delete geometryShaderSource;
			delete fragmentShaderSource;

			return shaderResource;
		}

		/**
		 * Method is used to load Shader source code from file.
		 * @param	shaderFileName is path to shader program source code.
		 * @return	loaded shader source code string.
		 */
		char* ShaderFactory::loadShaderSource(const char* shaderFileName)
		{
			char* shaderSource = nullptr;
    
			if(shaderFileName != nullptr)
			{
				ifstream file;
				file.open(shaderFileName, ios::binary);
		
				if(file.is_open())
				{
					file.seekg(0,ios::end);
					int count = static_cast<int>(file.tellg());
					file.seekg(0,ios::beg);
			
					if(count > 0)
					{
						shaderSource = new char[count + 1];
						file.read(shaderSource, count * sizeof(char));
						shaderSource[count] = '\0';
					}
				}
				else
				{
					Logger::getInstance()->saveLog(Log<string>("Shader source file loading error detected: "));
					Logger::getInstance()->saveLog(Log<string>(string(shaderFileName)));
				}
				file.close();
			}

			return shaderSource;
		}
	}
}
