#pragma once
#include "BulletBridge.h"

class Boss_Bullet : public BulletBridge
{
public:
	Object* Target;
	Object* Player;
	Object* MB;
	bool AT;
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Boss_Bullet();
	virtual ~Boss_Bullet();
};

