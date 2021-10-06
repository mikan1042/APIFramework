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


	Rectangle(_hdc,
		int(RealObject->GetPosition().x - (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y - (RealObject->GetScale().y / 2)),
		int(RealObject->GetPosition().x + (RealObject->GetScale().x / 2)),
		int(RealObject->GetPosition().y + (RealObject->GetScale().y / 2)));
	

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

void FairyEnemy::Release()
{

}
