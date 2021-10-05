#include "LV1_Bullet.h"

#include "Object.h"
#include "ObjectManager.h"

LV1_Bullet::LV1_Bullet()
{

}

LV1_Bullet::~LV1_Bullet()
{

}


void LV1_Bullet::Initialize()
{
	Speed = 7.0f;

	DrawKey = "NomalBullet";

	ImageList = Object::GetImageList();

}

int LV1_Bullet::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y -= _rTransInfo.Direction.y * Speed;

	return 0;
}


void LV1_Bullet::Render(HDC _hdc)
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

void LV1_Bullet::Release()
{

}
