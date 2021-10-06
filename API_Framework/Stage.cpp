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

	// ** 오브젝트 매니저에서 총알 리스트를 받아옴. (포인터로...)
	BulletList = ObjectManager::GetInstance()->GetBulletList();

	// ** 오브젝트 매니저에서 몬스터 리스트를 받아옴. (포인터로...)
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();

	// ** 오브젝트 매니저에서 아이템 리스트를 받아옴. (포인터로...)
	ItemList = ObjectManager::GetInstance()->GetItemList();

	// **  오브젝트 매니저에서 몬스터탄막 리스트를 받아옴. (포인터로...)
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();

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






	//------------------------------------------------------




}

void Stage::Update()
{
	// ** 업데이트를 실행시켜준다.
	m_Schedule->Update();

	m_pPlayer->Update();

	m_pButton->Update();


	// ** EnemyList를 순회한다.
	for (vector<Object*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		// ** 적과 플레이어가 충돌했을경우
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			// ** 콘솔에 대화를 출력
			cout << "플레이어의 죽음" << endl;
		}
	}
	// ** ItemList를 순회한다.
	for (vector<Object*>::iterator iter = ItemList->begin();
		iter != ItemList->end();)
	{
		// ** 아이템과 플레이어가 충돌했을경우 
		if (CollisionManager::RectCollision((*iter), m_pPlayer))
		{
			string Key = (*iter)->GetDrawKey();

			if (Key == "Power")
			{
				int Pow = m_pPlayer->GetPower();
				++Pow;
				m_pPlayer->SetPower(Pow);
				cout << "파워" << endl;
			}
			if (Key == "Boom")
				cout << "폭탄" << endl;

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



	// ** 총알 리스트의 progress
	for (vector<Object*>::iterator iter = BulletList->begin();
		iter != BulletList->end(); )
	{
		// ** 총알이 화면 밖을 넘어가게 되면 reutrn 1 을 반환 하고, 
		// ** iResult == 1이면 총알은 삭제됨.
		int iResult = (*iter)->Update();

 		if ((*iter)->GetPosition().y <= 10)
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
				// 체력이 0이하일 경우
				if (Hp <= 0)
				{
					srand((unsigned)time(NULL));
					int Ritem = (rand() % 2) + 1;


					if(Ritem == 1)
					ItemList->push_back(CreateItem<Power>((*iter2)->GetPosition(), "Power"));
					else if (Ritem == 2)
					ItemList->push_back(CreateItem<Boom>((*iter2)->GetPosition(),"Boom"));


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

		// ** 총알을 삭제하는 구간.
		if (iResult == 1)
			iter = BulletList->erase(iter);
		else
			++iter;
	}

	//플레이어와 요정의 공격이 부딪혔을경우
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
