#include "Chat.h"
#include "ObjectManager.h"

Chat::Chat()
{

}

Chat::~Chat()
{

}

void Chat::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Chat2 = 1;
	Time1 = GetTickCount64();

}

int Chat::Update()
{
	Chat1 = ObjectManager::GetInstance()->GetPlayer()->GetChat();


	if (GetAsyncKeyState('Z'))
	{
		if (Time1 + 200 <= GetTickCount64())
		++Chat2;
		Time1 = GetTickCount64();
	}



	return 0;
}

void Chat::Render(HDC _hdc)
{
	if (!Chat1)
	{
		// 그림 출력
		{
		// 레이무
		TransparentBlt(_hdc,
			120,
			250,
			128 * 1.3f,
			256 * 1.3f,
			ImageList["C_Reimu"]->GetMemDC(),
			0,
			0,
			128,
			256,
			RGB(255, 0, 255));

		// 채팅배경
		TransparentBlt(_hdc,
			70,
			250,
			700,
			500,
			ImageList["Chat"]->GetMemDC(),
			0,
			0,
			1280,
			720,
			RGB(255, 0, 255));
		}

		// 대화 출력
		{
			if (Chat2 == 1)
				TextOut(_hdc, 150, 550, "거봐! 아무것도 없잖아", sizeof("거봐! 아무것도 없잖아"));
			else if (Chat2 == 2)
				TextOut(_hdc, 150, 550, "밤은 이제 막 시작되었을뿐이야...", sizeof("밤은 이제 막 시작되었을뿐이야..."));
			else if (Chat2 == 3)   
				TextOut(_hdc, 150, 550, "서둘러 날 데리고 나왔으면서\n 서두르지 말고 자시고가 어딨어!", sizeof("서둘러 날 데리고 나왔으면서\n 서두르지 말고 자시고가 어딨어!"));
			else if (Chat2 == 4)   
				TextOut(_hdc, 150, 550, "보수는 비싸게 받을거니까 기억해둬", sizeof("보수는 비싸게 받을거니까 기억해둬"));
			else if (Chat2 == 5)   
				TextOut(_hdc, 150, 550, "잠깐, 아까부터 아무것도 없다니", sizeof("잠깐, 아까부터 아무것도 없다니"));
			else if (Chat2 == 6)   
				TextOut(_hdc, 150, 550, "내가 있었잖아", sizeof("내가 있었잖아"));
			else if (Chat2 == 7)   
				TextOut(_hdc, 150, 550, "그렇게 걱정하지 않아도...", sizeof("그렇게 걱정하지 않아도..."));
			else if (Chat2 == 8)   
				TextOut(_hdc, 150, 550, "보수는 확실히 지불할게 ", sizeof("보수는 확실히 지불할게 "));
			else if (Chat2 == 9)   
				TextOut(_hdc, 150, 550, "나는 당신이 아니니까", sizeof("나는 당신이 아니니까"));
			else if (Chat2 == 10)  
				TextOut(_hdc, 150, 550, "잠깐잠깐잠깐", sizeof("잠깐잠깐잠깐"));
			else if (Chat2 == 11)  
				TextOut(_hdc, 150, 550, "나를 무시하다니 배짱 한번 두둑한걸.", sizeof("나를 무시하다니 배짱 한번 두둑한걸."));
			else if (Chat2 == 12)  
				TextOut(_hdc, 150, 550, "그만큼의 각오는 하고 왔단 뜻이겠지!", sizeof("그만큼의 각오는 하고 왔단 뜻이겠지!"));
			else if (Chat2 == 13)  
				TextOut(_hdc, 150, 550, "그거 개그지?", sizeof("그거 개그지?"));
			else if (Chat2 == 14)  
				TextOut(_hdc, 150, 550, "개그친 거야?", sizeof("개그친 거야?"));
			else if (Chat2 == 15)  
				TextOut(_hdc, 150, 550, "그러고보니 밤에 외출할 때", sizeof("그러고보니 밤에 외출할 때"));
			else if (Chat2 == 16)  
				TextOut(_hdc, 150, 550, "중요한걸 신사에 두고와버렸네", sizeof("중요한걸 신사에 두고와버렸네"));
			else if (Chat2 == 17)  
				TextOut(_hdc, 150, 550, "?", sizeof("?"));
			else if (Chat2 == 18)  
				TextOut(_hdc, 150, 550, "당신이 말하는 거 뭔지 알겠어. 모기향?", sizeof("당신이 말하는 거 뭔지 알겠어. 모기향?"));
			else if (Chat2 == 19)  
				TextOut(_hdc, 150, 550, "반딧불이라니까!", sizeof("반딧불이라니까!"));
			else if (Chat2 == 20)
				Chat1 = true;
		}

	}
	else
	{

	}

}

void Chat::Release()
{

}
