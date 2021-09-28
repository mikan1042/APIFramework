#include "Enemy.h"
#include "ObjectManager.h"
#include "FairyEnemy.h"


Enemy::Enemy() : BridgeObject(NULL)
{

}

Enemy::~Enemy()
{
	Release();
}


void Enemy::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(25.0f, 25.0f);


	Active = false;
	strKey = "Enemy";

	Speed = 1.5f;
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
	delete BridgeObject;
	BridgeObject = nullptr;
}
