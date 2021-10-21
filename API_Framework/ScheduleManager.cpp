#include "ScheduleManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Enemy.h"
#include "Boss.h"


#include "FairyEnemy.h"
#include "FairyEnemy1.h"
#include "FairyEnemy2.h"

#include "Monster_Bullet.h"
#include "monster_Bullet1.h"
#include "Ellipse_Bullet.h"
#include "Ellipse_Bullet1.h"
#include "Boss_Bullet.h"
#include "Boss_Bullet1.h"
#include "Boss_Bullet2.h"




void ScheduleManager::Initialize()
{
	BossList = ObjectManager::GetInstance()->GetBossList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyList2 = ObjectManager::GetInstance()->GetEnemyList2();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	EnemyBulletList1 = ObjectManager::GetInstance()->GetEnemyBulletList1();
	Time1 = GetTickCount64();
	Time2 = GetTickCount64();
	Time3 = GetTickCount64();
	Time4 = GetTickCount64();
	Time5 = GetTickCount64();
	Time6 = GetTickCount64();
	Time7 = GetTickCount64();
	Time1Count = 0.0f;
	Time2Count = 0.0f;
	Time3Count = 0.0f;
	Time6Count = 0.0f;
	angle1 = 0;
	angle2 = 72;
	angle3 = 144;
	angle4 = 216;
	angle5 = 288;
	a = 0;
	b = 0;
}

int ScheduleManager::Update()
{	
	
	// 1�ʸ��� �����Ѵ�
	if (Time1 + 1000 <= GetTickCount64())
	{
		++Time1Count;
	
		// �÷��̾ ������尡 true�� ��� 
		if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
		{
			Time3Count += 0.5f;
	
			for (vector<Object*>::iterator iter = BossList->begin();
				iter != BossList->end(); ++iter)
			{	
				 if ((*iter)->GetPower() == 0)								
				 	this->BossAT1();
			}
		}
	
		Time1 = GetTickCount64();
	}

	// 0.5�ʸ��� �����Ѵ�.
	if (Time2 + 500 <= GetTickCount64())
	{
		//ī��Ʈ ����
		Time2Count += 0.5f;
		// �Ϲ����� ��������
		if (!ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
		{
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
				this->Fairymove2(50, float(rand() % 150 + 50), 22.0f, 27.0f);
				this->Fairymove3(800, float(rand() % 150 + 50), 22.0f, 27.0f);
			}

			if (Time2Count == 31.0f)
			{
				// ** �̾߱⸦ ����
				ObjectManager::GetInstance()->GetPlayer()->SetChat(true);
			}
		}
		Time2 = GetTickCount64();
	}
	 // 3�ʸ��� �����Ѵ�.

	if (Time3 + 3000 <= GetTickCount64())
	{
		Time3Count += 1.0f;
	
		if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
		{
			for (vector<Object*>::iterator iter = BossList->begin();
				iter != BossList->end(); ++iter)
			{
				 if ((*iter)->GetPower() == -1)						
				 {
				 	this->BossAT1();
				 	this->BossAT1_1();
				 }
				 else if ((*iter)->GetPower() == -2)			
				 {
				 	this->BossAT2();
				 }
				 if ((*iter)->GetPower() == -3)
				 {
					 this->BossAT1();
				 	this->BossAT2_1();
				
				 }
					 if ((*iter)->GetPower() == -4)
					 {
					 	this->BossAT1();
					 }

				
			}
		}
	
	
	
		Time3 = GetTickCount64();
	}


	if (Time5 + 200 <= GetTickCount64())
	{
		if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
		{
			for (vector<Object*>::iterator iter = BossList->begin();
				iter != BossList->end(); ++iter)
			{
				if ((*iter)->GetPower() == -4)
				{
					this->BossAT3();
				}
			}


		}
			Time5 = GetTickCount64();

	}

	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
	{






		

		// ** ������ ���� ����			������ �̵����� ����
		for (vector<Object*>::iterator iter = BossList->begin();
			iter != BossList->end(); ++iter)
		{
			// ** ������ ���� ����
			if ((*iter)->GetPower() == -5)
			{
				if (Time6 + 30 <= GetTickCount64())
				{
					EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet1>(angle1, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
					EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet1>(angle2, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
					EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet1>(angle3, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
					EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet1>(angle4, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
					EnemyBulletList->push_back(CreateBullet<Ellipse_Bullet1>(angle5, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));

					if (angle1 < 360) angle1 += 6;
					else angle1 = 0;
					if (angle2 < 360) angle2 += 6;
					else angle2 = 0;
					if (angle3 < 360) angle3 += 6;
					else angle3 = 0;
					if (angle4 < 360) angle4 += 6;
					else angle4 = 0;
					if (angle5 < 360) angle5 += 6;
					else angle5 = 0;


					Time6 = GetTickCount64();
				}
		}

			// ** ������ �̵� ������ �����Ѵ�.
			if (Time6 + 5300 <= GetTickCount64())
			{

			}
	}

		

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

		if ((*iter)->GetPosition().y == _y &&  (*iter)->GetPosition().x == _x)
		{
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList->push_back(CreateBullet<Monster_Bullet>(0, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
		}
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

		if ((*iter)->GetPosition().y == _y && (*iter)->GetPosition().x == _x)
		{
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList->push_back(CreateBullet<Monster_Bullet>(0, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
		}
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
			(*iter)->SetDirection(Vector3(0.1f, 0.0f));

		}

	}
}

void ScheduleManager::BossAT1()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
	{
		// �⺻���� ��ź���� (1������)
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


	}
}

void ScheduleManager::BossAT1_1()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
	{
		// �⺻���� ��ź���� (1������)
			// angle�� ����
		float sp;

		// ��ź�� �߻��ϱ� ���� ź���� 60�� ����
		for (int i = 1; i < 15; i++)
		{
			// �����Ҷ����� �߻簢�� �ٸ����ϱ����ؼ� angle�� i * 6�� �ؼ� ź������ angle���� ���� �����Ѵ�.
			sp = i * 0.7f;
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList->push_back(CreateBullet<Boss_Bullet>(0, sp, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
			EnemyBulletList->push_back(CreateBullet<Boss_Bullet>(50, sp, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
			EnemyBulletList->push_back(CreateBullet<Boss_Bullet>(-50, sp, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
		}

	}
}

void ScheduleManager::BossAT2()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
	{
		// �⺻���� ��ź���� (1������)
	// angle�� ����
		int angle;

		// ��ź�� �߻��ϱ� ���� ź���� 60�� ����
		for (int i = 0; i < 60; i++)
		{
			// �����Ҷ����� �߻簢�� �ٸ����ϱ����ؼ� angle�� i * 6�� �ؼ� ź������ angle���� ���� �����Ѵ�.
			angle = i * 6;
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList1->push_back(CreateBullet<Boss_Bullet1>(angle, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
		}

		
	}
}

void ScheduleManager::BossAT2_1()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
	{
		// �⺻���� ��ź���� (1������)
// angle�� ����
		int angle;

		// ��ź�� �߻��ϱ� ���� ź���� 60�� ����
		for (int i = 0; i < 60; i++)
		{
			// �����Ҷ����� �߻簢�� �ٸ����ϱ����ؼ� angle�� i * 6�� �ؼ� ź������ angle���� ���� �����Ѵ�.
			angle = i * 6;
			EnemyBulletList->push_back(CreateBullet<Boss_Bullet2>(angle, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));

		}
	}
}

void ScheduleManager::BossAT3()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
	{
		{
			// EnemyBulletList�� ������ ������ �߰��Ѵ�. 
			EnemyBulletList1->push_back(CreateBullet<Monster_Bullet>(0, (*iter)->GetPosition(), Vector3(16.0f, 16.0f)));
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
Object* ScheduleManager::CreateBullet(float _x, float _s, Vector3 _vPos, Vector3 _sPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(_vPos, _sPos, _x, _s, pBridge);

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