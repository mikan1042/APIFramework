#pragma once
#include "Headers.h"
#include "Object.h"
#include "Bridge.h"

class ScheduleManager : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new ScheduleManager(*this); }

public:
	vector<Object*>* EnemyList;
	vector<Object*>* EnemyBulletList;
	ULONGLONG Time1;

public:
	// 몬스터 생성 및 추격탄 
	void Fairy1();
	// 몬스터 생성 및 원탄
	void Fairy2();


	template <typename T>
	Object* CreateBullet(float _x, Vector3 _vPos, Vector3 _sPos);

	template <typename T>
	Object* CreateEnemy(float _x, float _y, float _a, float _b, float _z);
public:
	ScheduleManager(){}
	~ScheduleManager() {}
};

