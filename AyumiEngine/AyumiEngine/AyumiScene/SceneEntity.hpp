/**
 * File contains declaration of SceneEntity class.
 * @file	SceneEntity.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-24
 */

#ifndef SCENEENTITY_HPP
#define SCENEENTITY_HPP

#include "SceneNode.hpp"

//#include "EntityLogic.hpp"
#include "EntityState.hpp"
#include "EntityGeometry.hpp"
#include "EntityMaterial.hpp"
#include "EntityPhysics.hpp"
#include <boost/function.hpp> 
#include "EntityUpdateType.hpp"

#include "../AyumiScript.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{	
		class SceneEntity;
		typedef boost::function<void (SceneEntity*,float)> UpdateFunction;	

		/**
		 * Structure represents SceneEntity logic data like update type and update script/function interface
		 * and functionality which will be used to update entity.
		 */
		struct EntityLogic
		{
			EntityUpdateType updateType;
			UpdateFunction updateFunction;
			AyumiScript* updateScript;
			lua_State* virtualMachine;
		};

		/**
		 * Class represents base element of engine scene - SceneEntity. All visibile game objects are scene entities.
		 * Each scene entity must have unique name and mesh/material name id which is used to get resources from ResourceManager.
		 * SceneEntity class is divided to five structure components which represents geometry, physics, material, state
		 * and logic. Scene entity can be updated by three independent way - by extending ScenEntity class, defining 
		 * update function or running Lua script.
		 */
		class SceneEntity : public SceneNode
		{
		private:
			void prepareUpdateScript();	
			luabind::object getEntityPosition() const;
			luabind::object getEntityOrientation() const;
			luabind::object getEntityScale() const;

		public:
			std::string entityName;
			std::string geometryName;
			std::string materialName;
			EntityGeometry entityGeometry;
			EntityPhysics entityPhysics;
			EntityMaterial entityMaterial;
			EntityState entityState;
			EntityLogic entityLogic;

			SceneEntity(const std::string& entityName, const std::string& meshName, const std::string& materialName);
			virtual ~SceneEntity();

			virtual void updateEntity(const float elapsedTime) {};
			void initializeSceneEntity();
			void setGeometryData(AyumiResource::Mesh* geometryMesh);
			void configureGeometryAttributes();
			void attachMaterial();
			void detachMaterial();

			void setEntityPosition(const float x, const float y, const float z);
			void setEntityOrientation(const float x, const float y, const float z);
			void setEntityScale(const float x, const float y, const float z);		
			void setExtendingUpdating();
			void setFunctionUpdating(UpdateFunction updateFunction);
			void setScriptUpdatating(const char* scriptName);
		};
	}
}
#endif
