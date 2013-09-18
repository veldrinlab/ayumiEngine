/**
 * File contains declaration of ResourceManager class.
 * @file    ResourceManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-10
 */

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "TextureManager.hpp"
#include "MeshManager.hpp"
#include "ShaderManager.hpp"

#include "../Logger.hpp"
#include "../AyumiCore/Configuration.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represnets one of Engine mosst important subsytem - ResourceManager which is used to load and store
		 * any kind of Engine resources like meshes, textures, shaders, scripts and audio files. ResourceManager class agregates
		 * one templated Manager class for each type of resources.
		 */
		class ResourceManager
		{
		private:
			MeshManager* meshManager;
			TextureManager* textureManager;
			ShaderManager* shaderManager;

		public:
			ResourceManager();
			~ResourceManager();

			void updateMeshResources(const std::string& scriptPath);
			void updateTextureResources(const std::string& scriptPath);
			void updateShaderResources(const std::string& scriptPath);

			Mesh* getMeshResource(const std::string& name);
			TextureResource getTextureResource(const std::string& name);
			ShaderResource getShaderResource(const std::string& name);
		};
	}
}
#endif
