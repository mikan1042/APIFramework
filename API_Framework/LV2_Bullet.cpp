#include "LV2_Bullet.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"

LV2_Bullet::LV2_Bullet()
{

}

LV2_Bullet::~LV2_Bullet()
{

}


void LV2_Bullet::Initialize()
{
	Speed = 7.0f;

	DrawKey = "guidedBullet";

	ImageList = Object::GetImageList();

	Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());

	ATon = false;

}

int LV2_Bullet::Update(Transform& _rTransInfo)
{


	Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());

	if (Target)
	{
		_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());

		_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
		_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

		ATon = true;
	}
	else
	{
		float vx = cos(-angle * PI / 180.0f);
		float vy = sin(-angle * PI / 180.0f);

		if (ATon)
		{
			_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
			_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;
		}
		else
		{
			_rTransInfo.Position.x += vx * Speed;
			_rTransInfo.Position.y += vy * Speed;
		}
	}

	return 0;
}


void LV2_Bullet::Render(HDC _hdc)
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

void LV2_Bullet::Release()
{

}
