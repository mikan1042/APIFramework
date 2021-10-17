#pragma once
#include "Object.h"

class PlayerLife : public Object
{

public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new PlayerLife(*this); }
public:
	PlayerLife();
	PlayerLife(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~PlayerLife();
};

