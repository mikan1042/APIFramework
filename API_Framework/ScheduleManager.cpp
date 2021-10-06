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
	// 1�ʸ��� �����Ѵ�.
	if (Time1 + 1000 <= GetTickCount64())
	{
		// ���� ���� �� �������� 
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

// �������� 1
void ScheduleManager::Fairy1()
{
	// ������ �������� �����Ѵ�.
	EnemyList->push_back(CreateEnemy<FairyEnemy>(float(rand() % (WindowsWidth - 600) + 60),-50 , 25, 25, 5));

	// EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// List�� �ִ� Object�� Y��ǥ�� 120�� �Ѿ����
		 if ((*iter)->GetPosition().y > 120)
		 {
			 // Object�� �̵������� 0���� �ʱ�ȭ ���� �������� ���ϰ��Ѵ�.
			 (*iter)->SetDirection(Vector3 (0.0f, 0.0f));

			 // EnemyBulletList�� ������ ������ �߰��Ѵ�. 
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
											
													// ��ǥ, ũ�� , ü��
	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}