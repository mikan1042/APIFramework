#pragma once
#include "BulletBridge.h"

class Boss_Bullet3 : public BulletBridge
{
public:
	ULONGLONG Time1;
	Object* Target;
	Object* Player;
	Object* MB;
	bool AT;
	bool Ell;
	float a;
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

public:
	Boss_Bullet3();
	virtual ~Boss_Bullet3();
};

