#pragma once
#include "Scene.h"
#include "Object.h"

class Logo : public Scene
{
private:
	map<string, Bitmap*> ImageList;
	Object* p_Start;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Logo();
	virtual ~Logo();
};