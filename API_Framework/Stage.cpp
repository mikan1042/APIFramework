#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "Stage_Back.h"
#include "MyButton.h"
#include "BackGround.h"
#include "FairyEnemy.h"
#include "Item.h"
#include "Power.h"
#include "Boom.h"
#include "ScheduleManager.h"


Stage::Stage() : m_pPlayer(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	m_pPlayer = ObjectManager::GetInstance()->GetPlayer();

	// ** ������Ʈ �Ŵ������� �Ѿ� ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	BulletList = ObjectManager::GetInstance()->GetBulletList();

	// ** ������Ʈ �Ŵ������� ���� ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();

	// ** ������Ʈ �Ŵ������� ������ ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	ItemList = ObjectManager::GetInstance()->GetItemList();

	// **  ������Ʈ �Ŵ������� ����ź�� ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();

	// ** �̹��� ����Ʈ�� �޾ƿ´�.
	ImageList = Object::GetImageList();


	// ** ����ϱ��� �ʱ⼳��
	State_Back = new Stage_Back;
	State_Back->Initialize();

	Back_Ground = new BackGround;
	Back_Ground->Initialize();


	m_pButton = new MyButton;
	m_pButton->Initialize();

	m_Schedule = new ScheduleManager;
	m_Schedule->Initialize();






	//------------------------------------------------------




}

void Stage::Update()
{
	// ** ������Ʈ�� ��������ش�.
	m_Schedule->Update();

	m_pPlayer->Update();

	m_pButton->Update();


	// ** EnemyList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// ** ���� �÷��̾ �浹�������
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			// ** �ֿܼ� ��ȭ�� ���
			cout << "�÷��̾��� ����" << endl;
		}
	}
	// ** ItemList�� ��ȸ�Ѵ�.
	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end();)
	{
		// ** �����۰� �÷��̾ �浹������� 
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			string Key = (*iter)->GetDrawKey();

			if (Key == "Power")
			{
				int Pow = m_pPlayer->GetPower();
				++Pow;
				m_pPlayer->SetPower(Pow);
				cout << "�Ŀ�" << endl;
			}
			if (Key == "Boom")
				cout << "��ź" << endl;

			iter = ItemList->erase(iter);
		}
		else
			++iter;
	}


	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
		(*iter)->Update();

	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end(); ++iter)
		(*iter)->Update();

	for (vector<Object*>::iterator iter = EnemyBulletList->begin();
		iter != EnemyBulletList->end(); ++iter)
		(*iter)->Update();



	// ** �Ѿ� ����Ʈ�� progress
	for (vector<Object*>::iterator iter = BulletList->begin();
		iter != BulletList->end(); )
	{
		// ** �Ѿ��� ȭ�� ���� �Ѿ�� �Ǹ� reutrn 1 �� ��ȯ �ϰ�, 
		// ** iResult == 1�̸� �Ѿ��� ������.
		int iResult = (*iter)->Update();

 		if ((*iter)->GetPosition().y <= 10)
			iResult = 1;

		// ** Enemy ����Ʈ�� progress
		for (vector<Object*>::iterator iter2 = EnemyList->begin();
			iter2 != EnemyList->end(); )
		{
			// ** �浹 ó��
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp�� ���� �޾ƿ´�
				float Hp = (*iter2)->GetHp();
				// ** ���� ü�� ����
				--Hp;
				// ü���� 0������ ���
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 2) + 1;


					if(Ritem == 1)
					ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));
					else if (Ritem == 2)
					ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(),"Boom"));


					//���� �����Ѵ�.
					iter2 = EnemyList->erase(iter2);

				}
				else
				//�پ�� Hp�� ���� �����ش�.
				(*iter2)->SetHp(Hp);


				// ** ������ ������Ʈ�� �����ѵ�
				iResult = 1;

				// ** ���� �ݺ����� Ż��.
				// ** ���� : �Ѿ� 1���� ������ 1���� �����ϱ� ����. 
				break;

				//** break �� �ȵǸ� �Ѿ��� ������ �������� �浹ü�� �������϶� ��� �浹�� ������.
			}
			else
				++iter2;
		}

		// ** �Ѿ��� �����ϴ� ����.
		if (iResult == 1)
			iter = BulletList->erase(iter);
		else
			++iter;
	}

	//�÷��̾�� ������ ������ �ε��������
	for (vector<Object*>::iterator iter = EnemyBulletList->begin();
		iter != EnemyBulletList->end();)
	{
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			iter = EnemyBulletList->erase(iter);
		}
		else
			++iter;
	}
}

void Stage::Render(HDC _hdc)
{
	Back_Ground->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());
	
	for (vector<Object*>::iterator iter = BulletList->begin();
		iter != BulletList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = EnemyBulletList->begin();
		iter != EnemyBulletList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());



	m_pPlayer->Render(ImageList["Buffer"]->GetMemDC());

	m_pButton->Render(ImageList["Buffer"]->GetMemDC());


	State_Back->Render(ImageList["Buffer"]->GetMemDC());



	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		ImageList["Buffer"]->GetMemDC(),
		0, 0, 
		SRCCOPY);
}

void Stage::Release()
{

}

template <typename T>
Object* Stage::CreateItem(Vector3 _vPos, string _Key)
{
	Bridge* pBridge = new T;

	Object* pItem = ObjectFactory<Item>::CreateObject(_vPos, _Key, pBridge);

	return pItem;
}
