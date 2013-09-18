/**
 * File contains definition of LightManager class.
 * @file    LightManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-05-15
 */

#include "LightManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiResource;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class default constructor. Create and prepare lights load script.
		 */
		LightManager::LightManager()
		{
			lightScript = new AyumiScript(Configuration::getInstance()->getLightScriptName()->c_str());
			prepareLightScript();
		}
		
		/**
		 * Class destructor, free allocated memory. Delete light script and clear lights data.
		 */
		LightManager::~LightManager()
		{
			delete lightScript;
			clearLights();
		}
		
		/**
		 * Method is used to initialize scene light object. Execute light loading script.
		 */
		void LightManager::initializeLightManager()
		{
			lightScript->executeScript();
		}

		/**
		 * Method is used to update lights collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void LightManager::updateLights(const string& scriptPath)
		{
			lightScript->setScriptFile(scriptPath.c_str());
			lightScript->executeScript();
		}


		/**
		 * Method is used to send Directional, Point and Spot Lights data to shader in Forward Rendering lighting.
		 * @param	shader is pointer to destination shader.
		 */
		void LightManager::sendLightsData(Shader* shader)
		{
			for(DirectionalLights::const_iterator it = directionalLights.begin(); it != directionalLights.end(); ++it)
			{
				DirectionalLight* light = (*it).first;
				vector<string> uniforms = (*it).second;
				shader->setUniform3fv(uniforms[0].c_str(),light->direction.data());
				shader->setUniform4fv(uniforms[1].c_str(),light->color.ambient.data());
				shader->setUniform4fv(uniforms[2].c_str(),light->color.diffuse.data());
				shader->setUniform4fv(uniforms[3].c_str(),light->color.specular.data());
			}

			for(PointLights::const_iterator it = pointLights.begin(); it != pointLights.end(); ++it)
			{
				PointLight* light = (*it).first;
				vector<string> uniforms = (*it).second;
				shader->setUniform3fv(uniforms[0].c_str(),light->position.data());
				shader->setUniform4fv(uniforms[1].c_str(),light->color.ambient.data());
				shader->setUniform4fv(uniforms[2].c_str(),light->color.diffuse.data());
				shader->setUniform4fv(uniforms[3].c_str(),light->color.specular.data());
				shader->setUniformf(uniforms[4].c_str(),light->radius);
			}

			for(SpotLights::const_iterator it = spotLights.begin(); it != spotLights.end(); ++it)
			{
				SpotLight* light = (*it).first;
				vector<string> uniforms = (*it).second;
				shader->setUniform3fv(uniforms[0].c_str(),light->position.data());
				shader->setUniform4fv(uniforms[1].c_str(),light->color.ambient.data());
				shader->setUniform4fv(uniforms[2].c_str(),light->color.diffuse.data());
				shader->setUniform4fv(uniforms[3].c_str(),light->color.specular.data());
				shader->setUniform3fv(uniforms[4].c_str(),light->direction.data());	
				shader->setUniformf(uniforms[5].c_str(),light->range);
				shader->setUniformf(uniforms[6].c_str(),light->cosInnerCone);
				shader->setUniformf(uniforms[7].c_str(),light->cosOuterCone);
			}
		}

		/**
		 * Accessor to private directional light collection member.
		 * @return	pointer to directional lights collection.
		 */
		DirectionalLights* LightManager::getDirectionalLights()
		{
			return &directionalLights;
		}

		/**
		 * Accessor to private point light collection member.
		 * @return	pointer to point lights collection.
		 */
		PointLights* LightManager::getPointLights()
		{
			return &pointLights;
		}

		/**
		 * Accessor to private spot light collection member.
		 * @return	pointer to spot lights collection.
		 */
		SpotLights* LightManager::getSpotLights()
		{
			return &spotLights;
		}

		/**
		 * Private method which is used to prepare light load script. By using Luabind engine register LightManager class
		 * to Lua namespace and bind global pointer to engine light manager object.
		 */
		void LightManager::prepareLightScript()
		{
			luabind::module(lightScript->getVirtualMachine())
			[
				luabind::class_<LightManager>("LightManager")
				.def("addDirectionalLight",&LightManager::addDirectionalLight)
				.def("addPointLight",&LightManager::addPointLight)
				.def("addSpotLight",&LightManager::addSpotLight)
				.def("deleteDirectionalLight",&LightManager::deleteDirectionalLight)
				.def("deletePointLight",&LightManager::deletePointLight)
				.def("deleteSpotLight",&LightManager::deleteSpotLight)
				.def("clearLights",&LightManager::clearLights)
			];

			luabind::globals(lightScript->getVirtualMachine())["LightManager"] = this;
		}

		/**
		 * Private method which is used to load directional light. It can be called from Lua script.
		 * @param	name is light id.
		 * @param	color is light color vector.
		 * @param	direction is light direction vector.
		 */
		void LightManager::addDirectionalLight(const string& name, const luabind::object& color, const luabind::object& direction)
		{
			DirectionalLight* light = new DirectionalLight();

			light->type = DIRECTIONAL;
			light->name = name;

			light->color.ambient[0] = luabind::object_cast<float>(color[1]);
			light->color.ambient[1] = luabind::object_cast<float>(color[2]);
			light->color.ambient[2] = luabind::object_cast<float>(color[3]);
			light->color.ambient[3] = luabind::object_cast<float>(color[4]);

			light->color.diffuse[0] = luabind::object_cast<float>(color[5]);
			light->color.diffuse[1] = luabind::object_cast<float>(color[6]);
			light->color.diffuse[2] = luabind::object_cast<float>(color[7]);
			light->color.diffuse[3] = luabind::object_cast<float>(color[8]);

			light->color.specular[0] = luabind::object_cast<float>(color[9]);
			light->color.specular[1] = luabind::object_cast<float>(color[10]);
			light->color.specular[2] = luabind::object_cast<float>(color[11]);
			light->color.specular[3] = luabind::object_cast<float>(color[12]);

			light->direction[0] = luabind::object_cast<float>(direction[1]);
			light->direction[1] = luabind::object_cast<float>(direction[2]);
			light->direction[2] = luabind::object_cast<float>(direction[3]);
	
			vector<string> uniforms;
			int i = directionalLights.size();

			string uniformBase = "directionalLight[";
			uniformBase += boost::lexical_cast<string>(i);
			uniformBase+= "]";
			string uniformName = uniformBase + ".direction";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".ambient";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".diffuse";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".specular";
			uniforms.push_back(uniformName);
			
			directionalLights.push_back(make_pair(light,uniforms));
			
			if(directionalLights.size() + pointLights.size() + spotLights.size() >= 8)
				Logger::getInstance()->saveLog(Log<string>("Too many lights for Forward Rendering!"));
		}

		/**
		 * Private method which is used to load point light. It can be called from Lua script.
		 * @param	name is light id.
		 * @param	color is light color vector.
		 * @param	position is light position vector.
		 * @param	radius is point light sphere radius.
		 */
		void LightManager::addPointLight(const string& name, const luabind::object& color, const luabind::object& position, const float radius)
		{
			PointLight* light = new PointLight();

			light->type = POINT;
			light->name = name;

			light->color.ambient[0] = luabind::object_cast<float>(color[1]);
			light->color.ambient[1] = luabind::object_cast<float>(color[2]);
			light->color.ambient[2] = luabind::object_cast<float>(color[3]);
			light->color.ambient[3] = luabind::object_cast<float>(color[4]);

			light->color.diffuse[0] = luabind::object_cast<float>(color[5]);
			light->color.diffuse[1] = luabind::object_cast<float>(color[6]);
			light->color.diffuse[2] = luabind::object_cast<float>(color[7]);
			light->color.diffuse[3] = luabind::object_cast<float>(color[8]);

			light->color.specular[0] = luabind::object_cast<float>(color[9]);
			light->color.specular[1] = luabind::object_cast<float>(color[10]);
			light->color.specular[2] = luabind::object_cast<float>(color[11]);
			light->color.specular[3] = luabind::object_cast<float>(color[12]);

			light->position[0] = luabind::object_cast<float>(position[1]);
			light->position[1] = luabind::object_cast<float>(position[2]);
			light->position[2] = luabind::object_cast<float>(position[3]);

			light->radius = radius;

			vector<string> uniforms;
			int i = pointLights.size();

			string uniformBase = "pointLight[";
			uniformBase += boost::lexical_cast<string>(i);
			uniformBase+= "]";

			string uniformName = uniformBase + ".position";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".ambient";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".diffuse";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".specular";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".radius";
			uniforms.push_back(uniformName);

			pointLights.push_back(make_pair(light,uniforms));

			if(directionalLights.size() + pointLights.size() + spotLights.size() >= 8)
				Logger::getInstance()->saveLog(Log<string>("Too many lights for Forward Rendering!"));
		}

		/**
		 * Private method which is used to load spot light. It can be called from Lua script.
		 * @param	name is light id.
		 * @param	color is light color vector.
		 * @param	position is light position vector.
		 * @param	direction is light direction vector.
		 * @param	range is point light range.
		 * @param	cosInnerCone is spot light inner cone.
		 * @param	cosOuterCone is spot light outer cone.
		 */
		void LightManager::addSpotLight(const string& name, const luabind::object& color, const luabind::object& position, const luabind::object& direction,  const float range, const float cosInnerCone, const float cosOuterCone)
		{
			SpotLight* light = new SpotLight();

			light->type = SPOT;
			light->name = name;

			light->color.ambient[0] = luabind::object_cast<float>(color[1]);
			light->color.ambient[1] = luabind::object_cast<float>(color[2]);
			light->color.ambient[2] = luabind::object_cast<float>(color[3]);
			light->color.ambient[3] = luabind::object_cast<float>(color[4]);

			light->color.diffuse[0] = luabind::object_cast<float>(color[5]);
			light->color.diffuse[1] = luabind::object_cast<float>(color[6]);
			light->color.diffuse[2] = luabind::object_cast<float>(color[7]);
			light->color.diffuse[3] = luabind::object_cast<float>(color[8]);

			light->color.specular[0] = luabind::object_cast<float>(color[9]);
			light->color.specular[1] = luabind::object_cast<float>(color[10]);
			light->color.specular[2] = luabind::object_cast<float>(color[11]);
			light->color.specular[3] = luabind::object_cast<float>(color[12]);

			light->position[0] = luabind::object_cast<float>(position[1]);
			light->position[1] = luabind::object_cast<float>(position[2]);
			light->position[2] = luabind::object_cast<float>(position[3]);

			light->direction[0] = luabind::object_cast<float>(direction[1]);
			light->direction[1] = luabind::object_cast<float>(direction[2]);
			light->direction[2] = luabind::object_cast<float>(direction[3]);

			light->range = range;
			light->cosInnerCone = cosInnerCone;
			light->cosOuterCone = cosOuterCone;

			vector<string> uniforms;
			int i = spotLights.size();

			string uniformBase = "spotLight[";
			uniformBase += boost::lexical_cast<string>(i);
			uniformBase+= "]";

			string uniformName = uniformBase + ".position";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".ambient";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".diffuse";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".specular";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".direction";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".range";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".cosInnerCone";
			uniforms.push_back(uniformName);
			uniformName = uniformBase + ".cosOuterCone";
			uniforms.push_back(uniformName);

			spotLights.push_back(make_pair(light,uniforms));
			if(directionalLights.size() + pointLights.size() + spotLights.size() >=8 )
				Logger::getInstance()->saveLog(Log<string>("Too many lights for Forward Rendering!"));
		}

		/**
		 * Private method which is used to delete directional light from light collection. It can be called from Lua script.
		 * @param	name is light id.
		 */
		void LightManager::deleteDirectionalLight(const string& name)
		{
			DirectionalLights::const_iterator it = directionalLights.begin();

			for(; it != directionalLights.end(); ++it)
				if((*it).first->name == name)
					break;
			if(it != directionalLights.end())
				directionalLights.erase(it);
		}

		/**
		 * Private method which is used to delete point light from light collection. It can be called from Lua script.
		 * @param	name is light id.
		 */
		void LightManager::deletePointLight(const string& name)
		{
			PointLights::const_iterator it = pointLights.begin();

			for(; it != pointLights.end(); ++it)
				if((*it).first->name == name)
					break;
			if(it != pointLights.end())
				pointLights.erase(it);
		}

		/**
		 * Private method which is used to delete spot light from light collection. It can be called from Lua script.
		 * @param	name is light id.
		 */
		void LightManager::deleteSpotLight(const string& name)
		{
			SpotLights::const_iterator it = spotLights.begin();

			for(; it != spotLights.end(); ++it)
				if((*it).first->name == name)
					break;
			if(it != spotLights.end())
				spotLights.erase(it);
		}

		/**
		 * Private method which is used to clear all lights data. It can be called from Lua script.
		 */
		void LightManager::clearLights()
		{
			for(DirectionalLights::const_iterator it = directionalLights.begin(); it != directionalLights.end(); ++it)
				delete (*it).first;
			directionalLights.clear();
			
			for(PointLights::const_iterator it = pointLights.begin(); it != pointLights.end(); ++it)
				delete (*it).first;
			pointLights.clear();
			for(SpotLights::const_iterator it = spotLights.begin(); it != spotLights.end(); ++it)
				delete (*it).first;
			spotLights.clear();
		}
	}
}
