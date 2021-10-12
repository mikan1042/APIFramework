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

	EnemyList = ObjectManager::GetInstance()->GetEnemyList();

	ATon = false;

}

int LV2_Bullet::Update(Transform& _rTransInfo)
{
	// �밢������ ���ư����� ��ǥ�� �����Ѵ�.
		float vx = cos(-angle * PI / 180.0f);
		float vy = sin(-angle * PI / 180.0f);
		// ź���� ��ġ���� ������ ��ǥ�� Speed��ŭ�� �ӵ��� ���ư���.
		_rTransInfo.Position.x += vx * Speed;
		_rTransInfo.Position.y += vy * Speed;
		
		//	for (vector<Object*>::iterator iter = EnemyList->begin();
		//		iter != EnemyList->end();)
		//	{
		//		if ((*iter)->GetPosition().y > 60)
		//		{

					Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());

					if (Target)
					{
						_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());
						ATon = true;

						_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
						_rTransInfo.Position.y += _rTransInfo.Direction.y;
					}

					if (ATon)
					{
						_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
						_rTransInfo.Position.y += _rTransInfo.Direction.y;
					}
		// 		}
				
		// 			++iter;
		// 	}


	return 0;
}


void LV2_Bullet::Render(HDC _hdc)
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

void LV2_Bullet::Release()
{

}
