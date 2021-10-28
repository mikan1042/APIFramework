#include "Player.h"

#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "MathManager.h"

#include "Bullet.h"
#include "LV1_Bullet.h"
#include "LV2_Bullet.h"
#include "Yukari_Bullet.h"

#include "Enemy.h"
#include "FairyEnemy.h"
#include "Boss.h"
#include "Power.h"
#include "Reimu_Boom.h"
#include "SoundManager.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(420.0f, 640.0f);
	TransInfo.Scale = Vector3(28.0f, 43.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(TransInfo.Scale.x, TransInfo.Scale.y);

	Active = false;

	Frame = 0;

	Time1 = GetTickCount64();
	Time2 = GetTickCount64();

	// ** �÷��̾��� ���
	Player_Swap = false;

	BoomOn = false;
	Chat = false;
	GodMode = false;
	BossMode = false;
	BossOn = false;
	Win = false;
	angle = 0;

	Offset = Vector3(0.0f, 0.0f);

	BulletList = ObjectManager::GetInstance()->GetBulletList();
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	ItemList = ObjectManager::GetInstance()->GetItemList();
	PlayerBoom = ObjectManager::GetInstance()->GetPlayerBoom();
	EnemyBulletList = ObjectManager::GetInstance()->GetEnemyBulletList();

	Power = 1;
	Boom = 3;
	Hp = 5;

	Anime = 0;
	Anime1 = 0;
	God = 0;

}

int Player::Update()
{

	if (AmTime + 170 <= GetTickCount64())
	{
		Anime += 28;
		Anime1 += 32;
		AmTime = GetTickCount64();

		if (Anime >= 112)
			Anime = 0;
		if (Anime1 >= 128)
			Anime1 = 0;
	}

	// �÷��̾��� ��������
	if (ObjectManager::GetInstance()->GetPlayer()->GetGodMode())
	{
		if (Time2 + 1000 <= GetTickCount64())
		{
			++God;
			Time2 = GetTickCount64();
		}
		if(God == 2)
			ObjectManager::GetInstance()->GetPlayer()->SetGodMode(false);
	}
	else
		God = 0;

	// �浹 ��ǥ = ���� ��ǥ 
	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);

	// ** �� ĳ���� �������� ��� ** //

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_LEFT)
		TransInfo.Position.x -= Speed;
	if (dwKey & KEY_RIGHT)
		TransInfo.Position.x += Speed;
	if (dwKey & KEY_UP)
		TransInfo.Position.y -= Speed;
	if (dwKey & KEY_DOWN)
		TransInfo.Position.y += Speed;

	if (GetAsyncKeyState(VK_SHIFT))
		ObjectManager::GetInstance()->GetPlayer()->SetPlayer_Swap(true);
	else
		ObjectManager::GetInstance()->GetPlayer()->SetPlayer_Swap(false);
	


	// �̾߱����࿩��
	if (ObjectManager::GetInstance()->GetPlayer()->GetChat())
	{

	}
	else
	{
		// ĳ���Ͱ� ���̹� �� ��� ** //
		if (!ObjectManager::GetInstance()->GetPlayer()->GetPlayer_Swap())
		{
			//** ���̹� �⺻ ���� ** //
			Speed = 5.0f;


			// ** ZŰ�� �������
			if (GetAsyncKeyState('Z'))
			{
				// ** �Ŀ��� 1�̻� 30 ������ ���
				if (Power >= 1)
				{
					// ** 0.2�ʸ��� �����Ѵ�.
					if (Time1 + 200 <= GetTickCount64())
					{
						SoundManager::GetInstance()->OnPlaySound("reimu_at");
						// ** BulletLIst�� ź���� �߰��Ѵ�.
						BulletList->push_back(CreateBullet<LV1_Bullet>(0, Vector3(13.0f, 14.0f), TransInfo.Position));
						if (Power >= 10)
						{
							BulletList->push_back(CreateBullet<LV2_Bullet>(60, Vector3(13.0f, 14.0f), TransInfo.Position));
							BulletList->push_back(CreateBullet<LV2_Bullet>(120, Vector3(13.0f, 14.0f), TransInfo.Position));
						}
						Time1 = GetTickCount64();
					}
				}
			}
			// ** XŰ�� �������
			if (GetAsyncKeyState('X'))
			{
				// ��ź�� �ִ°��
				if (Boom > 0)
				{
					// ��ź Ʈ���Ű� false�� ���
					if (!BoomOn)
					{
						SoundManager::GetInstance()->OnPlaySound("boom");

						//��ź�� �ߺ��ؼ� �������� ���ϵ��� �Է� �����̸� �ش�. 
							//��ź�� �����Ѵ�.
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));

						// ��ź�� ������ �ϳ� ���δ�
						--Boom;
						// ���� ��ź�� ������ �����ش�.
						ObjectManager::GetInstance()->GetPlayer()->SetBoom(Boom);
						// ��ź Ʈ���Ÿ� true�� ���� �����ؼ� ��ź�� ������� ���ϰ� ���´�
						BoomOn = true;
						ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
					}
					// ��ź Ʈ���Ű� true�� ���
					else
					{
						// ��ź�� ����ѵ� 2���� �ٽ� ��ź�� ����� �� �ֵ��� �Ѵ�.
						if (Time2 + 2000 <= GetTickCount64())
						{
							//�ٽ� ��ź�� ����� �� �ֵ��� Ʈ���Ÿ� false�� �����Ѵ�.
							BoomOn = false;
							Time2 = GetTickCount64();
						}
					}

				}

			}

		}
		// ** ĳ���Ͱ� ��ī�� �� ��� ** //
		else
		{
			//** ��ī�� �⺻ ���� ** //
			Speed = 1.5f;
			if (GetAsyncKeyState('Z'))
			{
				if (Power >= 1)
				{
					if (Time1 + 150 <= GetTickCount64())
					{
						SoundManager::GetInstance()->OnPlaySound("reimu_at");
						if (Power >= 10)
						{
							BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), (Vector3(TransInfo.Position.x - 10.0f, TransInfo.Position.y + 10.0f))));
							BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), (Vector3(TransInfo.Position.x + 10.0f, TransInfo.Position.y + 10.0f))));
						}
						BulletList->push_back(CreateBullet<Yukari_Bullet>(0, Vector3(16.0f, 15.0f), TransInfo.Position));

						Time1 = GetTickCount64();
					}
				}
			}
			if (GetAsyncKeyState('X'))
			{
				// ��ź�� �ִ°��
				if (Boom > 0)
				{
					// ��ź Ʈ���Ű� false�� ���
					if (!BoomOn)
					{
						SoundManager::GetInstance()->OnPlaySound("boom");

						//��ź�� �ߺ��ؼ� �������� ���ϵ��� �Է� �����̸� �ش�. 
							//��ź�� �����Ѵ�.
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));
						PlayerBoom->push_back(CreateBullet<Reimu_Boom>(float(rand() % (130) + 40), Vector3(86.0f, 85.0f), TransInfo.Position));

						// ��ź�� ������ �ϳ� ���δ�
						--Boom;
						// ���� ��ź�� ������ �����ش�.
						ObjectManager::GetInstance()->GetPlayer()->SetBoom(Boom);
						// ��ź Ʈ���Ÿ� true�� ���� �����ؼ� ��ź�� ������� ���ϰ� ���´�
						BoomOn = true;
						ObjectManager::GetInstance()->GetPlayer()->SetGodMode(true);
					}
					// ��ź Ʈ���Ű� true�� ���
					else
					{
						// ��ź�� ����ѵ� 2���� �ٽ� ��ź�� ����� �� �ֵ��� �Ѵ�.
						if (Time2 + 2000 <= GetTickCount64())
						{
							//�ٽ� ��ź�� ����� �� �ֵ��� Ʈ���Ÿ� false�� �����Ѵ�.
							BoomOn = false;
							Time2 = GetTickCount64();
						}
					}

				}

			}


		}
	}


		// ** ĳ���Ͱ� ȭ���� ����� ���ϰ� �ϱ����� ���� ** //
		{
			if (TransInfo.Position.x <= 60)
				TransInfo.Position.x = 60;
			if (TransInfo.Position.x >= 785)
				TransInfo.Position.x = 785;
			if (TransInfo.Position.y >= 670)
				TransInfo.Position.y = 670;
			if (TransInfo.Position.y <= 25)
				TransInfo.Position.y = 25;
		}



			return 0;
		
	
}

void Player::Render(HDC _hdc)
{
	// ** ���̹� �� ��� ��¹�� ** //
	if (!ObjectManager::GetInstance()->GetPlayer()->GetPlayer_Swap())
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
			int(TransInfo.Position.y - (TransInfo.Scale.y / 2)),
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			ImageList["Reimu"]->GetMemDC(),
			Anime,
			0,
			int(TransInfo.Scale.x),
			int(TransInfo.Scale.y),
			RGB(255, 0, 255));
	}
	// ** ��ī�� �� ��� ��¹�� ** //
	else
	{
		TransparentBlt(_hdc,
			int(TransInfo.Position.x - (32/2)),
			int(TransInfo.Position.y - (45/2)),
			int(32),
			int(45),
			ImageList["Yukari"]->GetMemDC(),
			Anime1,
			0,
			int(32),
			int(45),
			RGB(255, 0, 255));


	}
}

void Player::Release()
{

}


template <typename T>
Object* Player::CreateBullet(float _x, Vector3 _sPos, Vector3 _vPos)
{
	Bridge* pBridge = new T;

	Object* pBullet = ObjectFactory<Bullet>::CreateObject(_vPos, _sPos, _x, pBridge);

	return pBullet;
}

template <typename T>
Object* Player::CreateEnemy(float _x, float _y, float _a, float _b, float _z)
{
	Bridge* pBridge = new T;

	Object* pEnemy = ObjectFactory<Enemy>::CreateObject(_x, _y, _a, _b, _z, pBridge);

	return pEnemy;
}