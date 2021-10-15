#include "ScheduleManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Enemy.h"


#include "FairyEnemy.h"
#include "FairyEnemy1.h"
#include "FairyEnemy2.h"

#include "Monster_Bullet.h"
#include "Ellipse_Bullet.h"




void ScheduleManager::Initialize()
{
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyList2 = ObjectManager::GetInstance()->GetEnemyList2();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	Time1 = GetTickCount64();
	Time2 = GetTickCount64();
	Time3 = GetTickCount64();
	Time1Count = 0.0f;
	Time2Count = 0.0f;
	Time3Count = 0.0f;
	a = 0;
	b = 0;
}

int ScheduleManager::Update()
{
	if (Time1 + 100 <= GetTickCount64())
	{
		Time1Count += 0.1f;

		Time1 = GetTickCount64();
	}

	// 0.5�ʸ��� �����Ѵ�.
	if (Time2 + 500 <= GetTickCount64())
	{
		//ī��Ʈ ����
		Time2Count += 0.5f;

		// ù��° ���� ���ʿ��� �������� �����Դٰ� �ٽ� �ö�
		if (Time2Count < 12.0f)
		{
			this->Fairymove1((215 - a), 0, 0.0f, 2.0f);
							   
			this->Fairymove1((215 + a), 0, 2.0f, 4.0f);
							   
			this->Fairymove1((215 - a), 0, 4.0f, 6.0f);
							   
			this->Fairymove1((215 + a), 0, 6.0f, 8.0f);

			a += 25;
			if (a > 75)
				a = 0;
		}

		// �ι�° ���� ������ ������ ���� ź���� �߻��Ѵ�.
		if (Time2Count < 13.0f)
		{
			this->Fairy3(200, -50, 8.0f, 8.4f);
			this->Fairy3(600, -50, 10.0f, 10.4f);

		}

		// ����° ���� ���ʿ��� �������� �����Դٰ� �ٽ� �ö�
		if (Time2Count < 20.0f)
		{
			this->Fairymove1((630 - a), 0, 11.0f, 13.0f);
							  
			this->Fairymove1((630 + a), 0, 13.0f, 15.0f);
							  
			this->Fairymove1((630 - a), 0, 15.0f, 17.0f);
							  
			this->Fairymove1((630 + a), 0, 17.0f, 19.0f);

			a += 25;
			if (a > 75)
				a = 0;
		}

		// �׹�° ���� ���ʰ� �����ʿ��� ���� �ݴ�������� ���ư��鼭 ���߿� ����(������X)����
		if (Time2Count > 22.0f && Time2Count < 28.5f)
		{
			this->Fairymove2(300, 200, 22.0f, 27.0f);
			this->Fairymove3(600, 200, 22.0f, 27.0f);
		}

		if (Time2Count == 31.0f)
		{
			// ** �̾߱⸦ ����
			ObjectManager::GetInstance()->GetPlayer()->SetChat(true);
		}











		Time2 = GetTickCount64();
	}




	return 0;
}

void ScheduleManager::Render(HDC _hdc)
{

}

void ScheduleManager::Release()
{
}

void ScheduleManager::Fairymove1(int _x, int _y, float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if (Time2Count >= _t && Time2Count < _tt)
		// ������ �������� �����Ѵ�.
		EnemyList->push_back(CreateEnemy<FairyEnemy>(_x, _y, 25, 25, 1));


}

void ScheduleManager::Fairymove2(int _x, int _y, float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if (Time2Count >= _t && Time2Count < _tt)
		// ������ �������� �����Ѵ�.
		EnemyList->push_back(CreateEnemy<FairyEnemy2>(_x, _y, 25, 25, 1));

	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		(*iter)->SetDirection(Vector3(1.0f, 0.0f));
	}


}

void ScheduleManager::Fairymove3(int _x, int _y, float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if (Time2Count >= _t && Time2Count < _tt)
		// ������ �������� �����Ѵ�.
		EnemyList2->push_back(CreateEnemy<FairyEnemy2>(_x, _y, 25, 25, 1));
	
	for (vector<Object*>::iterator iter = EnemyList2->begin();
		iter != EnemyList2->end(); ++iter)
	{
		(*iter)->SetDirection(Vector3(-1.0f, 0.0f));
	}


}

// ** ������ ���ٷ� ������ ���ذ���
void ScheduleManager::Fairy1(int _x, int _y , float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if(Time2Count >= _t  && Time2Count < _tt)
	// ������ �������� �����Ѵ�.
	EnemyList->push_back(CreateEnemy<FairyEnemy>(_x, _y, 25, 25, 1));

	// EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// List�� �ִ� Object�� Y��ǥ�� 120�� �Ѿ����
		 if ((*iter)->GetPosition().y > 120 && (*iter)->GetPosition().x == _x)
		 {
			 // EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			 EnemyBulletList->push_back(CreateBullet<Monster_Bullet>(0,(*iter)->GetPosition(), Vector3(16.0f, 16.0f)));

			 // Object�� �̵������� ������� �̵���Ų��
			 (*iter)->SetDirection(Getangle(230.0f));

		 }
		 if ((*iter)->GetPosition().x < (_x - 60))
		 {
			 // Object�� �̵������� ������� �̵���Ų��
			 (*iter)->SetDirection(Getangle(210.0f));
		 }
	}
}

// ** ������ ���ٷ� ������ ���ذ���
void ScheduleManager::Fairy2(int _x, int _y, float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if (Time2Count >= _t && Time2Count < _tt)
		// ������ �������� �����Ѵ�.
		EnemyList->push_back(CreateEnemy<FairyEnemy>(_x, _y, 25, 25, 1));

	// EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// List�� �ִ� Object�� Y��ǥ�� 120�� �Ѿ����
		if ((*iter)->GetPosition().y > 120 && (*iter)->GetPosition().x == _x)
		{
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList->push_back(CreateBullet<Monster_Bullet>(0, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));

			// Object�� �̵������� 0���� �ʱ�ȭ ���� �������� ���ϰ��Ѵ�.
			(*iter)->SetDirection(Getangle(-30.0f));

		}

		 if ((*iter)->GetPosition().x > (_x + 60))
		 {
		 	// Object�� �̵������� 0���� �ʱ�ȭ ���� �������� ���ϰ��Ѵ�.
		 	(*iter)->SetDirection(Getangle(-10.0f));
		 }
	}
}

// ������ ������ ��ź�� �߻� 
void ScheduleManager::Fairy3(int _x, int _y, float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if (Time2Count >= _t && Time2Count < _tt)
	// ������ �������� �����Ѵ�.
	EnemyList1->push_back(CreateEnemy<FairyEnemy1>(_x, _y, 25, 25, 10));

	// EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList1->begin();
		iter != EnemyList1->end(); ++iter)
	{
		// List�� �ִ� Object�� Y��ǥ�� 120�� �Ѿ����
		if ((*iter)->GetPosition().y > 120 && (*iter)->GetPosition().x == _x)
		{

			// angle�� ����
			int angle;

				// ��ź�� �߻��ϱ� ���� ź���� 60�� ����
			for (int i = 0; i < 60; i++)
			{
				// �����Ҷ����� �߻簢�� �ٸ����ϱ����ؼ� angle�� i * 6�� �ؼ� ź������ angle���� ���� �����Ѵ�.
				angle = i * 6;
				// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
				EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet>(angle, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
			}
			// Object�� �̵������� 0���� �ʱ�ȭ ���� �������� ���ϰ��Ѵ�.
			(*iter)->SetDirection(Vector3(1.0f, 0.0f));

		}

	}
}


Vector3 ScheduleManager::Getangle(float _x)
{
	float vx = cos(-_x * PI / 180.0f);
	float vy = sin(-_x * PI / 180.0f);

	Vector3 VV(vx, vy);
	return VV;
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