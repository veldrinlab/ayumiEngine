/**
 * File contains declaration of ParticleManager class.
 * @file    ParticleManager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-11
 */

#ifndef PARTICLEMANAGER_HPP
#define PARTICLEMANAGER_HPP

#include "ParticleEmiter.hpp"
#include "../AyumiScript.hpp"
#include "../AyumiResource/ResourceManager.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		typedef std::vector<ParticleEmiter*> ParticleEmiters;
	
		/**
		 * Class represents SpriteManager which is one Renderer managers used to create, store and update
		 * particle effects emiters. Particle systems are to create suck effects like smoke, weather effects, fire,
		 * explosions and many other special effects based on small particles which is defined by texture.
		 * Particle Emiters store data of points - in Geometry Shader Engine create textured quads and add size, color
		 * and other properties.
		 */
		class ParticleManager
		{
		private:
			ParticleEmiters emiters;
			ParticleEmiter* particleEmiter;
			Particle storageParticle;
			AyumiScript* particleEmiterScript;
			AyumiResource::ResourceManager* engineResource;

			void prepareParticleScript();
			void setVelocity(const luabind::object& velocity);
			void setAcceleration(const luabind::object& acceleration);
			void setRotation(const luabind::object& rotation);
			void setColor(const luabind::object& color);
			void setSize(const float size);
			void setLifeTime(const float lifeTime);
			void setParticleAmount(const int amount);
			void setEmiterShader(const std::string& name);
			void setEmiterTexture(const std::string& name);

		public:
			ParticleManager(AyumiResource::ResourceManager* engineResource);
			~ParticleManager();

			void initializeParticleManager();
			void updateEmiters(const float elapsedTime);
			void addParticleEmiter(const std::string& name, const std::string& path, boost::function<void (ParticleEmiter*)> initializeFunction,
								boost::function<void (ParticleEmiter*,float)> updateFunction, const AyumiMath::Vector3D& origin);
			void deleteParticleEmiter(const std::string& name);

			ParticleEmiters* getEmiters();
		};
	}
}

#endif
