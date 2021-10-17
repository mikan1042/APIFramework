#include "PlayerLife.h"
#include "ObjectManager.h"


PlayerLife::PlayerLife()
{

}

PlayerLife::~PlayerLife()
{

}

void PlayerLife::Initialize()
{
	TransInfo.Position = Vector3(ObjectManager::GetInstance()->GetPlayer()->GetPosition());
	TransInfo.Scale = Vector3(8.0f, 8.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(TransInfo.Scale.x, TransInfo.Scale.y);

}

int PlayerLife::Update()
{
	TransInfo.Position = Vector3(ObjectManager::GetInstance()->GetPlayer()->GetPosition());
	return 0;
}

void PlayerLife::Render(HDC _hdc)
{
	Rectangle(_hdc,
		int(TransInfo.Position.x - (TransInfo.Scale.x / 2) - 2 ),
		int(TransInfo.Position.y - (TransInfo.Scale.y / 2) - 2),
		int(TransInfo.Position.x + (TransInfo.Scale.x / 2)),
		int(TransInfo.Position.y + (TransInfo.Scale.y / 2)));

}

void PlayerLife::Release()
{
}
