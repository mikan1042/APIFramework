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
	Speed = 5.0f;
	DrawKey = "Enemy_Bullet";
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	ImageList = Object::GetImageList();


	Player = ObjectManager::GetInstance()->GetPlayer();
	AT = false;


}

int Monster_Bullet::Update(Transform& _rTransInfo)
{



		Target = ObjectManager::GetInstance()->GetPlayerTarget(Player->GetPosition());

		if (Target)
		{
			if(!AT)
			_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());
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

void Monster_Bullet::Render(HDC _hdc)
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

void Monster_Bullet::Release()
{

}

