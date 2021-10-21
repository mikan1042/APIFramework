#include "Chat.h"
#include "Boss.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "ObjectFactory.h"

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
	BossStop = false;

	BossList = ObjectManager::GetInstance()->GetBossList();

}

int Chat::Update()
{
	Chat1 = ObjectManager::GetInstance()->GetPlayer()->GetChat();

	if (!BossStop)
	{
		for (vector<Object*>::iterator iter = BossList->begin();
			iter != BossList->end(); ++iter)
		{
			if ((*iter)->GetPosition().y > 130)
			{
				(*iter)->SetDirection(Vector3(0.0f, 0.0f));
				BossStop = true;
			}
		}
	}


	if (GetAsyncKeyState('Z'))
	{
		if (Time1 + 100 <= GetTickCount64())
			++Chat2;
		Time1 = GetTickCount64();
	}



	return 0;
}

void Chat::Render(HDC _hdc)
{
	if (Chat1)
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

		// 리글
		TransparentBlt(_hdc,
			550,
			250,
			128 * 1.3f,
			261 * 1.3f,
			ImageList["C_Ligle"]->GetMemDC(),
			0,
			0,
			128,
			261,
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

		// 만났을 때의 대화 출력
		{
			if (!ObjectManager::GetInstance()->GetPlayer()->GetWin())
			{
				if (Chat2 == 1)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"거봐! 아무것도 없잖아", 12);
				}
				else if (Chat2 == 2)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"밤은 이제 막 시작되었을뿐이야...", 19);
				}
				else if (Chat2 == 3)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"서두르지 말라고", 8);
				}
				else if (Chat2 == 4)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"서둘러 날 데리고 나왔으면서", 15);
					TextOut(_hdc, 150, 570, L"서두르지 말고 자시고가 어딨어!", 17);
				}
				else if (Chat2 == 5)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"보수는 비싸게 받을거니까 기억해둬", 18);
				}
				else if (Chat2 == 6)
				{
					TextOut(_hdc, 150, 515, L"???", 3);
					TextOut(_hdc, 150, 550, L"잠깐, 아까부터 아무것도 없다니", 17);
				}
				else if (Chat2 == 7)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"내가 있었잖아", 7);
					if (!ObjectManager::GetInstance()->GetPlayer()->GetBossOn())
					{
						// ** EnemyList에 보스를 추가한다.
						BossList->push_back(CreateEnemy<Boss>(500, -50, 34, 59, 724));

						ObjectManager::GetInstance()->GetPlayer()->SetBossOn(true);
					}
				}
				else if (Chat2 == 8)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"그렇게 걱정하지 않아도...", 15);
				}
				else if (Chat2 == 9)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"보수는 확실히 지불할게", 12);
				}
				else if (Chat2 == 10)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"나는 당신이 아니니까", 11);
				}
				else if (Chat2 == 11)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"잠깐잠깐잠깐", 6);
				}
				else if (Chat2 == 12)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"나를 무시하다니 배짱 한번 두둑한걸.", 20);
				}
				else if (Chat2 == 13)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"그만큼의 각오는 하고 왔단 뜻이겠지!", 20);
				}
				else if (Chat2 == 14)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"그거 개그지?", 7);
				}
				else if (Chat2 == 15)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"개그친 거야?", 7);
				}
				else if (Chat2 == 16)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"그러고보니 밤에 외출할 때", 14);
				}
				else if (Chat2 == 17)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"중요한걸 신사에 두고와버렸네", 15);
				}
				else if (Chat2 == 18)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"?", 1);
				}
				else if (Chat2 == 19)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"당신이 말하는 거 뭔지 알겠어. 모기향?", 22);
				}
				else if (Chat2 == 20)
				{
					TextOut(_hdc, 150, 515, L"리글 나이트버그", 8);
					TextOut(_hdc, 150, 550, L"반딧불이라니까!", 8);
				}
				else if (Chat2 == 21)
				{
					// 채팅모드를 종료시켜 채팅과 나오는 이미지를 제거
					ObjectManager::GetInstance()->GetPlayer()->SetChat(false);
					// 보스모드를 실행시켜 보스의 패턴을 진행할 수 있도록 한다.
					ObjectManager::GetInstance()->GetPlayer()->SetBossMode(true);

					Chat2 = 50;

				}
			}
		}


		//승리시 대화 출력
		{
			if (ObjectManager::GetInstance()->GetPlayer()->GetWin())
			{
				if (Chat2 == 51)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"정말이지, 밤은 벌레가 많아서 싫어.", 20);
				}
				else if (Chat2 == 52)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"밤에만 깨 있는 녀석이 뭔 소리래.", 19);
				}
				else if (Chat2 == 53)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"그래, 밤에 자연이 더욱 풍부하다는 소리야", 23);
				}
				else if (Chat2 == 54)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"요즘 반딧불의 수가 많이 늘었어", 17);
				}
				else if (Chat2 == 55)
				{
					TextOut(_hdc, 150, 515, L"레이무", 3);
					TextOut(_hdc, 150, 550, L"왠지 바깥세계가 좀 걱정되는데.", 17);
				}
				else if (Chat2 == 56)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"어라? 잘 알고 있네?", 12);
				}
				else if (Chat2 == 57)
				{
					TextOut(_hdc, 150, 515, L"유카리", 3);
					TextOut(_hdc, 150, 550, L"그래도 걱정 같은 걸 하는 건 당신답지 않아.", 25);
				}
			}
		}

	}
	else
	{

	}

}

void Chat::Release()
{

}

template <typename T>
Object* Chat::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;
	// 좌표, 크기 , 체력
	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}