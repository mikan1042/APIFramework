#include "Item.h"
#include "ObjectManager.h"
#include "Power.h"


Item::Item() : BridgeObject(NULL)
{

}

Item::~Item()
{
	Release();
}


void Item::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 1.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);


	Active = false;
	strKey = "Item";
}

int Item::Update()
{

	if (BridgeObject)
		BridgeObject->Update(TransInfo);

	return 0;
}

void Item::Render(HDC _hdc)
{

	if (BridgeObject)
		BridgeObject->Render(_hdc);


}

void Item::Release()
{
	delete BridgeObject;
	BridgeObject = nullptr;
}
