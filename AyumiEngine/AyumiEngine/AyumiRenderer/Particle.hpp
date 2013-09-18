/**
 * File contains declaration of Particle structure.
 * @file	Particle.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-12
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Structure represents particle system basic element properties like position or color.
		 */
		struct Particle
		{
			AyumiMath::Vector3D position;
			AyumiMath::Vector3D rotation;
			AyumiMath::Vector3D velocity;
			AyumiMath::Vector3D acceleration;
			AyumiMath::Vector4D color;
			float lifeTime;
			float size;
		};
	}
}
#endif
