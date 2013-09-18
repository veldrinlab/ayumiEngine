/**
 * File contains declaration of ParticleEmiter structure.
 * @file	ParticleEmiter.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-12
 */

#ifndef PARTICLEEMITER_HPP
#define PARTICLEEMITER_HPP

#include <boost/function.hpp>

#include "Particle.hpp"

#include "../AyumiUtils/Vertex.hpp"
#include "../AyumiResource/Texture.hpp"
#include "../AyumiResource/Shader.hpp"
#include "../AyumiUtils/VertexArrayObject.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents Particle Emiter which is used to create particle effects. Particle Emiter is 
		 * defined by Lua script and store data of all particles, points geometry and initialize/update function.
		 */
		struct ParticleEmiter
		{
			//todo color in vbo
			Particle* particles;
			std::string name;
			AyumiMath::Vector3D origin;
			AyumiResource::Shader* shader;
			AyumiResource::Texture* texture;
			boost::function<void (ParticleEmiter*)> initializeFunction;
			boost::function<void (ParticleEmiter*,float)> updateFunction;
			AyumiUtils::VertexArrayObject* particleVao;
			GLuint particleVbo;
			AyumiUtils::Vertex<>* points;
			int particleAmount;
		};
	}
}
#endif
