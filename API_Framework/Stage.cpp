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
	// ** 오브젝트 매니저에서 총알 리스트를 받아옴. (포인터로...)
	BulletList = ObjectManager::GetInstance()->GetBulletList();

	// ** 오브젝트 매니저에서 몬스터 리스트를 받아옴. (포인터로...)
	BossList = ObjectManager::GetInstance()->GetBossList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	EnemyList1 = ObjectManager::GetInstance()->GetEnemyList1();
	EnemyList2 = ObjectManager::GetInstance()->GetEnemyList2();

	// ** 오브젝트 매니저에서 아이템 리스트를 받아옴. (포인터로...)
	ItemList = ObjectManager::GetInstance()->GetItemList();

	// **  오브젝트 매니저에서 몬스터탄막 리스트를 받아옴. (포인터로...)
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();
	EnemyBulletList1 = ObjectManager::GetInstance()->GetEnemyBulletList1();

	// **  오브젝트 매니저에서 몬스터탄막 리스트를 받아옴. (포인터로...)
	PlayerBoom = ObjectManager::GetInstance()->GetPlayerBoom();





	// ** 이미지 리스트를 받아온다.
	ImageList = Object::GetImageList();


	// ** 사용하기전 초기설정
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


	// ** 업데이트를 실행시켜준다.
	m_Schedule->Update();

	m_pPlayer->Update();

	m_pButton->Update();

	m_uHp->Update();

	m_Chat->Update();

	PlayerL->Update();

	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
		BossH->Update();




	// 무적이 아닐경우에만 충돌
	if (!ObjectManager::GetInstance()->GetPlayer()->GetGodMode())
	{
		// ** 적과 플레이어의 충돌
		for (vector<Object*>::iterator iter = BossList->begin();
			iter != BossList->end(); ++iter)
		{
			// ** 적과 플레이어가 충돌했을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));

				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** 적과 플레이어의 충돌
		for (vector<Object*>::iterator iter = EnemyList->begin();
			iter != EnemyList->end(); ++iter)
		{
			// ** 적과 플레이어가 충돌했을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** 적과 플레이어의 충돌
		for (vector<Object*>::iterator iter = EnemyList1->begin();
			iter != EnemyList1->end(); ++iter)
		{
			// ** 적과 플레이어가 충돌했을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** 적과 플레이어의 충돌
		for (vector<Object*>::iterator iter = EnemyList2->begin();
			iter != EnemyList2->end(); ++iter)
		{
			// ** 적과 플레이어가 충돌했을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
			}
		}
		// ** 플레이어와 요정의 공격의 충돌
		for (vector<Object*>::iterator iter = EnemyBulletList->begin();
			iter != EnemyBulletList->end();)
		{

			// 요정의 탄막과 플레이어가 부딪혔을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// 요정의 탄막을 제거한다.
				iter = EnemyBulletList->erase(iter);

				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
			// 요정의 탄막이 화면밖을 벗어났을 경우
			else if ((*iter)->GetPosition().x > 950 ||
				(*iter)->GetPosition().x < -150 ||
				(*iter)->GetPosition().y < -150 ||
				(*iter)->GetPosition().y > 870)
			{
				// 요정의 탄막을 제거한다.
				iter = EnemyBulletList->erase(iter);
			}
			else
				++iter;
		}
		for (vector<Object*>::iterator iter = EnemyBulletList1->begin();
			iter != EnemyBulletList1->end();)
		{

			// 요정의 탄막과 플레이어가 부딪혔을경우
			if (CollisionManager::RectCollision((*iter), PlayerL))
			{
				SoundManager::GetInstance()->OnPlaySound("se_pldead00");
				// 요정의 탄막을 제거한다.
				iter = EnemyBulletList1->erase(iter);

				// ** 플레이어의 HP를 받아온다
				int pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
				// ** HP를 1줄인다
				--pHp;
				// ** 변경한 HP값을 보내준다.
				ObjectManager::GetInstance()->GetPlayer()->SetHp(pHp);
				// ** 플레이어의 위치를 재조정한다.
				ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
				ObjectManager::GetInstance()->GetPlayer()->SetPosition(Vector3(420.0f, 640.0f));
			}
			// 요정의 탄막이 화면밖을 벗어났을 경우
			else if ((*iter)->GetPosition().x > 950 ||
				(*iter)->GetPosition().x < -150 ||
				(*iter)->GetPosition().y < -150 ||
				(*iter)->GetPosition().y > 870)
			{
				// 요정의 탄막을 제거한다.
				iter = EnemyBulletList1->erase(iter);
			}
			else
				++iter;
		}
	}



	// ** 플레이어와 아이템의 충돌
	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end();)
	{
		// ** 아이템과 플레이어가 충돌했을경우 
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			string Key = (*iter)->GetDrawKey();

			if (Key == "Power")
			{
				SoundManager::GetInstance()->OnPlaySound("item");
				
				int Pow = m_pPlayer->GetPower();
				++Pow;
				m_pPlayer->SetPower(Pow);
				cout << "파워" << endl;
				if(Pow > 10) ++Sc[2];
			}
			if (Key == "Boom")
			{
				SoundManager::GetInstance()->OnPlaySound("item");

				int Booom = m_pPlayer->GetBoom();
				++Booom;
				m_pPlayer->SetBoom(Booom);
				cout << "폭탄" << endl;
			}

			iter = ItemList->erase(iter);
		}
		else
			++iter;
	}

	//아이템의 움직임을 업데이트
	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end(); ++iter)
		(*iter)->Update();

	// ** 플레이어의 폭탄의 움직임을 업데이트
	for (vector<Object*>::iterator iter = PlayerBoom->begin();
		iter != PlayerBoom->end(); ++iter)
		(*iter)->Update();


	// ** 플레이어의 폭탄과 보스의 충돌
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
	// ** 플레이어의 폭탄과 적의 충돌								** 몬스터가 화면밖을 벗어날 경우 삭제
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
	// ** 플레이어의 폭탄과 적의 충돌								** 몬스터가 화면밖을 벗어날 경우 삭제
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
	// ** 플레이어의 폭탄과 적의 충돌								** 몬스터가 화면밖을 벗어날 경우 삭제
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



	// ** 플레이어의 탄막과 요정의 충돌
	for (vector<Object*>::iterator iter = BulletList->begin();
		iter != BulletList->end(); )
	{
		// ** 총알이 화면 밖을 넘어가게 되면 reutrn 1 을 반환 하고, 
		// ** iResult == 1이면 총알은 삭제됨.
		int iResult = (*iter)->Update();

		if ((*iter)->GetPosition().y <= 10 || (*iter)->GetPosition().x <= 60 || (*iter)->GetPosition().x >= 785)
			iResult = 1;

		// ** Enemy 리스트의 progress
		for (vector<Object*>::iterator iter2 = EnemyList->begin();
			iter2 != EnemyList->end(); )
		{
			// ** 충돌 처리
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp의 값을 받아온다
				float Hp = (*iter2)->GetHp();
				// ** 몬스터 체력 감소
				--Hp;
				//점수를 100증가
				++Sc[2];
				// 체력이 0이하일 경우
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//점수를 100증가
					++Sc[2];



					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
					else if (Ritem >= 2)
						ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


					//적을 제거한다.
					iter2 = EnemyList->erase(iter2);



				}
				else
					//줄어든 Hp의 값을 보내준다.
					(*iter2)->SetHp(Hp);


				// ** 삭제할 오브젝트로 지정한뒤
				iResult = 1;

				// ** 현재 반복문을 탈출.
				// ** 이유 : 총알 1개에 오브젝 1개를 삭제하기 위함. 
				break;

				//** break 가 안되면 총알이 생성된 시점에서 충돌체가 여러개일때 모두 충돌후 삭제됨.
			}
			else
				++iter2;
		}

		for (vector<Object*>::iterator iter2 = EnemyList1->begin();
			iter2 != EnemyList1->end(); )
		{
			// ** 충돌 처리
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp의 값을 받아온다
				float Hp = (*iter2)->GetHp();
				// ** 몬스터 체력 감소
				--Hp;
				//점수를 100증가
				++Sc[2];

				// 체력이 0이하일 경우
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//점수를 100증가
					++Sc[2];



					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
					else if (Ritem >= 2)
						ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


					//적을 제거한다.
					iter2 = EnemyList1->erase(iter2);

				}
				else
					//줄어든 Hp의 값을 보내준다.
					(*iter2)->SetHp(Hp);


				// ** 삭제할 오브젝트로 지정한뒤
				iResult = 1;

				// ** 현재 반복문을 탈출.
				// ** 이유 : 총알 1개에 오브젝 1개를 삭제하기 위함. 
				break;

				//** break 가 안되면 총알이 생성된 시점에서 충돌체가 여러개일때 모두 충돌후 삭제됨.
			}
			else
				++iter2;
		}

		for (vector<Object*>::iterator iter2 = EnemyList2->begin();
			iter2 != EnemyList2->end(); )
		{
			// ** 충돌 처리
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp의 값을 받아온다
				float Hp = (*iter2)->GetHp();
				// ** 몬스터 체력 감소
				--Hp;
				//점수를 100증가
				++Sc[2];

				// 체력이 0이하일 경우
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 100) + 1;

					//점수를 100증가
					++Sc[2];


					if (Ritem == 1)
						ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(), "Boom"));
					else if (Ritem >= 2)
						ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));


					//적을 제거한다.
					iter2 = EnemyList2->erase(iter2);

				}
				else
					//줄어든 Hp의 값을 보내준다.
					(*iter2)->SetHp(Hp);


				// ** 삭제할 오브젝트로 지정한뒤
				iResult = 1;

				// ** 현재 반복문을 탈출.
				// ** 이유 : 총알 1개에 오브젝 1개를 삭제하기 위함. 
				break;

				//** break 가 안되면 총알이 생성된 시점에서 충돌체가 여러개일때 모두 충돌후 삭제됨.
			}
			else
				++iter2;
		}

		for (vector<Object*>::iterator iter2 = BossList->begin();
			iter2 != BossList->end(); )
		{
			// ** 충돌 처리
			if (CollisionManager::BulletCollision((*iter), (*iter2)))
			{
				//Hp의 값을 받아온다
				float Hp = (*iter2)->GetHp();
				// ** 몬스터 체력 감소
				Hp -= 2;
				//점수를 100증가
				++Sc[2];

				// 체력이 0이하일 경우
				if (Hp <= 0)
				{
					//점수를 100증가
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
					//줄어든 Hp의 값을 보내준다.
					(*iter2)->SetHp(Hp);


				// ** 삭제할 오브젝트로 지정한뒤
				iResult = 1;

				// ** 현재 반복문을 탈출.
				// ** 이유 : 총알 1개에 오브젝 1개를 삭제하기 위함. 
				break;

				//** break 가 안되면 총알이 생성된 시점에서 충돌체가 여러개일때 모두 충돌후 삭제됨.
			}
			else
				++iter2;
		}

		// ** 총알을 삭제하는 구간.
		if (iResult == 1)
			iter = BulletList->erase(iter);
		else
			++iter;
	}
	

	// ** 플레이어의 폭탄과 요정의 공격의 충돌
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



	// ** HP가 0이 되었을 경우											
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
