#include "Logo.h"
#include "Player.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"


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


	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");




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





	ImageList["Mole"] = (new Bitmap)->LoadBmp(L"../Resource/Mole.bmp");
	ImageList["Hole"] = (new Bitmap)->LoadBmp(L"../Resource/Hole.bmp");
	ImageList["Effect"] = (new Bitmap)->LoadBmp(L"../Resource/Effect.bmp");

	ImageList["on_off_Back"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Back.bmp");
	ImageList["on_off_Button"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Button.bmp");

	Object::SetImageList(ImageList);
}

void Logo::Update()
{
	if (GetAsyncKeyState('A'))
		SceneManager::GetInstance()->SetScene(SCENEID::MENU);
}

void Logo::Render(HDC _hdc)
{
    
}

void Logo::Release()
{

}
