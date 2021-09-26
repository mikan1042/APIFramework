#pragma once
#include "Object.h"

class BackGround : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()
	{
		return new BackGround(*this);
	};
public:
	BackGround();
	virtual ~BackGround();
};