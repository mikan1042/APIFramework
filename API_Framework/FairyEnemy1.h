#pragma once
#include "EnemyBridge.h"

class FairyEnemy1 : public EnemyBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	template <typename T>
	Object* CreateBullet(float _x, Vector3 _sPos);
public:
	FairyEnemy1();
	virtual ~FairyEnemy1();
};

