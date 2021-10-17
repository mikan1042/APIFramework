#include "BossHp.h"

#include "ObjectManager.h"




void BossHp::Initialize()
{
	DrawKey = "BossHp";

	ImageList = Object::GetImageList();

	BossList = ObjectManager::GetInstance()->GetBossList();
}

int BossHp::Update()
{
	for (vector<Object*>::iterator iter = BossList->begin();
		iter != BossList->end(); ++iter)
		Hp = (*iter)->GetHp();

	return 0;
}

void BossHp::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		60,
		30,
		Hp,
		7,
		ImageList[DrawKey]->GetMemDC(),
		0, 0,
		Hp,
		7,
		RGB(255, 0, 255));
}

void BossHp::Release()
{
}