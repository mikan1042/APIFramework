#pragma once
#include "Object.h"

class Y_Char : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	Object* Player;


	virtual Object* Clone()
	{
		return new Y_Char(*this);
	};



public:
	Y_Char();
	virtual ~Y_Char();
};