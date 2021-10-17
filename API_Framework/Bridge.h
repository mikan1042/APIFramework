#pragma once
#include "Headers.h"

class Object;
class Bridge
{
protected:
	float angle;
	float Speed;
	string DrawKey;
	Object* RealObject;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& _rTransInfo)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	void SetObject(Object* _pObject) { RealObject = _pObject; }
	void Setangle(float _angle) { angle = _angle; }
	void SetSpeed(float _Speed) { Speed = _Speed; }
public:
	Bridge();
	virtual ~Bridge();
};

