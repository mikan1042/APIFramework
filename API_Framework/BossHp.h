#pragma once
#include "Object.h"

class BossHp : public Object
{
public:
	float Hp;
	vector<Object*>* BossList;
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new BossHp(*this); }
public:
	BossHp() {}
	~BossHp() {}
};

