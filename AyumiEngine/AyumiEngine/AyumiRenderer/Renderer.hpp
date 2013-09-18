/**
 * File contains declaration of Renderer class.
 * @file    Renderer.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-12
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <deque>
#include <algorithm>
#include <boost/function.hpp>

#include "LightManager.hpp"
#include "MaterialManager.hpp"
#include "EffectManager.hpp"
#include "SpriteManager.hpp"
#include "ParticleManager.hpp"
#include "TransformationMatrices.hpp"
#include "VolumeStorage.hpp"
#include "Occlusion.hpp"
#include "ShadowMap.hpp"

#include "../AyumiCore/Configuration.hpp"
#include "../AyumiScene/SceneManager.hpp"
#include "../AyumiResource/ResourceManager.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		typedef std::pair<std::string, boost::function<void()>> RenderTask;
		typedef std::deque<RenderTask> RenderQueue;
		typedef std::vector<ShadowMap*> ShadowMaps;

		/**
		 * Class represents one of main Engine modules which is used to render 2D/3D scene objects
		 * in OpenGL context window. Renderer use SceneManager data to draw visible object, 2D sprites etc.
		 * Renderer store few important managers: ResourceManager, MaterialManager, LightManager and 2D module
		 * SpriteManager. Renderer is the only place where projecion Matrices are calculated and transmitted to
		 * object shaders. Pipeline is done by task queue.
		 */
		class Renderer
		{
		private:
			RenderQueue renderQueue;
			AyumiScene::SceneManager* engineScene;
			AyumiResource::ResourceManager* engineResource;
			AyumiCore::StateMachine* engineState;
			MaterialManager* materials;
			LightManager* lights;
			Occlusion* occlusionCulling;
			VolumeStorage* volumes;
			TransformationMatrices orthogonalProjection;
			TransformationMatrices perspectiveProjection;
			SpriteManager* sprites;
			EffectManager* effects;
			ParticleManager* particles;
			ShadowMaps shadowMaps;
			AyumiResource::Shader* renderToDepth;
	
			void renderSceneEntities();
			void renderSprites();
			void renderParticles();
			void renderBoundingVolumes();
			void renderOctTree();
			void performOcclusionQuery();
			void renderShadowMaps();
			
			void renderSceneEntity(AyumiScene::SceneEntity* entity);
			void renderParticleEmiter(ParticleEmiter* emiter);
			void renderBoundingBox(AyumiScene::SceneEntity* entity);
			void renderOctTreeNode(AyumiScene::OctNode* node);
			void renderOccluder(AyumiScene::SceneEntity* entity);
			
			void renderClearScene();
			void renderOffScreenScene();
			void renderOffScreenPrevious();
			void renderFinalRendering();
			void updatePerspectiveProjection();
			void updateOrthogonalProjection();
			void initializeShadowMaps();
		public:
			Renderer(AyumiScene::SceneManager* engineScene);
			~Renderer();

			void initializeRenderer();
			void initializePostProcess();
			void renderScene();
			void addRenderTask(const std::string& task);
			void addCustomRenderTask(const std::string& task, boost::function<void()> function);
			void deleteRenderTask(const std::string& task);
			void clearRenderQueue();
			void prepareEntity(AyumiScene::SceneEntity* entity, bool occlusionChecking = true);
			void prepareAnimatedEntity(AyumiScene::AnimatedEntity* entity, bool occlusionChecking = true);
			void releaseEntity();
			void updateShadowSource(const int id, const AyumiMath::Vector3D& position, const AyumiMath::Vector3D& direction);
			
			AyumiScene::SceneManager* getEngineScene() const;		
			AyumiResource::ResourceManager* getEngineResource() const;
			SpriteManager* getSpriteManager() const;
			ParticleManager* getParticleManager() const;
			LightManager* getLightManager() const;
			MaterialManager* getMaterialManager() const;
			EffectManager* getEffectManager() const;
			ShadowMaps* getShadowMaps();
		};
	}
}
#endif
