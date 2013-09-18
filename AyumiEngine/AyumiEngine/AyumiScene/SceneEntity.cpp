/**
 * File contains definition of SceneEntity class.
 * @file	SceneEntity.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-10-24
 */


#include "SceneEntity.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	entityName is scene entity name id.
		 * @param	meshName is scene entity mesh name id.
		 * @param	materialName is scene entity material name id.
		 */
		 SceneEntity::SceneEntity(const string& entityName, const string& meshName, const string& materialName)
		{
			this->entityName = entityName;
			this->geometryName = meshName;
			this->materialName = materialName;
			entityGeometry.geometryBox = nullptr;
			entityGeometry.geometrySphere = nullptr;
			entityGeometry.geometryVao = nullptr;
			entityGeometry.geomteryVbo = nullptr;
			entityLogic.updateScript = nullptr;
			entityLogic.virtualMachine = nullptr;
		}

		/**
		 * Class destructor, free allocated memory. Delete entity geoemtry bufferes and script modules if used.
		 */
		SceneEntity::~SceneEntity()
		{
			delete entityGeometry.geometryVao;
			if(entityGeometry.geomteryVbo != nullptr)
				delete entityGeometry.geomteryVbo;
			delete entityGeometry.geometryBox;
			delete entityGeometry.geometrySphere;

			if(entityLogic.updateScript != nullptr)
				delete entityLogic.updateScript;
			if(entityLogic.virtualMachine != nullptr)
				lua_close(entityLogic.virtualMachine);
		}

		/**
		 * Method is used to initialize scene entity data to default.
		 */
		void SceneEntity::initializeSceneEntity()
		{
			entityState.isVisible = true;
			entityState.isDead = false;
			entityState.position.set(0.0f,0.0f,0.0f);
			entityState.rotation.set(0.0f,0.0f,0.0f);
			entityState.scale.set(1.0f,1.0f,1.0f);
			entityState.orientation.set(0.0f,0.0f,0.0f,1.0f);
			entityLogic.updateType = NONE;
			entityPhysics.acceleration.set(0.0f,0.0f,0.0f);
			entityPhysics.velocity.set(0.0f,0.0f,0.0f);
			entityPhysics.isKinematic = false;
		}

		/**
		 * Method is used to set geometry data of ScenEntity. Create EntityGeometry struct of VAO/VBO and Bounding
		 * Volumes based on poniter to entity geometry mesh object.
		 * @param	geometryMesh is pointer to scene eneity geometry mesh object.
		 */
		void SceneEntity::setGeometryData(Mesh* geometryMesh)
		{
			entityGeometry.geometryMesh = geometryMesh;
			entityGeometry.geometryVao = new VertexArrayObject();
			entityGeometry.geomteryVbo = new VertexBufferObject(*entityGeometry.geometryMesh);
			entityGeometry.geometryBox = new BoundingBox(*geometryMesh);
			entityGeometry.geometrySphere = new BoundingSphere(*geometryMesh,entityState.position);
		}

		/**
		 * Method is used to configure scene entity geometry buffers attributes. Create SceneEntity VAO and initialize VBO.
		 */
		void SceneEntity::configureGeometryAttributes()
		{
			entityGeometry.geometryVao->bindVertexArray();
			entityGeometry.geomteryVbo->vertexPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"vertex");
			entityGeometry.geomteryVbo->normalPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"normal");
			entityGeometry.geomteryVbo->texCoordPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"texCoord");
			entityGeometry.geomteryVbo->tangentPosition = glGetAttribLocation(entityMaterial.entityShader->getShaderProgram(),"tangent");
			glVertexAttribPointer(entityGeometry.geomteryVbo->vertexPosition,3,GL_FLOAT,GL_FALSE,sizeof(Vertex<>),reinterpret_cast<const GLubyte *>(0) + 0);
			glVertexAttribPointer(entityGeometry.geomteryVbo->normalPosition,3,GL_FLOAT,GL_FALSE,sizeof(Vertex<>),reinterpret_cast<const GLubyte *>(0) + sizeof(float)*3);
			glVertexAttribPointer(entityGeometry.geomteryVbo->texCoordPosition,2,GL_FLOAT,GL_FALSE,sizeof(Vertex<>),reinterpret_cast<const GLubyte *>(0) + sizeof(float)*6);
			glVertexAttribPointer(entityGeometry.geomteryVbo->tangentPosition,4,GL_FLOAT,GL_FALSE,sizeof(Vertex<>),reinterpret_cast<const GLubyte *>(0) + sizeof(float)*8);
			entityGeometry.geomteryVbo->bindBufferObject();
		}

		/**
		 * Method is used to attach scene entity render buffers and shaders.
		 */
		void SceneEntity::attachMaterial()
		{
			entityMaterial.entityShader->bindShader();
			entityGeometry.geometryVao->bindVertexArray();
		}

		/**
		 * Method is used to detach scene entity render buffers and shaders.
		 */
		void SceneEntity::detachMaterial()
		{
			entityMaterial.entityShader->unbindShader();
			entityGeometry.geometryVao->unbindVertexArray();
		}

		/**
		 * Method is used to set entity position.
		 * @param	position is entity new position vector.
		 */
		void SceneEntity::setEntityPosition(const float x, const float y, const float z)
		{
			entityState.position = Vector3D(x,y,z);
		}

		/**
		 * Method is used to set entity orientation. Vector with euler angles which is method param is used
		 * to calculate entity orientation quaternion.
		 * @param	orientation is entity rotation euler angles vector.
		 */
		void SceneEntity::setEntityOrientation(const float x, const float y, const float z)
		{
			entityState.rotation = Vector3D(x,y,z);
			Quaternion rotation(Vector3D(1.0f,0.0f,0.0f),x);
			rotation *= Quaternion(Vector3D(0.0f,1.0f,0.0f),y);
			rotation *= Quaternion(Vector3D(0.0f,0.0f,1.0f),z);
			entityState.orientation = rotation;
		}

		/**
		 * Method is used to set entity scale.
		 * @param	scale is entity new scale vector.
		 */
		void SceneEntity::setEntityScale(const float x, const float y, const float z)
		{
			entityState.scale = Vector3D(x,y,z);
		}

		/**
		 * Method is used to set scene entity update type to extending. It is one of three updating possibilities.
		 */
		void SceneEntity::setExtendingUpdating()
		{
			entityLogic.updateType = EXTENDING;
		}

		/**
		 * Method is used to set scene entity update type to function. It is one of three updating possibilities.
		 * @param	udpateFunction is entity update functor object.
		 */
		void SceneEntity::setFunctionUpdating(UpdateFunction updateFunction)
		{
			entityLogic.updateType = FUNCTION;
			entityLogic.updateFunction = updateFunction;
		}

		/**
		 * Method is used to set scene entity update type to script. It is one of three updating possibilities.
		 * @param	scriptName is update script file name.
		 */
		void SceneEntity::setScriptUpdatating(const char* scriptName)
		{
			entityLogic.updateType = SCRIPT;
			entityLogic.virtualMachine = lua_open();
			luabind::open(entityLogic.virtualMachine);
			entityLogic.updateScript = new AyumiScript(scriptName);
			entityLogic.updateScript->setVirtualMachine(entityLogic.virtualMachine);
			prepareUpdateScript();
		}

		/**
		 * Private method which is used to prepare entity update script. By using Luabind engine register SceneEntity class
		 * to Lua namespace and bind global pointer to engine entity object.
		 */
		void SceneEntity::prepareUpdateScript()
		{
			luabind::module(entityLogic.virtualMachine)
			[
				luabind::class_<SceneEntity>("ScenEntity")
				.def("setEntityPosition",&SceneEntity::setEntityPosition)
				.def("setEntityOrientation",&SceneEntity::setEntityOrientation)
				.def("setEntityScale",&SceneEntity::setEntityScale)
				.def("getEntityPosition",&SceneEntity::getEntityPosition)
				.def("getEntityOrientation",&SceneEntity::getEntityOrientation)
				.def("getEntityScale",&SceneEntity::getEntityScale)
			];

			luabind::globals(entityLogic.updateScript->getVirtualMachine())["Entity"] = this;
		}

		/**
		 * Private method which is used to get current entity position in entity update Lua script.
		 * @return	luabind object which is table of entity position data.
		 */
		luabind::object SceneEntity::getEntityPosition() const
		{
			luabind::object data = luabind::newtable(entityLogic.virtualMachine);
			for(int i = 0; i < 3; ++i)
				data[i+1] = entityState.position[i];
            return data;
		}

		/**
		 * Private method which is used to get current entity orientation in entity update Lua script.
		 * @return	luabind object which is table of entity orientation data.
		 */
		luabind::object SceneEntity::getEntityOrientation() const
		{
			luabind::object data = luabind::newtable(entityLogic.virtualMachine);
			for(int i = 0; i < 3; ++i)
				data[i+1] = entityState.rotation[i];
			 return data;
		}

		/**
		 * Private method which is used to get current entity scale in entity update Lua script.
		 * @return	luabind object which is table of entity scale data.
		 */
		luabind::object SceneEntity::getEntityScale() const
		{
			luabind::object data = luabind::newtable(entityLogic.virtualMachine);
			for(int i = 0; i < 3; ++i)
				data[i+1] = entityState.scale[i];
            return data;
		}
	}
}
