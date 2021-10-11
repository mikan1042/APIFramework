#include "Reimu_Boom.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Reimu_Boom::Reimu_Boom()
{

}

Reimu_Boom::~Reimu_Boom()
{

}

void Reimu_Boom::Initialize()
{
	Speed = 7.0f;

	DrawKey = "Reimu_Boom";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;



}

int Reimu_Boom::Update(Transform& _rTransInfo)
{

	float vx = cos(-angle * PI / 180.0f);
	float vy = sin(-angle * PI / 180.0f);


	_rTransInfo.Position.x += vx * Speed;
	_rTransInfo.Position.y += vy * Speed;



	return 0;
}

void Reimu_Boom::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - 6),
		int(RealObject->GetPosition().y - 36),
		int(RealObject->GetScale().x * 1.3f),
		int(RealObject->GetScale().y * 1.3f),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));
}

void Reimu_Boom::Release()
{

}

