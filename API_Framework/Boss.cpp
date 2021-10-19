#include "Boss.h"

#include "Object.h"
#include "ObjectManager.h"

Boss::Boss()
{

}

Boss::~Boss()
{

}


void Boss::Initialize()
{
	Speed = 3.0f;

	DrawKey = "Ligle";

	ImageList = Object::GetImageList();

	AmTime = GetTickCount64();

	Anime = 0;

}

int Boss::Update(Transform& _rTransInfo)
{
	// 애니메이션을 진행
	if (AmTime + 170 <= GetTickCount64())
	{
		Anime += 34;
		AmTime = GetTickCount64();

		if (Anime >= 170)
			Anime = 0;
	}


	if (ObjectManager::GetInstance()->GetPlayer()->GetBossMode())
	{
		if (Speed == 0.0f)
		{
			Speed = 5.0f;
			//	_rTransInfo.Direction = Getangle(float(rand() % 300 + 0));
				_rTransInfo.Direction = Getangle(-500);
		}
		else if (Speed < 0)
		{
			Speed = 0;
		}
		else if (Speed > 0)
		{
		 Speed -= 0.05f;
		}


		 if (_rTransInfo.Position.x < 90) { _rTransInfo.Position.x = 90; }
		 if (_rTransInfo.Position.x > 600) { _rTransInfo.Position.x = 600; }
		 if (_rTransInfo.Position.y < 50) { _rTransInfo.Position.y = 50; }




	}



	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}


void Boss::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y - (RealObject->GetScale().y / 2)),
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		ImageList[DrawKey]->GetMemDC(),
		Anime, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(670),
		int(45),
		int(16),
		ImageList["Boss_Ld"]->GetMemDC(),
		0, 0,
		int(45),
		int(16),
		RGB(255, 0, 255));

}

void Boss::Release()
{

}


Vector3 Boss::Getangle(float _x)
{
	float vx = cos(-_x * PI / 180.0f);
	float vy = sin(-_x * PI / 180.0f);

	Vector3 VV(vx, vy);
	return VV;
}