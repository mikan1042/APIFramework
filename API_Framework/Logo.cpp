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

	
	// ** ���� ȭ��
	ImageList["Logo"] = (new Bitmap)->LoadBmp(L"../Resource/Logo.bmp");

	// ** Buffer �� ���
	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");
	ImageList["BGR"] = (new Bitmap)->LoadBmp(L"../Resource/BGR.bmp");

	// ** ü��,��ź UI
	ImageList["Hp"] = (new Bitmap)->LoadBmp(L"../Resource/Hp.bmp");
	ImageList["U_Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Boom.bmp");
	ImageList["BossHp"] = (new Bitmap)->LoadBmp(L"../Resource/BossHp.bmp");




	// ** �� ��� �� ������ ������
	ImageList["Power"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Power.bmp");
	ImageList["Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Boom.bmp");



	// ** ä��â
	ImageList["Chat"] = (new Bitmap)->LoadBmp(L"../Resource/Chat.bmp");
	// ** ���̹��� �Ϸ���Ʈ
	ImageList["C_Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/C_Reimu.bmp");
	// ** ������ �Ϸ���Ʈ
	ImageList["C_Ligle"] = (new Bitmap)->LoadBmp(L"../Resource/C_Ligle.bmp");






	// ** ���̹� ĳ���� **//
	ImageList["Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/Reimu.bmp");


	// ** ���̹� �⺻ ���� **//
	ImageList["NomalBullet"] = (new Bitmap)->LoadBmp(L"../Resource/NomalBullet.bmp");
	ImageList["guidedBullet"] = (new Bitmap)->LoadBmp(L"../Resource/guidedBullet.bmp");

	// ** ���̹� ��ź ���� **//
	ImageList["Reimu_Boom"] = (new Bitmap)->LoadBmp(L"../Resource/player_Boom.bmp");




	




	// ** ��ī�� ĳ���� **//
	ImageList["Yukari"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari.bmp");


	// ** ��ī�� ���� ��� **//
	ImageList["On"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_On.bmp");
	// ** ��ī�� ����� ��� **//
	ImageList["Off"] = (new Bitmap)->LoadBmp(L"../Resource/Yukari_AT_Off.bmp");

	// ** ���� **//
	ImageList["FairyEnemy"] = (new Bitmap)->LoadBmp(L"../Resource/Fairy.bmp");

	
	// ** ������ ���� **//
	ImageList["Enemy_Bullet"] = (new Bitmap)->LoadBmp(L"../Resource/Enemy_Bullet.bmp");




	// ** ���� **//
	ImageList["Boss"] = (new Bitmap)->LoadBmp(L"../Resource/Boss.bmp");

	ImageList["on_off_Back"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Back.bmp");
	ImageList["on_off_Button"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Button.bmp");

	Object::SetImageList(ImageList);


	// ** ����ȭ�� ** //
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
	// ** ����ȭ�� ** //
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
