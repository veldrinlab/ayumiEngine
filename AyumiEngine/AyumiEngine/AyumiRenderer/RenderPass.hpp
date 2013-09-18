/**
 * File contains declaraion of RenderPass structure.
 * @file    RenderPass.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-20
 */

#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include "Sprite.hpp"
#include "MaterialProperties.hpp"
#include "../AyumiUtils/FrameBufferObject.hpp"
#include "../AyumiResource/Shader.hpp"
#include "../AyumiResource/Texture.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents data of post-processing pass. It store Frame Buffer, shaders and additional
		 * parametres/control flags. All post-processing effects like Bloom, Depth of Field are collection of 
		 * defined RenderPasses.
		 */
		struct RenderPass
		{
			AyumiUtils::FrameBufferObject* frameBuffer;
			AyumiResource::Shader* shader;
			AyumiResource::Texture* renderResult;
			AyumiRenderer::Sprite* sprite;
			IntegerUniforms integers;
			FloatUniforms floats;
			TextureUniforms textures;
			bool offScreenRenderingScene;
			bool offScreenRenderingPrevious;
			bool finalRendering;
			bool clearBeforeFinal;
		};
	}
}
#endif
