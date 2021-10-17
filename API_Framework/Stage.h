#pragma once
#include "Scene.h"


class Object;
class Stage : public Scene
{
private:
	Object* State_Back;
	Object* Back_Ground;
	Object* m_pPlayer;
	Object* m_pButton;
	Object* m_Fairy;
	Object* m_Schedule;
	Object* m_uHp;
	Object* m_Chat;
	Object* PlayerL;
	Object* BossH;

	vector<Object*>* BossList;
	vector<Object*>* EnemyList;
	vector<Object*>* EnemyList1;
	vector<Object*>* EnemyList2;
	vector<Object*>* BulletList;
	vector<Object*>* EnemyBulletList;
	vector<Object*>* EnemyBulletList1;
	vector<Object*>* ItemList;
	vector<Object*>* PlayerBoom;
	vector<Object*>* ObjectList;

	map<string, Bitmap*> ImageList;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	template <typename T>
	Object* CreateItem(Vector3 _vPos, string _Key);
public:
	Stage();
	virtual ~Stage();
};

