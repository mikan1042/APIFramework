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
	Speed = 1.5f;

	DrawKey = "Boss";

	ImageList = Object::GetImageList();

}

int Boss::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}


void Boss::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(500),
		int(100),
		int(46),
		int(67),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(46),
		int(67),
		RGB(255, 0, 255));
}

void Boss::Release()
{

}
