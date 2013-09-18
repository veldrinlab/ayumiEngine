#include "AyumiDemo.hpp"
#include "AyumiEngine/EngineInterface.hpp"

//
#include <iostream>

using namespace std;
using namespace boost;
using namespace AyumiEngine;
using namespace AyumiEngine::AyumiCore;
using namespace AyumiEngine::AyumiInput;
using namespace AyumiEngine::AyumiRenderer;
using namespace AyumiEngine::AyumiResource;
using namespace AyumiEngine::AyumiUtils;
using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiSound;
using namespace AyumiEngine::AyumiPhysics;

static bool isRunning;

AyumiEngine::AyumiScene::SceneEntity* sky;
AyumiEngine::AyumiScene::SceneEntity* terrain;

float timeAccumulator;
bool timeUpdate;

void exitSkyDemo()
{
	isRunning = false;
}

void controlDayTime() {
	timeUpdate = !timeUpdate;
}

void updateSunLight() {

	if(timeUpdate) {
		timeAccumulator += EngineInterface::getElapsedTime()/15;

		PointLight* light = EngineInterface::getPointLight(0);

		float radius = 10000.0f;
		float lightRadius = 12500.0f;
		light->position[0] = sin(CommonMath::PI*timeAccumulator)*radius;
		light->position[1] = cos(CommonMath::PI*timeAccumulator)*radius;

		light->radius = max(0.0f,7500.0f+cos(CommonMath::PI*timeAccumulator)*lightRadius);
	}
}

void updatePreetham(EntityMaterial* material, const float deltaTime) {
	if(timeUpdate) {
		material->vectors["lightDirection"][0] = sin(CommonMath::PI*timeAccumulator);
		material->vectors["lightDirection"][1] = cos(CommonMath::PI*timeAccumulator);

		// update Preetham Coefficients
		material->vectors["A"][0] = -0.01925f * material->floats["turbidity"] - 0.25922f;
		material->vectors["A"][1] = -0.01669f * material->floats["turbidity"] - 0.26078f;
		material->vectors["A"][2] = 0.17872f * material->floats["turbidity"] - 1.46303f;
		
		material->vectors["B"][0] = -0.06651f * material->floats["turbidity"] + 0.00081f;
		material->vectors["B"][1] = -0.09495f * material->floats["turbidity"] + 0.00921f;
		material->vectors["B"][2] = -0.35540f * material->floats["turbidity"] + 0.42749f;
		
		material->vectors["C"][0] = -0.00041f * material->floats["turbidity"] + 0.21247f;
		material->vectors["C"][1] = -0.00792f * material->floats["turbidity"] + 0.21023f;
		material->vectors["C"][2] = -0.02266f * material->floats["turbidity"] + 5.32505f;

		material->vectors["D"][0] = -0.06409f * material->floats["turbidity"] - 0.89887f;
		material->vectors["D"][1] = -0.04405f * material->floats["turbidity"] - 1.65369f;
		material->vectors["D"][2] = 0.12064f * material->floats["turbidity"] - 2.57705f;

		material->vectors["E"][0] = -0.00325f * material->floats["turbidity"] + 0.04517f;
		material->vectors["E"][1] = -0.01092f * material->floats["turbidity"] + 0.05291f;
		material->vectors["E"][2] = -0.06696f * material->floats["turbidity"] + 0.37027f;

		// update Zenith Color
		const float cosTheta = material->vectors["lightDirection"][1];
		float theta = acos(cosTheta);
		Vector4D theta2 = Vector4D(1, theta, theta*theta, theta*theta*theta);
		const float turbidity2 = material->floats["turbidity"] * material->floats["turbidity"];
		
		Vector4D cx1 = Vector4D(0.0f,0.00209f, -0.00375f, 0.00165f);
		Vector4D cx2 = Vector4D(0.00394f, -0.03202f, 0.06377f, -0.02903f);
		Vector4D cx3 = Vector4D(0.25886f, 0.06052f, -0.21196f, 0.11693f);
		Vector4D cy1 = Vector4D(0.0f, 0.00317f, -0.00610f, 0.00275f);
		Vector4D cy2 = Vector4D(0.00516f, -0.04153f, 0.08970f, -0.04214f);
		Vector4D cy3 = Vector4D(0.26688f, 0.06670f, -0.26756f, 0.15346f);
		
		Vector3D zenithYxy;
		
		zenithYxy[0] = (4.0453f * material->floats["turbidity"] - 4.971f) * tan((4/9 - material->floats["turbidity"]/120) * (CommonMath::PI - 2 * theta)) - 0.2155f * material->floats["turbidity"] + 2.4192f;
		zenithYxy[1] = turbidity2 * dot4(cx1, theta2) + material->floats["turbidity"] * dot4(cx2, theta2) + dot4(cx3, theta2);
		zenithYxy[2] = turbidity2 * dot4(cy1, theta2) + material->floats["turbidity"] * dot4(cy2, theta2) + dot4(cy3, theta2);

		Vector3D zenithColor(zenithYxy[1],zenithYxy[2], zenithYxy[0]); 
					
		Vector3D f0ThetaSun;
		f0ThetaSun[0] = (1.0f + material->vectors["A"][0] * exp(material->vectors["B"][0])) * (1.0f + material->vectors["C"][0] * exp(material->vectors["D"][0] * theta) + material->vectors["E"][0] * cosTheta * cosTheta);
		f0ThetaSun[1] = (1.0f + material->vectors["A"][1] * exp(material->vectors["B"][1])) * (1.0f + material->vectors["C"][1] * exp(material->vectors["D"][1] * theta) + material->vectors["E"][1] * cosTheta * cosTheta);
		f0ThetaSun[2] = (1.0f + material->vectors["A"][2] * exp(material->vectors["B"][2])) * (1.0f + material->vectors["C"][2] * exp(material->vectors["D"][2] * theta) + material->vectors["E"][2] * cosTheta * cosTheta);
			
		zenithColor[0] /= f0ThetaSun[0];
		zenithColor[1] /= f0ThetaSun[1];
		zenithColor[2] /= f0ThetaSun[2];

		float Kn = 0.0f;
		Kn = f0ThetaSun[2];
		Kn /= (1.0f + material->vectors["A"][2] * exp(material->vectors["B"][2]/cosTheta)) * (1.0f + material->vectors["C"][2] * exp(material->vectors["D"][2] * 0) + material->vectors["E"][2] * 1.0f);
		zenithColor[2] *= Kn;

		material->vectors["zenith"][0] = zenithColor[0];
		material->vectors["zenith"][1] = zenithColor[1];
		material->vectors["zenith"][2] = zenithColor[2];
	}
}

void runSkyDemo()
{
	isRunning = true;
	timeAccumulator = -0.55f;
	timeUpdate = true;
	EngineInterface::createEngine("Data/Scripts/config.lua");

	EngineInterface::connectKeyboardAction(Escape,exitSkyDemo);
	EngineInterface::addRenderTask("renderSprites");
	EngineInterface::addGameLoopTask("updateSunLight",updateSunLight);

	FreeCamera* camera = new FreeCamera(Vector3D(50.0f,0.0f,50.0f),Vector3D(0.0f,0.0f,1.0f));
	camera->setVelocity(1000.0f,1000.0f,1000.0f);
	camera->setRotateVelocity(10.0f,10.0f,10.0f);
	EngineInterface::connectKeyboardAction(W,boost::bind(&FreeCamera::moveCameraForward,camera));
	EngineInterface::connectKeyboardAction(S,boost::bind(&FreeCamera::moveCameraBack,camera));
	EngineInterface::connectKeyboardAction(A,boost::bind(&FreeCamera::rotateCameraLeft,camera));
	EngineInterface::connectKeyboardAction(D,boost::bind(&FreeCamera::rotateCameraRight,camera));
	EngineInterface::connectKeyboardAction(Q,boost::bind(&FreeCamera::moveCameraUp,camera));
	EngineInterface::connectKeyboardAction(E,boost::bind(&FreeCamera::moveCameraDown,camera));
	EngineInterface::connectMouseMoveAction(boost::bind(&FreeCamera::changeViewTarget,camera,_1,_2));
	EngineInterface::addSceneCamera(camera);

	//sky
	sky = new SceneEntity("Sky","Sphere","Preetham");
	sky->initializeSceneEntity();
	sky->setEntityScale(1000.0f,1000.0f,1000.0f);
	sky->setEntityPosition(0.0f,-1000.0f,0.0f);
	EngineInterface::addIndependentToScene(sky);

	// init preetham
	EngineInterface::addMaterialUpdateFunction("preetham",updatePreetham);
	EngineInterface::connectKeyboardAction(U,controlDayTime);

	// terrain
	terrain = new SceneEntity("Terrain","Terrain","Terrain");
	terrain->initializeSceneEntity();
	terrain->setEntityPosition(-128.0f*50,-1200.0f,-128.0f*50);
	EngineInterface::addIndependentToScene(terrain);

	EngineInterface::initializeFont("Font",32);
	EngineInterface::addSprite("AyumiLogo",Vector3D(-450.0f,-400.0f,0.0f),Vector3D(256.0f,47.0f,0.0f));

	EngineInterface::runGameLoop(&isRunning);
	EngineInterface::releaseEngine();
}
