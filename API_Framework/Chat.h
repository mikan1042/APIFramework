#pragma once
#include "Object.h"

class Chat : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new Chat(*this); }

public:
	ULONGLONG Time1;

	bool Chat1;
	int Chat2;
public:
	Chat();
	Chat(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Chat();
};

