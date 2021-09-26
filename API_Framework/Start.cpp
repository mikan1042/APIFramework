#include "Start.h"

Start::Start()
{

}

Start::~Start()
{

}


void Start::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Active = false;
}

int Start::Update()
{

	return 0;
}

void Start::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		0,
		0,
		1280,
		720,
		ImageList["Logo"]->GetMemDC(),
		0,
		0,
		1280,
		720,
		RGB(255, 0, 255));
}

void Start::Release()
{

}
