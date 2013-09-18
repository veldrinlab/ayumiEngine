/**
 * File contains definition of MaterialManager class.
 * @file    MaterialManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#include "MaterialManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class constructor with initialize parameters. Create and prepare materials load scripts.
		 * @param	engineResource is pointer to Renderer ResourceManager object.
		 */
		MaterialManager::MaterialManager(ResourceManager* engineResource)
		{
			this->engineResource = engineResource;
			materialScript = new AyumiScript("null");
			materialListScript = new AyumiScript(Configuration::getInstance()->getMaterialScriptName()->c_str());
			prepareMaterialScripts();
		}

		/**
		 * Class destructor, free allocated memory. Delete materials load scripts.
		 */
		MaterialManager::~MaterialManager()
		{
			clearResourceMap();
			delete materialScript;
			delete materialListScript;
		}

		/**
		 * Method is used to initialize MaterialManager. Execute materials loading script.
		 */
		void MaterialManager::initializeMaterialManager()
		{
			materialListScript->executeScript();
		}

		/**
		 * Method is used to update materials collection by running resource control Lua script.
		 * @param	scriptPath is path to Lua resource control script.
		 */
		void MaterialManager::updateMaterials(const string& scriptPath)
		{
			materialListScript->setScriptFile(scriptPath.c_str());
			materialScript->executeScript();
		}

		void MaterialManager::sendMaterialData(EntityMaterial* m, const float deltaTime)
		{
			if(m->updateFunctorName != "null") {
				
				materialUpdateFunctors[m->updateFunctorName](m,deltaTime);

				for(VectorUniforms::const_iterator it = m->vectors.begin(); it != m->vectors.end(); ++it)
					m->entityShader->setUniform3fv(it->first,it->second.data());	

				for(IntegerUniforms::const_iterator it = m->integers.begin(); it != m->integers.end(); ++it)
					m->entityShader->setUniformi((*it).first,(*it).second);
	
				for(FloatUniforms::const_iterator it = m->floats.begin(); it != m->floats.end(); ++it)
					m->entityShader->setUniformf((*it).first,(*it).second);
			}
		}

		void MaterialManager::registerMaterialUpdateFunction(const string& name, MaterialUpdateFunction functor)
		{
			materialUpdateFunctors.insert(make_pair(name,functor));
		}

		/**
		 * Private method which is used to prepare materials load script. By using Luabind engine register MaterialManager
		 * class to Lua namespace and bind global pointer to engine material manager object and current material definition.
		 */
		void MaterialManager::prepareMaterialScripts()
		{
			luabind::module(materialScript->getVirtualMachine())
			[
				luabind::class_<MaterialManager>("MaterialManager")
				.def("loadMaterial",&MaterialManager::loadMaterial)
				.def("releaseMaterial",&MaterialManager::releaseMaterial)
				.def("clearMaterials",&MaterialManager::clearMaterials)
				.def("loadMaterialName",&MaterialManager::loadMaterialName)
				.def("loadMaterialIntegerParameter",&MaterialManager::loadMaterialIntegerParameter)
				.def("loadMaterialFloatParameter",&MaterialManager::loadMaterialFloatParameter)
				.def("loadMaterialLayer",&MaterialManager::loadMaterialLayer)
				.def("loadMaterialShader",&MaterialManager::loadMaterialShader)
				.def("loadMaterialAmbient",&MaterialManager::loadMaterialAmbient)
				.def("loadMaterialDiffuse",&MaterialManager::loadMaterialDiffuse)
				.def("loadMaterialSpecular",&MaterialManager::loadMaterialSpecular)
				.def("loadMaterialShininess",&MaterialManager::loadMaterialShininess)
				.def("setDepthTest",&MaterialManager::setDepthTest)
				.def("setBackFaceCull",&MaterialManager::setBackFaceCull)
				.def("loadEffectVectorUniform",&MaterialManager::loadEffectVectorUniform)
				.def("loadMaterialUpdateFunctor",&MaterialManager::loadMaterialUpdateFunctor)
			];

			luabind::globals(materialScript->getVirtualMachine())["Material"] = this;
			luabind::globals(materialListScript->getVirtualMachine())["MaterialManager"] = this;
		}

		/**
		 * Private method which is used to initialize loaded material, set material constant layers and material
		 * properties uniforms.
		 */
		void MaterialManager::initializeMaterial()
		{
			material->entityShader->bindShader();

			for(IntegerUniforms::const_iterator it = material->integers.begin(); it != material->integers.end(); ++it)
				material->entityShader->setUniformi((*it).first,(*it).second);

			for(FloatUniforms::const_iterator it = material->floats.begin(); it != material->floats.end(); ++it)
				material->entityShader->setUniformf((*it).first,(*it).second);

			for(TextureUniforms::const_iterator it = material->textures.begin(); it != material->textures.end(); ++it)
				material->entityShader->setUniformTexture((*it).first,(*it).second);

			for(VectorUniforms::const_iterator it = material->vectors.begin(); it != material->vectors.end(); ++it)
					material->entityShader->setUniform3fv(it->first,it->second.data());

			material->entityShader->setUniform4fv("material.ambient",material->materialProperties.ambient.data());
			material->entityShader->setUniform4fv("material.diffuse",material->materialProperties.diffuse.data());
			material->entityShader->setUniform4fv("material.specular",material->materialProperties.specular.data());
			material->entityShader->setUniformf("material.shininess",material->materialProperties.shininess);
			material->entityShader->unbindShader();
		}

		/**
		 * Private method which is used to load new material from material definition script. It can be called from Lua script.
		 * @param	scriptFileName is material definition file name.
		 */
		void MaterialManager::loadMaterial(const string& scriptFileName)
		{
			material = new EntityMaterial();

			//
			//default
			material->depthTest = true; 
			material->backfaceCull = true;
			material->updateFunctorName = "null"; //istotne!

			materialScript->setScriptFile(scriptFileName.c_str());
			materialScript->executeScript();
			initializeMaterial();
			addResource(material->materialName,Material(material));
		}

		/**
		 * Private method which is used to release material from manager container. It can be called from Lua script.
		 * @param	name is resource name id.
		 */
		void MaterialManager::releaseMaterial(const string& name)
		{
			deleteResource(name);
		}

		/**
		 * Private method which is used to release all materials from manager container. It can be called from Lua script.
		 */
		void MaterialManager::clearMaterials()
		{
			clearResourceMap();
		}

		/**
		 * Private method which is used to load material name. It can be called from Lua script.
		 * @param	name is material name string.
		 */
		void MaterialManager::loadMaterialName(const string& name)
		{
			material->materialName = name;
		}

		/**
		 * Private method which is used to load material integer parameter. It can be called from Lua script.
		 * @param	parameterName is material param name.
		 * @param	value is parameter value.
		 */
		void MaterialManager::loadMaterialIntegerParameter(const string& parameterName, const int value)
		{
			material->integers.insert(make_pair(parameterName,value));
		}

		/**
		 * Private method which is used to load material float parameter. It can be called from Lua script.
		 * @param	parameterName is material param name.
		 * @param	value is parameter value.
		 */
		void MaterialManager::loadMaterialFloatParameter(const string& parameterName, const float value)
		{
			material->floats.insert(make_pair(parameterName,value));
		}

		/**
		 * Private method which is used to load material layer. It can be called from Lua script.
		 * @param	layerName is material layer name.
		 * @param	slot is texture slot.
		 */
		void MaterialManager::loadMaterialLayer(const string& layerName, const unsigned int slot)
		{
			material->textures.insert(make_pair(layerName,slot));
			material->materialLayers.push_back(engineResource->getTextureResource(layerName).get());
		}

		/**
		 * Private method which is used to load material shader. It can be called from Lua script.
		 * @param	name is material shader name.
		 */
		void MaterialManager::loadMaterialShader(const string& name)
		{
			material->entityShader = engineResource->getShaderResource(name).get();
		}

		/**
		 * Private method which is used to load material ambient properties. It can be called from Lua script.
		 * @param	ambinet is material ambient properties array.
		 */
		void MaterialManager::loadMaterialAmbient(const luabind::object& ambient)
		{
			material->materialProperties.ambient[0] = luabind::object_cast<float>(ambient[1]);
			material->materialProperties.ambient[1] = luabind::object_cast<float>(ambient[2]);
			material->materialProperties.ambient[2] = luabind::object_cast<float>(ambient[3]);
			material->materialProperties.ambient[3] = luabind::object_cast<float>(ambient[4]);
		}

		/**
		 * Private method which is used to load material diffuse properties. It can be called from Lua script.
		 * @param	ambinet is material diffuse properties array.
		 */
		void MaterialManager::loadMaterialDiffuse(const luabind::object& diffuse)
		{
			material->materialProperties.diffuse[0] = luabind::object_cast<float>(diffuse[1]);
			material->materialProperties.diffuse[1] = luabind::object_cast<float>(diffuse[2]);
			material->materialProperties.diffuse[2] = luabind::object_cast<float>(diffuse[3]);
			material->materialProperties.diffuse[3] = luabind::object_cast<float>(diffuse[4]);
		}

		/**
		 * Private method which is used to load material specular properties. It can be called from Lua script.
		 * @param	ambinet is material specular properties array.
		 */
		void MaterialManager::loadMaterialSpecular(const luabind::object& specular)
		{
			material->materialProperties.specular[0] = luabind::object_cast<float>(specular[1]);
			material->materialProperties.specular[1] = luabind::object_cast<float>(specular[2]);
			material->materialProperties.specular[2] = luabind::object_cast<float>(specular[3]);
			material->materialProperties.specular[3] = luabind::object_cast<float>(specular[4]);
		}

		/**
		 * Private method which is used to load material shininess properties. It can be called from Lua script.
		 * @param	shininess is material shininess properties.
		 */
		void MaterialManager::loadMaterialShininess(const float shininess)
		{
			material->materialProperties.shininess = shininess;
		}

		void MaterialManager::loadMaterialUpdateFunctor(const string& name)
		{
			material->updateFunctorName = name;
		}

		void MaterialManager::setDepthTest(const string& depthTest)
		{
			material->depthTest = (depthTest == "true" || depthTest == "True" || depthTest == "TRUE");
		}

		void MaterialManager::setBackFaceCull(const string& backfaceCull)
		{
			material->backfaceCull = (backfaceCull == "true" || backfaceCull == "True" || backfaceCull == "TRUE");
		}

		void MaterialManager::loadEffectVectorUniform(const string& name, const luabind::object& vector)
		{
			Vector3D v;

			v[0] = luabind::object_cast<float>(vector[1]);
			v[1] = luabind::object_cast<float>(vector[2]);
			v[2] = luabind::object_cast<float>(vector[3]);

			material->vectors.insert(make_pair(name,v));
		}
	}
}
