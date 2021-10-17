#pragma once
#include "Bridge.h"

class BulletBridge : public Bridge
{
protected:
	bool ATon;
	map<string, Bitmap*> ImageList;
	vector<Object*>* EnemyList;
	vector<Object*>* EnemyBulletList;
	vector<Object*>* EnemyBulletList1;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& _rTransInfo)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:

	BulletBridge();
	virtual ~BulletBridge();
};

