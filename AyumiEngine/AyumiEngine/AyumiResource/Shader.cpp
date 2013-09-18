/**
 * File contains definition of Shader class.
 * @file    Shader.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#include "Shader.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Set object default values. 
		 */
		Shader::Shader()
		{
			shaderProgram = 0;
			shaderVertex = 0;
			shaderGeometry = 0;
			shaderFragment = 0;
			vertexPath = nullptr;
			fragmentPath = nullptr;
			geometryPath = nullptr;
			resourceName = nullptr;
			resourceType = SHADER;
		}

		/** 
		 * Constructor with initialize parameters.
		 * @param	name is shader name.
		 */
		Shader::Shader(const char* name)
		{
			resourceName = name;
			resourceType = SHADER;	
			shaderProgram = 0;
			shaderVertex = 0;
			shaderGeometry = 0;
			shaderFragment = 0;
			vertexPath = nullptr;
			fragmentPath = nullptr;
			geometryPath = nullptr;
		}

		/**
		 * Class destructor, free allocated memory. Detach and delete shader program.
		 */
		Shader::~Shader()
		{
			if(shaderFragment != 0)
			{
				glDetachShader(shaderProgram, shaderFragment);
				glDeleteShader(shaderFragment);
			}
			
			if(shaderGeometry != 0)
			{
				glDetachShader(shaderProgram, shaderGeometry);
				glDeleteShader(shaderGeometry);
			}

			if(shaderVertex != 0)
			{
				glDetachShader(shaderProgram, shaderVertex);
				glDeleteShader(shaderVertex);
			}
			glDeleteProgram(shaderProgram);
		}
	
		/**
		 * Method is used to bind shader program.
		 */
		void Shader::bindShader()
		{
			glUseProgram(shaderProgram);
		}

		/**
		 * Method is used to unbind shader program.
		 */
		void Shader::unbindShader()
		{
			glUseProgram(0);
		}

		/**
		 * Method is used to create shader program.
		 */
		void Shader::createShaderProgram()
		{
			shaderProgram = glCreateProgram();
		}

		/**
		 * Method is used to create vertex shader program.
		 */
		void Shader::createVertexShader()
		{
			shaderVertex = glCreateShader(GL_VERTEX_SHADER);
		}

		/**
		 * Method is used to create geometry shader program.
		 */
		void Shader::createGeometryShader()
		{
			shaderGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		}

		/**
		 * Method is used to create fragment shader program.
		 */
		void Shader::createFragmentShader()
		{
			shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
		}

		/**
		 * Method is used to set uniform float value to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	value is uniform value.
		 */
		void Shader::setUniformf(const string& name, const float value)
		{
			glUniform1f(glGetUniformLocation(shaderProgram,name.c_str()),value);
		}

		/**
		 * Method is used to set uniform int value to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	value is uniform value.
		 */
		void Shader::setUniformi(const string& name, const int value)
		{
			glUniform1i(glGetUniformLocation(shaderProgram,name.c_str()),value);
		}

		/**
		 * Method is used to set uniform float vec2 to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	value is uniform vec2 first value.
		 * @param	value is uniform vec2 second value.
		 */
		void Shader::setUniform2f(const string& name, const float value, const float value2)
		{
			glUniform2f(glGetUniformLocation(shaderProgram,name.c_str()),value,value2);
		}

		/**
		 * Method is used to set uniform float 3-element array to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	valueArray is pointer to uniform float array.
		 */
		void Shader::setUniform3fv(const string& name, const float* valueArray)
		{
			glUniform3fv(glGetUniformLocation(shaderProgram,name.c_str()),1,valueArray);
		}

		/**
		 * Method is used to set uniform float 4-element array to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	valueArray is pointer to uniform float array.
		 */
		void Shader::setUniform4fv(const string&name, const float* valueArray)
		{
			glUniform4fv(glGetUniformLocation(shaderProgram,name.c_str()),1,valueArray);
		}

		/**
		 * Method is used to set uniform texture unit to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	texture is uniform texture unit.
		 */
		void Shader::setUniformTexture(const string& name, const int unit)
		{
			glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), unit);
		}

		/**
		 * Method is used to set uniform float 3x3 matrix to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	valueArray is pointer to uniform float array.
		 */
		void Shader::setUniformMatrix3fv(const string& name,const float* valueArray)
		{
			glUniformMatrix3fv(glGetUniformLocation(shaderProgram,name.c_str()),1,GL_FALSE,valueArray);
		}

		/**
		 * Method is used to set uniform float 4x4 matrix to shader program.
		 * @param	name is uniform name which is used to shader program.
		 * @param	valueArray is pointer to uniform float array.
		 */
		void Shader::setUniformMatrix4fv(const string& name, const float* valueArray)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram,name.c_str()),1,GL_FALSE,valueArray);
		}

		/**
		 * Accessor to shader program private member.
		 * @return	shader program id.
		 */
		unsigned int Shader::getShaderProgram() const
		{
			return shaderProgram;
		}

		/**
		 * Accessor to shader vertex program private member.
		 * @return	vertex shader program.
		 */
		unsigned int Shader::getShaderVertex() const
		{
			return shaderVertex;
		}

		/**
		 * Accessor to shader geometry program private member.
		 * @return	geometry shader program.
		 */
		unsigned int Shader::getShaderGeometry() const
		{
			return shaderGeometry;
		}

		/**
		 * Accessor to shader fragmnet program private member.
		 * @return	fragment shader program.
		 */
		unsigned int Shader::getShaderFragment() const
		{
			return shaderFragment;
		}

		/**
		 * Setter of vertex program path private member.
		 * @param	path is new path to vertex program.
		 */
		void Shader::setVertexPath(const char* path)
		{
			vertexPath = path;
		}

		/**
		 * Setter of fragment program path private member.
		 * @param	path is new path to fragment program.
		 */
		void Shader::setFragmentPath(const char* path)
		{
			fragmentPath = path;
		}

		/**
		 * Setter of geometry program path private member.
		 * @param	geometry is new path to vertex program.
		 */
		void Shader::setGeometryPath(const char* path)
		{
			geometryPath = path;
		}
	}
}
