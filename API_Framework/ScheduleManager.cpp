#include "ScheduleManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Enemy.h"


#include "FairyEnemy.h"
#include "Monster_Bullet.h"




void ScheduleManager::Initialize()
{
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	Time1 = GetTickCount64();
}

int ScheduleManager::Update()
{
	if (Time1 + 300 <= GetTickCount64())
	{
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

// ��������1
void ScheduleManager::Fairy1()
{
	EnemyList->push_back(CreateEnemy<FairyEnemy>(float(rand() % (WindowsWidth - 600) + 60),-50 , 25, 25, 5));

	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		 if ((*iter)->GetPosition().y > 120)
		 {
			 (*iter)->SetDirection(Vector3 (0.0f, 0.0f));



		 }
	}
}

// �������� ( �÷��̾ �븮�� ����)
void ScheduleManager::FairyAT()
{

}




template <typename T>
Object* ScheduleManager::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;
											
													// ��ǥ, ũ�� , ü��
	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}