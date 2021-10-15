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
	vector<Object*>* EnemyList1;
	vector<Object*>* EnemyList2;
	vector<Object*>* EnemyBulletList;
	ULONGLONG Time1;
	ULONGLONG Time2;
	ULONGLONG Time3;

	float angle;

	float Time1Count;
	float Time2Count;
	float Time3Count;

	int a;
	int b;

public:
	// 몬스터 생성 및 원탄
	void Fairymove1(int _x, int _y, float _t, float _tt);
	void Fairymove2(int _x, int _y, float _t, float _tt);
	void Fairymove3(int _x, int _y, float _t, float _tt);

	// 몬스터 생성 및 추격탄 
	void Fairy1(int _x, int _y, float _t, float _tt);
	void Fairy2(int _x, int _y, float _t , float _tt);
	// 몬스터 생성 및 원탄
	void Fairy3(int _x, int _y, float _t, float _tt);

	// 이동값 받아오기
	Vector3 Getangle(float _x);


	template <typename T>
	Object* CreateBullet(float _x, Vector3 _vPos, Vector3 _sPos);

	template <typename T>
	Object* CreateEnemy(float _x, float _y, float _a, float _b, float _z);
public:
	ScheduleManager(){}
	~ScheduleManager() {}
};

