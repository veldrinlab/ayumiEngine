/**
 * File contains definition of EngineInterface class.
 * @file    EngineInterface.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "EngineInterface.hpp"

using namespace std;
using namespace boost;
using namespace AyumiEngine;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiInput;
using namespace AyumiEngine::AyumiRenderer;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiSound;
using namespace AyumiEngine::AyumiPhysics;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiDestruction;

Engine* EngineInterface::engine = nullptr;

void EngineInterface::createEngine(const string& configPath, const bool physicsUsage)
{
	Configuration::getInstance()->configureEngine(configPath);
//	Logger::getInstance()->saveLog(Log<string>("Engine creation started"));
	VirtualMachine::getInstance();
	engine = new Engine();
	engine->initializeEngine(physicsUsage);
//	Logger::getInstance()->saveLog(Log<string>("Engine creation ended"));	
}

void EngineInterface::releaseEngine()
{
	engine->killPhysicsThread();
	Logger::getInstance()->saveLog(Log<string>("Engine release started"));
	delete engine;
	Logger::getInstance()->saveLog(Log<string>("Engine release ended"));
	Configuration::killInstance();
	Logger::killInstance();
	VirtualMachine::killInstance();
}

void EngineInterface::runGameLoop(bool* runCondition, const bool startPhysics)
{
	if(startPhysics)
		engine->runPhysicsThread();

	while(*runCondition == true && engine->getEngineContext()->getContextWindow()->isOpen())
		engine->mainThread();
}

void EngineInterface::addGameLoopTask(const string& taskName, boost::function<void()> task)
{
	engine->addTask(taskName,task);
}

void EngineInterface::deleteGameLoopTask(const string& taskName)
{
	engine->deleteTask(taskName);
}

float EngineInterface::getElapsedTime()
{
	return engine->getEngineMainTimer()->getTimeStep();
}

void EngineInterface::addRenderTask(const string& taskName)
{
	engine->getEngineRenderer()->addRenderTask(taskName);
}

void EngineInterface::addCustomRenderTask(const string& taskName, boost::function<void()> task)
{
	engine->getEngineRenderer()->addCustomRenderTask(taskName,task);
}

void EngineInterface::deleteRenderTask(const string& taskName)
{
	engine->getEngineRenderer()->deleteRenderTask(taskName);
}

void EngineInterface::clearRenderQueue()
{
	engine->getEngineRenderer()->clearRenderQueue();
}

void EngineInterface::addUpdateTask(const string& taskName)
{
	engine->getEngineScene()->addUpdateTask(taskName);
}

void EngineInterface::addCustomUpdateTask(const string& taskName, boost::function<void()> task)
{
	engine->getEngineScene()->addCustomUpdateTask(taskName,task);
}

void EngineInterface::deleteUpdateTask(const string& taskName)
{
	engine->getEngineScene()->deleteUpdateTask(taskName);
}

void EngineInterface::connectKeyboardAction(const InputKey& key, boost::function<void ()> method)
{
	engine->getEngineInput()->connectKeyboardAction(key,method);
}

void EngineInterface::connectMouseAction(const InputMouseButton& button, boost::function<void ()> method)
{
	engine->getEngineInput()->connectMouseAction(button,method);
}

void EngineInterface::connectMouseMoveAction(boost::function<void (int,int)> method)
{
	engine->getEngineInput()->connectMouseMoveAction(method);
}

void EngineInterface::connectPadAction(const InputPadButton& button, boost::function<void ()> method)
{
	engine->getEngineInput()->connectPadAction(button,method);
}

void EngineInterface::connectMoveAxisAction(const InputAxis& axis, boost::function<void (float)> method)
{
	engine->getEngineInput()->connectMoveAxisAction(axis,method);
}

void EngineInterface::disconnectKeyboardAction(const InputKey& key)
{
	engine->getEngineInput()->disconnectKeyboardAction(key);
}

void EngineInterface::disconnectMoveAction()
{
	engine->getEngineInput()->disconnectMoveAction();
}

void EngineInterface::disconnectMoveWheelAction()
{
	engine->getEngineInput()->disconnectMoveWheelAction();
}

void EngineInterface::disconnectPadAction(const InputPadButton& button)
{
	engine->getEngineInput()->disconnectPadAction(button);
}

void EngineInterface::disconnectMoveAxisAction(const InputAxis& axis)
{
	engine->getEngineInput()->disconnectMoveAxisAction(axis);
}

void EngineInterface::addSceneCamera(Camera* camera)
{
	engine->getEngineScene()->addCamera(camera);
}

void EngineInterface::addEntityToScene(SceneEntity* entity)
{
	engine->getEngineRenderer()->prepareEntity(entity);
	engine->getEngineScene()->addSceneEntity(entity);
}

void EngineInterface::addIndependentToScene(SceneEntity* entity)
{
	engine->getEngineRenderer()->prepareEntity(entity,false);
	engine->getEngineScene()->addIndependentEntity(entity);
}

void EngineInterface::addAnimatedEntityToScene(AnimatedEntity* entity)
{
	engine->getEngineRenderer()->prepareAnimatedEntity(entity);
	engine->getEngineScene()->addAnimatedEntity(entity);
}

void EngineInterface::deleteEntityFromScene(const string& name)
{
	engine->getEngineScene()->deleteSceneEntity(name);
	engine->getEngineRenderer()->releaseEntity();
}

void EngineInterface::deleteIndependentFromScene(const string& name)
{
	engine->getEngineScene()->deleteIndependentEntity(name);
}

void EngineInterface::deleteAnimatedEntityFromScene(const string& name)
{
	engine->getEngineScene()->deleteAnimatedEntity(name);
	engine->getEngineRenderer()->releaseEntity();
}

void EngineInterface::clearScene()
{
	engine->getEngineScene()->clearScene();
}

SceneEntity* EngineInterface::getEntity(const string& name)
{
	return engine->getEngineScene()->getEntity(name);
}

AnimatedEntity* EngineInterface::getAnimatedEntity(const string& name)
{
	return engine->getEngineScene()->getAnimatedEntity(name);
}

Camera* EngineInterface::getCamera()
{
	return engine->getEngineScene()->getWorldCamera();
}

void EngineInterface::addStaticActor(SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask)
{
	engine->getEnginePhysics()->addStaticActor(entity,type,filterGroup,filterMask);
}

void EngineInterface::addDynamicActor(SceneEntity* entity, ShapeType type, PxU32 filterGroup, PxU32 filterMask)
{
	engine->getEnginePhysics()->addDynamicActor(entity,type,filterGroup,filterMask);
}

void EngineInterface::addHeightFieldActor(SceneEntity* entity, unsigned char* heightData, const Vector4D& params, PxU32 filterGroup, PxU32 filterMask)
{
	engine->getEnginePhysics()->addHeightFieldActor(entity,heightData,params,filterGroup,filterMask);
}

void EngineInterface::addCollisionCallback(const string& name1, const string& name2, boost::function<void()> method)
{
	engine->getEnginePhysics()->addCollisionCallback(name1,name2,method);
}

void EngineInterface::deleteStaticActors(const string& name)
{
	engine->getEnginePhysics()->removeStaticActor(name);
}

	void EngineInterface::deleteDynamicActors(const string& name)
{
	engine->getEnginePhysics()->removeDynamicActor(name);
}

std::string EngineInterface::rayCastTest(const Vector3D& position, const Vector3D& direction, const float rayLength)
{
	return engine->getEnginePhysics()->rayCastTest(position,direction,rayLength);
}

void EngineInterface::setGravity(const AyumiEngine::AyumiMath::Vector3D& gravity)
{
	engine->getEnginePhysics()->setGravity(gravity);
}

CollisionActors EngineInterface::getCollisionActors()
{
	return engine->getEnginePhysics()->getCollisionActors();
}

void EngineInterface::initializeFont(const string& fontName, const int fontSize)
{
	Texture* fontTexture = nullptr;
	fontTexture = engine->getEngineRenderer()->getEngineResource()->getTextureResource(fontName).get();
	engine->getEngineRenderer()->getSpriteManager()->initializeFont(fontTexture,fontSize);
}

void EngineInterface::addSprite(const string& spriteName, const Vector3D& position, const Vector3D& size, const float alpha)
{
	Texture* spriteTexture = nullptr;
	spriteTexture = engine->getEngineRenderer()->getEngineResource()->getTextureResource(spriteName).get();
	engine->getEngineRenderer()->getSpriteManager()->addSprite(spriteName,spriteTexture,position,size,alpha);
}

void EngineInterface::updateSprite(const string& spriteName, const Vector3D& position, const Vector3D& size, const float alpha)
{
	engine->getEngineRenderer()->getSpriteManager()->updateSprite(spriteName,position,size,alpha);
}

void EngineInterface::addText(const string& name, const string& text, const Vector3D& position)
{
	engine->getEngineRenderer()->getSpriteManager()->createText(name,text,position);
}

void EngineInterface::updateText(const string& name, const string& text)
{
	engine->getEngineRenderer()->getSpriteManager()->updateText(name,text);
}

void EngineInterface::deleteSprite(const string& name)
{
	engine->getEngineRenderer()->getSpriteManager()->deleteSprite(name);
}

void EngineInterface::deleteText(const string& name)
{
	engine->getEngineRenderer()->getSpriteManager()->deleteText(name);
}

void EngineInterface::addParticleEmiter(const string& name, const string& path,boost::function<void (AyumiEngine::AyumiRenderer::ParticleEmiter*)> initializeFunction, boost::function<void (ParticleEmiter*,float)> updateFunction, const Vector3D& origin)
{
	engine->getEngineRenderer()->getParticleManager()->addParticleEmiter(name,path,initializeFunction,updateFunction,origin);
}

void EngineInterface::deleteParticleEmiter(const string& name)
{
	engine->getEngineRenderer()->getParticleManager()->deleteParticleEmiter(name);
}

void EngineInterface::updateLights(const string& scriptPath)
{
	engine->getEngineRenderer()->getLightManager()->updateLights(scriptPath);
}

void EngineInterface::updateMaterials(const string& scriptPath)
{
	engine->getEngineRenderer()->getMaterialManager()->updateMaterials(scriptPath);
}

void EngineInterface::updateEffects(const string& scriptPath)
{
	engine->getEngineRenderer()->getEffectManager()->updateEffects(scriptPath);
	engine->getEngineRenderer()->initializePostProcess();
}

void EngineInterface::updateShadowSource(const int id, const Vector3D& position, const Vector3D& direction)
{
	engine->getEngineRenderer()->updateShadowSource(id,position,direction);
}

DirectionalLight* EngineInterface::getDirLight(const int id)
{
	return engine->getEngineRenderer()->getLightManager()->getDirectionalLights()->at(id).first;
}

PointLight* EngineInterface::getPointLight(const int id)
{
	return engine->getEngineRenderer()->getLightManager()->getPointLights()->at(id).first;
}

void EngineInterface::addMaterialUpdateFunction(const string& name, MaterialUpdateFunction function)
{
	engine->getEngineRenderer()->getMaterialManager()->registerMaterialUpdateFunction(name,function);
}

void EngineInterface::playSoundEffect(const string& name)
{
	engine->getEngineSound()->playSoundEffect(name);
}

void EngineInterface::playMusicTrack(const string& name)
{
	engine->getEngineSound()->playMusicTrack(name);
}

void EngineInterface::pauseSoundEffect(const string& name)
{
	engine->getEngineSound()->pauseSoundEffect(name);
}

void EngineInterface::pauseMusicTrack(const string& name)
{
	engine->getEngineSound()->pauseMusicTrack(name);
}

void EngineInterface::stopSoundEffect(const string& name)
{
	engine->getEngineSound()->stopSoundEffect(name);
}

void EngineInterface::stopMusicTrack(const string& name)
{
	engine->getEngineSound()->stopMusicTrack(name);
}

void EngineInterface::updateListenerPosition(const Vector3D& position)
{
	engine->getEngineSound()->updateListenerPosition(position);
}

void EngineInterface::update3DSoundEffect(const string& name, const Vector3D& position)
{
	engine->getEngineSound()->update3DSoundEffect(name,position);
}

void EngineInterface::update3DMusicTrack(const string& name, const Vector3D& position)
{
	engine->getEngineSound()->update3DMusicTrack(name,position);
}

void EngineInterface::updateSounds(const string& scriptPath)
{
	engine->getEngineSound()->updateSounds(scriptPath);
}

void EngineInterface::updateMeshResources(const string& scriptPath)
{
	engine->getEngineRenderer()->getEngineResource()->updateMeshResources(scriptPath);
}

void EngineInterface::updateTextureResources(const string& scriptPath)
{
	engine->getEngineRenderer()->getEngineResource()->updateTextureResources(scriptPath);
}

void EngineInterface::updateShaderResources(const string& scriptPath)
{
	engine->getEngineRenderer()->getEngineResource()->updateShaderResources(scriptPath);
}

DestructibleTerrain* EngineInterface::createDestructibleTerrain(SceneEntity* entity, const string& path, const Vector4D& params, PxU32 filterGroup, PxU32 filterMask)
{
	DestructibleTerrain* terrain = new DestructibleTerrain();
	terrain->createDestructibleTerrain(static_cast<int>(params[0]),path);
	terrain->entity = entity;
	terrain->params = params;
	terrain->filterGroup = filterGroup;
	terrain->filterMask = filterMask;
	addHeightFieldActor(entity,terrain->fileData,params,filterGroup,filterMask);
	return terrain;
}

void EngineInterface::executeTerrainDestruction(DestructibleTerrain* terrain, Vector3D position, const int range, const float power)
{
	position[0] += terrain->params[0]*0.5f*terrain->params[1];
	position[2] += terrain->params[0]*0.5f*terrain->params[2];

	if(position[0] < 0)
		position[0] *= -1.0f;
	if(position[1] < 0)
		position[1] *= -1.0f;
	if(position[2] < 0)
		position[2] *= -1.0f;

	const int x = static_cast<int>(position[0] / terrain->params[1]);
	const int z = static_cast<int>(position[2] / terrain->params[2]);

	for(int i = -range; i < range; ++i)
	{
		for(int j = -range; j < range; ++j)
		{
			terrain->entity->entityGeometry.geometryMesh->getVertices()[(x+i)*256+(z+j)].y -= power;
			terrain->fileData[(x+i)*256+(z+j)] -= static_cast<unsigned char>(power*256/terrain->params[3]);
		}		
	}
	
	delete terrain->entity->entityGeometry.geomteryVbo;
	terrain->entity->entityGeometry.geomteryVbo = new VertexBufferObject(*terrain->entity->entityGeometry.geometryMesh);
	terrain->entity->configureGeometryAttributes();
	
	deleteStaticActors(terrain->entity->entityName);
	addHeightFieldActor(terrain->entity,terrain->fileData,terrain->params,terrain->filterGroup,terrain->filterMask);
}

void EngineInterface::releaseDestructibleTerrain(DestructibleTerrain* terrain)
{
	terrain->deleteDestructibleTerrain();
}

void EngineInterface::createFractureConnection(FractureObjects objects, FractureConnections connections)
{
	for(FractureObjects::const_iterator it = objects.begin(); it != objects.end(); ++it)
		addDynamicActor((*it),CONVEX,0,0);

	for(FractureConnections::const_iterator it = connections.begin(); it != connections.end(); ++it)
		engine->getEnginePhysics()->addJoint((*it).firstPart,(*it).secondPart,(*it).force,(*it).torque);
}

void EngineInterface::executeFractureDestruction(const Vector3D& position, const Vector3D& direction, const float rayLength, const Vector3D& force)
{
	string name = engine->getEnginePhysics()->rayCastTest(position,direction,rayLength);	
	SceneEntity* entity = getEntity(name);

	Vector3D forceDirection = direction;
	Vector3D forceVector = -forceDirection * force[0];

	if(entity != nullptr)
		entity->entityPhysics.acceleration.set(forceVector[0],forceVector[1],forceVector[2]);
}

Mesh* EngineInterface::executeMeshDifference(SceneEntity* first, SceneEntity* second)
{
	Mesh* result = nullptr;

	if(first == nullptr || second == nullptr)
		return result;

	GeoModifier* modifier = new GeoModifier(first,second);
	result = modifier->getDifference();
	delete modifier;
	
	return result;
}

int EngineInterface::getVisibleObjects()
{
	int x = 0;

	vector<SceneEntity*>::const_iterator it = engine->getEngineScene()->getSceneGraph()->sceneEntities.begin();

	for(; it != engine->getEngineScene()->getSceneGraph()->sceneEntities.end(); ++it)
		if((*it)->entityState.isVisible == true)
			x++;

	return x;
}
