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


Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(420.0f, 640.0f);
	TransInfo.Scale = Vector3(33.0f, 49.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(TransInfo.Scale.x, TransInfo.Scale.y);

	Active = false;

	Frame = 0;

	Time1 = GetTickCount64();

	// ** 플레이어의 모습
	Player_Swap = false;
	// ** 유카리 모드일때 공격
	Yukari_AT = false;

	Offset = Vector3(0.0f, 0.0f);

	BulletList = ObjectManager::GetInstance()->GetBulletList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	ItemList = ObjectManager::GetInstance()->GetItemList();

	Power = 2;
	Boom = 3;

}

int Player::Update()
{


	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);

	// ** 두 캐릭터 공통으로 사용 ** //

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	// ** 왼쪽으로 이동 ** //
	if (dwKey & KEY_LEFT)
		TransInfo.Position.x -= Speed;
	// ** 오른쪽으로 이동 ** //
	if (dwKey & KEY_RIGHT)
		TransInfo.Position.x += Speed;
	// ** 위로 이동 ** //
	if (dwKey & KEY_UP)
		TransInfo.Position.y -= Speed;
	// ** 아래로 이동 ** //
	if (dwKey & KEY_DOWN)
		TransInfo.Position.y += Speed;

	// ** 쉬프트 키를 누르고 있을경우 캐릭터가 교체 ** //
	if (GetAsyncKeyState(VK_SHIFT))
		Player_Swap = true;
	else
		Player_Swap = false;


	// 캐릭터가 레이무 일 경우 ** //
	if (!Player_Swap)
	{
		//** 레이무 기본 설정 ** //
		Speed = 5.0f;

		 
		// ** Z키를 누를경우
		if (GetAsyncKeyState('Z'))
		{
			if (Power == 1)
			{
				if (Time1 + 200 <= GetTickCount64())
				{
					BulletList->push_back(CreateBullet<LV1_Bullet>(0, Vector3(13.0f, 14.0f)));
					Time1 = GetTickCount64();
				}
			}
			if (Power == 2)
			{
				if (Time1 + 200 <= GetTickCount64())
				{
					BulletList->push_back(CreateBullet<LV1_Bullet>(0, Vector3(13.0f, 14.0f)));
					BulletList->push_back(CreateBullet<LV2_Bullet>(60, Vector3(13.0f, 14.0f)));
					BulletList->push_back(CreateBullet<LV2_Bullet>(120, Vector3(13.0f, 14.0f)));
					Time1 = GetTickCount64();
				}
			}
		}
		if (GetAsyncKeyState('C'))
		{
			if (Time1 + 200 <= GetTickCount64())
			{
				EnemyList->push_back(CreateEnemy<Boss>(300, 200,46,67,100));
				Time1 = GetTickCount64();
			}
		}

	}
	// ** 캐릭터가 유카리 일 경우 ** //
	else
	{
		//** 유카리 기본 설정 ** //
		Speed = 1.5f;




		// ** Z키를 누를경우 공격 ** //
		if (GetAsyncKeyState('Z'))
		{
			if (Time1 + 200 <= GetTickCount64())
			{
				Yukari_AT = true;

				Target = ObjectManager::GetInstance()->GetTarget(TransInfo.Position);

				if (EnemyList != nullptr)
					Yukari_AT = false;

				if (Target)
				{
					TransInfo.Direction = MathManager::GetDirection(TransInfo.Position, Target->GetPosition());

					TransInfo.Position.x += TransInfo.Direction.x * Speed;
					TransInfo.Position.x += TransInfo.Direction.x * Speed;

				}

				Time1 = GetTickCount64();

			}
		}
		else
			Yukari_AT = false;
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
	//플레이어의 판정박스
	Rectangle(_hdc,
		int(Collider.Position.x - (Collider.Scale.x / 2)),
		int(Collider.Position.y - (Collider.Scale.y / 2)),
		int(Collider.Position.x + (Collider.Scale.x / 2)),
		int(Collider.Position.y + (Collider.Scale.y / 2)));


	// ** 레이무 인 경우 출력방식 ** //
	if (!Player_Swap)
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
			int(TransInfo.Position.y - (TransInfo.Scale.y / 2)),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			ImageList["Reimu"]->GetMemDC(),
			int(TransInfo.Scale.x * Frame),
			int(TransInfo.Scale.y * 0),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			RGB(255, 0, 255));
	}
	// ** 유카리 인 경우 출력방식 ** //
	else
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
			int(TransInfo.Position.y - (TransInfo.Scale.y / 2)),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			ImageList["Yukari"]->GetMemDC(),
			int(TransInfo.Scale.x * Frame),
			int(TransInfo.Scale.y * 0),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			RGB(255, 0, 255));

		if (!Yukari_AT)
		{
			TransparentBlt(_hdc,
				int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
				int(TransInfo.Position.y - (TransInfo.Scale.y / 2)- 60),
				int(32),
				int(43),
				ImageList["Off"]->GetMemDC(),
				int(TransInfo.Scale.x * Frame),
				int(TransInfo.Scale.y * 0),
				int(32),
				int(43),
				RGB(255, 0, 255));
		}
		//	else
		//	{
		//		TransparentBlt(_hdc,
		//			int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
		//			int(TransInfo.Position.y - (TransInfo.Scale.y / 2) - 60),
		//			int(33),
		//			int(33),
		//			ImageList["On"]->GetMemDC(),
		//			int(TransInfo.Scale.x * Frame),
		//			int(TransInfo.Scale.y * 0),
		//			int(33),
		//			int(33),
		//			RGB(255, 0, 255));
		//	}
	}
}

void Player::Release()
{
	
}


template <typename T>
Object* Player::CreateBullet(float _x, Vector3 _sPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(TransInfo.Position, _sPos, _x, pBridge);

	return pBullet;
}

template <typename T>
Object* Player::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;

	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}