#include "Logo.h"
#include "Player.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BackGround.h"
#include "Start.h"


Logo::Logo()
{

}

Logo::~Logo()
{

}

void Logo::Initialize()
{
	ObjectManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectFactory<Player>::CreateObject() );

	
	// 시작 화면
	ImageList["Logo"] = (new Bitmap)->LoadBmp(L"../Resource/Logo.bmp");

	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");
	ImageList["BGR"] = (new Bitmap)->LoadBmp(L"../Resource/BGR.bmp");


	ImageList["Logo"] = (new Bitmap)->LoadBmp(L"../Resource/Logo.bmp");


	





	// ** 레이무 캐릭터 **//
	ImageList["Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/Reimu.bmp");


	// ** 레이무 기본 공격 **//
	ImageList["NomalBullet"] = (new Bitmap)->LoadBmp(L"../Resource/NomalBullet.bmp");









	// ** 유카리 캐릭터 **//
	ImageList["Yukari"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari.bmp");


	// ** 유카리 공격 모드 **//
	ImageList["On"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_On.bmp");
	// ** 유카리 비공격 모드 **//
	ImageList["Off"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_Off.bmp");

	// ** 요정 **//
	ImageList["Fairy"] = (new Bitmap)->LoadBmp(L"../Resource/Fairy.bmp");








	ImageList["Mole"] = (new Bitmap)->LoadBmp(L"../Resource/Mole.bmp");
	ImageList["Hole"] = (new Bitmap)->LoadBmp(L"../Resource/Hole.bmp");
	ImageList["Effect"] = (new Bitmap)->LoadBmp(L"../Resource/Effect.bmp");

	ImageList["on_off_Back"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Back.bmp");
	ImageList["on_off_Button"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Button.bmp");

	Object::SetImageList(ImageList);



	p_Start = new Start;
	p_Start->Initialize();
}

void Logo::Update()
{
	if (GetAsyncKeyState('A'))
		SceneManager::GetInstance()->SetScene(SCENEID::MENU);
}
 
void Logo::Render(HDC _hdc)
{

	p_Start->Render(ImageList["Buffer"]->GetMemDC());



	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		ImageList["Buffer"]->GetMemDC(),
		0, 0,
		SRCCOPY);
}

void Logo::Release()
{

}
