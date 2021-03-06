#pragma once
#include "Bridge.h"

class ItemBirdge : public Bridge
{
protected:
	float Speed;
	map<string, Bitmap*> ImageList;
	vector<Object*>* EnemyList;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& _rTransInfo)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	ItemBirdge();
	virtual ~ItemBirdge();
};

