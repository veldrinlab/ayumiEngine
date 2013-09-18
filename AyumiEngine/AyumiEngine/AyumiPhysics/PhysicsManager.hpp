/**
 * File contains declaraion of PhysicsManager class.
 * @file    PhysicsManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-18
 */

#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include "PhysicsUtils.hpp"
#include "CollisionHandler.hpp"

#include "../Logger.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiPhysics
	{
		/**
		 * Class represents one of main Engine modules which is used to store and simulate engine physics data.
		 * Engine use NVIDIA PhysX3 library to calculate physics simulations. Manager store data of scene actors,
		 * detect and handle collision between them. User must add new actor - static or dynamic(can be also heightField
		 * type), set collision filter group and set up collision callback which is simple boost::function object connected
		 * with pair of defined actors.
		 */
		class PhysicsManager
		{
		private:
			PxPhysics* physicsSDK;
			PxScene* scene;
			CollisionHandler* collisionHandler;
			PhysicsMaterials materials;
			StaticActors staticActors; 
			DynamicActors dynamicActors; 
			PxDefaultErrorCallback defaultErrorCallback;
			PxDefaultAllocator defaultAllocatorCallback;
			PxSimulationFilterShader defaultFilterShader;
			PxCooking* cooking;

			void initializeScene();
			void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);
		public:
			PhysicsManager();
			~PhysicsManager();

			void initializePhysicsManager();
			void simulatePhysics(const float elapsedTime);
			void getSimulationResults();
			void updatePhysics();
			void updateForce();

			void addStaticActor(AyumiScene::SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask);
			void addDynamicActor(AyumiScene::SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask);
			void addHeightFieldActor(AyumiScene::SceneEntity* entity, unsigned char* heightData, const AyumiMath::Vector4D& params, PxU32 filterGroup, PxU32 filterMask); 
			void removeStaticActor(const std::string& name);
			void removeDynamicActor(const std::string& name);
			void setGravity(const AyumiMath::Vector3D& gravity);
			void addPhysicsMaterial(const std::string& name, const AyumiMath::Vector3D& params);
			void addCollisionCallback(const std::string& name, const std::string& name2, boost::function<void()> method);
			void addJoint(const std::string& name, const std::string& name2, const float force, const float torque);
			std::string rayCastTest(const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& direction, const float rayLength);
			CollisionActors getCollisionActors();
		};
	}
}
#endif
