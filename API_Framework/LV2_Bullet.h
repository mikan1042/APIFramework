#pragma once
#include "BulletBridge.h"

class LV2_Bullet : public BulletBridge
{
public:
	Object* Target;
	ULONGLONG Time1;
	vector<Object*>* EnemyList;
	vector<Object*>* EnemyList1;
	vector<Object*>* EnemyList2;

	ULONGLONG AmTime;

	int Anime;
	int BL;

public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	LV2_Bullet();
	virtual ~LV2_Bullet();
};

