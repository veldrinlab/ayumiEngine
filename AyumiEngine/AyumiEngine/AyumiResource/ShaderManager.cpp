/**
 * File contains definition of ShaderManager class.
 * @file    ShaderManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-12
 */

#include "ShaderManager.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class constructor with initialize parameters. Create and prepare resource loading script.
		 * @param	scriptFileName is name of resource loading script.
		 */
		ShaderManager::ShaderManager(const char* scriptFileName)
		{
			shaderFactory = new ShaderFactory();
			resourceScript = new AyumiScript(scriptFileName);
			prepareResourceScript();	
		}

		/**
		 * Class destructor, free allocated memory for loading script.
		 */
		ShaderManager::~ShaderManager()
		{
			clearResourceMap();
			delete shaderFactory;
			delete resourceScript;
		}

		/**
		 * Method is used to execute resource loading script.
		 */
		void ShaderManager::initializeResources()
		{
			resourceScript->executeScript();
		}

		/**
		 * Method is used to update shader resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void ShaderManager::updateResources(const string& scriptPath)
		{
			resourceScript->setScriptFile(scriptPath.c_str());
			resourceScript->executeScript();
		}

		/**
		 * Private method which is used to prepare loading script. By using Luabind engine register Manager class
		 * to Lua namespace and bind global pointer to manager object.
		 */
		void ShaderManager::prepareResourceScript()
		{
			luabind::module(resourceScript->getVirtualMachine())
			[
				luabind::class_<ShaderManager>("ShaderManager")
				.def("registerResource",(void(ShaderManager::*)(const string&, const string&, const string&, const string&))&ShaderManager::registerResource)
				.def("registerResource",(void(ShaderManager::*)(const string&, const string&, const string&, const string&, const string&))&ShaderManager::registerResource)
				.def("releaseResource",&ShaderManager::releaseResource)
				.def("clearResources",&ShaderManager::clearResources)
			];
			luabind::globals(resourceScript->getVirtualMachine())["ShaderManager"] = this;
		}

		/**
		 * Private method which is used to register new resource to manager container. It can be called from Lua script.
		 * @param	name is new resource name id.
		 * @param	type is GLSL shader type.
		 * @param	vertPath is new vertex shader source path.
		 * @param	fragPath is new fragment shader source path.
		 */
		void ShaderManager::registerResource(const string& name, const string& type, const string& vertPath, const string& fragPath)
		{
			Shader* shaderResource = nullptr;
			shaderResource = shaderFactory->createShaderResource(name,type,vertPath,string(),fragPath);
			addResource(name,ShaderResource(shaderResource));
		}

		/**
		 * Private method which is used to register new resource to manager container. It can be called from Lua script.
		 * @param	name is new resource name id.
		 * @param	type is GLSL shader type.
		 * @param	vertPath is new vertex shader source path.
		 * @param	fragPath is new fragment shader source path.
		 * @paam	geomPath is new geometry shader source path.
		 */
		void ShaderManager::registerResource(const string& name, const string& type, const string& vertPath, const string& fragPath, const string& geomPath)
		{
			Shader* shaderResource = nullptr;
			shaderResource = shaderFactory->createShaderResource(name,type,vertPath,geomPath,fragPath);
			addResource(name,ShaderResource(shaderResource));
		}

		/**
		 * Private method which is used to release resource from manager container. It can be called from Lua script.
		 * @param	name is resource name id.
		 */
		void ShaderManager::releaseResource(const string& name)
		{
			deleteResource(name);
		}

		/**
		 * Private method which is used to release all resources from manager container. It can be called from Lua script.
		 */
		void ShaderManager::clearResources()
		{
			clearResourceMap();
		}
	}
}
