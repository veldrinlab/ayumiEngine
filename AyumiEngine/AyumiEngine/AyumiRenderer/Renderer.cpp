/**
 * File contains definition of Renderer class.
 * @file    Renderer.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-12
 */

#include "Renderer.hpp"

using namespace std;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiUtils;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class constructor with initialize parameters. Create and initialize all managers and matrices.
		 * @param	engineScene is pointer to engine SceneManager.
		 */
		Renderer::Renderer(SceneManager* engineScene)
		{
			this->engineScene = engineScene;
			engineState = Configuration::getInstance()->getCoreState();
			engineResource = new ResourceManager();
			materials = new MaterialManager(engineResource);
			effects = new EffectManager(engineResource,sprites);
			lights = new LightManager();
			sprites = new SpriteManager();
			volumes = new VolumeStorage();
			occlusionCulling = new Occlusion();
			particles = new ParticleManager(engineResource);
		}

		/**
		 * Class destructor, free allocated memory for resource managers units.
		 */
		Renderer::~Renderer()
		{
			renderQueue.clear();
			delete engineResource;
			delete materials;
			delete lights;
			delete sprites;
			delete volumes;
			delete occlusionCulling;
			delete effects;
			delete particles;
			for(ShadowMaps::const_iterator it = shadowMaps.begin(); it != shadowMaps.end(); ++it)
			{
				glDeleteFramebuffers(1,&(*it)->frameBuffer);
				glDeleteTextures(1,&(*it)->depthTexture);
				delete (*it);
			}
			delete renderToDepth;
		}	

		/**
		 * Method is used to initialize Renderer: managers and start-up state.
		 */
		void Renderer::initializeRenderer()
		{
			lights->initializeLightManager();
			materials->initializeMaterialManager();
			sprites->initializeSpriteManager();
			effects->initializeEffectManager();
			particles->initializeParticleManager();
			volumes->initializeVolumeStorage();	
			engineState->depthState.on(); 
			engineState->blendState.on();
			updatePerspectiveProjection();
			updateOrthogonalProjection();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			initializeShadowMaps();
			initializePostProcess();
			
		}

		/**
		 * Method is used to initialize post-process effects pipeline.
		 */
		void Renderer::initializePostProcess()
		{
			if(effects->getRenderPassList()->size() == 0)
			{	
				renderQueue.push_back(make_pair("renderClearScene",boost::bind(&Renderer::renderClearScene,this)));
				renderQueue.push_back(make_pair("renderSceneEntities",boost::bind(&Renderer::renderSceneEntities,this)));	
			}
			else
			{
				for(vector<RenderPass*>::const_iterator it = effects->getRenderPassList()->begin(); it != effects->getRenderPassList()->end(); ++it)
				{
					if((*it)->offScreenRenderingScene)
						renderQueue.push_back(make_pair("renderOffScreenScene",boost::bind(&Renderer::renderOffScreenScene,this)));
					else if((*it)->offScreenRenderingPrevious)
						renderQueue.push_back(make_pair("renderOffScreenPrevious",boost::bind(&Renderer::renderOffScreenPrevious,this)));
					else if((*it)->finalRendering)
					{
						if((*it)->clearBeforeFinal)
							renderQueue.push_back(make_pair("renderClearScene",boost::bind(&Renderer::renderClearScene,this)));
						renderQueue.push_back(make_pair("renderFinalRendering",boost::bind(&Renderer::renderFinalRendering,this)));
					}
				}
			}
		}
			
		/**
		 * Method is used to render engine scene. Class main method which is part of Renderer public API.
		 */
		void Renderer::renderScene()
		{
			for(RenderQueue::const_iterator it = renderQueue.begin(); it != renderQueue.end(); ++it)
				(*it).second();
		}

		/**
		 * Method is used to add new render task to rendering pipeline. Tasks like render OctTree or render sprites.
		 * @param	task is name of new task.
		 */
		void Renderer::addRenderTask(const string& task)
		{
			RenderQueue::const_iterator it = renderQueue.begin();

			for(; it != renderQueue.end(); ++it)
				if(((*it).first == "renderSceneEntities") || ((*it).first == "renderOffScreenScene"))
					break;

			if(it != renderQueue.end())
			{
				if(task == "renderOctTree")
					renderQueue.insert(++it,make_pair("renderOctTree",boost::bind(&Renderer::renderOctTree,this)));
				else if(task == "renderBoundingVolumes")
					renderQueue.insert(++it,make_pair("renderBoundingVolumes",boost::bind(&Renderer::renderBoundingVolumes,this)));
				else if(task == "renderParticles")
					renderQueue.insert(++it,make_pair("renderParticles",boost::bind(&Renderer::renderParticles,this)));
				else if(task == "renderSprites")
					renderQueue.push_back(make_pair("renderSprites",boost::bind(&Renderer::renderSprites,this)));
				else if(task == "performOcclusionQuery")
					renderQueue.push_front(make_pair("performOcclusionQuery",boost::bind(&Renderer::performOcclusionQuery,this)));
				else if(task == "renderShadows")
					renderQueue.push_front(make_pair("renderShadows",boost::bind(&Renderer::renderShadowMaps,this)));
				else if(task == "renderSceneEntities")
					renderQueue.push_back(make_pair("renderSceneEntities2",boost::bind(&Renderer::renderSceneEntities,this)));
			}
		}

		/**
		 * Method is used to add user defined task to renderer pipeline.
		 * @param	task is name of user defined task.
		 * @param	function is funtion object of user defined task.
		 */
		void Renderer::addCustomRenderTask(const string& task, boost::function<void()> function)
		{
			renderQueue.push_back(make_pair(task,function));
		}

		/**
		 * Method is used to delete task from rendering pipeline. Tasks like render OctTree or render sprites.
		 * @param	task is name of task to deete.
		 */
		void Renderer::deleteRenderTask(const string& task)
		{
			RenderQueue::const_iterator it = renderQueue.begin();
			for(; it != renderQueue.end(); ++it)
				if((*it).first == task)
					break;
			if(it != renderQueue.end())
				renderQueue.erase(it);
		}

		/**
		 * Method is used to clear render queue - rendering pipeline.
		 */
		void Renderer::clearRenderQueue()
		{
			renderQueue.clear();
		}

		/**
		 * Method is used to prepare new entity rendering data: get material and configure vertex buffers.
		 * @param	entity is pointer to new scene entity.
		 * @param	occlusionChecking is bool flag to determine if entity will be affected by occlusion culling.
		 */
		void Renderer::prepareEntity(SceneEntity* entity, bool occlusionChecking)
		{
			entity->entityMaterial = *materials->getResource(entity->materialName).get();
			entity->setGeometryData(engineResource->getMeshResource(entity->geometryName));
			entity->configureGeometryAttributes();
			if(occlusionChecking)
				occlusionCulling->addNewQuery();
		}

		/**
		 * Method is used to prepare new animated entity rendering data: get material and configure vertex buffers.
		 * @param	entity is pointer to new animated scene entity.
		 * @param	occlusionChecking is bool flag to determine if entity will be affected by occlusion culling.
		 */
		void Renderer::prepareAnimatedEntity(AnimatedEntity* entity, bool occlusionChecking)
		{
			entity->entityMaterial = *materials->getResource(entity->materialName).get();
			entity->setGeometryData(engineResource->getMeshResource(entity->geometryName));
			entity->configureGeometryAttributes();
			if(occlusionChecking)
				occlusionCulling->addNewQuery();
		}

		/**
		 * Method is used to realese entity - delete entity occlusion query object.
		 */
		void Renderer::releaseEntity()
		{
			occlusionCulling->deleteQuery();
		}

		/**
		 * Method is used to update shadow light source data.
		 * @param	id is shadow map structure id.
		 * @param	position is shadow light source position.
		 * @param	direction is shadow light source direction in euler angles.
		 */
		void Renderer::updateShadowSource(const int id, const Vector3D& position, const Vector3D& direction)
		{
			shadowMaps[id]->position = position;
			shadowMaps[id]->direction = direction;
		}

		/**
		 * Accessor to private engine scene member.
		 * @return	pointer to engine scene.
		 */
		SceneManager* Renderer::getEngineScene() const
		{
			return engineScene;
		}

		/**
		 * Accessor to private engine resource member.
		 * @return	pointer to engine resource.
		 */
		ResourceManager* Renderer::getEngineResource() const
		{
			return engineResource;
		}

		/**
		 * Accessor to private engine SpriteManager member.
		 * @return	pointer to engine SpriteManager object.
		 */
		SpriteManager* Renderer::getSpriteManager() const
		{
			return sprites;
		}

		/**
		 * Accessor to private engine ParticleManager member.
		 * @return	pointer to engine ParticleManager object.
		 */
		ParticleManager* Renderer::getParticleManager() const
		{
			return particles;
		}

		/**
		 * Accessor to private engine LightManager member.
		 * @return	pointer to engine LightManager object.
		 */
		LightManager* Renderer::getLightManager() const
		{
			return lights;
		}

		/**
		 * Accessor to private engine MaterialManager member.
		 * @return	pointer to engine MaterialManager object.
		 */
		MaterialManager* Renderer::getMaterialManager() const
		{
			return materials;
		}

		/**
		 * Accessor to private engine EffectManager member.
		 * @return	pointer to engine EffectManager object.
		 */
		EffectManager* Renderer::getEffectManager() const
		{
			return effects;
		}

		/**
		 * Accessor to private engine shadow maps collection member.
		 * @return	pointer to engine shadow maps collection object.
		 */
		ShadowMaps* Renderer::getShadowMaps()
		{
			return &shadowMaps;
		}

		/**
		 * Private method which is used to render scene entities. One of render tasks.
		 */
		void Renderer::renderSceneEntities()		
		{
			engineState->blendState.off();
			updatePerspectiveProjection();
			for_each(engineScene->getSceneGraph()->sceneEntities.begin(),engineScene->getSceneGraph()->sceneEntities.end(),boost::bind(&Renderer::renderSceneEntity,this,_1));
			for_each(engineScene->getSceneGraph()->animatedEntities.begin(),engineScene->getSceneGraph()->animatedEntities.end(),boost::bind(&Renderer::renderSceneEntity,this,_1));
			engineState->backCullingState.off();
			const float far = engineScene->getWorldCamera()->far;
			engineScene->getWorldCamera()->far = 100000.0f;
			updatePerspectiveProjection();
			for_each(engineScene->getSceneGraph()->independentEntities.begin(),engineScene->getSceneGraph()->independentEntities.end(),boost::bind(&Renderer::renderSceneEntity,this,_1));
			engineScene->getWorldCamera()->far = far;
		}

		/**
		 * Private method which is used to render sprites. One of render tasks.
		 */
		void Renderer::renderSprites()
		{
			engineState->blendState.on();
			engineState->depthState.off();
			engineState->backCullingState.off();
			updateOrthogonalProjection();

			for(SpriteBatch::const_iterator it = sprites->getSpriteCollection()->begin(); it != sprites->getSpriteCollection()->end(); ++it)
			{
				orthogonalProjection.reset();
				orthogonalProjection.modelMatrix.Translatef((*it)->getPosition());
				orthogonalProjection.modelMatrix.Scalef((*it)->getSize());
				(*it)->attachRenderObjects();
				(*it)->getShader()->setUniformMatrix4fv("projectionMatrix",orthogonalProjection.projectionMatrix.data());
				(*it)->getShader()->setUniformMatrix4fv("modelViewMatrix",orthogonalProjection.modelMatrix.transpose().data());
				(*it)->getShader()->setUniformTexture("ColorMapSampler",0);
				(*it)->getShader()->setUniformf("alpha",(*it)->getAlpha());
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_RECTANGLE,*(*it)->getTexture()->getTexture());
				glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
				(*it)->detachRenderObjects();
			}

			for(TextBatch::const_iterator it = sprites->getTextCollection()->begin(); it != sprites->getTextCollection()->end(); ++it)
			{
				for(vector<TextElement>::const_iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
				{	
					orthogonalProjection.modelMatrix.LoadIdentity();
					orthogonalProjection.modelMatrix.Translatef((*it2).second);
					orthogonalProjection.modelMatrix.Scalef((*it2).first->getSize());
					(*it2).first->attachRenderObjects();
					(*it2).first->getShader()->setUniformMatrix4fv("projectionMatrix",orthogonalProjection.projectionMatrix.data());
					(*it2).first->getShader()->setUniformMatrix4fv("modelViewMatrix",orthogonalProjection.modelMatrix.transpose().data());
					(*it2).first->getShader()->setUniformTexture("ColorMapSampler",0);
					(*it2).first->getShader()->setUniformf("alpha",(*it2).first->getAlpha());				
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_RECTANGLE,*(*it2).first->getTexture()->getTexture());
					glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
					(*it2).first->detachRenderObjects();
				}
			}
			engineState->depthState.on();
			engineState->backCullingState.on();
		}

		/**
		 * Private method which is used to render particle effects. One of render tasks.
		 */
		void Renderer::renderParticles()
		{
			updatePerspectiveProjection();
			engineState->blendState.on();
			engineState->depthState.off();
			particles->updateEmiters(engineScene->getDeltaTime());
			for_each(particles->getEmiters()->begin(),particles->getEmiters()->end(),boost::bind(&Renderer::renderParticleEmiter,this,_1));
			engineState->depthState.on();
		}

		/**
		 * Private method which is used to render bounding volumes. One of render tasks.
		 */
		void Renderer::renderBoundingVolumes()
		{
			updatePerspectiveProjection();
			volumes->setRenderMode(LINES);
			for_each(engineScene->getSceneGraph()->sceneEntities.begin(),engineScene->getSceneGraph()->sceneEntities.end(),boost::bind(&Renderer::renderBoundingBox,this,_1));
			for_each(engineScene->getSceneGraph()->animatedEntities.begin(),engineScene->getSceneGraph()->animatedEntities.end(),boost::bind(&Renderer::renderBoundingBox,this,_1));
			for_each(engineScene->getSceneGraph()->independentEntities.begin(),engineScene->getSceneGraph()->independentEntities.end(),boost::bind(&Renderer::renderBoundingBox,this,_1));
		}

		/**
		 * Private method which is used to render scene OctTree. One of render tasks.
		 */
		void Renderer::renderOctTree()
		{
			updatePerspectiveProjection();
			volumes->setRenderMode(LINES);
			renderOctTreeNode(engineScene->getOctTree()->getRoot());
		}

		/**
		 * Private method which is used to perform occlusion query. One of render tasks.
		 */
		void Renderer::performOcclusionQuery()
		{
			occlusionCulling->prepareEntities(engineScene);
			volumes->setRenderMode(TRIANGLES);
			updatePerspectiveProjection();
			for_each(engineScene->getSceneGraph()->sceneEntities.begin(),engineScene->getSceneGraph()->sceneEntities.end(),boost::bind(&Renderer::renderOccluder,this,_1));
			volumes->setRenderMode(LINES);
			occlusionCulling->checkQueriesResults(engineScene);
			renderClearScene();
		}

		/**
		 * Private method which is used to render shadow maps. One for each directional light on scene.
		 */
		void Renderer::renderShadowMaps()
		{
			for(ShadowMaps::const_iterator it = shadowMaps.begin(); it != shadowMaps.end(); ++it)
			{
				glBindFramebuffer(GL_FRAMEBUFFER,(*it)->frameBuffer);
				renderToDepth->bindShader();
				glViewport(0,0,(*it)->shadowMapWidth,(*it)->shadowMapHeight);
				glClear(GL_DEPTH_BUFFER_BIT);
				glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE); 
				glCullFace(GL_FRONT);
				glEnable(GL_CULL_FACE);
				updatePerspectiveProjection();
				perspectiveProjection.reset();
				vector<SceneEntity*>* entities = &engineScene->getSceneGraph()->sceneEntities;
				vector<AnimatedEntity*>* animated = &engineScene->getSceneGraph()->animatedEntities;
				
				(*it)->lightMatrix.LoadIdentity();
				Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),(*it)->direction[0]);
				rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),(*it)->direction[1]);
				rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),(*it)->direction[2]);
				(*it)->lightMatrix *= rotate.matrix4(); 
				(*it)->lightMatrix.Translatef(-(*it)->position[0],-(*it)->position[1],-(*it)->position[2]);

				for(unsigned i = 0; i < entities->size(); ++i)
				{	
					perspectiveProjection.reset();
					perspectiveProjection.modelMatrix.Translatef(entities->at(i)->entityState.position);
					perspectiveProjection.modelMatrix *= entities->at(i)->entityState.orientation.matrix4();
					perspectiveProjection.modelMatrix.Scalef(entities->at(i)->entityState.scale);
					perspectiveProjection.modelViewMatrix = (*it)->lightMatrix * perspectiveProjection.modelMatrix;
					entities->at(i)->entityGeometry.geometryVao->bindVertexArray();
					renderToDepth->setUniformMatrix4fv("projectionMatrix",perspectiveProjection.projectionMatrix.data());
					renderToDepth->setUniformMatrix4fv("modelViewMatrix",perspectiveProjection.modelViewMatrix.transpose().data());
					glDrawElements(GL_TRIANGLES,entities->at(i)->entityGeometry.geometryMesh->getTrianglesAmount()*3,GL_UNSIGNED_INT,NULL);
					entities->at(i)->entityGeometry.geometryVao->unbindVertexArray();
				}
				
				for(unsigned i = 0; i < animated->size(); ++i)
				{
					perspectiveProjection.reset();
					perspectiveProjection.modelMatrix.Translatef(animated->at(i)->entityState.position);
					perspectiveProjection.modelMatrix *= animated->at(i)->entityState.orientation.matrix4();
					perspectiveProjection.modelMatrix.Scalef(animated->at(i)->entityState.scale);
					perspectiveProjection.modelViewMatrix = (*it)->lightMatrix * perspectiveProjection.modelMatrix;
					animated->at(i)->entityGeometry.geometryVao->bindVertexArray();
					renderToDepth->setUniformMatrix4fv("projectionMatrix",perspectiveProjection.projectionMatrix.data());
					renderToDepth->setUniformMatrix4fv("modelViewMatrix",perspectiveProjection.modelViewMatrix.data());
					glDrawElements(GL_TRIANGLES,animated->at(i)->entityGeometry.geometryMesh->getTrianglesAmount()*3,GL_UNSIGNED_INT,NULL);
					animated->at(i)->entityGeometry.geometryVao->unbindVertexArray();
				}
				
				renderToDepth->unbindShader();
				glBindFramebuffer(GL_FRAMEBUFFER,0);
				glViewport(0,0,Configuration::getInstance()->getResolutionWidth(),Configuration::getInstance()->getResolutionHeight());
				glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE); 
				glCullFace(GL_BACK);
				glDisable(GL_CULL_FACE);
			}
		}

		/**
		 * Private method which is used to render scene entity. It is part of scene entity rendering renderer
		 * task. Method is used to render one SceneEntity.
		 * @param	entity is pointer to scene entity representation.
		 */
		void Renderer::renderSceneEntity(SceneEntity* entity)
		{
			if(entity->entityState.isVisible)
			{
				perspectiveProjection.reset();
				perspectiveProjection.modelMatrix.Translatef(entity->entityState.position);
				perspectiveProjection.modelMatrix *= entity->entityState.orientation.matrix4();
				perspectiveProjection.modelMatrix.Scalef(entity->entityState.scale);					
				perspectiveProjection.modelViewMatrix = perspectiveProjection.viewMatrix * perspectiveProjection.modelMatrix;
				perspectiveProjection.createNormalMatrix();

				entity->attachMaterial();
				lights->sendLightsData(entity->entityMaterial.entityShader);
				perspectiveProjection.sendMatricesData(entity->entityMaterial.entityShader);
				materials->sendMaterialData(&entity->entityMaterial,engineScene->getDeltaTime());

				for(unsigned i = 0; i < shadowMaps.size(); ++i)
				{
					shadowMaps[i]->lightMatrix.LoadIdentity();
					Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),shadowMaps[i]->direction[0]);
					rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),shadowMaps[i]->direction[1]);
					rotate *= Quaternion(Vector3D(0.0f,0.0f,1.0f),shadowMaps[i]->direction[2]);
					shadowMaps[i]->lightMatrix *= rotate.matrix4(); 
					shadowMaps[i]->lightMatrix.Translatef(-shadowMaps[i]->position[0],-shadowMaps[i]->position[1],-shadowMaps[i]->position[2]);			
					shadowMaps[i]->lightMatrix.transpose();
					shadowMaps[i]->shadowMatrix.LoadIdentity();
					shadowMaps[i]->shadowMatrix = shadowMaps[i]->shadowMatrix * shadowMaps[i]->bias;
					shadowMaps[i]->shadowMatrix = perspectiveProjection.projectionMatrix * shadowMaps[i]->shadowMatrix;	
					shadowMaps[i]->shadowMatrix = shadowMaps[i]->lightMatrix * shadowMaps[i]->shadowMatrix;
					shadowMaps[i]->shadowMatrix = perspectiveProjection.inverseViewMatrix * shadowMaps[i]->shadowMatrix;
					entity->entityMaterial.entityShader->setUniformMatrix4fv(shadowMaps[i]->matrixName,shadowMaps[i]->shadowMatrix.data());
				}
				
				unsigned int layer = 0;
				for(; layer < entity->entityMaterial.materialLayers.size(); ++layer)
				{
					glActiveTexture(GL_TEXTURE0 + layer);
					glBindTexture(entity->entityMaterial.materialLayers[layer]->getType(),*entity->entityMaterial.materialLayers[layer]->getTexture());
				}

				for(unsigned i = 0; i < shadowMaps.size(); ++i)
				{
					entity->entityMaterial.entityShader->setUniformTexture(shadowMaps[i]->textureName,layer);
					glActiveTexture(GL_TEXTURE0+layer);
					glBindTexture(GL_TEXTURE_2D,shadowMaps[i]->depthTexture);
					layer++;
				}
				glDrawElements(GL_TRIANGLES,entity->entityGeometry.geometryMesh->getTrianglesAmount()*3,GL_UNSIGNED_INT,NULL);
				entity->detachMaterial();
			}
		}

		/**
		 * Private method which is used to render particle emiter. It is part of particle systems rendering
		 * render task. Method is used to render one particle emiter.
		 * @param	emiter is pointer to particle emiter representaion
		 */	
		void Renderer::renderParticleEmiter(ParticleEmiter* emiter)
		{	
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			perspectiveProjection.reset();
			perspectiveProjection.modelMatrix.Translatef(emiter->origin);
			perspectiveProjection.modelViewMatrix = perspectiveProjection.viewMatrix * perspectiveProjection.modelMatrix;
			emiter->particleVao->bindVertexArray();		
			glBindBuffer(GL_ARRAY_BUFFER,emiter->particleVbo);
			glBufferData(GL_ARRAY_BUFFER,emiter->particleAmount*12*sizeof(float),emiter->points,GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER,0);
			emiter->shader->bindShader();
			perspectiveProjection.sendMatricesData(emiter->shader);
			emiter->shader->setUniformTexture("particleMap",0);
			emiter->shader->setUniformf("pointSize",emiter->particles[0].size);
			emiter->shader->setUniform4fv("color",emiter->particles->color.data());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,*emiter->texture->getTexture());
			glDrawArrays(GL_POINTS,0,emiter->particleAmount);
			emiter->shader->unbindShader();
			emiter->particleVao->unbindVertexArray();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		/**
		 * Private method which is used to render entity Bounding Box. It is part of bounding volumes rendering
		 * render task. Method is used to render entity boudning volume.
		 * @param	entity is pointer to scene entity representation.
		 */
		void Renderer::renderBoundingBox(SceneEntity* entity)
		{
			if(entity->entityState.isVisible)
			{
				Vector3D scaleBase = (entity->entityGeometry.geometryBox->max-entity->entityGeometry.geometryBox->min)*0.5f;
				Vector3D scale = entity->entityState.scale; 
				perspectiveProjection.reset();
				perspectiveProjection.modelMatrix.Translatef(entity->entityState.position);
				perspectiveProjection.modelMatrix *= entity->entityState.orientation.matrix4();
				perspectiveProjection.modelMatrix.Scalef(scaleBase[0]*scale[0],scaleBase[1]*scale[1],scaleBase[2]*scale[2]);
				perspectiveProjection.modelViewMatrix = perspectiveProjection.viewMatrix * perspectiveProjection.modelMatrix;
				volumes->attachVolumeBuffers();
				perspectiveProjection.sendMatricesData(volumes->getShader());
				glDrawArrays(GL_LINES,0,24);
				volumes->detachVolumeBuffers();
			}
		}

		/**
		 * Private method which is used to render OctTree node. It is part of oct tree rendering renderer
		 * task. Method is used to render one OctTree node.
		 * @param	node is pointer to OctTree node.
		 */
		void Renderer::renderOctTreeNode(OctNode* node)
		{
			perspectiveProjection.reset();
			perspectiveProjection.modelMatrix.Translatef(node->position);	
			perspectiveProjection.modelMatrix.Scalef(node->size);
			perspectiveProjection.modelViewMatrix = perspectiveProjection.viewMatrix * perspectiveProjection.modelMatrix;
			volumes->attachVolumeBuffers();
			perspectiveProjection.sendMatricesData(volumes->getShader());
			glDrawArrays(GL_LINES,0,24);
			volumes->detachVolumeBuffers();
	
			for(int i = 0; i < 8; ++i)
				if(node->children[i] != nullptr)
					renderOctTreeNode(node->children[i]);
		}

		/**
		 * Private method which is used to render occluder. It is part of occlusion culling render task.
		 * It is used to determine if some entities are occluded by another in occlusion culling algorithm.
		 * SceneEntity occluder if defined as filled bounding box.
		 * @param	entity is pointer to scene entity representation.
		 */
		void Renderer::renderOccluder(SceneEntity* entity)
		{
			if(entity->entityState.isVisible)
			{
				glBeginQuery(GL_SAMPLES_PASSED,*occlusionCulling->getQuery());
				Vector3D scaleBase = (entity->entityGeometry.geometryBox->max-entity->entityGeometry.geometryBox->min)*0.5f;
				Vector3D scale = entity->entityState.scale; 
				perspectiveProjection.reset();
				perspectiveProjection.modelMatrix.Translatef(entity->entityState.position);
				perspectiveProjection.modelMatrix *= entity->entityState.orientation.matrix4();
				perspectiveProjection.modelMatrix.Scalef(scaleBase[0]*scale[0],scaleBase[1]*scale[1],scaleBase[2]*scale[2]);
				perspectiveProjection.modelViewMatrix = perspectiveProjection.viewMatrix * perspectiveProjection.modelMatrix;
				volumes->attachVolumeBuffers();
				perspectiveProjection.sendMatricesData(volumes->getShader());
				glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,NULL);
				volumes->detachVolumeBuffers();
				glEndQuery(GL_SAMPLES_PASSED);
			}
		}

		/**
		 * Private method which is used to render clear scene. One of generic post process render tasks.
		 */
		void Renderer::renderClearScene()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 * Private method which is used to render off-screen scene. One of generic post process render tasks.
		 */
		void Renderer::renderOffScreenScene()
		{
			engineState->blendState.off();
			effects->getRenderPassList()->at(effects->currentID)->frameBuffer->bind();
			renderClearScene();
			renderSceneEntities();
			effects->getRenderPassList()->at(effects->currentID)->frameBuffer->unbind();
			engineState->blendState.on();
			effects->currentID++;
		}

		/**
		 * Private method which is used to render off-screen previous results of rendering. One of generic post process render tasks.
		 */
		void Renderer::renderOffScreenPrevious()
		{
			engineState->depthState.off();
			engineState->backCullingState.off();
			effects->getRenderPassList()->at(effects->currentID)->frameBuffer->bind();
			renderClearScene();

			Sprite* current = effects->getRenderPassList()->at(effects->currentID)->sprite;
			effects->getRenderPassList()->at(effects->currentID-1)->renderResult->setTexture(effects->getRenderPassList()->at(effects->currentID-1)->frameBuffer->getColorBuffer());
			current->setTexture(effects->getRenderPassList()->at(effects->currentID-1)->renderResult);

			updateOrthogonalProjection();
			orthogonalProjection.modelMatrix.LoadIdentity();
			orthogonalProjection.modelMatrix.Translatef(current->getPosition().x(),current->getPosition().y(),0.0f);
			orthogonalProjection.modelMatrix.Scalef(current->getSize().x(),current->getSize().y(),0.0f);
			Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),180.0f); 
			rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),0.0f); 
			orthogonalProjection.modelMatrix *= rotate.matrix4(); 
			Matrix4D modelViewProjection = transpose(orthogonalProjection.projectionMatrix*orthogonalProjection.modelMatrix);

			current->attachRenderObjects();

			current->getShader()->setUniformMatrix4fv("modelViewProjectionMatrix",modelViewProjection.data());
			current->getShader()->setUniformTexture("FrameBuffer",0);
			
			for(FloatUniforms::const_iterator it = effects->getRenderPassList()->at(effects->currentID)->floats.begin(); it != effects->getRenderPassList()->at(effects->currentID)->floats.end(); ++it)
				current->getShader()->setUniformf((*it).first,(*it).second);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_RECTANGLE,*current->getTexture()->getTexture());
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
			current->detachRenderObjects();
			effects->getRenderPassList()->at(effects->currentID)->frameBuffer->unbind();
			engineState->depthState.on();
			engineState->backCullingState.on();
			effects->currentID++;
		}

		/**
		 * Private method which is used to render final result of post-processing effect. One of generic post process render tasks.
		 */
		void Renderer::renderFinalRendering()
		{
			engineState->depthState.off();
			engineState->backCullingState.off();
			updateOrthogonalProjection();
	
			Sprite* current = effects->getRenderPassList()->at(effects->currentID)->sprite;
			effects->getRenderPassList()->at(effects->currentID-1)->renderResult->setTexture(effects->getRenderPassList()->at(effects->currentID-1)->frameBuffer->getColorBuffer());
			current->setTexture(effects->getRenderPassList()->at(effects->currentID-1)->renderResult);

			orthogonalProjection.modelMatrix.LoadIdentity();
			orthogonalProjection.modelMatrix.Translatef(current->getPosition().x(),current->getPosition().y(),0.0f);
			orthogonalProjection.modelMatrix.Scalef(current->getSize().x(),current->getSize().y(),0.0f);
			Quaternion rotate(Vector3D(1.0f,0.0f,0.0f),180.0f);
			rotate *= Quaternion(Vector3D(0.0f,1.0f,0.0f),0.0f);
			orthogonalProjection.modelMatrix *= rotate.matrix4();
			Matrix4D modelViewProjection = transpose(orthogonalProjection.projectionMatrix*orthogonalProjection.modelMatrix);

			current->attachRenderObjects();
			current->getShader()->setUniformMatrix4fv("modelViewProjectionMatrix",modelViewProjection.data());
			current->getShader()->setUniformTexture("FrameBuffer",0);
			current->getShader()->setUniformTexture("FrameBuffer2",1);

			for(FloatUniforms::const_iterator it = effects->getRenderPassList()->at(effects->currentID)->floats.begin(); it != effects->getRenderPassList()->at(effects->currentID)->floats.end(); ++it)
				current->getShader()->setUniformf((*it).first,(*it).second);

			int passAmount = effects->getRenderPassList()->size() - 1;
			for(int i = 0; i < passAmount-1; i++)
			{
				Sprite* pass = effects->getRenderPassList()->at(effects->currentID-passAmount+i)->sprite;
				glActiveTexture(GL_TEXTURE0+i);
				glBindTexture(GL_TEXTURE_RECTANGLE,*pass->getTexture()->getTexture());
			}
			glActiveTexture(GL_TEXTURE0+passAmount-1);
			glBindTexture(GL_TEXTURE_RECTANGLE,*current->getTexture()->getTexture());
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
			current->detachRenderObjects();
			engineState->depthState.on();
			engineState->backCullingState.on();
			effects->currentID = 0;
		}

		/**
		 * Private method which is used to update perspective projection transformation matrices.
		 */
		void Renderer::updatePerspectiveProjection()
		{
			Camera* currentCamera = engineScene->getWorldCamera();
			perspectiveProjection.modelMatrix.LoadIdentity();
			currentCamera->setViewMatrix(&perspectiveProjection.viewMatrix);
			currentCamera->setProjectionMatrix(&perspectiveProjection.projectionMatrix);
			perspectiveProjection.projectionMatrix.transpose();
			perspectiveProjection.inverseViewMatrix = inverse(perspectiveProjection.viewMatrix);
			perspectiveProjection.inverseViewMatrix.transpose();
		}
		
		/**
		 * Private method which is used to update orthogonal projection transformation matrices.
		 */
		void Renderer::updateOrthogonalProjection()
		{
			const int width = Configuration::getInstance()->getResolutionWidth();
			const int height = Configuration::getInstance()->getResolutionHeight();

			orthogonalProjection.modelMatrix.LoadIdentity();
			orthogonalProjection.viewMatrix.LoadIdentity();
			orthogonalProjection.projectionMatrix.LoadIdentity();
			orthogonalProjection.projectionMatrix.Ortho2D(-width,width,-height,height);
			orthogonalProjection.projectionMatrix.transpose();
		}

		/**
		 * Private method is used to intiialize shadow maps for directiona lights source.
		 */
		void Renderer::initializeShadowMaps()
		{
			renderToDepth = new Shader("renderToDepth");
			renderToDepth->setVertexPath("null");
			renderToDepth->setFragmentPath("null");
			renderToDepth->createVertexShader();
			renderToDepth->createFragmentShader();

			const char* vertexShaderSource = renderToDepthVertex;
			const char* fragmentShaderSource = renderToDepthFragment;

			if(vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
				Logger::getInstance()->saveLog(Log<string>("Sprite shader loading error detected: "));
		
			glShaderSource(renderToDepth->getShaderVertex(),1,&vertexShaderSource,0);
			glShaderSource(renderToDepth->getShaderFragment(),1,&fragmentShaderSource,0);
			glCompileShader(renderToDepth->getShaderVertex());
			glCompileShader(renderToDepth->getShaderFragment());
			renderToDepth->createShaderProgram();
			glAttachShader(renderToDepth->getShaderProgram(),renderToDepth->getShaderVertex());
			glAttachShader(renderToDepth->getShaderProgram(),renderToDepth->getShaderFragment());
			glLinkProgram(renderToDepth->getShaderProgram());

			unsigned lightAmount = lights->getDirectionalLights()->size();
			lightAmount += lights->getPointLights()->size();
			lightAmount += lights->getSpotLights()->size();

			for(unsigned i = 0; i < lightAmount; ++i)
			{
				ShadowMap* shadowMap = new ShadowMap();
				shadowMap->shadowMapHeight = 1024;
				shadowMap->shadowMapWidth = 1024;
				GLenum FBOstatus;
				glGenTextures(1,&shadowMap->depthTexture);
				glBindTexture(GL_TEXTURE_2D,shadowMap->depthTexture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
				glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
				glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY); 				

				glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,shadowMap->shadowMapWidth,shadowMap->shadowMapHeight,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,0);
				glBindTexture(GL_TEXTURE_2D,0);
				glGenFramebuffers(1,&shadowMap->frameBuffer);
				glBindFramebuffer(GL_FRAMEBUFFER, shadowMap->frameBuffer);
				
				glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,shadowMap->depthTexture,0);
				FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
				if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
					Logger::getInstance()->saveLog(Log<string>("ShadowMap FrameBuffer creaton error occurred!"));
				
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				shadowMap->bias = Matrix4D(0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.5,0.5,0.5,1.0);
				shadowMaps.push_back(shadowMap);
				string uniform = "shadowMatrix";
				uniform += boost::lexical_cast<string>(i);
				shadowMap->matrixName = uniform;
				uniform = "shadowTexture";
				uniform += boost::lexical_cast<string>(i);
				shadowMap->textureName = uniform;	
			}
		}
	}
}
