#pragma once
#include "Object.h"

class Start : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()
	{
		return new Start(*this);
	};
public:
	Start();
	virtual ~Start();
};