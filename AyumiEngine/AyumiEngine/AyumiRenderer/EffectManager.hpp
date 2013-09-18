/**
 * File contains declaraion of EffectManager class.
 * @file    EffectManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-20
 */

#ifndef EFFECTMANAGER_HPP
#define EFFECTMANAGER_HPP

#include "RenderPass.hpp"
#include "SpriteManager.hpp"
#include "../AyumiScript.hpp"
#include "../AyumiCore/Configuration.hpp"
#include "../AyumiResource/ResourceManager.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class represents one of main Renderer manager class - EffectManager. It is used to load, store
		 * and configure generic post-processing passes to perform many fullscreen shader effects like: motion
		 * blur, depth of field or boolm effect. Effects definition are stored in Lua script, also all effects
		 * are loaded from Lua script which name is stored in Configuration object.
		 */
		class EffectManager
		{
		private:
			std::vector<RenderPass*> renderPassList;
			RenderPass* currentRenderPass;
			AyumiScript* renderPassScript;
			AyumiScript* renderPassListScript;
			AyumiResource::ResourceManager* engineResource;
			SpriteManager* sprites;

			void prepareEffectScripts();
			void loadEffect(const std::string& scriptFileName);
			void startEffectPass();
			void endEffectPass();
			void loadOffScreenRenderingScene(const bool value);
			void loadOffScreenRenderingPrevious(const bool value);
			void loadFinalRendering(const bool value);
			void loadClearBeforeFinal(const bool value);
			void loadFrameBufferParams(const std::string& renderTarget, const int width, const int height,const std::string& textureType);
			void loadEffectShader(const std::string& shaderName);
			void loadEffectIntegerUniform(const std::string& uniformName, const int value);
			void loadEffectFloatUniform(const std::string& uniformName, const float value);
			void loadEffectTextureUniform(const std::string& uniformName, const unsigned int value);
		
		public:
			EffectManager(AyumiResource::ResourceManager* engineResource, SpriteManager* sprites);
			~EffectManager();

			void initializeEffectManager();
			void updateEffects(const std::string& scriptPath);
		
			std::vector<RenderPass*>* getRenderPassList();
			RenderPass* getCurrentRenderPass() const;
			int currentID;
		};
	}
}
#endif
