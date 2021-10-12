#include "Reimu_Boom.h"

#include "Object.h"
#include "ObjectManager.h"
#include "MathManager.h"


Reimu_Boom::Reimu_Boom()
{

}

Reimu_Boom::~Reimu_Boom()
{

}

void Reimu_Boom::Initialize()
{
	Speed = 7.0f;

	DrawKey = "Reimu_Boom";
	ImageList = Object::GetImageList();

	Time1 = GetTickCount64();

}

int Reimu_Boom::Update(Transform& _rTransInfo)
{

	float vx = cos(-angle * PI / 180.0f);
	float vy = sin(-angle * PI / 180.0f);


	_rTransInfo.Position.x += vx * Speed;
	_rTransInfo.Position.y += vy * Speed;


	Target = ObjectManager::GetInstance()->GetTarget(RealObject->GetPosition());

	if (Target)
	{
		_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());

		_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
		_rTransInfo.Position.y += _rTransInfo.Direction.y;
	}




	return 0;
}

void Reimu_Boom::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y - (RealObject->GetScale().y / 2)),
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));
}

void Reimu_Boom::Release()
{

}

