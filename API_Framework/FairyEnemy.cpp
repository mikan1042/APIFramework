#include "FairyEnemy.h"

#include "Object.h"
#include "ObjectManager.h"

FairyEnemy::FairyEnemy()
{

}

FairyEnemy::~FairyEnemy()
{

}


void FairyEnemy::Initialize()
{
	Speed = 1.5f;

	DrawKey = "FairyEnemy";

	ImageList = Object::GetImageList();

}

int FairyEnemy::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}


void FairyEnemy::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - 50),
		int(RealObject->GetPosition().y - 50),
		int(25),
		int(25),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(25),
		int(25),
		RGB(255, 0, 255));
}

void FairyEnemy::Release()
{

}
