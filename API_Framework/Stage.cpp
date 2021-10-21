#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "PlayerLife.h"
#include "Enemy.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "Stage_Back.h"
#include "MyButton.h"
#include "BackGround.h"
#include "FairyEnemy.h"
#include "FairyEnemy1.h"
#include "FairyEnemy2.h"
#include "Item.h"
#include "Power.h"
#include "Boom.h"
#include "ScheduleManager.h"
#include "UI_Hp.h"
#include "Chat.h"
#include "BossHp.h"
#include "Y_Char.h"


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
	BossList = ObjectManager::GetInstance()->GetBossList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyList2 = ObjectManager::GetInstance()->GetEnemyList2();

	// ** ������Ʈ �Ŵ������� ������ ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	ItemList = ObjectManager::GetInstance()->GetItemList();

	// **  ������Ʈ �Ŵ������� ����ź�� ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	EnemyBulletList1 = ObjectManager::GetInstance()->GetEnemyBulletList1();

	// **  ������Ʈ �Ŵ������� ����ź�� ����Ʈ�� �޾ƿ�. (�����ͷ�...)
	PlayerBoom = ObjectManager::GetInstance()->GetPlayerBoom();


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

	m_uHp = new UI_Hp;
	m_uHp->Initialize();

	m_Chat = new Chat;
	m_Chat->Initialize();

	PlayerL = new PlayerLife;
	PlayerL ->Initialize();

	BossH = new BossHp;
	BossH->Initialize();

	YukariBullet = new Y_Char;
	YukariBullet->Initialize();






	//------------------------------------------------------




}

void Stage::Update()
{
	// ** ������Ʈ�� ��������ش�.
	m_Schedule->Update();

	m_pPlayer->Update();

	m_pButton->Update();

	m_uHp->Update();

	m_Chat->Update();

	PlayerL->Update();

	YukariBullet->Update();


	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
	BossH->Update();




	// ������ �ƴҰ�쿡�� �浹
	if (!ObjectManager::GetInstance()->GetPlayer()->GetGodMode())
	{
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = BossList->begin();
			iter != BossList->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList->begin();
			iter != EnemyList->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList1->begin();
			iter != EnemyList1->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList2->begin();
			iter != EnemyList2->end(); ++iter)
			{
				// ** ���� �÷��̾ �浹�������
				if (CollisionManager::RectCollision((*iter), PlayerL))
				{
					// ** �÷��̾��� HP�� �޾ƿ´�
					int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
					// ** HP�� 1���δ�
					--pHp;
					// ** ������ HP���� �����ش�.
					ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
					// ** �÷��̾��� ��ġ�� �������Ѵ�.
					ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				}
			}
		// ** �÷��̾�� ������ ������ �浹
		for (vector<Object*>::iterator iter = EnemyBulletList->begin();
			iter != EnemyBulletList->end();)
		{	

			// ������ ź���� �÷��̾ �ε��������
 			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList->erase(iter);

				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
			// ������ ź���� ȭ����� ����� ���
			else if ((*iter)->GetPosition().x > 950||
					(*iter)->GetPosition().x < -150 ||
					(*iter)->GetPosition().y < -150 ||
					(*iter)->GetPosition().y > 870)
			{
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList->erase(iter);
			}
			else
				++iter;
		}
		for (vector<Object*>::iterator iter = EnemyBulletList1->begin();
			iter != EnemyBulletList1->end();)
		{

			// ������ ź���� �÷��̾ �ε��������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList1->erase(iter);

				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
			// ������ ź���� ȭ����� ����� ���
			else if ((*iter)->GetPosition().x > 950 ||
				(*iter)->GetPosition().x < -150 ||
				(*iter)->GetPosition().y < -150 ||
				(*iter)->GetPosition().y > 870)
			{
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList1->erase(iter);
			}
			else
				++iter;
		}
	}



	// ** �÷��̾�� �������� �浹
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

	//�������� �������� ������Ʈ
	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end(); ++iter)
		(*iter)->Update();

	// ** �÷��̾��� ��ź�� �������� ������Ʈ
	for (vector<Object*>::iterator iter = PlayerBoom->begin();
		iter != PlayerBoom->end(); ++iter)
		(*iter)->Update();


	// ** �÷��̾��� ��ź�� ������ �浹
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end();)
	{
		(*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{
			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				float Bhp = (*iter)->GetHp();
				iter1 = PlayerBoom->erase(iter1);
				(*iter)->SetHp(Bhp -= 72.4f);
			}
			else
				++iter1;
		}
			++iter;
	}
	// ** �÷��̾��� ��ź�� ���� �浹								** ���Ͱ� ȭ����� ��� ��� ����
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end();)
	{
		int iResult = (*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{
			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				iResult = 1;
				break;
			}
			else
				++iter1;
		}
		if (iResult == 1)
			iter = EnemyList->erase(iter);
		else if ((*iter)->GetPosition().x > 800 ||
			(*iter)->GetPosition().x < 50 ||
			(*iter)->GetPosition().y > 720)
		{
			iter = EnemyList->erase(iter);
		}
		else
			++iter;
	}
	// ** �÷��̾��� ��ź�� ���� �浹								** ���Ͱ� ȭ����� ��� ��� ����
	for (vector<Object*>::iterator iter = EnemyList1->begin();
		iter != EnemyList1->end();)
	{
		int iResult = (*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{
			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				iResult = 1;
				break;
			}
			else
				++iter1;
		}
		if (iResult == 1)
			iter = EnemyList1->erase(iter);
		else if ((*iter)->GetPosition().x > 800 ||
			(*iter)->GetPosition().x < 50 ||
			(*iter)->GetPosition().y > 720)
		{
			iter = EnemyList1->erase(iter);
		}
		else if ((*iter)->GetPosition().y < -100)
		{
			iter = EnemyList1->erase(iter);
		}
		else
			++iter;
	}
	// ** �÷��̾��� ��ź�� ���� �浹								** ���Ͱ� ȭ����� ��� ��� ����
	for (vector<Object*>::iterator iter = EnemyList2->begin();
		iter != EnemyList2->end();)
	{
		int iResult = (*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{
			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				iResult = 1;
				break;
			}
			else
				++iter1;
		}
		if (iResult == 1)
			iter = EnemyList2->erase(iter);
		else if ((*iter)->GetPosition().x > 800 ||
			(*iter)->GetPosition().x < 50 ||
			(*iter)->GetPosition().y > 720)
		{
			iter = EnemyList2->erase(iter);
		}
		else if ((*iter)->GetPosition().y < -100)
		{
			iter = EnemyList2->erase(iter);
		}
		else
			++iter;
	}



	// ** �÷��̾��� ź���� ������ �浹
	for (vector<Object*>::iterator iter = BulletList->begin();
		iter != BulletList->end(); )
	{
		// ** �Ѿ��� ȭ�� ���� �Ѿ�� �Ǹ� reutrn 1 �� ��ȯ �ϰ�, 
		// ** iResult == 1�̸� �Ѿ��� ������.
		int iResult = (*iter)->Update();

 		if ((*iter)->GetPosition().y <= 10 || (*iter)->GetPosition().x <= 60 || (*iter)->GetPosition().x >= 785)
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
					int Ritem = (rand() % 100) + 1;


					if(Ritem == 1)
					ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(),"Boom"));
					else if (Ritem >= 2)
					ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


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

		for (vector<Object*>::iterator iter2 = EnemyList1->begin();
			iter2 != EnemyList1->end(); )
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
					int Ritem = (rand() % 100) + 1;


					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
					else if (Ritem >= 2)
						ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


					//���� �����Ѵ�.
					iter2 = EnemyList1->erase(iter2);

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

		for (vector<Object*>::iterator iter2 = EnemyList2->begin();
			iter2 != EnemyList2->end(); )
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
					int Ritem = (rand() % 100) + 1;


					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
					else if (Ritem >= 2)
						ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


					//���� �����Ѵ�.
					iter2 = EnemyList2->erase(iter2);

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

		for (vector<Object*>::iterator iter2 = BossList->begin();
			iter2 != BossList->end(); )
		{
			// ** �浹 ó��
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp�� ���� �޾ƿ´�
				float Hp = (*iter2)->GetHp();
				// ** ���� ü�� ����
				Hp -= 2;
				// ü���� 0������ ���
				if (Hp <= 0)
				{
					if ((*iter2)->GetPower() > -5)
					{
						int Bhp = (*iter2)->GetPower();
						(*iter2)->SetPower(--Bhp);
						Hp = 724;
						(*iter2)->SetHp(Hp);
					}
					else
					{
						ObjectManager::GetInstance()->GetPlayer()->SetWin(true);
						ObjectManager::GetInstance()->GetPlayer()->SetChat(true);
						ObjectManager::GetInstance()->GetPlayer()->SetChat1(true);
						ObjectManager::GetInstance()->GetPlayer()->SetBossMode(false);
					}

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



	 // ** �÷��̾��� ��ź�� ������ ������ �浹
	for (vector<Object*>::iterator iter = EnemyBulletList->begin();
		iter != EnemyBulletList->end();)
	{
		int iResult = (*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{

			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				iResult = 1;
				break;
			}
			else if ((*iter)->GetPosition().x > 800 ||
				(*iter)->GetPosition().x < 50 ||
				(*iter)->GetPosition().y < 0 ||
				(*iter)->GetPosition().y > 720)
			{
				iResult = 1;
				break;
			}
			else
				++iter1;
		}
		if (iResult == 1)
			iter = EnemyBulletList->erase(iter);
		else
		++iter;
	}
	for (vector<Object*>::iterator iter = EnemyBulletList1->begin();
		iter != EnemyBulletList1->end();)
	{
		int iResult = (*iter)->Update();

		for (vector<Object*>::iterator iter1 = PlayerBoom->begin();
			iter1 != PlayerBoom->end();)
		{

			if (CollisionManager::RectCollision((*iter1), (*iter)))
			{
				iResult = 1;
				break;
			}
			else if ((*iter)->GetPosition().x > 800 ||
				(*iter)->GetPosition().x < 50 ||
				(*iter)->GetPosition().y < 0 ||
				(*iter)->GetPosition().y > 720)
			{
				iResult = 1;
				break;
			}
			else
				++iter1;
		}
		if (iResult == 1)
			iter = EnemyBulletList1->erase(iter);
		else
			++iter;
	}







		
	// ** HP�� 0�� �Ǿ��� ���												�ӽ�
	if (ObjectManager::GetInstance()->GetPlayer()->GetHp() <= 0)
	{

	}










}

void Stage::Render(HDC _hdc)
{
	Back_Ground->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = EnemyList1->begin();
		iter != EnemyList1->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = EnemyList2->begin();
		iter != EnemyList2->end(); ++iter)
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

	for (vector<Object*>::iterator iter = EnemyBulletList1->begin();
		iter != EnemyBulletList1->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = PlayerBoom->begin();
		iter != PlayerBoom->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	
	m_pPlayer->Render(ImageList["Buffer"]->GetMemDC());

	m_pButton->Render(ImageList["Buffer"]->GetMemDC());


	State_Back->Render(ImageList["Buffer"]->GetMemDC());

	m_uHp->Render(ImageList["Buffer"]->GetMemDC());

	m_Chat->Render(ImageList["Buffer"]->GetMemDC());

	YukariBullet->Render(ImageList["Buffer"]->GetMemDC());


	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
	BossH->Render(ImageList["Buffer"]->GetMemDC());

	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());



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
