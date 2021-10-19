#include "Ellipse_Bullet1.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Ellipse_Bullet1::Ellipse_Bullet1()
{

}

Ellipse_Bullet1::~Ellipse_Bullet1()
{

}

void Ellipse_Bullet1::Initialize()
{
	Speed = 4.0f;

	DrawKey = "Enemy_Bullet";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;



}

int Ellipse_Bullet1::Update(Transform& _rTransInfo)
{

	float vx = cos(-angle * PI / 180.0f);
	float vy = sin(-angle * PI / 180.0f);


	_rTransInfo.Position.x += vx * Speed;
	_rTransInfo.Position.y += vy * Speed;



	return 0;
}

void Ellipse_Bullet1::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y - (RealObject->GetScale().y / 2)),
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));
}

void Ellipse_Bullet1::Release()
{

}

