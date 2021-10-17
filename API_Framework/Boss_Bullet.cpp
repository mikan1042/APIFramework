#include "Boss_Bullet.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Boss_Bullet::Boss_Bullet()
{

}

Boss_Bullet::~Boss_Bullet()
{

}

void Boss_Bullet::Initialize()
{
	DrawKey = "Enemy_Bullet";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;


}

int Boss_Bullet::Update(Transform& _rTransInfo)
{

	Target = ObjectManager::GetInstance()->GetPlayerTarget(Player->GetPosition());

	if (Target)
	{
		Vector3 Tg = Target->GetPosition();
		Tg.x += angle;
		if (!AT)
			_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Tg);
		AT = true;

		_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
		_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	}
	else
	{
		_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
		_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;
	}


	return 0;
}

void Boss_Bullet::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** ���� ��� ��ġ
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

void Boss_Bullet::Release()
{

}

