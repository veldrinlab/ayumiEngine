/**
 * File contains definition of MeshManager class.
 * @file    MeshManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-23
 */

#include "MeshManager.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class constructor with initialize parameters. Create and prepare resource loading script.
		 * @param	scriptFileName is name of resource loading script.
		 */
		MeshManager::MeshManager(const char* scriptFileName)
		{
			meshFactory = new MeshFactory();
			resourceScript = new AyumiScript(scriptFileName);
			prepareResourceScript();		
		}

		/**
		 * Class destructor, free allocated memory. Relese all resources and mesh factory.
		 */
		MeshManager::~MeshManager()
		{
			delete resourceScript;
			delete meshFactory;
			clearResources();
		}

		/**
		 * Method is used to execute resource loading script.
		 */
		void MeshManager::initializeResources()
		{
			resourceScript->executeScript();
		}

		/**
		 * Method is used to update mesh resources collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void MeshManager::updateResources(const string& scriptPath)
		{
			resourceScript->setScriptFile(scriptPath.c_str());
			resourceScript->executeScript();
		}

		/**
		 * Private method which is used to prepare loading script. By using Luabind engine register Manager class
		 * to Lua namespace and bind global pointer to manager object.
		 */
		void MeshManager::prepareResourceScript()
		{
			luabind::module(resourceScript->getVirtualMachine())
			[
				luabind::class_<MeshManager>("MeshManager")
				.def("registerResource",&MeshManager::registerResource)
				.def("releaseResource",&MeshManager::releaseResource)
				.def("clearResources",&MeshManager::clearResources)
				.def("setRawParameters",&MeshManager::setRawParameters)
			];

			luabind::globals(resourceScript->getVirtualMachine())["MeshManager"] = this;
		}

		/**
		 * Private method which is used to register new resource to manager container. It can be called from Lua script.
		 * @param	name is new resource name id.
		 * @param	type is new resource type.
		 * @param	path is new resource file path.
		 */
		void MeshManager::registerResource(const string& name, const string& type, const string& path)
		{
			Mesh* meshResource = nullptr;
			meshResource = meshFactory->createMeshResource(name,type,path);
			addResource(name,meshResource);
		}

		/**
		 * Private method which is used to release resource from manager container. It can be called from Lua script.
		 * @param	name is resource name id.
		 */
		void MeshManager::releaseResource(const string& name)
		{
			map<string,Mesh*>::const_iterator it = resourceMap.begin();
			for(; it != resourceMap.end(); ++it)
				if((*it).first == name)
					break;

			if(it != resourceMap.end())
			{
				if((*it).second->isComponentMesh())
					delete [] (*it).second;
				else
					delete (*it).second;
				deleteResource(name);
			}
		}

		/**
		 * Private method which is used to release all resources from manager container. It can be called from Lua script.
		 */
		void MeshManager::clearResources()
		{
			for(map<string,Mesh*>::const_iterator it = resourceMap.begin(); it != resourceMap.end(); ++it)
			{
				if((*it).second->isComponentMesh())
					delete [] (*it).second;
				else
					delete (*it).second;
			}
			clearResourceMap();
		}

		/**
		 * Private method which is used to set raw mesh file loading parameters.
		 * @param	size is raw file size;
		 * @param	rowScale is raw mesh row scale.
		 * @param	columnScale is raw mesh column scale.
		 * @param	heightScale is raw mesh height scale.
		 * @param	maxCoord is raw mesh max coord.
		 */
		void MeshManager::setRawParameters(const int size, const float rowScale, const float columnScale, const float heightScale, const float maxCoord)
		{
			meshFactory->initRawParameters(size,rowScale,columnScale,heightScale,maxCoord);
		}
	}
}
