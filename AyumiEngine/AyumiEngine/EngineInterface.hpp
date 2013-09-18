/**
 * File contains declaraion of EngineInterface class.
 * @file    EngineInterface.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef ENGINEINTERFACE_HPP
#define ENGINEINTERFACE_HPP

//#include <boost/thread.hpp>

#include "Engine.hpp"
#include "AyumiDestruction/AyumiDestruction.hpp"

class EngineInterface
{
private:
	static AyumiEngine::Engine* engine;
	
public:
	// Main start-up/shutdown engine API
	static void createEngine(const std::string& configPath, const bool physicsUsage = true);
	static void releaseEngine();
	static void runGameLoop(bool* runCondition, const bool startPhysics = true);
	static void addGameLoopTask(const std::string& taskName, boost::function<void()> task);
	static void deleteGameLoopTask(const std::string& taskName);
	static float getElapsedTime();

	// Render/Update pipeline configure API
	static void addRenderTask(const std::string& taskName);
	static void addCustomRenderTask(const std::string& taskName, boost::function<void()> task);
	static void deleteRenderTask(const std::string& taskName);
	static void clearRenderQueue();
	static void addUpdateTask(const std::string& taskName);
	static void addCustomUpdateTask(const std::string& taskName, boost::function<void()> task);
	static void deleteUpdateTask(const std::string& taskName);

	//Engine InputManager API 
	static void connectKeyboardAction(const AyumiEngine::AyumiInput::InputKey& key, boost::function<void ()> method);
	static void connectMouseAction(const AyumiEngine::AyumiInput::InputMouseButton& button, boost::function<void ()> method);
	static void connectMouseMoveAction(boost::function<void (int,int)> method);
	static void connectPadAction(const AyumiEngine::AyumiInput::InputPadButton& button, boost::function<void ()> method);
	static void connectMoveAxisAction(const AyumiEngine::AyumiInput::InputAxis& axis, boost::function<void (float)> method);
	static void disconnectKeyboardAction(const AyumiEngine::AyumiInput::InputKey& key);
	static void disconnectMoveAction();
	static void disconnectMoveWheelAction();
	static void disconnectPadAction(const AyumiEngine::AyumiInput::InputPadButton& button);
	static void disconnectMoveAxisAction(const AyumiEngine::AyumiInput::InputAxis& axis);

	//Engine SceneManager API
	static void addSceneCamera(AyumiEngine::AyumiScene::Camera* camera);
	static void addEntityToScene(AyumiEngine::AyumiScene::SceneEntity* entity);
	static void addIndependentToScene(AyumiEngine::AyumiScene::SceneEntity* entity);
	static void addAnimatedEntityToScene(AyumiEngine::AyumiScene::AnimatedEntity* entity);
	static void deleteEntityFromScene(const std::string& name);
	static void deleteIndependentFromScene(const std::string& name);
	static void clearScene();
	static void deleteAnimatedEntityFromScene(const std::string& name);
	static AyumiEngine::AyumiScene::SceneEntity* getEntity(const std::string& name);
	static AyumiEngine::AyumiScene::AnimatedEntity* getAnimatedEntity(const std::string& name);
	static AyumiEngine::AyumiScene::Camera* getCamera();
	
	//Engine PhysicsManager API
	static void addStaticActor(AyumiEngine::AyumiScene::SceneEntity* entity, AyumiEngine::AyumiPhysics::ShapeType type, PxU32 filterGroup, PxU32 filterMask);
	static void addDynamicActor(AyumiEngine::AyumiScene::SceneEntity* entity, AyumiEngine::AyumiPhysics::ShapeType type, PxU32 filterGroup, PxU32 filterMask);
	static void addHeightFieldActor(AyumiEngine::AyumiScene::SceneEntity* entity, unsigned char* heightData, const AyumiEngine::AyumiMath::Vector4D& params, PxU32 filterGroup, PxU32 filterMask); 
	static void addCollisionCallback(const std::string& name1, const std::string& name2, boost::function<void()> method);
	static void deleteStaticActors(const std::string& name);
	static void deleteDynamicActors(const std::string& name);
	static std::string rayCastTest(const AyumiEngine::AyumiMath::Vector3D& position, const AyumiEngine::AyumiMath::Vector3D& direction, const float rayLength);
	static void setGravity(const AyumiEngine::AyumiMath::Vector3D& gravity);
	static AyumiEngine::AyumiPhysics::CollisionActors getCollisionActors();

	//Engine Renderer API
	static void initializeFont(const std::string& fontName, const int fontSize);
	static void addSprite(const std::string& spriteName, const AyumiEngine::AyumiMath::Vector3D& position, const AyumiEngine::AyumiMath::Vector3D& size, const float alpha=1.0f);
	static void updateSprite(const std::string& spriteName, const AyumiEngine::AyumiMath::Vector3D& position, const AyumiEngine::AyumiMath::Vector3D& size, const float alpha);
	static void addText(const std::string& name, const std::string& text, const AyumiEngine::AyumiMath::Vector3D& position);
	static void updateText(const std::string& name, const std::string& text);
	static void deleteSprite(const std::string& name);
	static void deleteText(const std::string& name);
	static void addParticleEmiter(const std::string& name, const std::string& path, boost::function<void (AyumiEngine::AyumiRenderer::ParticleEmiter*)> initializeFunction, boost::function<void (AyumiEngine::AyumiRenderer::ParticleEmiter*,float)> updateFunction, const AyumiEngine::AyumiMath::Vector3D& origin);
	static void deleteParticleEmiter(const std::string& name);
	static void updateLights(const std::string& scriptPath);
	static void updateMaterials(const std::string& scriptPath);
	static void updateEffects(const std::string& scriptPath);
	static void updateShadowSource(const int id, const AyumiEngine::AyumiMath::Vector3D& position, const AyumiEngine::AyumiMath::Vector3D& direction);
	
	static AyumiEngine::AyumiRenderer::DirectionalLight* getDirLight(const int id);
	static AyumiEngine::AyumiRenderer::PointLight* getPointLight(const int id);
	static void addMaterialUpdateFunction(const std::string& name, AyumiEngine::AyumiRenderer::MaterialUpdateFunction function);

	//Engine SoundManager API
	static void playSoundEffect(const std::string& name);
	static void playMusicTrack(const std::string& name);
	static void pauseSoundEffect(const std::string& name);
	static void pauseMusicTrack(const std::string& name);
	static void stopSoundEffect(const std::string& name);
	static void stopMusicTrack(const std::string& name);
	static void updateListenerPosition(const AyumiEngine::AyumiMath::Vector3D& position);
	static void update3DSoundEffect(const std::string& name, const AyumiEngine::AyumiMath::Vector3D& position);
	static void update3DMusicTrack(const std::string& name, const AyumiEngine::AyumiMath::Vector3D& position);
	static void updateSounds(const std::string& scriptPath);

	// Engine ResourceManager API
	static void updateMeshResources(const std::string& scriptPath);
	static void updateTextureResources(const std::string& scriptPath);
	static void updateShaderResources(const std::string& scriptPath);
	
	// Engine AyumiDestruction API
	static AyumiEngine::AyumiDestruction::DestructibleTerrain* createDestructibleTerrain(AyumiEngine::AyumiScene::SceneEntity* entity, const std::string& path, const AyumiEngine::AyumiMath::Vector4D& params, PxU32 filterGroup, PxU32 filterMask);
	static void executeTerrainDestruction(AyumiEngine::AyumiDestruction::DestructibleTerrain* terrain, AyumiEngine::AyumiMath::Vector3D position, const int range, const float power);
	static void releaseDestructibleTerrain(AyumiEngine::AyumiDestruction::DestructibleTerrain* terrain);
	static void createFractureConnection(AyumiEngine::AyumiDestruction::FractureObjects objects, AyumiEngine::AyumiDestruction::FractureConnections connections);
	static void executeFractureDestruction(const AyumiEngine::AyumiMath::Vector3D& position, const AyumiEngine::AyumiMath::Vector3D& direction, const float rayLength, const AyumiEngine::AyumiMath::Vector3D& force);
	static AyumiEngine::AyumiResource::Mesh* executeMeshDifference(AyumiEngine::AyumiScene::SceneEntity* first, AyumiEngine::AyumiScene::SceneEntity* second);

	// Engine Debug functions
	static int getVisibleObjects();
};
#endif
