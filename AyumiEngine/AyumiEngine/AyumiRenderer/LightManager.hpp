/**
 * File contains declaration of LightManager class.
 * @file    LightManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-15
 */

#ifndef LIGHTMANAGER_HPP
#define LIGHTMANAGER_HPP

#include <boost/lexical_cast.hpp>
#include <vector>

#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"

#include "../AyumiScript.hpp"
#include "../AyumiCore/Configuration.hpp"
#include "../AyumiResource/Shader.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		typedef std::vector<std::pair<DirectionalLight*,std::vector<std::string>>> DirectionalLights;
		typedef std::vector<std::pair<PointLight*,std::vector<std::string>>> PointLights;
		typedef std::vector<std::pair<SpotLight*,std::vector<std::string>>> SpotLights;

		/**
		 * Class represents LightManager which is important part of Renderer used to load and store data
		 * of scene lights which is used in Forward Rendering. User can define and load three type of lights:
		 * spot, point and directional from Lua script. 8 lights is maximum value for good efficient. User can
		 * add more lights to scene but it cannot be calculated in real-time. 
		 */
		class LightManager
		{
		private:
			AyumiScript* lightScript;
			DirectionalLights directionalLights;
			PointLights pointLights;
			SpotLights spotLights;
			
			void prepareLightScript();
			void addDirectionalLight(const std::string& name, const luabind::object& color, const luabind::object& direction);
			void addPointLight(const std::string& name, const luabind::object& color, const luabind::object& position, const float radius);
			void addSpotLight(const std::string& name, const luabind::object& color, const luabind::object& position, const luabind::object& direction,  const float range, const float cosInnerCone, const float cosOuterCone);
			
			void deleteDirectionalLight(const std::string& name);
			void deletePointLight(const std::string& name);
			void deleteSpotLight(const std::string& name);
			void clearLights();

		public:
			LightManager();
			~LightManager();

			void initializeLightManager();
			void updateLights(const std::string& scriptPath);
			void sendLightsData(AyumiResource::Shader* shader);

			DirectionalLights* getDirectionalLights();
			PointLights* getPointLights();
			SpotLights* getSpotLights();
		};
	}
}
#endif
