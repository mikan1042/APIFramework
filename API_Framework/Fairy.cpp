#include "Fairy.h"

#include "Object.h"
#include "ObjectManager.h"

Fairy::Fairy()
{

}

Fairy::~Fairy()
{

}


void Fairy::Initialize()
{
	Speed = 1.5f;

	DrawKey = "Fairy";

	ImageList = Object::GetImageList();

}

int Fairy::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}


void Fairy::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(600),
		int(0),
		int(25),
		int(25),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(25),
		int(25),
		RGB(255, 0, 255));
}

void Fairy::Release()
{

}
