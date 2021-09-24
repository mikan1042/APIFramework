#pragma once
#include "BulletBridge.h"

class LV1_Bullet : public BulletBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	LV1_Bullet();
	virtual ~LV1_Bullet();
};

