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

	
	// ** 시작 화면
	ImageList["Logo"] = (new Bitmap)->LoadBmp(L"../Resource/Logo.bmp");

	// ** Buffer 및 배경
	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");
	ImageList["BGR"] = (new Bitmap)->LoadBmp(L"../Resource/BGR.bmp");

	// ** 체력,폭탄 UI
	ImageList["Hp"] = (new Bitmap)->LoadBmp(L"../Resource/Hp.bmp");
	ImageList["U_Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Boom.bmp");
	ImageList["BossHp"] = (new Bitmap)->LoadBmp(L"../Resource/BossHp.bmp");




	// ** 적 사망 시 나오는 아이템
	ImageList["Power"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Power.bmp");
	ImageList["Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Boom.bmp");



	// ** 채팅창
	ImageList["Chat"] = (new Bitmap)->LoadBmp(L"../Resource/Chat.bmp");
	// ** 레이무의 일러스트
	ImageList["C_Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/C_Reimu.bmp");
	// ** 리글의 일러스트
	ImageList["C_Ligle"] = (new Bitmap)->LoadBmp(L"../Resource/C_Ligle.bmp");






	// ** 레이무 캐릭터 **//
	ImageList["Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/Reimu.bmp");


	// ** 레이무 기본 공격 **//
	ImageList["NomalBullet"] = (new Bitmap)->LoadBmp(L"../Resource/NomalBullet.bmp");
	ImageList["guidedBullet"] = (new Bitmap)->LoadBmp(L"../Resource/guidedBullet.bmp");

	// ** 레이무 폭탄 공격 **//
	ImageList["Reimu_Boom"] = (new Bitmap)->LoadBmp(L"../Resource/player_Boom.bmp");




	




	// ** 유카리 캐릭터 **//
	ImageList["Yukari"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari.bmp");


	// ** 유카리 공격 모드 **//
	ImageList["On"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_On.bmp");
	// ** 유카리 비공격 모드 **//
	ImageList["Off"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_Off.bmp");

	// ** 요정 **//
	ImageList["FairyEnemy"] = (new Bitmap)->LoadBmp(L"../Resource/Fairy.bmp");

	
	// ** 요정의 공격 **//
	ImageList["Enemy_Bullet"] = (new Bitmap)->LoadBmp(L"../Resource/Enemy_Bullet.bmp");




	// ** 보스 **//
	ImageList["Boss"] = (new Bitmap)->LoadBmp(L"../Resource/Boss.bmp");

	ImageList["on_off_Back"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Back.bmp");
	ImageList["on_off_Button"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Button.bmp");

	Object::SetImageList(ImageList);


	// ** 시작화면 ** //
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
	// ** 시작화면 ** //
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
