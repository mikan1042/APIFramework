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
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyList2 = ObjectManager::GetInstance()->GetEnemyList2();

	ATon = false;

}

int LV2_Bullet::Update(Transform& _rTransInfo)
{
		for (vector<Object*>::iterator iter = EnemyList->begin();
			iter != EnemyList->end(); ++iter)
		{
			if((*iter)->GetPosition().y < 90)
				Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());
		}
		for (vector<Object*>::iterator iter = EnemyList1->begin();
			iter != EnemyList1->end(); ++iter)
		{
			if ((*iter)->GetPosition().y < 90)
				Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());
		}
		for (vector<Object*>::iterator iter = EnemyList2->begin();
			iter != EnemyList2->end(); ++iter)
		{
			if ((*iter)->GetPosition().y < 90)
				Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());
		}


	// �밢������ ���ư����� ��ǥ�� �����Ѵ�.
		float vx = cos(-angle * PI / 180.0f);
		float vy = sin(-angle * PI / 180.0f);
		// ź���� ��ġ���� ������ ��ǥ�� Speed��ŭ�� �ӵ��� ���ư���.
		_rTransInfo.Position.x += vx * Speed;
		_rTransInfo.Position.y += vy * Speed;
		






		if (Target)
		{
			_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());
			ATon = true;

			_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
			_rTransInfo.Position.y += _rTransInfo.Direction.y;
		}
		else
		{
			_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
			_rTransInfo.Position.y += _rTransInfo.Direction.y;
		}

		if (ATon)
		{
			_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
			_rTransInfo.Position.y += _rTransInfo.Direction.y;
		}



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
