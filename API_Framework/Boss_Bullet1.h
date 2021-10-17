#pragma once
#include "BulletBridge.h"

class Boss_Bullet1 : public BulletBridge
{
public:
	ULONGLONG Time1;
	Object* Target;
	Object* Player;
	Object* MB;
	bool AT;
	bool Ell;
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Boss_Bullet1();
	virtual ~Boss_Bullet1();
};

