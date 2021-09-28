#pragma once
#include "EnemyBridge.h"

class FairyEnemy : public EnemyBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	FairyEnemy();
	virtual ~FairyEnemy();
};

