/**
 * File contains declaration of Shader class.
 * @file    Shader.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL\glew.h>
#include <fstream>

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		class Shader
		{
		private:
			unsigned int shaderProgram;
			unsigned int shaderVertex;
			unsigned int shaderFragment;
	
			char* loadShaderSource(const char* shaderFileName);

		public:
			Shader();
			Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
			~Shader();

			void initializeShader(const char* vertexShaderFile, const char* fragmentShaderFile);
			void bindShader(); //Activate
			void unbindShader(); //deactivate
			unsigned int getShaderProgram() const;

			void setUniformf(const std::string& name, const float value);
			void setUniformi(const std::string& name, const int value);
			void setUniformTexture(const std::string& name, const int unit);
			void setUniformMatrix3fv(const std::string& name,const float* valueArray);
			void setUniformMatrix4fv(const std::string& name,const float* valueArray);
		};
	}
}
#endif
