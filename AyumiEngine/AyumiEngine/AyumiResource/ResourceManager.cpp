/**
 * File contains definition of ShaderManager class.
 * @file    ShaderManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-10
 */

#include "ResourceManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiCore;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Set up subsystems and executes loading scripts.
		 */
		ResourceManager::ResourceManager()
		{
			meshManager = new MeshManager(Configuration::getInstance()->getMeshScriptName()->c_str());
			textureManager = new TextureManager(Configuration::getInstance()->getTextureScriptName()->c_str());	
			shaderManager = new ShaderManager(Configuration::getInstance()->getShaderScriptName()->c_str());

			meshManager->initializeResources();
			textureManager->initializeResources();
			shaderManager->initializeResources();
		}

		/**
		 * Class destructor, free allocated memeory for object subsystems.
		 */
		ResourceManager::~ResourceManager()
		{
			delete textureManager;
			delete shaderManager;
			delete meshManager;
		}

		/**
		 * Method is used to update mesh resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void ResourceManager::updateMeshResources(const string& scriptPath)
		{
			meshManager->updateResources(scriptPath);
		}

		/**
		 * Method is used to update texture resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void ResourceManager::updateTextureResources(const string& scriptPath)
		{
			textureManager->updateResources(scriptPath);
		}

		/**
		 * Method is used to update shader resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void ResourceManager::updateShaderResources(const string& scriptPath)
		{
			shaderManager->updateResources(scriptPath);
		}

		/**
		 * Accessor to engine Mesh resource container. If resource doesn't exist manager will try to load
		 * it or they will return default resource with error log.
		 * @param	name is resource id.
		 * @return	pointer to mesh resource.
		 */
		Mesh* ResourceManager::getMeshResource(const string& name)
		{
			Mesh* resource = meshManager->getResource(name);
			
			if(resource == nullptr)
			{
				Logger::getInstance()->saveLog(Log<string>("Error loading mesh resource: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
			
			return resource;
		}

		/**
		 * Accessor to engine Texture resource container. If resource doesn't exist manager will try to load
		 * it or they will return default resource with error log.
		 * @param	name is resource id.
		 * @return	shared pointer to texture resource.
		 */
		TextureResource ResourceManager::getTextureResource(const string& name)
		{
			TextureResource resource = textureManager->getResource(name);
			
			if(resource == nullptr)
			{
				Logger::getInstance()->saveLog(Log<string>("Error loading texture resource: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}
			
			return resource;
		}

		/**
		 * Accessor to engine Shader resource container. If resource doesn't exist manager will try to load
		 * it or they will return default resource with error log.
		 * @param	name is resource id.
		 * @return	shared pointer to Shader resource.
		 */
		ShaderResource ResourceManager::getShaderResource(const string& name)
		{
			ShaderResource resource = shaderManager->getResource(name);
			
			if(resource == nullptr)
			{
				Logger::getInstance()->saveLog(Log<string>("Error loading shader resource: "));
				Logger::getInstance()->saveLog(Log<string>(name));
			}

			return resource;
		}
	}
}
