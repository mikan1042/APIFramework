#include "Player.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Bullet.h"
#include "LV1_Bullet.h"
#include "Yukari_Bullet.h"


Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(WindowsWidth / 2, WindowsHeight / 2);
	TransInfo.Scale = Vector3(33.0f, 49.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(120.0f, 60.0f);

	Active = false;

	Frame = 0;
	OldPositionY = 0.0f;
	JumpSpeed = 8.0f;
	JumpTime = 0.0f;

	Player_Swap = false;

	Offset = Vector3(0.0f, 0.0f);

	BulletList = ObjectManager::GetInstance()->GetBulletList();
}

int Player::Update()
{

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
		Speed = 4.0f;




		// ** Z키를 누를경우 공격 ** //
		if (GetAsyncKeyState('Z'))
			BulletList->push_back(CreateBullet<LV1_Bullet>());
	}
	// ** 캐릭터가 유카리 일 경우 ** //
	else
	{
		//** 유카리 기본 설정 ** //
		Speed = 2.0f;




		// ** Z키를 누를경우 공격 ** //
		if (GetAsyncKeyState('Z'))
			BulletList->push_back(CreateBullet<Yukari_Bullet>());
	}





	return 0;
}

void Player::Render(HDC _hdc)
{
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
	}
}

void Player::Release()
{
	
}


template <typename T>
Object* Player::CreateBullet()
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(TransInfo.Position, pBridge);

	return pBullet;
}
