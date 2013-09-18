/**
 * File contains AyumiPhysics utility functons, structures and typedefs.
 * @file    PhysicsUtils.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-18
 */

#ifndef PHYSICSUTILS_HPP
#define PHYSICSUTILS_HPP

#include <PhysXAPI/PxPhysicsAPI.h>
#include <PhysXAPI/extensions/PxExtensionsAPI.h>
#include <PhysXAPI/extensions/PxDefaultErrorCallback.h>
#include <PhysXAPI/extensions/PxDefaultAllocator.h> 
#include <PhysXAPI/extensions/PxDefaultCpuDispatcher.h>
#include <PhysXAPI/extensions/PxDefaultSimulationFilterShader.h>
#include <PhysXAPI/extensions/PxShapeExt.h>
#include <PhysXAPI/cooking/PxCooking.h>
//#include <PhysXAPI/PxTkStream.h>

#include <vector>
#include <string>

#include "../AyumiScene/SceneEntity.hpp"

namespace AyumiEngine
{
	namespace AyumiPhysics
	{
		/**
		 * Structure represents connector between dynamic SceneEntity logic and physics which is stored by PhysX manager.
		 */
		struct DynamicActor
		{
			AyumiScene::SceneEntity* entityLogic;
			PxRigidDynamic* entityPhysics;
			PxU32 shapesAmount;
			PxShape** shapes;
		};

		/**
		 * Structure represents connector between static SceneEntity logic and physics which is stored by PhysX manager.
		 */
		struct StaticActor
		{
			AyumiScene::SceneEntity* entityLogic;
			PxRigidStatic* entityPhysics;
		};

		/**
		 * Few typedef which is used in PhysicsManager to make source code smmother.
		 */
		typedef std::pair<std::string,PxMaterial*> PhysicMaterial;
		typedef std::vector<PhysicMaterial> PhysicsMaterials;
		typedef std::vector<StaticActor*> StaticActors; 
		typedef std::vector<DynamicActor*> DynamicActors; 

		/**
		 * Enumeration represents all available physics actors shape types.
		 */
		enum ShapeType
		{
			PLANE,
			BOX,
			SPHERE,
			CAPSULE,
			CONVEX
		};

		/**
		 * Static method which is used to filter and configure collision detection between pairs of physics actors.
		 * This function is only called by PhysX itself.
		 * @param	attributes0 is some PxFilter attributes of first actor.
		 * @param	filterData0 is some PxFilterData of first actor.
		 * @param	attributes1 is some PxFilter attributes of second actor.
		 * @param	filterData1 is some PxFilterData of second actor.
		 * @param	pairFlags is reference to pair flags.
		 * @param	constantBlock is pointer to some data. Only NVIDIA guys know what the fuck is this.
		 * @param	constantBlockSize is size of constant data block.
		 * @return	filter flags.
		 */
		static PxFilterFlags filterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
		{
			if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
			{
				pairFlags = PxPairFlag::eTRIGGER_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_PERSISTS;
				return PxFilterFlag::eDEFAULT;
			}
			
			pairFlags = PxPairFlag::eCONTACT_DEFAULT;
			if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
				pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
	
			return PxFilterFlag::eDEFAULT;
		}
	}
}
#endif
