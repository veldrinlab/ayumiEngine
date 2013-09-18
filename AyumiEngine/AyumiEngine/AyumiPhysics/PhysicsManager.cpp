/**
 * File contains definition of PhysicsManager class.
 * @file    PhysicsManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-18
 */

#include "PhysicsManager.hpp"

using namespace std;
//using namespace PxToolkit;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiPhysics
	{
		/**
		 * Class default constructor. Create PhysiX SDK object and collision handler.
		 */
		PhysicsManager::PhysicsManager()
		{	
			physicsSDK = PxCreatePhysics(PX_PHYSICS_VERSION,defaultAllocatorCallback,defaultErrorCallback,PxTolerancesScale());
			if(physicsSDK == nullptr)
				Logger::getInstance()->saveLog(Log<string>("Physics SDK creation error occurred!"));
			collisionHandler = new CollisionHandler();
		}

		/**
		 * Class destructor, free allocated memory. Release PhysX object and remove actors and materials.
		 */
		PhysicsManager::~PhysicsManager()
		{
			delete collisionHandler;
			PxCloseExtensions();
			scene->release();
			cooking->release();
			physicsSDK->release();
		}

		/**
		 * Method is used to initialize physics manager, init PhysX extensions and cooking objects.
		 */
		void PhysicsManager::initializePhysicsManager()
		{
			if(!PxInitExtensions(*physicsSDK))
				Logger::getInstance()->saveLog(Log<string>("Physics Extensions initialization error occurred!"));
			
			PxFoundation& foundation = physicsSDK->getFoundation();
			cooking = PxCreateCooking(PX_PHYSICS_VERSION, &foundation, PxCookingParams());

			if(!cooking)
				Logger::getInstance()->saveLog(Log<string>("Physics Cooking creation error occurred!"));

			defaultFilterShader = filterShader;
			initializeScene();
			addPhysicsMaterial("Default",Vector3D(0.5,0.5,0.0));
			//PxExtensionVisualDebugger::connect(physicsSDK->getPvdConnectionManager(),"localhost",5425, 10000, true);
		}

		/**
		 * Method is used to run physics simulation.
		 * @param	elapsedTime is time between frames. For PhysX we use fixed, const time step for exampel 1/60 s.
		 */
		void PhysicsManager::simulatePhysics(const float elapsedTime)
		{
			scene->simulate(elapsedTime);
		}

		/**
		 * Method is used to get physics simulation results.
		 */
		void PhysicsManager::getSimulationResults()
		{
			while(!scene->fetchResults());
		}

		/**
		 * Method is used to apply forces to scene actors. Not only gravity can influent objects state.
		 * It is used in fracture implementation to apply forces to objects.
		 */
		void PhysicsManager::updateForce()
		{
			for(unsigned i = 0; i < dynamicActors.size(); ++i)
			{
				Vector3D v = dynamicActors[i]->entityLogic->entityState.position;
				PxVec3 force = PxVec3(dynamicActors[i]->entityLogic->entityPhysics.acceleration[0],dynamicActors[i]->entityLogic->entityPhysics.acceleration[1],dynamicActors[i]->entityLogic->entityPhysics.acceleration[2]);
				PxRigidBodyExt::setMassAndUpdateInertia(*dynamicActors[i]->entityPhysics,1.0);
				PxRigidBodyExt::addForceAtPos(*dynamicActors[i]->entityPhysics,force, PxVec3(v[0],v[1],v[2]), PxForceMode::eFORCE);
				dynamicActors[i]->entityLogic->entityPhysics.acceleration.set(0.0f,0.0f,0.0f);
			}
		}

		/**
		 * Method is used to update dynamic actors physics state.
		 */
		void PhysicsManager::updatePhysics()
		{
			for(unsigned i = 0; i < dynamicActors.size(); ++i)
			{
				if(dynamicActors[i]->entityLogic->entityPhysics.isKinematic)
				{
					PxTransform transformation;
					PxVec3 position = PxVec3(dynamicActors[i]->entityLogic->entityState.position[0],dynamicActors[i]->entityLogic->entityState.position[1],dynamicActors[i]->entityLogic->entityState.position[2]);
					PxQuat orientation = PxQuat(dynamicActors[i]->entityLogic->entityState.orientation[0],dynamicActors[i]->entityLogic->entityState.orientation[1],dynamicActors[i]->entityLogic->entityState.orientation[2],dynamicActors[i]->entityLogic->entityState.orientation[3]);
					transformation.p = position;
					transformation.q = orientation;
					dynamicActors[i]->entityPhysics->setGlobalPose(transformation);
				}
				else
				{
					dynamicActors[i]->entityPhysics->getShapes(dynamicActors[i]->shapes,dynamicActors[i]->shapesAmount);  
					PxTransform transformation = PxShapeExt::getGlobalPose(*dynamicActors[i]->shapes[0]);
					Quaternion q = Quaternion(transformation.q.x,transformation.q.y,transformation.q.z,transformation.q.w);
					Vector3D v = Vector3D(transformation.p.x,transformation.p.y,transformation.p.z);
					dynamicActors[i]->entityLogic->entityState.position = v;
					dynamicActors[i]->entityLogic->entityState.orientation = q;
				}
			}
		}

		/**
		 * Method is used to add new static actor to physics scene. Now only plane shape can be used.
		 * @param	entity is pointer to scene entity which will be added to physics simulation.
		 * @param	type is enumeration of shape type.
		 * @param	filterGroup is actor own id.
		 * @param	filterMask is mask to filter pairs that trigger a contact callback.
		 */
		void PhysicsManager::addStaticActor(SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask)
		{
			PxVec3 position;
			PxQuat orientation;
			PxTransform transformation;

			if(entity == nullptr)
			{
				 transformation = PxTransform(PxVec3(0.0f,1.0f,0.0f),PxQuat(PxHalfPi,PxVec3(0.0f, 0.0f, 1.0f)));
			}
			else
			{
				position = PxVec3(entity->entityState.position[0],entity->entityState.position[1],entity->entityState.position[2]);
				orientation = PxQuat(entity->entityState.orientation[0],entity->entityState.orientation[1],entity->entityState.orientation[2],entity->entityState.orientation[3]);
				transformation = PxTransform(position,orientation); 
			}

			PxRigidStatic* actor = nullptr;
			actor = physicsSDK->createRigidStatic(transformation);
			
			if(!actor)
				Logger::getInstance()->saveLog(Log<string>("Static Actor creation error occurred!"));
			
			PxShape* shape = nullptr;

			if(type == PLANE)
				shape = actor->createShape(PxPlaneGeometry(),*materials[0].second);
			else
				return;

			if(!shape)
				Logger::getInstance()->saveLog(Log<string>("Static Actor shape creation error occurred!"));
			
			actor->setName("World Plane");
			setupFiltering(actor,filterGroup,filterMask);
			scene->addActor(*actor);

			StaticActor* s = new StaticActor();
			s->entityLogic = entity;
			s->entityPhysics = actor;
			staticActors.push_back(s);
		}

		/**
		 * Method is used to add new dynamic actor to physics scene.
		 * @param	entity is pointer to scene entity which will be added to physics simulation.
		 * @param	type is enumeration of shape type.
		 * @param	filterGroup is actor own id.
		 * @param	filterMask is mask to filter pairs that trigger a contact callback.
		 */
		void PhysicsManager::addDynamicActor(SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask)
		{
			PxRigidDynamic* actor = nullptr;
			
			PxVec3 position = PxVec3(entity->entityState.position[0],entity->entityState.position[1],entity->entityState.position[2]);	
			PxQuat orientation = PxQuat(entity->entityState.orientation[0],entity->entityState.orientation[1],entity->entityState.orientation[2],entity->entityState.orientation[3]);
			PxReal density = 1.0f;
			PxTransform transformation = PxTransform(position,orientation); 

			if(type == BOX)
			{
				float x = (entity->entityGeometry.geometryBox->max.x() - entity->entityGeometry.geometryBox->min.x())*entity->entityState.scale.x()*0.5f;
				float y = (entity->entityGeometry.geometryBox->max.y() - entity->entityGeometry.geometryBox->min.y())*entity->entityState.scale.y()*0.5f;
				float z = (entity->entityGeometry.geometryBox->max.z() - entity->entityGeometry.geometryBox->min.z())*entity->entityState.scale.z()*0.5f;
				
				PxVec3 dimensions(x,y,z);
				actor = PxCreateDynamic(*physicsSDK,transformation,PxBoxGeometry(dimensions),*materials[0].second,density);
				PxRigidBodyExt::updateMassAndInertia(*actor, density);
			}
			else if(type == SPHERE)
			{
				float radius = entity->entityGeometry.geometrySphere->sphereRadius;
				actor = PxCreateDynamic(*physicsSDK,transformation,PxSphereGeometry(radius),*materials[0].second,density);
			}
			else if(type == CAPSULE)
			{
				float radius = entity->entityGeometry.geometrySphere->sphereRadius;
				actor = PxCreateDynamic(*physicsSDK,transformation,PxCapsuleGeometry(radius/2, radius),*materials[0].second,density);
			}
			else if(type == CONVEX)
			{
				/*int vertsCount = entity->entityGeometry.geometryMesh->getVerticesAmount();
				AyumiUtils::Vertex<>* verts = entity->entityGeometry.geometryMesh->getVertices();
				PxVec3* convexVerts = new PxVec3[vertsCount];

				for(int i = 0; i < vertsCount; ++i)
					convexVerts[i] = PxVec3(verts[i].x,verts[i].y,verts[i].z);

				PxConvexMeshDesc convexDesc;
				convexDesc.points.count = entity->entityGeometry.geometryMesh->getVerticesAmount();
				convexDesc.points.stride = sizeof(PxVec3);
				convexDesc.points.data = convexVerts;
				convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

				MemoryWriteBuffer buf;
				if(cooking->cookConvexMesh(convexDesc, buf))
				{
					PxConvexMesh* convexMesh = physicsSDK->createConvexMesh(MemoryReadBuffer(buf.data));
					actor = PxCreateDynamic(*physicsSDK,transformation,PxConvexMeshGeometry(convexMesh,PxMeshScale()),*materials[0].second,density);
				}
				else
				{
					Logger::getInstance()->saveLog(Log<string>("Convex Mesh creation error occurred!"));
					return;
				}*/
				//delete[] convexVerts;
			}
			else
			{
				Logger::getInstance()->saveLog(Log<string>("Dynamic Actor shape creation error occurred!"));
				return;
			}

			if(!actor)
				Logger::getInstance()->saveLog(Log<string>("Static Actor creation error occurred!"));
			
			PxRigidBodyExt::updateMassAndInertia(*actor, density);
			actor->setAngularDamping(0.75);
			actor->setLinearVelocity(PxVec3(0,0,0));
			actor->setName(entity->entityName.c_str());
			setupFiltering(actor,filterGroup,filterMask);
			scene->addActor(*actor);
			
			DynamicActor* d = new DynamicActor();
			d->entityLogic = entity;
			d->entityPhysics = actor;
			d->shapesAmount = actor->getNbShapes();
			d->shapes = new PxShape*[d->shapesAmount];
			dynamicActors.push_back(d);
		}

		/**
		 * Method is used to add heightfield actor to physics scene.
		 * @param	entity is actor logic object.
		 * @param	heightData is terrain height map data.
		 * @param	params is terrain parameters: heightmap size, row/column scale, max. height.
		 * @param	filterGroup is actor own id.
		 * @param	filterMask is mask to filter pairs that trigger a contact callback.
		 */
		void PhysicsManager::addHeightFieldActor(SceneEntity* entity, unsigned char* heightData, const Vector4D& params, PxU32 filterGroup, PxU32 filterMask)
		{
			int terrainSize = static_cast<int>(params.x());

			PxHeightFieldSample* samples = new PxHeightFieldSample[terrainSize*terrainSize];
			PxHeightFieldDesc descriptor;
			descriptor.nbColumns = static_cast<int>(terrainSize);
			descriptor.nbRows = static_cast<int>(terrainSize);
	
			for(int i = 0; i < terrainSize*terrainSize; ++i)
				samples[i].height = static_cast<PxI16>(heightData[i]);

			descriptor.samples.data = samples;
			descriptor.samples.stride = sizeof(PxHeightFieldSample);

			PxHeightField* heightField = physicsSDK->createHeightField(descriptor);
			PxHeightFieldGeometry geometry(heightField, PxMeshGeometryFlags(),params.w()*0.00390625f,params.y(),params.z());
			PxTransform transformation = PxTransform(PxVec3(-terrainSize*0.5f*params.y(),0.0f,-terrainSize*0.5f*params.z()),PxQuat::createIdentity());

			PxRigidStatic* heightFieldActor = physicsSDK->createRigidStatic(transformation);
			PxShape* aHeightFieldShape = heightFieldActor->createShape(geometry,*materials[0].second);
			heightFieldActor->setName(entity->entityName.c_str());
			setupFiltering(heightFieldActor,filterGroup,filterMask);
			scene->addActor(*heightFieldActor);
			
			StaticActor* s = new StaticActor();
			s->entityLogic = entity;
			s->entityPhysics = heightFieldActor;
			staticActors.push_back(s);
		}

		/**
		 * Method is used to remove static actor from physics scene.
		 * @param	name is actor name id.
		 */
		void PhysicsManager::removeStaticActor(const string& name)
		{
			StaticActors::const_iterator it = staticActors.begin();
			for(; it != staticActors.end(); ++it)
				if((*it)->entityLogic->entityName == name)
					break;

			if(it != staticActors.end())
			{
				scene->removeActor(*(*it)->entityPhysics);
				staticActors.erase(it);
			}
		}

		/**
		 * Method is used to remove dynamic actor from physics scene.
		 * @param	name is actor name id.
		 */
		void PhysicsManager::removeDynamicActor(const string& name)
		{
			DynamicActors::const_iterator it = dynamicActors.begin();
			for(; it != dynamicActors.end(); ++it)
				if((*it)->entityLogic->entityName == name)
					break;

			if(it != dynamicActors.end())
			{
				scene->removeActor(*(*it)->entityPhysics);
				dynamicActors.erase(it);
			}
		}

		/**
		 * Method is used to set physics scene gravity.
		 * @param	gravity is gravity vector.
		 */
		void PhysicsManager::setGravity(const Vector3D& gravity)
		{
			scene->setGravity(PxVec3(gravity.x(),gravity.y(),gravity.z()));
		}

		/**
		 * Method is used to add new physics material.
		 * @param	name is new material name.
		 * @param	params is material parameters vector: static friction, dynamic friction, restitution.
		 */
		void PhysicsManager::addPhysicsMaterial(const string& name, const Vector3D& params)
		{
			PxMaterial* material = physicsSDK->createMaterial(params.x(),params.y(),params.z());
			materials.push_back(make_pair(name,material));		
		}

		/**
		 * Method is used to add collision callback funtion to collision handler map.
		 * @param	name is first actor name.
		 * @param	name2 is second actor name.
		 * @param	method is callback function object.
		 */
		void PhysicsManager::addCollisionCallback(const string& name, const string& name2, boost::function<void()> method)
		{
			collisionHandler->addCollisionCallback(name,name2,method);
		}

		/**
		 * Method is used to add joint between two scene actors. This joints can be broken when defined
		 * amount of force/troque have been applied.
		 * @param	name is first actor name id.
		 * @param	name2 is second actor name id.
		 * @param	force is amount of force needed to brake joint.
		 * @param	torque is amount of torque needed to brake joint.
		 */
		void PhysicsManager::addJoint(const string& name, const string& name2, const float force, const float torque)
		{
			DynamicActor* first = nullptr;
			DynamicActor* second = nullptr;

			DynamicActors::const_iterator it = dynamicActors.begin();
			for(; it != dynamicActors.end(); ++it)
				if((*it)->entityLogic->entityName == name)
					break;
			if(it == dynamicActors.end())
				return;
			first = (*it);

			it = dynamicActors.begin();
			for(; it != dynamicActors.end(); ++it)
				if((*it)->entityLogic->entityName == name2)
					break;
			if(it == dynamicActors.end())
				return;
			second = (*it);

			PxTransform transformation;
			PxVec3 position = PxVec3(first->entityLogic->entityState.position[0],first->entityLogic->entityState.position[1],first->entityLogic->entityState.position[2]);
			PxQuat orientation = PxQuat(first->entityLogic->entityState.orientation[0],first->entityLogic->entityState.orientation[1],first->entityLogic->entityState.orientation[2],first->entityLogic->entityState.orientation[3]);
			transformation.p = position;
			transformation.q = orientation;

			PxTransform transformation2;
			PxVec3 position2 = PxVec3(second->entityLogic->entityState.position[0],second->entityLogic->entityState.position[1],second->entityLogic->entityState.position[2]);
			PxQuat orientation2 = PxQuat(second->entityLogic->entityState.orientation[0],second->entityLogic->entityState.orientation[1],second->entityLogic->entityState.orientation[2],second->entityLogic->entityState.orientation[3]);
			transformation2.p = position2;
			transformation2.q = orientation2;

			PxFixedJoint* fixed = PxFixedJointCreate(*physicsSDK,first->entityPhysics,transformation,second->entityPhysics,transformation2);
			fixed->setBreakForce(force,torque);
		}

		/**
		 * Method is used to perform ray cast collision test. It can be used in shooting games to check
		 * if bullet will hit scene actor.
		 * @param	position is ray origin vector.
		 * @param	direction is ray direction vector.
		 * @param	rayLength is ray length value.
		 * @return	name of actors that ray will hit, "None" otherwise.
		 */
		string PhysicsManager::rayCastTest(const Vector3D& position, const Vector3D& direction, const float rayLength)
		{
			PxRaycastHit hit;
			PxSceneQueryFlags flags;
			scene->raycastSingle(PxVec3(position[0],position[1],position[2]),PxVec3(-direction[0],-direction[1],-direction[2]),rayLength,flags,hit);
			if(hit.actor == nullptr)
				return string("None");
			return string(hit.actor->getName());
		}

		/**
		 * Accessor to private current collision actors name.
		 * @return	pair of current collision actors.
		 */
		CollisionActors PhysicsManager::getCollisionActors()
		{
			return collisionHandler->getCurrentActors();
		}

		/**
		 * Private method which is used to initialize engine physics scene. Create scene based on scene descriptor,
		 * set gravity, inner obejcts like cpu dispatcher, filter shader and simulation event callback object.
		 */
		void PhysicsManager::initializeScene()
		{
			PxSceneDesc sceneDesc(physicsSDK->getTolerancesScale());
			sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
			if(!sceneDesc.cpuDispatcher)
			{
				PxDefaultCpuDispatcher* cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
				if(!cpuDispatcher)
					Logger::getInstance()->saveLog(Log<string>("PxDefaultCpuDispatcherCreate creation error occurred!"));		
				sceneDesc.cpuDispatcher = cpuDispatcher;
			}

			if(!sceneDesc.filterShader)
				sceneDesc.filterShader = defaultFilterShader;

			scene = physicsSDK->createScene(sceneDesc);
		
			if(!scene)
				Logger::getInstance()->saveLog(Log<string>("Scene creation error occurred!"));
			
			scene->setVisualizationParameter(PxVisualizationParameter::eSCALE,1.0);
			scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES,1.0f);
			scene->setSimulationEventCallback(collisionHandler);
		}

		/**
		 * Private method which is used to setup actor collision filtering. To use colision detection callback
		 * user must define collision pairs.
		 * @param	actor is ponter to scene actor.
		 * @param	filterGroup is actor own id.
		 * @param	filterMask is mask to filter pairs that trigger a contact callback.
		 */
		void PhysicsManager::setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask)
		{
			PxFilterData filterData;
			filterData.word0 = filterGroup;
			filterData.word1 = filterMask;
			const PxU32 numShapes = actor->getNbShapes();
			PxShape** shapes = new PxShape*[numShapes];
			actor->getShapes(shapes, numShapes);
			for(PxU32 i = 0; i < numShapes; i++)
			{
				PxShape* shape = shapes[i];
				shape->setSimulationFilterData(filterData);
			}
			delete [] shapes;
		}
	}
}
