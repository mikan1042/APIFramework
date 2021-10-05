#pragma once
#include "Boom.h"

#include "Object.h"
#include "ObjectManager.h"

Boom::Boom()
{

}

Boom::~Boom()
{

}


void Boom::Initialize()
{
	Speed = -3.0f;

	DrawKey = "Boom";

	ImageList = Object::GetImageList();


}

int Boom::Update(Transform& _rTransInfo)
{

	if (Speed >= 2.0f)
		Speed == 2.0f;
	else
		Speed += 0.1f;

	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;


	return 0;
}


void Boom::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - 23.0f),
		int(RealObject->GetPosition().y - 33.5f),
		int(32),
		int(32),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(32),
		int(32),
		RGB(255, 0, 255));
}

void Boom::Release()
{

}
