#pragma once
#include "BulletBridge.h"

class Boss_Bullet2 : public BulletBridge
{
public:
	ULONGLONG Time1;
	Object* Target;
	Object* Player;
	Object* MB;
	bool AT;
	bool Ell;
	vector<Object*>* BossList;

public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	template <typename T>
	Object* CreateBullet(float _x, Vector3 _vPos, Vector3 _sPos);
public:
	Boss_Bullet2();
	virtual ~Boss_Bullet2();
};

