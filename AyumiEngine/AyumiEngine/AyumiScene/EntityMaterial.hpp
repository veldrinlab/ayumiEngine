/**
 * File contains declaration of EntityMaterial structure.
 * @file    EntityMaterial.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#ifndef ENTITYMATERIAL_HPP
#define ENTITYMATERIAL_HPP

#include <vector>
#include "../AyumiResource/Texture.hpp"
#include "../AyumiResource/Shader.hpp"
#include "../AyumiRenderer/MaterialProperties.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Structure represents ScenEntity Material which store material name, texture layeres, rendering shader
		 * and all additional parameters. Beside of entity geometry structure this is basic part of all engine
		 * scene entities.
		 */
		struct EntityMaterial
		{
			std::string materialName;
			std::vector<AyumiResource::Texture*> materialLayers;
			AyumiRenderer::MaterialProperties materialProperties;
			AyumiResource::Shader* entityShader;
			IntegerUniforms integers;
			FloatUniforms floats;
			TextureUniforms textures;

			//
			VectorUniforms vectors;
			std::string updateFunctorName;
			bool depthTest;
			bool backfaceCull;
		};
	}
}
#endif
