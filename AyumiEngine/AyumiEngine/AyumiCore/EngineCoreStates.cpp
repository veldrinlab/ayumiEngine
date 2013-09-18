/**
 * File contains definition of EngineCoreStates class.
 * @file    EngineCoreStates.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#include "EngineCoreStates.hpp"

namespace AyumiEngine
{
	namespace AyumiCore
	{
		/**
		 * Method is used to set Depth state to on state - turn on Engine depth testing.
		 */
		void Depth::on()
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_TRUE);
		}

		/**
		 * Method is used to set Depth state to off state - turn off Engine depth testing.
		 */
		void Depth::off()
		{
			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
		}

		/**
		 * Method is used to set Blend state to on state - turn on Engine blending.
		 */
		void Blend::on()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		/**
		 * Method is used to set Blend state to on state - turn off Engine blending.
		 */
		void Blend::off()
		{
			glDisable(GL_BLEND);
		}

		/**
		 * Method is used to set Wireframe state to on state - turn on Engine wireframe rendering.
		 */
		void Wireframe::on()
		{
			glPolygonMode(GL_FRONT,GL_LINE);
			glPolygonMode(GL_BACK,GL_LINE);
		}

		/**
		 * Method is used to set Wireframe state to off state - turn off Engine wireframe rendering.
		 */
		void Wireframe::off()
		{
			glPolygonMode(GL_FRONT,GL_FILL);
			glPolygonMode(GL_BACK,GL_FILL);
		}

		/**
		 * Method is used to set BackCulling state to on state - turn on Engine back face culling.
		 */
		void BackCulling::on()
		{
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}

		/**
		 * Method is used to set BackCulling state to off state - turn off Engine back face
		 * culling.
		 */
		void BackCulling::off()
		{
			glDisable(GL_CULL_FACE);
		}
	}
}
