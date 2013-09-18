/**
 * File contains declaraion of AyumiDestruction API
 * @file    AyumiDestruction.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef AYUMIDESTRUCTION_HPP
#define AYUMIDESTRUCTION_HPP

#include <vector>

#include "DestructibleTerrain.hpp"
#include "DestructibleObject.hpp"
#include "GeoModifier.hpp"

#include "../AyumiScene/SceneEntity.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		typedef std::vector<DestructibleObject> FractureConnections;
		typedef std::vector<AyumiScene::SceneEntity*> FractureObjects;
	}
}
#endif
