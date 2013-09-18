/**
 * File contains definition of TextureManager class.
 * @file    TextureManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-23
 */

#include "TextureManager.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class constructor with initialize parameters. Create and prepare resource loading script.
		 * @param	scriptFileName is name of resource loading script.
		 */
		TextureManager::TextureManager(const char* scriptFileName)
		{
			textureFactory = new TextureFactory();
			resourceScript = new AyumiScript(scriptFileName);
			prepareResourceScript();

			textureFactory->initializeFactory();
		}

		/**
		 * Class destructor, free allocated memory for loading script.
		 */
		TextureManager::~TextureManager()
		{
			clearResourceMap();
			delete textureFactory;
			delete resourceScript;
		}

		/**
		 * Method is used to execute resource loading script.
		 */
		void TextureManager::initializeResources()
		{
			resourceScript->executeScript();
		}

		/**
		 * Method is used to update texture resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void TextureManager::updateResources(const string& scriptPath)
		{
			resourceScript->setScriptFile(scriptPath.c_str());
			resourceScript->executeScript();
		}

		/** 
		 * Private method which is used to prepare loading script. By using Luabind engine register Manager class
		 * to Lua namespace and bind global pointer to manager object.
		 */
		void TextureManager::prepareResourceScript()
		{
			luabind::module(resourceScript->getVirtualMachine())
			[
				luabind::class_<TextureManager>("TextureManager")
				.def("registerResource",(void(TextureManager::*)(const string&, const string&, const string&))&TextureManager::registerResource)
				.def("registerResource",(void(TextureManager::*)(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&))&TextureManager::registerResource)
				.def("releaseResource",&TextureManager::releaseResource)
				.def("clearResources",&TextureManager::clearResources)
			];

			luabind::globals(resourceScript->getVirtualMachine())["TextureManager"] = this;
		}
		/**
		 * Private method which is used to register new resource to manager container. It can be called from Lua script.
		 * @param	name is new resource name id.
		 * @param	path is new resource file path.
		 * @param	type is new resource type.
		 */
		void TextureManager::registerResource(const string& name, const string& path, const string& type)
		{
			Texture* textureResource = nullptr;
			textureResource = textureFactory->createTextureResource(name,path,string(),string(),string(),string(),string(),type);
			addResource(name,TextureResource(textureResource));
		}

		/**
		 * Private method which is used to register new resource to manager container. It can be called from Lua script.
		 * @param	name is new resource name id.
		 * @param	path is new resource file layer path.
		 * @param	path2 is new resource file layer path.
		 * @param	path3 is new resource file layer path.
		 * @param	path4 is new resource file layer path.
		 * @param	path5 is new resource file layer path.
		 * @param	path6 is new resource file layer path.
		 * @param	type is new resource type.
		 */
		void TextureManager::registerResource(const string& name, const string& path, const string& path2, const string& path3,const string& path4, const string& path5, const string& path6, const string& type)
		{
			Texture* textureResource = nullptr;
			textureResource = textureFactory->createTextureResource(name,path,path2,path3,path4,path5,path6,type);
			addResource(name,TextureResource(textureResource));
		}

		/**
		 * Private method is used to release resource from manager container. It can be called from Lua script.
		 * @param	name is resource name id.
		 */
		void TextureManager::releaseResource(const string& name)
		{
			deleteResource(name);
		}

		/**
		 * Private method which is used to release all resources from manager container. It can be called from Lua script.
		 */
		void TextureManager::clearResources()
		{
			clearResourceMap();
		}
	}
}
