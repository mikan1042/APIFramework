#pragma once
#include "Scene.h"


class Object;
class Stage : public Scene
{
private:
	Object* State_Back;
	Object* Back_Ground;
	Object* m_pPlayer;
	Object* m_pEffect;
	Object* m_pButton;
	Object* m_Fairy;
	vector<Object*>* EnemyList;
	vector<Object*>* BulletList;
	vector<Object*>* ObjectList;

	map<string, Bitmap*> ImageList;

	// ** 타일 생성 개수
	int TileWidthCnt;
	int TileHeightCnt;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Stage();
	virtual ~Stage();
};