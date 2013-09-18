/**
 * File contains declaration of MaterialManager class.
 * @file    MaterialManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-25
 */

#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp> 
#include <string>
#include <map>
#include <deque>

#include "../AyumiScript.hpp"
#include "../AyumiCore/Configuration.hpp"
#include "../AyumiScene/EntityMaterial.hpp"
#include "../AyumiResource/ResourceManager.hpp"
#include "../AyumiUtils/Manager.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		typedef boost::shared_ptr<AyumiScene::EntityMaterial> Material;
		typedef boost::function<void (AyumiScene::EntityMaterial*,float)> MaterialUpdateFunction;
		typedef std::map<std::string,MaterialUpdateFunction> MaterialUpdateFunctors;
		

		/**
		 * Class represents one of main Renderer manager class - MaterialManager. It is used to load and 
		 * store Scene Entity materials which with geometry are bacis elements of every engine entity.
		 * Materials definitions are stored in Lua script, also all materials are loaded by Lua script.
		 * MaterialMnager extends templated Manager pattern.
		 */
		class MaterialManager : public AyumiUtils::Manager<std::string, Material>
		{
		private:
			AyumiScene::EntityMaterial* material;
			AyumiScript* materialScript;
			AyumiScript* materialListScript;
			AyumiResource::ResourceManager* engineResource;
			MaterialUpdateFunctors materialUpdateFunctors;

			void prepareMaterialScripts();
			void initializeMaterial();
			void loadMaterial(const std::string& scriptFileName);
			void releaseMaterial(const std::string& name);
			void clearMaterials();
			void loadMaterialName(const std::string& name);
			void loadMaterialIntegerParameter(const std::string& parameterName, const int value);
			void loadMaterialFloatParameter(const std::string& parameterName, const float value);
			void loadMaterialLayer(const std::string& layerName, const unsigned int slot);
			void loadMaterialShader(const std::string& name);
			void loadMaterialAmbient(const luabind::object& ambient); 
			void loadMaterialDiffuse(const luabind::object& diffuse); 
			void loadMaterialSpecular(const luabind::object& specular);
			void loadMaterialShininess(const float shininess);
			void loadMaterialUpdateFunctor(const std::string& name);
			void setDepthTest(const std::string& depthTest);
			void setBackFaceCull(const std::string& backfaceCull);
			void loadEffectVectorUniform(const std::string& name, const luabind::object& vector);

		public:
			MaterialManager(AyumiResource::ResourceManager* engineResource);
			~MaterialManager();

			void initializeMaterialManager();
			void updateMaterials(const std::string& sriptPath);
			void sendMaterialData(AyumiScene::EntityMaterial* m, const float deltaTime);
			void registerMaterialUpdateFunction(const std::string& name, MaterialUpdateFunction functor);
		};
	}
}
#endif
