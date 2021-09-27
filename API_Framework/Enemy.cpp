#include "Enemy.h"
#include "ObjectManager.h"
#include "Fairy.h"


Enemy::Enemy() : BridgeObject(NULL)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 1.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Collider.Position = Vector3(0.0f, 0.0f);
	Collider.Scale = Vector3(100.0f, 100.0f);

	BridgeObject = NULL;

	strKey = "Enemy";
	Active = false;
}

int Enemy::Update()
{
	if (BridgeObject)
		BridgeObject->Update(TransInfo);

	return 0;
}

void Enemy::Render(HDC _hdc)
{
	if (BridgeObject)
		BridgeObject->Render(_hdc);
}

void Enemy::Release()
{

}
