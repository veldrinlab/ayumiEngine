/**
 * File contains definition of EffectManager class.
 * @file    EffectManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-20
 */

#include "EffectManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiCore;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class constructo which initialize parameters.
		 * @param	engineResource is pointer to engine ResourceManager.
		 * @param	sprites is pointer to Renderer Sprite module.
		 */
		EffectManager::EffectManager(ResourceManager* engineResource, SpriteManager* sprites)
		{
			this->engineResource = engineResource;
			this->sprites = sprites;
			renderPassScript = new AyumiScript("null");
			renderPassListScript = new AyumiScript(Configuration::getInstance()->getEffectScriptName()->c_str());
			prepareEffectScripts();
			currentID = 0;
		}

		/**
		 * Class destructor, free allocated memory.
		 */
		EffectManager::~EffectManager()
		{
			delete renderPassScript;
			delete renderPassListScript;
			for(vector<RenderPass*>::const_iterator it = renderPassList.begin(); it != renderPassList.end(); ++it)
			{
				delete (*it)->renderResult;
				delete (*it)->frameBuffer;
				delete (*it)->sprite;
			}
			renderPassList.clear();
		}

		/**
		 * Method is used to initialize effect manager. Execute effects loading script.
		 */
		void EffectManager::initializeEffectManager()
		{
			renderPassListScript->executeScript();
		}

		/**
		 * Method is used to update post process effects pipeline by running Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void EffectManager::updateEffects(const string& scriptPath)
		{
			for(vector<RenderPass*>::const_iterator it = renderPassList.begin(); it != renderPassList.end(); ++it)
			{
				delete (*it)->renderResult;
				delete (*it)->frameBuffer;
				delete (*it)->sprite;
			}
			renderPassList.clear();

			renderPassListScript->setScriptFile(scriptPath.c_str());
			renderPassListScript->executeScript();
		}

		/**
		 * Accessor to private render pass collection member.
		 * @return	pointer to render pass collection.
		 */
		vector<RenderPass*>* EffectManager::getRenderPassList()
		{
			return &renderPassList;
		}

		/**
		 * Accessor to private current render pass member.
		 * @return	pointer to current render pass.
		 */
		RenderPass* EffectManager::getCurrentRenderPass() const
		{
			return currentRenderPass;
		}

		/**
		 * Private method which is used to prepare effects load script. By using Luabind engine register EffectManager
		 * class to Lua namespace and bind global pointer to engine effect manager object and current render pass.
		 */
		void EffectManager::prepareEffectScripts()
		{
			luabind::module(renderPassScript->getVirtualMachine())
			[
				luabind::class_<EffectManager>("EffectManager")
				.def("loadEffect",&EffectManager::loadEffect)
				.def("startEffectPass",&EffectManager::startEffectPass)
				.def("endEffectPass",&EffectManager::endEffectPass)
				.def("loadOffScreenRenderingScene",&EffectManager::loadOffScreenRenderingScene)
				.def("loadOffScreenRenderingPrevious",&EffectManager::loadOffScreenRenderingPrevious)
				.def("loadFinalRendering",&EffectManager::loadFinalRendering)
				.def("loadClearBeforeFinal",&EffectManager::loadClearBeforeFinal)
				.def("loadFrameBufferParams",&EffectManager::loadFrameBufferParams)
				.def("loadEffectShader",&EffectManager::loadEffectShader)
				.def("loadEffectIntegerUniform",&EffectManager::loadEffectIntegerUniform)
				.def("loadEffectFloatUniform",&EffectManager::loadEffectFloatUniform)
				.def("loadEffectTextureUniform",&EffectManager::loadEffectTextureUniform)
			];

			luabind::globals(renderPassScript->getVirtualMachine())["Effect"] = this;
			luabind::globals(renderPassListScript->getVirtualMachine())["EffectManager"] = this;
		}
		/**
		 * Private method which is used to load post-process effect.
		 * @param	scriptFileName is path to effect scritp file.
		 */
		void EffectManager::loadEffect(const string& scriptFileName)
		{
			renderPassScript->setScriptFile(scriptFileName.c_str());
			renderPassScript->executeScript();
		}

		/**
		 * Private method which is used to start loading new effect render pass. Create new RenderPass object.
		 */
		void EffectManager::startEffectPass()
		{
			currentRenderPass = new RenderPass();
		}

		/**
		 * Private method which is used to end loading new effect render pass. Create and configure RenderPass data.
		 */
		void EffectManager::endEffectPass()
		{
			currentRenderPass->renderResult = new Texture();
			const float width = static_cast<float>(currentRenderPass->frameBuffer->getWidth());
			const float height = static_cast<float>(currentRenderPass->frameBuffer->getHeight());
			currentRenderPass->sprite = sprites->createSprite(currentRenderPass->renderResult,currentRenderPass->shader,Vector3D(0.0f,0.0f,0.0f),Vector3D(width,height,0.0f));

			renderPassList.push_back(currentRenderPass);
			currentRenderPass = renderPassList[0];
		}

		/**
		 * Private method which is used to load one of control flag - off screen rendering scene.
		 * @param	value is control flag.
		 */
		void EffectManager::loadOffScreenRenderingScene(const bool value)
		{
			currentRenderPass->offScreenRenderingScene = value;
		}

		/**
		 * Private method which is used to load one of control flag - off screen rendering previous pass result.
		 * @param	value is control flag.
		 */
		void EffectManager::loadOffScreenRenderingPrevious(const bool value)
		{
			currentRenderPass->offScreenRenderingPrevious = value;
		}

		/**
		 * Private method which is used to load one of control flag - final rendering.
		 * @param	value is control flag.
		 */
		void EffectManager::loadFinalRendering(const bool value)
		{
			currentRenderPass->finalRendering = value;
		}

		/**
		 * Private method which is used to load one of control flag - clear before final rendering.
		 * @param	value is control flag.
		 */
		void EffectManager::loadClearBeforeFinal(const bool value)
		{
			currentRenderPass->clearBeforeFinal = value;
		}

		/**
		 * Private method which is used to load frame buffers initialize parameteres. Create new FBO and configure it.
		 * @param	renderTarget is name of render target. For example ColorBuffer/DepthBuffer.
		 * @param	width is buffer width.
		 * @param	height is buffer height.
		 * @param	textureType is rendert target texture type. For example Recntangle/Texture2D.
		 */
		void EffectManager::loadFrameBufferParams(const string& renderTarget, const int width, const int height, const string& textureType)
		{
			currentRenderPass->frameBuffer = new FrameBufferObject(width,height,depth32);
			currentRenderPass->frameBuffer->create();
			currentRenderPass->frameBuffer->bind();

			if(renderTarget == "ColorBuffer")
			{
				if(textureType == "Rectangle")
				{
					if(!currentRenderPass->frameBuffer->attachColorTexture(GL_TEXTURE_RECTANGLE,currentRenderPass->frameBuffer->createColorRectTexture(GL_RGBA,GL_RGBA8),0))
						Logger::getInstance()->saveLog(Log<string>("Buffer error with color attachment detected!"));
				}
				else if(textureType == "Texture2D")
				{
					if(!currentRenderPass->frameBuffer->attachColorTexture(GL_TEXTURE_2D,currentRenderPass->frameBuffer->createColorTexture(GL_RGBA,GL_RGBA8),0))
						Logger::getInstance()->saveLog(Log<string>("Buffer error with color attachment detected!"));
				}
			}
			else if(renderTarget == "DepthBuffer")
			{
				if(textureType == "Rectangle")
				{
					if(!currentRenderPass->frameBuffer->attachDepthTexture(GL_TEXTURE_RECTANGLE,currentRenderPass->frameBuffer->createColorRectTexture(GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT)))
						Logger::getInstance()->saveLog(Log<string>("Buffer error with color attachment detected!"));
				}
				else if(textureType == "Texture2D")
				{
					if(!currentRenderPass->frameBuffer->attachDepthTexture(GL_TEXTURE_2D,currentRenderPass->frameBuffer->createColorTexture(GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT)))
						Logger::getInstance()->saveLog(Log<string>("Buffer error with color attachment detected!"));
				}
			}

			if(!currentRenderPass->frameBuffer->isOk())
				Logger::getInstance()->saveLog(Log<string>("Error with frame buffer!"));
			
			currentRenderPass->frameBuffer->unbind();
		}

		/**
		 * Private method which is used to load effect shader.
		 * @param	shaderName is shader id.
		 */
		void EffectManager::loadEffectShader(const string& shaderName)
		{
			currentRenderPass->shader = engineResource->getShaderResource(shaderName).get();
		}

		/**
		 * Private method which is used to load effect integer parameter.
		 * @param	uniformName is material param name.
		 * @param	value is parameter value.
		 */
		void EffectManager::loadEffectIntegerUniform(const string& uniformName, const int value)
		{
			currentRenderPass->integers.insert(make_pair(uniformName,value));
		}

		/**
		 * Private method which is used to load effect float parameter.
		 * @param	uniformName is material param name.
		 * @param	value is parameter value.
		 */
		void EffectManager::loadEffectFloatUniform(const string& uniformName, const float value)
		{
			currentRenderPass->floats.insert(make_pair(uniformName,value));
		}

		/**
		 * Private method which is used to load effect texture parameter.
		 * @param	uniformName is material param name.
		 * @param	value is parameter value.
		 */
		void EffectManager::loadEffectTextureUniform(const string& uniformName, const unsigned int value)
		{
			currentRenderPass->textures.insert(make_pair(uniformName,value));
		}
	}
}
