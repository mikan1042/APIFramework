#include "UI_Hp.h"
#include "ObjectManager.h"

UI_Hp::UI_Hp()
{

}

UI_Hp::~UI_Hp()
{

}

void UI_Hp::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

}

int UI_Hp::Update()
{
	// ** �÷��̾��� ü�°��� �ǽð����� ������Ʈ�ؼ� �޾ƿ´�.
	pHp = ObjectManager::GetInstance()->GetPlayer()->GetHp();
	pBoom = ObjectManager::GetInstance()->GetPlayer()->GetBoom();



	return 0;
}

void UI_Hp::Render(HDC _hdc)
{
	// ** Hp ���
	{

	// ** ��������� ������쿡 ����� �ٲ۴�. 
	if(pHp >= 1)	TransparentBlt(_hdc, 885, 100, 12 * 2.0f, 12 * 2.0f, ImageList["Hp"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
	if (pHp >= 2)	TransparentBlt(_hdc, 910, 100, 12 * 2.0f, 12 * 2.0f, ImageList["Hp"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
	if (pHp >= 3)	TransparentBlt(_hdc, 935, 100, 12 * 2.0f, 12 * 2.0f, ImageList["Hp"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
	if (pHp >= 4)	TransparentBlt(_hdc, 960, 100, 12 * 2.0f, 12 * 2.0f, ImageList["Hp"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
	if (pHp >= 5)	TransparentBlt(_hdc, 985, 100, 12 * 2.0f, 12 * 2.0f, ImageList["Hp"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
	}

	// ** Boom ���
	{
		if (pBoom >= 1)	TransparentBlt(_hdc, 885, 130 , 12 * 2.0f, 12 * 2.0f, ImageList["U_Boom"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
		if (pBoom >= 2)	TransparentBlt(_hdc, 910, 130, 12 * 2.0f, 12 * 2.0f, ImageList["U_Boom"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
		if (pBoom >= 3)	TransparentBlt(_hdc, 935, 130, 12 * 2.0f, 12 * 2.0f, ImageList["U_Boom"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
		if (pBoom >= 4)	TransparentBlt(_hdc, 960, 130, 12 * 2.0f, 12 * 2.0f, ImageList["U_Boom"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));
		if (pBoom >= 5)	TransparentBlt(_hdc, 985,130 , 12 * 2.0f, 12 * 2.0f, ImageList["U_Boom"]->GetMemDC(), 0, 0, 12, 12, RGB(255, 0, 255));

	}

}

void UI_Hp::Release()
{

}
