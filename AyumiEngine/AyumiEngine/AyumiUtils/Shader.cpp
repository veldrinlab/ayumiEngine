/**
 * File contains definition of Shader class.
 * @file    Shader.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-10
 */

#include "Shader.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Default constructor, create empty object ready to initialize.
		 */
		Shader::Shader()
		{

		}

		/** 
		 * Constructor with initialize parameters.
		 * @param	vertexShaderFile is source code of Vertex Shader.
		 * @param	fragmentShaderFile is source code of Fragment Shader.
		 */
		Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
		{
			initializeShader(vertexShaderFile,fragmentShaderFile);
		}

		/**
		 * Default destructor. Detach and delete shader program.
		 */
		Shader::~Shader()
		{
			glDetachShader(shaderProgram, shaderFragment);
			glDetachShader(shaderProgram, shaderVertex);
			glDeleteShader(shaderFragment);
			glDeleteShader(shaderVertex);
			glDeleteProgram(shaderProgram);
		}

		/**
		 * Method is used to load Shader source code from file.
		 * @param	shaderFileName is path to shader program source code.
		 * @return	loaded shader source code string.
		 */
		char* Shader::loadShaderSource(const char* shaderFileName)
		{
			//loggery
			char* shaderSource = NULL;
    
			if (shaderFileName != NULL)
			{
				FILE *file = fopen(shaderFileName, "rt");
        
				if (file != NULL)
				{
					fseek(file, 0, SEEK_END);
					int count = ftell(file);
					rewind(file);
            
					if (count > 0)
					{
						// use new
						shaderSource = (char*)malloc(sizeof(char) * (count + 1));
						count = fread(shaderSource, sizeof(char), count, file);
						shaderSource[count] = '\0';
					}
					fclose(file);
				}
			}
			return shaderSource;
		}

		/**
		 * Method is used to initialize Shader object. Create Vertex and Fragment shaders, validate it, compile
		 * and create shader program.
		 * @param	vertexShaderFile is source code of Vertex Shader.
		 * @param	fragmentShaderFile is source code of Fragment Shader.
		 */	
		void Shader::initializeShader(const char* vertexShaderFile, const char* fragmentShaderFile)
		{
			shaderVertex = glCreateShader(GL_VERTEX_SHADER);
			shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);

			const char* vertexShaderSource = loadShaderSource(vertexShaderFile);
			const char* fragmentShaderSource = loadShaderSource(fragmentShaderFile);

			if(vertexShaderSource == NULL || fragmentShaderSource == NULL)
			{
				// logger
				printf("Shader loading error detected!\n");
				exit(0);
			}
			
			glShaderSource(shaderVertex,1,&vertexShaderSource,0);
			glShaderSource(shaderFragment,1,&fragmentShaderSource,0);
			
			delete vertexShaderSource;
			delete fragmentShaderSource;

			glCompileShader(shaderVertex);
			glCompileShader(shaderFragment);

			shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram,shaderVertex);
			glAttachShader(shaderProgram,shaderFragment);
			glLinkProgram(shaderProgram);

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
		 * Accessor to shader program.
		 * @return	shader program id.
		 */
		unsigned int Shader::getShaderProgram() const
		{
			return shaderProgram;
		}

		void Shader::setUniformf(const std::string& name, const float value)
		{
			glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
		}

		void Shader::setUniformi(const std::string& name, const int value)
		{
			glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
		}

		void Shader::setUniformTexture(const std::string& name, const int unit)
		{
			glUniform1i(glGetUniformLocationARB(shaderProgram, name.c_str()), unit);
		}

		void Shader::setUniformMatrix3fv(const std::string& name,const float* valueArray)
		{
			glUniformMatrix3fv(glGetUniformLocationARB(shaderProgram,name.c_str()),1,GL_FALSE,valueArray);
		}

		void Shader::setUniformMatrix4fv(const std::string& name, const float* valueArray)
		{
			glUniformMatrix4fv(glGetUniformLocationARB(shaderProgram,name.c_str()),1,GL_FALSE,valueArray);
		}

	}
}
