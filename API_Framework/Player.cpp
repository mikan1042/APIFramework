#include "Player.h"

#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "MathManager.h"

#include "Bullet.h"
#include "LV1_Bullet.h"
#include "LV2_Bullet.h"
#include "Yukari_Bullet.h"

#include "Enemy.h"
#include "FairyEnemy.h"
#include "Boss.h"
#include "Power.h"
#include "Reimu_Boom.h"
#include "SoundManager.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(420.0f, 640.0f);
	TransInfo.Scale = Vector3(28.0f, 43.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(TransInfo.Scale.x, TransInfo.Scale.y);

	Active = false;

	Frame = 0;

	Time1 = GetTickCount64();
	Time2 = GetTickCount64();

	// ** 플레이어의 모습
	Player_Swap = false;

	BoomOn = false;
	Chat = false;
	GodMode = false;
	BossMode = false;
	BossOn = false;
	Win = false;
	angle = 0;

	Offset = Vector3(0.0f, 0.0f);

	BulletList = ObjectManager::GetInstance()->GetBulletList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	ItemList = ObjectManager::GetInstance()->GetItemList();
	PlayerBoom = ObjectManager::GetInstance()->GetPlayerBoom();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();

	Power = 1;
	Boom = 3;
	Hp = 5;

	Anime = 0;
	Anime1 = 0;
	God = 0;

}

int Player::Update()
{

	if (AmTime + 170 <= GetTickCount64())
	{
		Anime += 28;
		Anime1 += 32;
		AmTime = GetTickCount64();

		if (Anime >= 112)
			Anime = 0;
		if (Anime1 >= 128)
			Anime1 = 0;
	}

	// 플레이어의 무적판정
	if (ObjectManager::GetInstance()->GetPlayer()->GetGodMode())
	{
		if (Time2 + 1000 <= GetTickCount64())
		{
			++God;
			Time2 = GetTickCount64();
		}
		if(God == 2)
			ObjectManager::GetInstance()->GetPlayer()->SetGodMode(false);
	}
	else
		God = 0;

	// 충돌 좌표 = 현재 좌표 
	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);

	// ** 두 캐릭터 공통으로 사용 ** //

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_LEFT)
		TransInfo.Position.x -= Speed;
	if (dwKey & KEY_RIGHT)
		TransInfo.Position.x += Speed;
	if (dwKey & KEY_UP)
		TransInfo.Position.y -= Speed;
	if (dwKey & KEY_DOWN)
		TransInfo.Position.y += Speed;

	if (GetAsyncKeyState(VK_SHIFT))
		ObjectManager::GetInstance()->GetPlayer()->SetPlayer_Swap(true);
	else
		ObjectManager::GetInstance()->GetPlayer()->SetPlayer_Swap(false);
	


	// 이야기진행여부
	if (ObjectManager::GetInstance()->GetPlayer()->GetChat())
	{

	}
	else
	{
		// 캐릭터가 레이무 일 경우 ** //
		if (!ObjectManager::GetInstance()->GetPlayer()->GetPlayer_Swap())
		{
			//** 레이무 기본 설정 ** //
			Speed = 5.0f;


			// ** Z키를 누를경우
			if (GetAsyncKeyState('Z'))
			{
				// ** 파워가 1이상 30 이하일 경우
				if (Power >= 1)
				{
					// ** 0.2초마다 실행한다.
					if (Time1 + 200 <= GetTickCount64())
					{
						SoundManager::GetInstance()->OnPlaySound("reimu_at");
						// ** BulletLIst에 탄막을 추가한다.
						BulletList->push_back(CreateBullet<LV1_Bullet>(0, Vector3(13.0f, 14.0f), TransInfo.Position));
						if (Power >= 10)
						{
							BulletList->push_back(CreateBullet<LV2_Bullet>(60, Vector3(13.0f, 14.0f), TransInfo.Position));
							BulletList->push_back(CreateBullet<LV2_Bullet>(120, Vector3(13.0f, 14.0f), TransInfo.Position));
						}
						Time1 = GetTickCount64();
					}
				}
			}
			// ** X키를 누를경우
			if (GetAsyncKeyState('X'))
			{
				// 폭탄이 있는경우
				if (Boom > 0)
				{
					// 폭탄 트리거가 false일 경우
					if (!BoomOn)
					{
						SoundManager::GetInstance()->OnPlaySound("boom");

						//폭탄이 중복해서 생성되지 못하도록 입력 딜레이를 준다. 
							//폭탄을 생성한다.
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));

						// 폭탄의 개수를 하나 줄인다
						--Boom;
						// 줄인 폭탄의 개수를 보내준다.
						ObjectManager::GetInstance()->GetPlayer()->SetBoom(Boom);
						// 폭탄 트리거를 true를 시켜 연속해서 폭탄을 사용하지 못하게 막는다
						BoomOn = true;
						ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
					}
					// 폭탄 트리거가 true일 경우
					else
					{
						// 폭탄을 사용한뒤 2초후 다시 폭탄을 사용할 수 있도록 한다.
						if (Time2 + 2000 <= GetTickCount64())
						{
							//다시 폭탄을 사용할 수 있도록 트리거를 false로 변경한다.
							BoomOn = false;
							Time2 = GetTickCount64();
						}
					}

				}

			}

		}
		// ** 캐릭터가 유카리 일 경우 ** //
		else
		{
			//** 유카리 기본 설정 ** //
			Speed = 1.5f;
			if (GetAsyncKeyState('Z'))
			{
				if (Power >= 1)
				{
					if (Time1 + 150 <= GetTickCount64())
					{
						SoundManager::GetInstance()->OnPlaySound("reimu_at");
						if (Power >= 10)
						{
							BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), (Vector3(TransInfo.Position.x - 10.0f, TransInfo.Position.y + 10.0f))));
							BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), (Vector3(TransInfo.Position.x + 10.0f, TransInfo.Position.y + 10.0f))));
						}
						BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), TransInfo.Position));

						Time1 = GetTickCount64();
					}
				}
			}
			if (GetAsyncKeyState('X'))
			{
				// 폭탄이 있는경우
				if (Boom > 0)
				{
					// 폭탄 트리거가 false일 경우
					if (!BoomOn)
					{
						SoundManager::GetInstance()->OnPlaySound("boom");

						//폭탄이 중복해서 생성되지 못하도록 입력 딜레이를 준다. 
							//폭탄을 생성한다.
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));

						// 폭탄의 개수를 하나 줄인다
						--Boom;
						// 줄인 폭탄의 개수를 보내준다.
						ObjectManager::GetInstance()->GetPlayer()->SetBoom(Boom);
						// 폭탄 트리거를 true를 시켜 연속해서 폭탄을 사용하지 못하게 막는다
						BoomOn = true;
						ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
					}
					// 폭탄 트리거가 true일 경우
					else
					{
						// 폭탄을 사용한뒤 2초후 다시 폭탄을 사용할 수 있도록 한다.
						if (Time2 + 2000 <= GetTickCount64())
						{
							//다시 폭탄을 사용할 수 있도록 트리거를 false로 변경한다.
							BoomOn = false;
							Time2 = GetTickCount64();
						}
					}

				}

			}


		}
	}


		// ** 캐릭터가 화면을 벗어나지 못하게 하기위해 설정 ** //
		{
			if (TransInfo.Position.x <= 60)
				TransInfo.Position.x = 60;
			if (TransInfo.Position.x >= 785)
				TransInfo.Position.x = 785;
			if (TransInfo.Position.y >= 670)
				TransInfo.Position.y = 670;
			if (TransInfo.Position.y <= 25)
				TransInfo.Position.y = 25;
		}



			return 0;
		
	
}

void Player::Render(HDC _hdc)
{
	// ** 레이무 인 경우 출력방식 ** //
	if (!ObjectManager::GetInstance()->GetPlayer()->GetPlayer_Swap())
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
			int(TransInfo.Position.y - (TransInfo.Scale.y / 2)),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			ImageList["Reimu"]->GetMemDC(),
			Anime,
			0,
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			RGB(255, 0, 255));
	}
	// ** 유카리 인 경우 출력방식 ** //
	else
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (32/2)),
			int(TransInfo.Position.y - (45/2)),
			int(32),
			int(45),
			ImageList["Yukari"]->GetMemDC(),
			Anime1,
			0,
			int(32),
			int(45),
			RGB(255, 0, 255));


	}
}

void Player::Release()
{

}


template <typename T>
Object* Player::CreateBullet(float _x, Vector3 _sPos, Vector3 _vPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(_vPos, _sPos, _x, pBridge);

	return pBullet;
}

template <typename T>
Object* Player::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;

	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}