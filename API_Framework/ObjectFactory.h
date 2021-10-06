#pragma once
#include "Object.h"
#include "Bullet.h"
#include "Bridge.h"


template <typename T>
class ObjectFactory
{
public:
	static Object* CreateObject()
	{
		Object* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static Object* CreateObject(Vector3 _vPos)
	{
		Object* pObj = new T;
		pObj->Initialize();
		pObj->SetPosition(_vPos);

		return pObj;
	}

	static Object* CreateObject(float _x, float _y)
	{
		Object* pObj = new T;
		pObj->Initialize();
		pObj->SetPosition(_x, _y);

		return pObj;
	}

	static Object* CreateObject(Vector3 _vPos, Vector3 _sPos ,float _x, Bridge* pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_vPos);
		pObj->SetScale(_sPos);

		pBridge->SetObject(pObj);
		pBridge->Initialize();
		pBridge->Setangle(_x);

		((T*)pObj)->SetBridge(pBridge);

		return pObj;
	}

	static Object* CreateObject(Vector3 _vPos, Vector3 _sPos, Bridge* pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_vPos);
		pObj->SetScale(_sPos);

		pBridge->SetObject(pObj);
		pBridge->Initialize();

		((T*)pObj)->SetBridge(pBridge);

		return pObj;
	}

	static Object* CreateObject(Vector3 _vPos, string _Key, Bridge* pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_vPos);
		pObj->SetDrawKey(_Key);


		pBridge->SetObject(pObj);
		pBridge->Initialize();

		((T*)pObj)->SetBridge(pBridge);

		return pObj;
	}

	static Object* CreateObject(float _x, float _y, float _a, float _b, float _z,Bridge* pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_x, _y);
		pObj->SetScale(_a, _b);
		pObj->SetHp(_z);


		pBridge->SetObject(pObj);
		pBridge->Initialize();

		((T*)pObj)->SetBridge(pBridge);

		return pObj;
	}
};