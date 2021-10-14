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

		// ��ȭ ���
		{
			if (Chat2 == 1)
				TextOut(_hdc, 150, 550, "�ź�! �ƹ��͵� ���ݾ�", sizeof("�ź�! �ƹ��͵� ���ݾ�"));
			else if (Chat2 == 2)
				TextOut(_hdc, 150, 550, "���� ���� �� ���۵Ǿ������̾�...", sizeof("���� ���� �� ���۵Ǿ������̾�..."));
			else if (Chat2 == 3)   
				TextOut(_hdc, 150, 550, "���ѷ� �� ������ �������鼭\n ���θ��� ���� �ڽð� �����!", sizeof("���ѷ� �� ������ �������鼭\n ���θ��� ���� �ڽð� �����!"));
			else if (Chat2 == 4)   
				TextOut(_hdc, 150, 550, "������ ��ΰ� �����Ŵϱ� ����ص�", sizeof("������ ��ΰ� �����Ŵϱ� ����ص�"));
			else if (Chat2 == 5)   
				TextOut(_hdc, 150, 550, "���, �Ʊ���� �ƹ��͵� ���ٴ�", sizeof("���, �Ʊ���� �ƹ��͵� ���ٴ�"));
			else if (Chat2 == 6)   
				TextOut(_hdc, 150, 550, "���� �־��ݾ�", sizeof("���� �־��ݾ�"));
			else if (Chat2 == 7)   
				TextOut(_hdc, 150, 550, "�׷��� �������� �ʾƵ�...", sizeof("�׷��� �������� �ʾƵ�..."));
			else if (Chat2 == 8)   
				TextOut(_hdc, 150, 550, "������ Ȯ���� �����Ұ� ", sizeof("������ Ȯ���� �����Ұ� "));
			else if (Chat2 == 9)   
				TextOut(_hdc, 150, 550, "���� ����� �ƴϴϱ�", sizeof("���� ����� �ƴϴϱ�"));
			else if (Chat2 == 10)  
				TextOut(_hdc, 150, 550, "���������", sizeof("���������"));
			else if (Chat2 == 11)  
				TextOut(_hdc, 150, 550, "���� �����ϴٴ� ��¯ �ѹ� �ε��Ѱ�.", sizeof("���� �����ϴٴ� ��¯ �ѹ� �ε��Ѱ�."));
			else if (Chat2 == 12)  
				TextOut(_hdc, 150, 550, "�׸�ŭ�� ������ �ϰ� �Դ� ���̰���!", sizeof("�׸�ŭ�� ������ �ϰ� �Դ� ���̰���!"));
			else if (Chat2 == 13)  
				TextOut(_hdc, 150, 550, "�װ� ������?", sizeof("�װ� ������?"));
			else if (Chat2 == 14)  
				TextOut(_hdc, 150, 550, "����ģ �ž�?", sizeof("����ģ �ž�?"));
			else if (Chat2 == 15)  
				TextOut(_hdc, 150, 550, "�׷����� �㿡 ������ ��", sizeof("�׷����� �㿡 ������ ��"));
			else if (Chat2 == 16)  
				TextOut(_hdc, 150, 550, "�߿��Ѱ� �Ż翡 �ΰ�͹��ȳ�", sizeof("�߿��Ѱ� �Ż翡 �ΰ�͹��ȳ�"));
			else if (Chat2 == 17)  
				TextOut(_hdc, 150, 550, "?", sizeof("?"));
			else if (Chat2 == 18)  
				TextOut(_hdc, 150, 550, "����� ���ϴ� �� ���� �˰ھ�. �����?", sizeof("����� ���ϴ� �� ���� �˰ھ�. �����?"));
			else if (Chat2 == 19)  
				TextOut(_hdc, 150, 550, "�ݵ����̶�ϱ�!", sizeof("�ݵ����̶�ϱ�!"));
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
