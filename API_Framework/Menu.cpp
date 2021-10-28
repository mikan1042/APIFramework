#include "Menu.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Object.h"
#include "SoundManager.h"


Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::Initialize()
{
	ImageList = Object::GetImageList();
	SQ = true;

	SoundManager::GetInstance()->Initialize();

	SoundManager::GetInstance()->LoadSoundDate("../Resource/Sound/se_cancel00.wav", "se_cancel00");
}

void Menu::Update()
{
	if (GetAsyncKeyState(VK_UP))
	{
		SQ = true;
		SoundManager::GetInstance()->OnPlaySound("se_cancel00");

	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		SQ = false;
		SoundManager::GetInstance()->OnPlaySound("se_cancel00");

	}


	if (SQ && GetAsyncKeyState('Z'))
		SceneManager::GetInstance()->SetScene(SCENEID::STAGE);
	if (!SQ && GetAsyncKeyState('Z'))
	{
	};
}

void Menu::Render(HDC _hdc)
{
	TransparentBlt(ImageList["Buffer"]->GetMemDC(),0,0,1280,720,ImageList["Menu"]->GetMemDC(),0,0,1280,720,RGB(255, 0, 255));

	if (SQ)
	{
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), 1050, 550, 167, 74, ImageList["Start"]->GetMemDC(), 0, 0, 167, 74, RGB(255, 0, 255));
		TransparentBlt(ImageList["Buffer"]->GetMemDC(), 1000, 610, 167, 74, ImageList["Quit1"]->GetMemDC(), 0, 0, 167, 74, RGB(255, 0, 255));
	}
	else
	{
		 TransparentBlt(ImageList["Buffer"]->GetMemDC(), 1020, 550, 167, 74, ImageList["Start1"]->GetMemDC(), 0, 0, 167, 74, RGB(255, 0, 255));
		 TransparentBlt(ImageList["Buffer"]->GetMemDC(), 1050, 610, 167, 74, ImageList["Quit"]->GetMemDC(), 0, 0, 167, 74, RGB(255, 0, 255));
	}



	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		ImageList["Buffer"]->GetMemDC(),
		0, 0,
		SRCCOPY);


}

void Menu::Release()
{

}
