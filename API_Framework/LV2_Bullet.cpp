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

	Anime = 0;
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


	// 대각선으로 날아가도록 좌표를 설정한다.
		float vx = cos(-angle * PI / 180.0f);
		float vy = sin(-angle * PI / 180.0f);
		// 탄막의 위치에서 설정한 좌표로 Speed만큼의 속도로 날아간다.
		_rTransInfo.Position.x += vx * Speed;
		_rTransInfo.Position.y += vy * Speed;
		

		if (AmTime + 100 <= GetTickCount64())
		{
			Anime += 18;
			AmTime = GetTickCount64();

			if (Anime >= 288)
				Anime = 0;
		}




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
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (18 / 2)),
		int(RealObject->GetPosition().y - (18 / 2)),
		int(18),
		int(18),
		ImageList[DrawKey]->GetMemDC(),
		Anime, 0,
		int(18),
		int(18),
		RGB(255, 0, 255));
}

void LV2_Bullet::Release()
{

}
