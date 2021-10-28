#include "Boss_Bullet3.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Boss_Bullet3::Boss_Bullet3()
{

}

Boss_Bullet3::~Boss_Bullet3()
{

}

void Boss_Bullet3::Initialize()
{
	Speed = 6.0f;
	DrawKey = "Enemy_Bullet1";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();

	Time1 = GetTickCount64();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;
	Ell = false;

	a = 0;
}

int Boss_Bullet3::Update(Transform& _rTransInfo)
{

		float vx = cos((angle + a) * PI / 180.0f);
		float vy = sin((angle + a) * PI / 180.0f);


		if (a > 100)
		{
			a += 0;
		}
		else
		a += 1.0f;


		_rTransInfo.Position.x += vx * Speed;
		_rTransInfo.Position.y += vy * Speed;


		cout << a << endl;



	return 0;
}

void Boss_Bullet3::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y - (RealObject->GetScale().y / 2)),
		int(RealObject->GetScale().x * 2.0f),
		int(RealObject->GetScale().y * 2.0f),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));
}

void Boss_Bullet3::Release()
{

}
