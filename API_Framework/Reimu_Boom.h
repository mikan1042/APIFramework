#pragma once
#include "BulletBridge.h"

class Reimu_Boom : public BulletBridge
{
public:
	Object* Target;
	Object* MB;
	ULONGLONG Time1;

public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Reimu_Boom();
	virtual ~Reimu_Boom();
};

