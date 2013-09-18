#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "AyumiEngine/EngineInterface.hpp"

class Missile : public AyumiEngine::AyumiScene::SceneEntity
{
public:
	AyumiEngine::AyumiMath::Vector3D moveDirection;
	bool isFired;

	Missile(const std::string& entityName,const std::string& meshName, const std::string& materialName);
	~Missile();

	void updateEntity(const float elapsedTime);
};

#endif
