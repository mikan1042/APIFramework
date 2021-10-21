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
		// �׸� ���
		{
		// ���̹�
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

		// ����
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

		// ä�ù��
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

		// ������ ���� ��ȭ ���
		{
			if (!ObjectManager::GetInstance()->GetPlayer()->GetWin())
			{
				if (Chat2 == 1)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"�ź�! �ƹ��͵� ���ݾ�", 12);
				}
				else if (Chat2 == 2)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"���� ���� �� ���۵Ǿ������̾�...", 19);
				}
				else if (Chat2 == 3)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"���θ��� �����", 8);
				}
				else if (Chat2 == 4)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"���ѷ� �� ������ �������鼭", 15);
					TextOut(_hdc, 150, 570, L"���θ��� ���� �ڽð� �����!", 17);
				}
				else if (Chat2 == 5)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"������ ��ΰ� �����Ŵϱ� ����ص�", 18);
				}
				else if (Chat2 == 6)
				{
					TextOut(_hdc, 150, 515, L"???", 3);
					TextOut(_hdc, 150, 550, L"���, �Ʊ���� �ƹ��͵� ���ٴ�", 17);
				}
				else if (Chat2 == 7)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"���� �־��ݾ�", 7);
					if (!ObjectManager::GetInstance()->GetPlayer()->GetBossOn())
					{
						// ** EnemyList�� ������ �߰��Ѵ�.
						BossList->push_back(CreateEnemy<Boss>(500, -50, 34, 59, 724));

						ObjectManager::GetInstance()->GetPlayer()->SetBossOn(true);
					}
				}
				else if (Chat2 == 8)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"�׷��� �������� �ʾƵ�...", 15);
				}
				else if (Chat2 == 9)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"������ Ȯ���� �����Ұ�", 12);
				}
				else if (Chat2 == 10)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"���� ����� �ƴϴϱ�", 11);
				}
				else if (Chat2 == 11)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"���������", 6);
				}
				else if (Chat2 == 12)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"���� �����ϴٴ� ��¯ �ѹ� �ε��Ѱ�.", 20);
				}
				else if (Chat2 == 13)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"�׸�ŭ�� ������ �ϰ� �Դ� ���̰���!", 20);
				}
				else if (Chat2 == 14)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"�װ� ������?", 7);
				}
				else if (Chat2 == 15)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"����ģ �ž�?", 7);
				}
				else if (Chat2 == 16)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"�׷����� �㿡 ������ ��", 14);
				}
				else if (Chat2 == 17)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"�߿��Ѱ� �Ż翡 �ΰ�͹��ȳ�", 15);
				}
				else if (Chat2 == 18)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"?", 1);
				}
				else if (Chat2 == 19)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"����� ���ϴ� �� ���� �˰ھ�. �����?", 22);
				}
				else if (Chat2 == 20)
				{
					TextOut(_hdc, 150, 515, L"���� ����Ʈ����", 8);
					TextOut(_hdc, 150, 550, L"�ݵ����̶�ϱ�!", 8);
				}
				else if (Chat2 == 21)
				{
					// ä�ø�带 ������� ä�ð� ������ �̹����� ����
					ObjectManager::GetInstance()->GetPlayer()->SetChat(false);
					// ������带 ������� ������ ������ ������ �� �ֵ��� �Ѵ�.
					ObjectManager::GetInstance()->GetPlayer()->SetBossMode(true);

					Chat2 = 50;

				}
			}
		}


		//�¸��� ��ȭ ���
		{
			if (ObjectManager::GetInstance()->GetPlayer()->GetWin())
			{
				if (Chat2 == 51)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"��������, ���� ������ ���Ƽ� �Ⱦ�.", 20);
				}
				else if (Chat2 == 52)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"�㿡�� �� �ִ� �༮�� �� �Ҹ���.", 19);
				}
				else if (Chat2 == 53)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"�׷�, �㿡 �ڿ��� ���� ǳ���ϴٴ� �Ҹ���", 23);
				}
				else if (Chat2 == 54)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"���� �ݵ����� ���� ���� �þ���", 17);
				}
				else if (Chat2 == 55)
				{
					TextOut(_hdc, 150, 515, L"���̹�", 3);
					TextOut(_hdc, 150, 550, L"���� �ٱ����谡 �� �����Ǵµ�.", 17);
				}
				else if (Chat2 == 56)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"���? �� �˰� �ֳ�?", 12);
				}
				else if (Chat2 == 57)
				{
					TextOut(_hdc, 150, 515, L"��ī��", 3);
					TextOut(_hdc, 150, 550, L"�׷��� ���� ���� �� �ϴ� �� ��Ŵ��� �ʾ�.", 25);
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
	// ��ǥ, ũ�� , ü��
	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}