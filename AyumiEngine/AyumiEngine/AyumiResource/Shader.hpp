/**
 * File contains declaration of Shader class.
 * @file    Shader.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-07-12
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <fstream>

#include "Resource.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represents one of basic Engine resource - Shader. Shaders are simple programs in GLSL
		 * language which is used to communicate with GPU. There are three types of shaders: vertex,
		 * geometry and fragment. There are used to render and rasterize geoemtry, create all kind of
		 * spiecial effects, post-processing, lights, material, geoemtry etc. 
		 */
		class Shader : public Resource
		{
		private:
			unsigned int shaderProgram;
			unsigned int shaderVertex;
			unsigned int shaderGeometry;
			unsigned int shaderFragment;
			const char* vertexPath;
			const char* fragmentPath;
			const char* geometryPath;

		public:
			Shader();
			Shader(const char* name);
			~Shader();

			void bindShader();
			void unbindShader();
			void createShaderProgram();
			void createVertexShader();
			void createGeometryShader();
			void createFragmentShader();
			void setUniformf(const std::string& name, const float value);
			void setUniformi(const std::string& name, const int value);
			void setUniform2f(const std::string& name, const float value, const float value2);
			void setUniform3fv(const std::string& name, const float* valueArray);
			void setUniform4fv(const std::string&name, const float* valueArray);
			void setUniformTexture(const std::string& name, const int unit);
			void setUniformMatrix3fv(const std::string& name,const float* valueArray);
			void setUniformMatrix4fv(const std::string& name,const float* valueArray);

			unsigned int getShaderProgram() const;
			unsigned int getShaderVertex() const;
			unsigned int getShaderGeometry() const;
			unsigned int getShaderFragment() const;
			void setVertexPath(const char* path);
			void setFragmentPath(const char* path);
			void setGeometryPath(const char* path);
		};
	}
}
#endif
