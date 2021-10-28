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
	ImageList["Menu"] = (new Bitmap)->LoadBmp(L"../Resource/Menu.bmp");
	ImageList["Start"] = (new Bitmap)->LoadBmp(L"../Resource/Start.bmp");
	ImageList["Start1"] = (new Bitmap)->LoadBmp(L"../Resource/Start1.bmp");
	ImageList["Quit"] = (new Bitmap)->LoadBmp(L"../Resource/Quit.bmp");
	ImageList["Quit1"] = (new Bitmap)->LoadBmp(L"../Resource/Quit1.bmp");
	ImageList["GG"] = (new Bitmap)->LoadBmp(L"../Resource/GameOver.bmp");
	ImageList["GC"] = (new Bitmap)->LoadBmp(L"../Resource/GameClear.bmp");

	// ** Buffer �� ���
	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");
	ImageList["BGR"] = (new Bitmap)->LoadBmp(L"../Resource/BGR.bmp");

	// ** ü��,��ź UI
	ImageList["Hp"] = (new Bitmap)->LoadBmp(L"../Resource/Hp.bmp");
	ImageList["U_Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Boom.bmp");
	ImageList["BossHp"] = (new Bitmap)->LoadBmp(L"../Resource/BossHp.bmp");

	ImageList["Test"] = (new Bitmap)->LoadBmp(L"../Resource/Test.bmp");
	ImageList["LNB"] = (new Bitmap)->LoadBmp(L"../Resource/LNB.bmp");



	ImageList["Ligle"] = (new Bitmap)->LoadBmp(L"../Resource/Ligle_sp.bmp");
	ImageList["Boss_Ld"] = (new Bitmap)->LoadBmp(L"../Resource/Boss_Ld.bmp");



	// ** �� ��� �� ������ ������
	ImageList["Power"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Power.bmp");
	ImageList["Boom"] = (new Bitmap)->LoadBmp(L"../Resource/Item_Boom.bmp");



	// ** ä��â
	ImageList["Chat"] = (new Bitmap)->LoadBmp(L"../Resource/Chat.bmp");
	// ** ���̹��� �Ϸ���Ʈ
	ImageList["C_Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/C_Reimu.bmp");
	// ** ��ī���� �Ϸ���Ʈ
	ImageList["C_Yukari"] = (new Bitmap)->LoadBmp(L"../Resource/C_Yukari.bmp");
	// ** ������ �Ϸ���Ʈ
	ImageList["C_Ligle"] = (new Bitmap)->LoadBmp(L"../Resource/C_Ligle.bmp");






	// ** ���̹� ĳ���� **//
	ImageList["Reimu"] = (new Bitmap)->LoadBmp(L"../Resource/Reimu.bmp");


	// ** ���̹� �⺻ ���� **//
	ImageList["NomalBullet"] = (new Bitmap)->LoadBmp(L"../Resource/NomalBullet.bmp");
	ImageList["guidedBullet"] = (new Bitmap)->LoadBmp(L"../Resource/guidedBullet1.bmp");

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
	ImageList["Enemy_Bullet1"] = (new Bitmap)->LoadBmp(L"../Resource/Enemy_Bullet1.bmp");




	// ** ���� **//
	ImageList["Boss"] = (new Bitmap)->LoadBmp(L"../Resource/Boss.bmp");

	ImageList["on_off_Back"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Back.bmp");
	ImageList["on_off_Button"] = (new Bitmap)->LoadBmp(L"../Resource/on_off_Button.bmp");


	ImageList["Number"] = (new Bitmap)->LoadBmp(L"../Resource/Number.bmp");
	ImageList["MAX"] = (new Bitmap)->LoadBmp(L"../Resource/MAX.bmp");


	Object::SetImageList(ImageList);


	// ** ����ȭ�� ** //
	p_Start = new Start;
	p_Start->Initialize();

	Time1 = GetTickCount64();

}

void Logo::Update()
{
	if (Time1 + 2000 <= GetTickCount64())
	{
		SceneManager::GetInstance()->SetScene(SCENEID::MENU);
		Time1 = GetTickCount64();
	}
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
