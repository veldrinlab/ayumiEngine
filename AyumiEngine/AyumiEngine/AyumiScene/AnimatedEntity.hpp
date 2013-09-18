/**
 * File contains declaration of AnimatedEntity class.
 * @file	AnimatedEntityEntity.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-24
 */

#ifndef ANIMATEDENTITY_HPP
#define ANIMATEDENTITY_HPP

#include "SceneEntity.hpp"
#include "KeyFrameAnimation.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class represents base element of engine scene - AnimatedEntity. It extends SceneEntity class. AnimatedEntity
		 * use md2 file formats for creating key frame animation.
		 */
		class AnimatedEntity : public SceneEntity
		{
		public:
			AnimationState animationState;

			AnimatedEntity(const std::string& entityName, const std::string& meshName, const std::string& materialName);
			~AnimatedEntity();

			void initializeAnimatedEntity();
			void updateAnimation(const float elapsedTime);
			void setAnimation(AnimationType type);
			void setGeometryData(AyumiResource::Mesh* geometryMesh);
			void configureGeometryAttributes();
		};
	}
}
#endif
