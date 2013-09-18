/**
 * File contains declaration of VolumeStorage class.
 * @file	VolumeStorage.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#ifndef VOLUMESTORAGE_HPP
#define VOLUMESTORAGE_HPP

#include <GL/glew.h>
#include <string>

#include "DefinedGeometry.hpp"
#include "DefinedShader.hpp"
#include "../Logger.hpp"
#include "../AyumiResource/Shader.hpp"

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Enumeration represents all possible bounding volumes rendering modes.
		 */
		enum RenderMode
		{
			LINES,
			TRIANGLES
		};

		/**
		 * Class represents one Renderer additional utitily object - VolumeStorage. It is used to create,
		 * store and configure available Bounding Volumes for rendering. Bounding Boxes and Spehres are rendered
		 * using defined shader. They can be rendered in two different modes: filled triangles or wireframe lines.
		 */
		class VolumeStorage
		{
		private:
			RenderMode renderMode;
			AyumiResource::Shader* shader;
			GLuint linesVao;
			GLuint linesBuffer;
			GLuint trianglesVao;
			GLuint trianglesBuffer;
			GLuint trianglesIndicesBuffer;
			GLuint linesVertexPosition;
			GLuint trianglesVertexPosition;
		
			void initializeVolumeShader();
		public:
			VolumeStorage();
			~VolumeStorage();

			void initializeVolumeStorage();
			void attachVolumeBuffers();
			void detachVolumeBuffers();

			AyumiResource::Shader* getShader() const;
			RenderMode getRenderMode() const;
		
			void setRenderMode(RenderMode mode);
		};
	}
}
#endif
