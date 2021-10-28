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
#include "SoundManager.h"



Stage::Stage() : m_pPlayer(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	SoundManager::GetInstance()->Initialize();

	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/th08_01.wav", "BGM");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/th08_02.wav", "BGM1");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/reimu_at.wav", "reimu_at");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/boom.wav", "boom");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/monster_at.wav", "monster_at");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/Smonster_at.wav", "Smonster_at");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/item.wav", "item");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/reimu_die.wav", "reimu_die");
	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/se_pldead00.wav", "se_pldead00");

	SoundManager::GetInstance()->OnPlaySound("BGM");

	

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
	PlayerL->Initialize();

	BossH = new BossHp;
	BossH->Initialize();


	for (int i = 0; i < 10; ++i)
		Sc[i] = 0;

	for (int i = 0; i < 10; ++i)
		HSc[i] = 0;

	HSc[2] = 4;
	HSc[3] = 2;
	HSc[4] = 6;
	HSc[5] = 1;

	BHp = 5;






	//------------------------------------------------------




}

void Stage::Update()
{
	SoundManager::GetInstance()->StramingUpdate();

	for (int i = 0; i < 10; ++i)
	{
		if (Sc[i] > 9)
		{
			Sc[i] = 0;
			++Sc[i + 1];
		}

	}


	// ** ������Ʈ�� ��������ش�.
	m_Schedule->Update();

	m_pPlayer->Update();

	m_pButton->Update();

	m_uHp->Update();

	m_Chat->Update();

	PlayerL->Update();

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
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));

				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList->begin();
			iter != EnemyList->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList1->begin();
			iter != EnemyList1->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** ���� �÷��̾��� �浹
		for (vector<Object*>::iterator iter = EnemyList2->begin();
			iter != EnemyList2->end(); ++iter)
		{
			// ** ���� �÷��̾ �浹�������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** �÷��̾�� ������ ������ �浹
		for (vector<Object*>::iterator iter = EnemyBulletList->begin();
			iter != EnemyBulletList->end();)
		{

			// ������ ź���� �÷��̾ �ε��������
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList->erase(iter);

				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
			// ������ ź���� ȭ����� ����� ���
			else if ((*iter)->GetPosition().x > 950 ||
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
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ������ ź���� �����Ѵ�.
				iter = EnemyBulletList1->erase(iter);

				// ** �÷��̾��� HP�� �޾ƿ´�
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP�� 1���δ�
				--pHp;
				// ** ������ HP���� �����ش�.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** �÷��̾��� ��ġ�� �������Ѵ�.
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
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
				SoundManager::GetInstance()->OnPlaySound("item");
				
				int Pow = m_pPlayer->GetPower();
				++Pow;
				m_pPlayer->SetPower(Pow);
				cout << "�Ŀ�" << endl;
				if(Pow > 10) ++Sc[2];
			}
			if (Key == "Boom")
			{
				SoundManager::GetInstance()->OnPlaySound("item");

				int Booom = m_pPlayer->GetBoom();
				++Booom;
				m_pPlayer->SetBoom(Booom);
				cout << "��ź" << endl;
			}

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
				//������ 100����
				++Sc[2];
				// ü���� 0������ ���
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//������ 100����
					++Sc[2];



					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
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
				//������ 100����
				++Sc[2];

				// ü���� 0������ ���
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//������ 100����
					++Sc[2];



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
				//������ 100����
				++Sc[2];

				// ü���� 0������ ���
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//������ 100����
					++Sc[2];


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
				//������ 100����
				++Sc[2];

				// ü���� 0������ ���
				if (Hp <= 0)
				{
					//������ 100����
					++Sc[2];

					if ((*iter2)->GetPower() > -5)
					{
						int Bhp = (*iter2)->GetPower();
						(*iter2)->SetPower(--Bhp);
						Hp = 724;
						(*iter2)->SetHp(Hp);
					
						if ((*iter2)->GetPower() == 0)	BHp = 5;
						if ((*iter2)->GetPower() == -1)	BHp = 4;
						if ((*iter2)->GetPower() == -2)	BHp = 3;
						if ((*iter2)->GetPower() == -3)	BHp = 2;
						if ((*iter2)->GetPower() == -4)	BHp = 1;
						if ((*iter2)->GetPower() == -5)	BHp = 100;

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
			else if ((*iter)->GetPosition().x > 1000 ||
				(*iter)->GetPosition().x < -250 ||
				(*iter)->GetPosition().y < -250 ||
				(*iter)->GetPosition().y > 900)
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
			else if ((*iter)->GetPosition().x > 1000 ||
				(*iter)->GetPosition().x < -250 ||
				(*iter)->GetPosition().y < -250 ||
				(*iter)->GetPosition().y > 900)
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

	m_Chat->Render(ImageList["Buffer"]->GetMemDC());

	State_Back->Render(ImageList["Buffer"]->GetMemDC());
	
	m_uHp->Render(ImageList["Buffer"]->GetMemDC());



	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
	{
		BossH->Render(ImageList["Buffer"]->GetMemDC());
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), 50, 60, 32, 42.5, ImageList["Number"]->GetMemDC(), 63 * BHp, 0, 64, 85, RGB(255, 0, 255));

	}

	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());




	for (int i = 0; i < 10; ++i)
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), (1105) - (i * 25), 60, 32, 42.5, ImageList["Number"]->GetMemDC(), (63 * Sc[i]), 0, 64, 85, RGB(255, 0, 255));

	for (int i = 0; i < 10; ++i)
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), (1120) - (i * 25), 23, 32, 42.5, ImageList["Number"]->GetMemDC(), (63 * HSc[i]), 0, 64, 85, RGB(255, 0, 255));

	if(m_pPlayer->GetPower() < 10)
	TransparentBlt(ImageList["Buffer"]->GetMemDC(), 880, 170, 32, 42.5, ImageList["Number"]->GetMemDC(), 63 * (m_pPlayer->GetPower()) - 1, 0, 64, 85, RGB(255, 0, 255));
	else
	TransparentBlt(ImageList["Buffer"]->GetMemDC(), 880, 174, 48 * 1.5f, 15 * 1.5f, ImageList["MAX"]->GetMemDC(), 0, 0, 48, 15, RGB(255, 0, 255));



	// ** HP�� 0�� �Ǿ��� ���											
	if (ObjectManager::GetInstance()->GetPlayer()->GetHp() <= 0)
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), 60, 300, 724, 122, ImageList["GG"]->GetMemDC(), 0, 0, 724, 122, RGB(255, 0, 255));






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
