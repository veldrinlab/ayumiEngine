/**
 * File contains definition of VolumeStorage class.
 * @file	VolumeStorage.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-09
 */

#include "VolumeStorage.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class default constructor. Set defulat values of object memebrs.
		 */
		VolumeStorage::VolumeStorage()
		{
			renderMode = LINES;
			linesVao = 0;
			linesBuffer = 0;
			linesVertexPosition = 0;
			trianglesVao = 0;
			trianglesBuffer = 0;
			trianglesIndicesBuffer = 0;
			trianglesVertexPosition = 0;
			shader = new Shader("BoundingVolume");
		}

		/**
		 * Class destructor, free allocated memeory. Delete created shader and created buffers.
		 */
		VolumeStorage::~VolumeStorage()
		{
			delete shader;
			glDeleteVertexArrays(1,&trianglesVao);
			glDeleteVertexArrays(1,&linesVao);
			glDeleteBuffers(1,&linesBuffer);
			glDeleteBuffers(1,&trianglesBuffer);
			glDeleteBuffers(1,&trianglesIndicesBuffer);
		}

		/**
		 * Private method which is used to initialize bounding volumes shader.
		 */
		void VolumeStorage::initializeVolumeShader()
		{
			shader->setVertexPath("null");
			shader->setFragmentPath("null");
			shader->createVertexShader();
			shader->createFragmentShader();

			const char* vertexShaderSource = boxVertexShader;
			const char* fragmentShaderSource = boxFragmentShader;

			if(vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
				Logger::getInstance()->saveLog(Log<string>("Volume shader loading error detected"));
	
			glShaderSource(shader->getShaderVertex(),1,&vertexShaderSource,0);
			glShaderSource(shader->getShaderFragment(),1,&fragmentShaderSource,0);
			
			glCompileShader(shader->getShaderVertex());
			glCompileShader(shader->getShaderFragment());

			shader->createShaderProgram();
			glAttachShader(shader->getShaderProgram(),shader->getShaderVertex());
			glAttachShader(shader->getShaderProgram(),shader->getShaderFragment());
			glLinkProgram(shader->getShaderProgram());
		}

		/**
		 * Method is used to initialize bounding volume storgae, generate Vertex Array Object and Vertex
		 * Buffer Objects of volumes geometry.
		 */
		void VolumeStorage::initializeVolumeStorage()
		{
			initializeVolumeShader();

			glGenVertexArrays(1,&linesVao);
			glBindVertexArray(linesVao);

			glGenBuffers(1,&linesBuffer);
			glBindBuffer(GL_ARRAY_BUFFER,linesBuffer);
			glBufferData(GL_ARRAY_BUFFER,sizeof(octNode),octNode,GL_STATIC_DRAW);
			
			linesVertexPosition = glGetAttribLocation(shader->getShaderProgram(),"vertex");
			glVertexAttribPointer(linesVertexPosition,3,GL_FLOAT,GL_FALSE,0,reinterpret_cast<const GLubyte *>(0) + 0);
			glEnableVertexAttribArray(linesVertexPosition);			
			glBindVertexArray(0);

			glGenVertexArrays(1,&trianglesVao);
			glBindVertexArray(trianglesVao);

			glGenBuffers(1,&trianglesBuffer);
			glBindBuffer(GL_ARRAY_BUFFER,trianglesBuffer);
			glBufferData(GL_ARRAY_BUFFER,sizeof(boxVertices),boxVertices,GL_STATIC_DRAW);

			glGenBuffers(1,&trianglesIndicesBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglesIndicesBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(boxIndices),boxIndices,GL_STATIC_DRAW);
			
			trianglesVertexPosition = glGetAttribLocation(shader->getShaderProgram(),"vertex");
			glVertexAttribPointer(trianglesVertexPosition,3,GL_FLOAT,GL_FALSE,0,reinterpret_cast<const GLubyte *>(0) + 0);
			glEnableVertexAttribArray(trianglesVertexPosition);			
			glBindVertexArray(0);
		}

		/**
		 * Method is used to attach volume buffer and shader. There are two posibilities: lines or triangles
		 * volumes which depeneds on choosen render mode.
		 */
		void VolumeStorage::attachVolumeBuffers()
		{
			shader->bindShader();
			if(renderMode == LINES)
				glBindVertexArray(linesVao);
			else
				glBindVertexArray(trianglesVao);
		}

		/**
		 * Method is used to detach volume buffer and shader.
		 */
		void VolumeStorage::detachVolumeBuffers()
		{
			shader->unbindShader();
			glBindVertexArray(0);
		}

		/**
		 * Accessor to private volume shader member.
		 * @return	pointer to volume shader.
		 */
		Shader* VolumeStorage::getShader() const
		{
			return shader;
		}

		/**
		 * Accessor to private volumes render mode member.
		 * @return	volumes render mode.
		 */
		RenderMode VolumeStorage::getRenderMode() const
		{
			return renderMode;
		}

		/**
		 * Setter for private volumes render mode member.
		 * @param	mode is new volumes render mode.
		 */
		void VolumeStorage::setRenderMode(RenderMode mode)
		{
			this->renderMode = mode;
		}
	}
}
