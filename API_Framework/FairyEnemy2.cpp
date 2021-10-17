#include "FairyEnemy2.h"

#include "Object.h"
#include "ObjectManager.h"

FairyEnemy2::FairyEnemy2()
{

}

FairyEnemy2::~FairyEnemy2()
{

}


void FairyEnemy2::Initialize()
{
	Speed = 5.0f;

	DrawKey = "FairyEnemy";

	ImageList = Object::GetImageList();

}

int FairyEnemy2::Update(Transform& _rTransInfo)
{

	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	return 0;
}


void FairyEnemy2::Render(HDC _hdc)
{

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(RealObject->GetPosition().x - 12.5f),
		int(RealObject->GetPosition().y - 12.5f),
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		int(RealObject->GetScale().x),
		int(RealObject->GetScale().y),
		RGB(255, 0, 255));


}

void FairyEnemy2::Release()
{

}
