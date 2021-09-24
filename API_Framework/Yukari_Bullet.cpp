#include "Yukari_Bullet.h"

#include "Object.h"
#include "ObjectManager.h"

Yukari_Bullet::Yukari_Bullet()
{

}

Yukari_Bullet::~Yukari_Bullet()
{

}


void Yukari_Bullet::Initialize()
{
	Speed = 7.0f;

	ImageList = Object::GetImageList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
}

int Yukari_Bullet::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y -= _rTransInfo.Direction.y * Speed;

	return 0;
}


void Yukari_Bullet::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - 8),
		int(RealObject->GetPosition().y - (12)),
		int(12),
		int(16),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(12),
		int(16),
		RGB(255, 0, 255));
}

void Yukari_Bullet::Release()
{

}
