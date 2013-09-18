/**
 * File contains declaraion of DestructibleTerrain structure.
 * @file    DestructibleTerrain.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef DESTRUCTIBLETERRAIN_HPP
#define DESTRUCTIBLETERRAIN_HPP

#include "../AyumiScene/SceneEntity.hpp"
#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Structure represnets all necessary data to execute terrain destruction. Terrain entity, params
		 * and base heightfield.
		 */
		struct DestructibleTerrain
		{
			AyumiScene::SceneEntity* entity;
			AyumiMath::Vector4D params;
			unsigned char* fileData;
			PxU32 filterGroup;
			PxU32 filterMask;

			/**
			 * Method is used to create destructible terrain.
			 * @param	size is height map size
			 * @param	path is path to height map file.
			 */
			void createDestructibleTerrain(const int size, const std::string& path)
			{
				fileData = new unsigned char[size*size];
				std::ifstream rawFile;
				rawFile.open(path,std::ios::in | std::ios::binary);
				if(rawFile.is_open())
					rawFile.read((char*)fileData,sizeof(unsigned char)*size*size);
				else
					std::cout << "Terrain raw file opening error occurred!" << std::endl; //logger
				rawFile.close();
			}

			/**
			 * Method is used to delete destructibel terrain. Free allocated memory.
			 */
			void deleteDestructibleTerrain()
			{
				delete [] fileData;
			}
		};
	}
}
#endif