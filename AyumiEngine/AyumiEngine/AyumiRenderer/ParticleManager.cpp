/**
 * File contains definition of ParticleManager class.
 * @file    ParticleManager.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-11-11
 */

#include "ParticleManager.hpp"

using namespace std;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiUtils;

namespace AyumiEngine
{
	namespace AyumiRenderer
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	engineResource is pointer to engine resource manager object.
		 */
		ParticleManager::ParticleManager(ResourceManager* engineResource)
		{
			this->engineResource = engineResource;
			particleEmiterScript = new AyumiScript("null");
			particleEmiter = nullptr;
		}

		/**
		 * Class destructor, free allocated memeory. Delete particle emiters data and load script object.
		 */
		ParticleManager::~ParticleManager()
		{
			delete particleEmiterScript;

			for(ParticleEmiters::const_iterator it = emiters.begin(); it != emiters.end(); ++it)
			{
				delete [] (*it)->particles;
				delete [] (*it)->points;
				delete (*it)->particleVao;
				glDeleteBuffers(1,&(*it)->particleVbo);
			}
			emiters.clear();
		}

		/**
		 * Method is used to initialize particle manager. Prepare particle emiters loading script
		 * and configure OpenGL state machine for enabling creating point size in geomety shader.
		 */
		void ParticleManager::initializeParticleManager()
		{
			prepareParticleScript();
			glEnable(GL_PROGRAM_POINT_SIZE);
		}

		/**
		 * Method is used to update particle emiters. Call update function for each emiter.
		 * @param	elapsedTime is difference betweenn two frame in seconds.
		 */
		void ParticleManager::updateEmiters(const float elapsedTime)
		{
			for(ParticleEmiters::const_iterator it = emiters.begin(); it != emiters.end(); ++it)
				(*it)->updateFunction((*it),elapsedTime);
		}

		/**
		 * Method is ued to add new particle emiter to scene. Create new emiter and initialize it by Lua script.
		 * @param	name is particle emiter name.
		 * @param	path is emiter script file path.
		 * @param	initializeFunction is emiter initialize functor object
		 * @param	updateFunction is emiter update functor object.
		 * @param	origin is particle position vector.
		 */
		void ParticleManager::addParticleEmiter(const string& name, const string& path, boost::function<void (ParticleEmiter*)> initializeFunction, boost::function<void (ParticleEmiter*,float)> updateFunction, const Vector3D& origin)
		{
			particleEmiter = new ParticleEmiter();
			particleEmiterScript->setScriptFile(path.c_str());
			particleEmiterScript->executeScript();

			particleEmiter->name = name;
			particleEmiter->origin = origin;
			particleEmiter->updateFunction = updateFunction;
			particleEmiter->initializeFunction = initializeFunction;
			particleEmiter->points = new Vertex<>[particleEmiter->particleAmount];
			for(int i = 0; i < particleEmiter->particleAmount; ++i)
			{
				particleEmiter->points[i].x = 0.0f;
				particleEmiter->points[i].y = 0.0f;
				particleEmiter->points[i].z = 0.0f;
			}

			particleEmiter->particleVao = new VertexArrayObject();
			glGenBuffers(1,&particleEmiter->particleVbo);
			glBindBuffer(GL_ARRAY_BUFFER,particleEmiter->particleVbo);
			glBufferData(GL_ARRAY_BUFFER,particleEmiter->particleAmount*12*sizeof(float),particleEmiter->points,GL_DYNAMIC_DRAW);
			
			GLuint positionLoc = glGetAttribLocation(particleEmiter->shader->getShaderProgram(), "inPosition");
			glVertexAttribPointer(positionLoc,3,GL_FLOAT,GL_FALSE,sizeof(Vertex<>),reinterpret_cast<const GLubyte *>(0) + 0);
			glEnableVertexAttribArray(positionLoc);
			glBindVertexArray(0);

			particleEmiter->particles = new Particle[particleEmiter->particleAmount];
			for(int i = 0; i < particleEmiter->particleAmount; i++)
			{
				particleEmiter->particles[i].position = origin;
				particleEmiter->particles[i].velocity = storageParticle.velocity;
				particleEmiter->particles[i].rotation = storageParticle.rotation;
				particleEmiter->particles[i].acceleration = storageParticle.acceleration;
				particleEmiter->particles[i].color = storageParticle.color;
				particleEmiter->particles[i].lifeTime = storageParticle.lifeTime;
				particleEmiter->particles[i].size = storageParticle.size;
			}
			
			particleEmiter->initializeFunction(particleEmiter);
			emiters.push_back(particleEmiter);
		}

		/**
		 * Method is used to delete particle emiter from scene.
		 * @param	name is emiter name id.
		 */
		void ParticleManager::deleteParticleEmiter(const string& name)
		{
			ParticleEmiters::const_iterator it = emiters.begin();

			for(; it != emiters.end(); ++it)
				if((*it)->name == name)
					break;

			if(it != emiters.end())
			{
				delete [] (*it)->particles;
				delete [] (*it)->points;
				delete (*it)->particleVao;
				glDeleteBuffers(1,&(*it)->particleVbo);
				emiters.erase(it);
			}
		}

		/**
		 * Accessor to private particle emiters member.
		 * @return	pointer to particle emiters collection.
		 */
		ParticleEmiters* ParticleManager::getEmiters()
		{
			return &emiters;
		}
		
		/**
		 * Private method which is used to prepare particle emiters load script. By using Luabind engine register ParticleManager
		 * class to Lua namespace and bind global pointer to engine particle manager object and current emiter definition.
		 */
		void ParticleManager::prepareParticleScript()
		{
			luabind::module(particleEmiterScript->getVirtualMachine())
			[
				luabind::class_<ParticleManager>("ParticleManager")
				.def("setVelocity",&ParticleManager::setVelocity)
				.def("setRotation",&ParticleManager::setRotation)
				.def("setAcceleration",&ParticleManager::setAcceleration)
				.def("setColor",&ParticleManager::setColor)
				.def("setSize",&ParticleManager::setSize)
				.def("setLifeTime",&ParticleManager::setLifeTime)
				.def("setParticleAmount",&ParticleManager::setParticleAmount)
				.def("setEmiterShader",&ParticleManager::setEmiterShader)
				.def("setEmiterTexture",&ParticleManager::setEmiterTexture)
			];

			luabind::globals(particleEmiterScript->getVirtualMachine())["Particles"] = this;;
		}

		/**
		 * Private method which is used to set particle emiter partilce velocity. It can be called from Lua script.
		 * @param	velocity is particle velocity vector.
		 */
		void ParticleManager::setVelocity(const luabind::object& velocity)
		{
			storageParticle.velocity[0] = luabind::object_cast<float>(velocity[1]);
			storageParticle.velocity[1] = luabind::object_cast<float>(velocity[2]);
			storageParticle.velocity[2] = luabind::object_cast<float>(velocity[3]);
		}

		/**
		 * Private method which is used to set particle emiter particle rotation. It can be called from Lua script.
		 * @param	rotation is particle rotation vector.
		 */
		void ParticleManager::setRotation(const luabind::object& rotation)
		{
			storageParticle.rotation[0] = luabind::object_cast<float>(rotation[1]);
			storageParticle.rotation[1] = luabind::object_cast<float>(rotation[2]);
			storageParticle.rotation[2] = luabind::object_cast<float>(rotation[3]);
		}

		/**
		 * Private method which is used to set particle emiter particle acceleration. It can be called from Lua script.
		 * @param	acceleration is particle acceleration vector.
		 */
		void ParticleManager::setAcceleration(const luabind::object& acceleration)
		{
			storageParticle.acceleration[0] = luabind::object_cast<float>(acceleration[1]);
			storageParticle.acceleration[1] = luabind::object_cast<float>(acceleration[2]);
			storageParticle.acceleration[2] = luabind::object_cast<float>(acceleration[3]);
		}

		/**
		 * Private method which is used to set particle emiter particle color. It can be called from Lua script.
		 * @param	color is particle color vector.
		 */
		void ParticleManager::setColor(const luabind::object& color)
		{
			storageParticle.color[0] = luabind::object_cast<float>(color[1]);
			storageParticle.color[1] = luabind::object_cast<float>(color[2]);
			storageParticle.color[2] = luabind::object_cast<float>(color[3]);
			storageParticle.color[3] = luabind::object_cast<float>(color[4]);
		}

		/**
		 * Private method which is used to set particle emiter particle size. It can be called from Lua script.
		 * @param	size is particle point size.
		 */
		void ParticleManager::setSize(const float size)
		{
			storageParticle.size = size;
		}

		/**
		 * Private method which is used to set particle emiter particle life time. It can be called from Lua script.
		 * @param	lifetim is particle life time.
		 */
		void ParticleManager::setLifeTime(const float lifeTime)
		{
			storageParticle.lifeTime = lifeTime;
		}
			
		/**
		 * Private method which is used to set particle emiter particle maximum amount. It can be called from Lua script.
		 * @param	amount is emiter particle amount.
		 */
		void ParticleManager::setParticleAmount(const int amount)
		{
			particleEmiter->particleAmount = amount;
		}

		/**
		 * Private method which is used to set particle emiter shader. It can be called from Lua script.
		 * @param	name is shader name id.
		 */
		void ParticleManager::setEmiterShader(const string& name)
		{
			particleEmiter->shader = engineResource->getShaderResource(name).get();
		}

		/**
		 * Private method which is used to set particle emiter texture. It can be called from Lua script.
		 * @param	name is texture name id.
		 */
		void ParticleManager::setEmiterTexture(const string& name)
		{
			particleEmiter->texture = engineResource->getTextureResource(name).get();
		}
	}
}
