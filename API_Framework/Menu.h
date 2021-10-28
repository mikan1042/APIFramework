#pragma once
#include "Scene.h"

class Menu : public Scene
{
public:
	map<string, Bitmap*> ImageList;
	bool SQ;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Menu();
	virtual ~Menu();
};