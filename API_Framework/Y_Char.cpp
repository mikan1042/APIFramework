#include "Y_Char.h"
#include "ObjectManager.h"

Y_Char::Y_Char()
{

}

Y_Char::~Y_Char()
{

}


void Y_Char::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(33.0f, 33.0f);

	Player = ObjectManager::GetInstance()->GetPlayer();
	Active = false;
}

int Y_Char::Update()
{
	// 플레이어의 위치를 받아온다.
	TransInfo.Position = Player->GetPosition();
	TransInfo.Direction = Player->GetPosition();


	

	return 0;
}

void Y_Char::Render(HDC _hdc)
{
	if(Player->GetPlayer_Swap())
	TransparentBlt(_hdc,
		int(TransInfo.Position.x - (32 / 2)),
		int(TransInfo.Position.y - (43 / 2) - 300),
		int(32),
		int(43),
		ImageList["Off"]->GetMemDC(),
		0, 0,
		int(32),
		int(43),
		RGB(255, 0, 255));
}

void Y_Char::Release()
{

}
