#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "LV1_Bullet.h"

Bullet::Bullet() : BridgeObject(NULL)
{

}

Bullet::~Bullet()
{
	Release();
}


void Bullet::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 1.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	BridgeObject = NULL;

	strKey = "Bullet";
	Active = false;
}

int Bullet::Update()
{
	if (BridgeObject)
		BridgeObject->Update(TransInfo);

	return 0;
}

void Bullet::Render(HDC _hdc)
{
	if (BridgeObject)
		BridgeObject->Render(_hdc);
}

void Bullet::Release()
{
	delete BridgeObject;
	BridgeObject = nullptr;
}
