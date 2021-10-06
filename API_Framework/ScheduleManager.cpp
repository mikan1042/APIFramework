#include "ScheduleManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Enemy.h"


#include "FairyEnemy.h"
#include "Monster_Bullet.h"




void ScheduleManager::Initialize()
{
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	Time1 = GetTickCount64();
}

int ScheduleManager::Update()
{
	// 1초마다 실행한다.
	if (Time1 + 1000 <= GetTickCount64())
	{
		// 요정 생성 및 요정공격 
		this->Fairy1();
		Time1 = GetTickCount64();
	}




	return 0;
}

void ScheduleManager::Render(HDC _hdc)
{

}

void ScheduleManager::Release()
{
}

// 요정생성 1
void ScheduleManager::Fairy1()
{
	// 요정을 랜덤으로 생성한다.
	EnemyList->push_back(CreateEnemy<FairyEnemy>(float(rand() % (WindowsWidth - 600) + 60),-50 , 25, 25, 5));

	// EnemyList를 순회한다.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// List에 있는 Object의 Y좌표가 120을 넘어갔을때
		 if ((*iter)->GetPosition().y > 120)
		 {
			 // Object의 이동방향을 0으로 초기화 시켜 움직이지 못하게한다.
			 (*iter)->SetDirection(Vector3 (0.0f, 0.0f));

			 // EnemyBulletList에 요정의 공격을 추가한다. 
			 EnemyBulletList->push_back(CreateBullet<Monster_Bullet>(0,(*iter)->GetPosition(), Vector3(16.0f, 16.0f)));

		 }
	}
}


template <typename T>
Object* ScheduleManager::CreateBullet(float _x, Vector3 _vPos, Vector3 _sPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(_vPos, _sPos, _x, pBridge);

	return pBullet;
}

template <typename T>
Object* ScheduleManager::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;
											
													// 좌표, 크기 , 체력
	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}