#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}


void BackGround::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Active = false;
}

int BackGround::Update()
{

	return 0;
}

void BackGround::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		0,
		0,
		1024,
		1024,
		ImageList["BGR"]->GetMemDC(),
		0,
		0,
		1024,
		1024,
		RGB(255, 0, 255));
}

void BackGround::Release()
{

}
