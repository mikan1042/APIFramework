#include "ScheduleManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Enemy.h"


#include "FairyEnemy.h"
#include "Monster_Bullet.h"
#include "Ellipse_Bullet.h"




void ScheduleManager::Initialize()
{
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	Time1 = GetTickCount64();
	Time2 = GetTickCount64();
	Time3 = GetTickCount64();
	TimeCount = 0.0f;
}

int ScheduleManager::Update()
{

	// 0.5�ʸ��� �����Ѵ�.
	if (Time1 + 500 <= GetTickCount64())
	{
		//ī��Ʈ ����
		TimeCount += 0.5f;

		// ù��° ���� ������ ���ٷ� ������ ���ذ��� (���ʿ��� 6��)
		if (TimeCount < 6.0f)
		{
			this->Fairy1(200, -50, 0.0f, 3.5f);
			this->Fairy1(230, -50, 0.0f, 3.5f);
		}

		// �ι�° ���� ������ ���ٷ� ������ ���ذ��� (�������� 6��)
		if (TimeCount < 12.0f)
		{
		this->Fairy2(600, -50, 4.0f, 7.5f);
		this->Fairy2(630, -50, 4.0f, 7.5f);
		}

		// ����° ���� ������ ������ ��ź�� �߻�
		if (TimeCount < 13.0f)
		{
			this->Fairy3(200, -50, 8.0f, 8.4f);
			this->Fairy3(600, -50, 10.0f, 10.4f);

		}

		if (TimeCount == 17.0f)
		{
			// ** �̾߱⸦ ����
			ObjectManager::GetInstance()->GetPlayer()->SetChat(true);
		}











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

// ** ������ ���ٷ� ������ ���ذ���
void ScheduleManager::Fairy1(int _x, int _y , float _t, float _tt)
{
	// ī��Ʈ�� ���ؼ� ������ �����Ѵ�.
	if(TimeCount >= _t  && TimeCount < _tt)
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
	if (TimeCount >= _t && TimeCount < _tt)
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
	if (TimeCount >= _t && TimeCount < _tt)
	// ������ �������� �����Ѵ�.
	EnemyList1->push_back(CreateEnemy<FairyEnemy>(_x, _y, 25, 25, 10));

	// EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList1->begin();
		iter != EnemyList1->end(); ++iter)
	{
		// List�� �ִ� Object�� Y��ǥ�� 120�� �Ѿ����
		if ((*iter)->GetPosition().y > 120 && (*iter)->GetPosition().x == _x)
		{
			// Object�� �̵������� 0���� �ʱ�ȭ ���� �������� ���ϰ��Ѵ�.
			(*iter)->SetDirection(Vector3(0.0f, 0.0f));

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
			(*iter)->SetDirection(Getangle(90.0f));

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