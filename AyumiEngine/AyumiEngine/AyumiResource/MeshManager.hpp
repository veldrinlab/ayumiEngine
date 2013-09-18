/**
 * File contains declaration of MaterialManager class.
 * @file    MaterialManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-23
 */

#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include <boost/shared_ptr.hpp>

#include "MeshFactory.hpp"
#include "../AyumiScript.hpp"
#include "../AyumiUtils/Manager.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		//typedef boost::shared_ptr<Mesh> MeshResource;
		
		/**
		 * Class represnets one of Engine ResourceManager subclass. MeshManager extends templated Manager pattern.
		 * It is used to load and store Mesh objects using AyumiScript. It can load model formats descriped in
		 * Engine documentation and even create procedural Mesh resources. It use MeshFactory to load supported 
		 * resources. 
		 */
		class MeshManager : public AyumiUtils::Manager<std::string,Mesh*>
		{
		private:
			MeshFactory* meshFactory;
			AyumiScript* resourceScript;
			
			void prepareResourceScript();
			void registerResource(const std::string& name, const std::string& type,const std::string& path);
			void releaseResource(const std::string& name);
			void clearResources();
			void setRawParameters(const int size, const float rowScale, const float columnScale, const float heightScale, const float maxCoord);
		public:
			MeshManager(const char* scriptFileName);
			~MeshManager();

			void initializeResources();
			void updateResources(const std::string& scriptPath);
		};
	}
}
#endif
