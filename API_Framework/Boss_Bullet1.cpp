#include "Boss_Bullet1.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Boss_Bullet1::Boss_Bullet1()
{

}

Boss_Bullet1::~Boss_Bullet1()
{

}

void Boss_Bullet1::Initialize()
{
	Speed = 6.0f;
	DrawKey = "Enemy_Bullet";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();

	Time1 = GetTickCount64();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;
	Ell = false;


}

int Boss_Bullet1::Update(Transform& _rTransInfo)
{
	if (!Ell)
	{
		float vx = cos(-angle * PI / 180.0f);
		float vy = sin(-angle * PI / 180.0f);


		_rTransInfo.Position.x += vx * Speed;
		_rTransInfo.Position.y += vy * Speed;

		if (Speed <= 0)
			Ell = true;
		else
			Speed -= 0.1f;


	}
	else
	{
	
			Target = ObjectManager::GetInstance()->GetPlayerTarget(Player->GetPosition());
		if (Target)
		{
			if (!AT)
			_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());
			AT = true;
	
			_rTransInfo.Position.x += _rTransInfo.Direction.x * 5;
			_rTransInfo.Position.y += _rTransInfo.Direction.y * 5;
	
		}
		else
		{
			_rTransInfo.Position.x += _rTransInfo.Direction.x * 5;
			_rTransInfo.Position.y += _rTransInfo.Direction.y * 5;
		}
	}



	return 0;
}

void Boss_Bullet1::Render(HDC _hdc)
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

void Boss_Bullet1::Release()
{

}

