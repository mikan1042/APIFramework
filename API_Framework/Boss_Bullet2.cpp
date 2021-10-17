#include "Boss_Bullet2.h"

#include "Object.h"
#include "Bullet.h"

#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "MathManager.h"

#include "monster_Bullet1.h"


Boss_Bullet2::Boss_Bullet2()
{

}

Boss_Bullet2::~Boss_Bullet2()
{

}

void Boss_Bullet2::Initialize()
{
	Speed = 6.0f;
	DrawKey = "Enemy_Bullet";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	EnemyBulletList1 = ObjectManager::GetInstance()->GetEnemyBulletList1();
	BossList = ObjectManager::GetInstance()->GetBossList();
	ImageList = Object::GetImageList();

	Time1 = GetTickCount64();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;
	Ell = false;


}

int Boss_Bullet2::Update(Transform& _rTransInfo)
{

	float vx = cos(-angle * PI / 180.0f);
	float vy = sin(-angle * PI / 180.0f);


	_rTransInfo.Position.x += vx * Speed;
	_rTransInfo.Position.y += vy * Speed;


	if (Speed >= 0)
		Speed -= 0.1f;
	else if (Speed >= -6.0f)
		Speed = -6.0f;

	




	return 0;
}

void Boss_Bullet2::Render(HDC _hdc)
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

void Boss_Bullet2::Release()
{

}

template <typename T>
Object* Boss_Bullet2::CreateBullet(float _x, Vector3 _vPos, Vector3 _sPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(_vPos, _sPos, _x, pBridge);

	return pBullet;
}