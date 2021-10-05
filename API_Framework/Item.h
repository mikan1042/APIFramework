#pragma once
#include "Object.h"

class Bridge;
class Item : public Object
{
private:
	Bridge* BridgeObject;
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Object* Clone()override { return new Item(*this); }
public:
	void SetBridge(Bridge* _pBridge) { BridgeObject = _pBridge; }
public:
	Item();
	Item(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Item();
};
