#pragma once
#include "Object.h"

class UI_Hp : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new UI_Hp(*this); }

public:
	int pHp;
	int pBoom;
public:
	UI_Hp();
	UI_Hp(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~UI_Hp();
};

