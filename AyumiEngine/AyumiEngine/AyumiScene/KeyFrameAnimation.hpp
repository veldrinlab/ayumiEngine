/**
 * File contains declaration of Key frame animation structures.
 * @file	KeyFrameAnimation.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-24
 */

#ifndef KEYFRAMEANIMATION_HPP
#define KEYGRAMEANIMATION_HPP

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Enumeration represents all available animation type for md2 model.
		 */
		enum AnimationType
		{
			STAND,
			RUN,
			ATTACK,
			PAIN_A,
			PAIN_B,
			PAIN_C,
			JUMP,
			FLIP,
			SALUTE,
			FALLBACK,
			WAVE,
			POINT,
			CROUCH_STAND,
			CROUCH_WALK,
			CROUCH_ATTACK,
			CROUCH_PAIN,
			CROUCH_DEATH, 
			DEATH_FALLBACK,
			DEATH_FALLFORWARD,
			DEATH_FALLBACKSLOW,
			BOOM,
			MAX_ANIMATIONS
		};

		/**
		 * Structure represents base data of key frame animation.
		 */
		struct Animation
		{
			int firstFrame;
			int lastFrame;
			int framePerSecond;
		};

		/**
		 * Structure represents data of key frame animation state.
		 */
		struct AnimationState
		{
			int startFrame;
			int endFrame;
			int framePerSecond;
			float currentTime;
			float oldTime;
			float interpolatonValue;
			AnimationType type;
			int currentFrame;
			int nextFrame;
		};

		/**
		 * Static array represents lists of md2 animation base data.
		 */
		static Animation animationList[21] =
		{
			{   1,  39,  9 },   // STAND
			{  40,  45, 10 },   // RUN
			{  46,  53, 10 },   // ATTACK
			{  54,  57,  7 },   // PAIN_A
			{  58,  61,  7 },   // PAIN_B
			{  62,  65,  7 },   // PAIN_C
			{  66,  71,  7 },   // JUMP
			{  72,  83,  7 },   // FLIP
			{  84,  94,  7 },   // SALUTE
			{  95, 111, 10 },   // FALLBACK
			{ 112, 122,  7 },   // WAVE
			{ 123, 134,  6 },   // POINT
			{ 135, 153, 10 },   // CROUCH_STAND
			{ 154, 159,  7 },   // CROUCH_WALK
			{ 160, 168, 10 },   // CROUCH_ATTACK
			{ 196, 172,  7 },   // CROUCH_PAIN
			{ 173, 177,  5 },   // CROUCH_DEATH
			{ 178, 183,  7 },   // DEATH_FALLBACK
			{ 184, 189,  7 },   // DEATH_FALLFORWARD
			{ 190, 197,  7 },   // DEATH_FALLBACKSLOW
			{ 198, 198,  5 },   // BOOM
		};
	}
}
#endif
