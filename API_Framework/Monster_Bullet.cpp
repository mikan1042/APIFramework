#include "Monster_Bullet.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Monster_Bullet::Monster_Bullet()
{

}

Monster_Bullet::~Monster_Bullet()
{

}

void Monster_Bullet::Initialize()
{
	Speed = 7.0f;

	DrawKey = "Enemy_Bullet";

	ImageList = Object::GetImageList();

	AT = true;
}

int Monster_Bullet::Update(Transform& _rTransInfo)
{
	if (AT)
	{
		Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());

		if (Target)
			_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());

		AT = false;
	}

		_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
		_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}

void Monster_Bullet::Render(HDC _hdc)
{

}

void Monster_Bullet::Release()
{

}

