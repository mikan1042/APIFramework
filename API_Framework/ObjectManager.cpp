#include "ObjectManager.h"
#include "MathManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "Enemy.h"
#include "Bullet.h"

ObjectManager* ObjectManager::Instance = nullptr;

void ObjectManager::Initialize()
{
	PrototypeObject = new Prototype;
	PrototypeObject->CreatePrototype();
}

Object* ObjectManager::CreateObject(string _Key)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = PrototypeObject->FindPrototypeObject(_Key);

	// ** 원형객체가 없다면....
	if (pProtoObject == nullptr)
		return nullptr;
	// ** 원형 객체가 있다면...
	else
	{
		// ** 원형객체를 복사 생성한다.
		Object* pObject = pProtoObject->Clone();
		pObject->Initialize();

		return pObject;
	}
}

// ** Prototype 생성 후 작업
void ObjectManager::FindObject(string _Key)
{
	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<string, list<Object*>>::iterator iter = DisableList.find(_Key);

	// ** 없으면.....
	if (iter == DisableList.end() || iter->second.empty())
	{
		Object* pObject = CreateObject(_Key);

		if (pObject == nullptr)
			return;

		// ** DisableList 삽입
		EnableList.push_back(pObject);
	}
	else
	{
		Object* pObject = iter->second.front();
		pObject->Initialize();

		// ** DisableList 삽입
		EnableList.push_back(pObject);
		iter->second.pop_front();
	}
}

Object* ObjectManager::CreateObject(string _Key, Vector3 _Position)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = PrototypeObject->FindPrototypeObject(_Key);

	// ** 원형객체가 없다면....
	if (pProtoObject == nullptr)
		return nullptr;
	// ** 원형 객체가 있다면...
	else
	{
		// ** 원형객체를 복사 생성한다.
		Object* pObject = pProtoObject->Clone();
		pObject->Initialize();
		pObject->SetPosition(_Position);

		return pObject;
	}
}

// ** Prototype 생성 후 작업
void ObjectManager::FindObject(string _Key, Vector3 _Position)
{
	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<string, list<Object*>>::iterator iter = DisableList.find(_Key);

	// ** 없으면.....
	if (iter == DisableList.end() || iter->second.empty())
	{
		Object* pObject = CreateObject(_Key, _Position);

		if (pObject == nullptr)
			return;

		// ** DisableList 삽입
		EnableList.push_back(pObject);
	}
	else
	{
		Object* pObject = iter->second.front();
		pObject->Initialize();
		pObject->SetPosition(_Position);

		// ** DisableList 삽입
		EnableList.push_back(pObject);

		iter->second.pop_front();
	}
}

void ObjectManager::AddObject(string _strKey)
{
	// ** 키값으로 탐색후 탐색이 완료된 결과물을 반환.
	map<string, list<Object*>>::iterator Disableiter = DisableList.find(_strKey);

	for (int i = 0; i < 5; ++i)
	{
		//** Object 객체를 생성. 
		Object* pObj = ObjectFactory<Enemy>::CreateObject();

		// ** 만약 결과물이 존재하지 않는다면....
		if (Disableiter == DisableList.end())
		{
			// ** 새로운 리스트를 생성.
			list<Object*> TempList;

			TempList.push_back(pObj);

			// ** 오브젝트가 추가된 리스트를 맵에 삽입.
			DisableList.insert(make_pair(_strKey, TempList));
		}
		// ** 결과물이 존재 한다면...
		else
			// ** 해당 리스트에 오브젝트를 추가
			Disableiter->second.push_back(pObj);
	}
}

void ObjectManager::RecallObject(Object* _Object)
{
	map<string, list<Object*>>::iterator iter = DisableList.find(_Object->GetKey());

	// ** 만약 결과물이 존재하지 않는다면....
	if (iter == DisableList.end())
	{
		// ** 새로운 리스트를 생성.
		list<Object*> TempList;

		TempList.push_back(_Object);

		// ** 오브젝트가 추가된 리스트를 맵에 삽입.
		DisableList.insert(make_pair(_Object->GetKey(), TempList));
	}
	// ** 결과물이 존재 한다면...
	else
		// ** 해당 리스트에 오브젝트를 추가
		iter->second.push_back(_Object);
}

Object* ObjectManager::GetTarget(Vector3 _Pos)
{
	// ** 멀티맵을 만든다. Key = 거리, value = Object
	multimap<float, Object*> FindTargetList;


	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for (vector<Object*>::iterator iter = EnemyList.begin();
		iter != EnemyList.end(); ++iter)
	{
		// ** 멀티맵에 Current 와 Target 의 거리를 구해서 추가한다.
		FindTargetList.insert(
			make_pair(
			MathManager::GetDistance(_Pos, (*iter)->GetPosition()),	// ** Key
			(*iter)));	// ** Value
	}
	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for (vector<Object*>::iterator iter = EnemyList1.begin();
		iter != EnemyList1.end(); ++iter)
	{
		// ** 멀티맵에 Current 와 Target 의 거리를 구해서 추가한다.
		FindTargetList.insert(
			make_pair(
				MathManager::GetDistance(_Pos, (*iter)->GetPosition()),	// ** Key
				(*iter)));	// ** Value
	}
	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for (vector<Object*>::iterator iter = EnemyList2.begin();
		iter != EnemyList2.end(); ++iter)
	{
		// ** 멀티맵에 Current 와 Target 의 거리를 구해서 추가한다.
		FindTargetList.insert(
			make_pair(
				MathManager::GetDistance(_Pos, (*iter)->GetPosition()),	// ** Key
				(*iter)));	// ** Value
	}
	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for (vector<Object*>::iterator iter = BossList.begin();
		iter != BossList.end(); ++iter)
	{
		// ** 멀티맵에 Current 와 Target 의 거리를 구해서 추가한다.
		FindTargetList.insert(
			make_pair(
				MathManager::GetDistance(_Pos, (*iter)->GetPosition()),	// ** Key
				(*iter)));	// ** Value
	}

	// ** 만약에 리스트에 아무것도 없다면....
	if (FindTargetList.empty())
		return nullptr;

	// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
	return FindTargetList.begin()->second;
}


















Object* ObjectManager::GetPlayerTarget(Vector3 _Pos)
{
	// ** 멀티맵을 만든다. Key = 거리, value = Object
	multimap<float, Object*> FindTargetList;

	// ** 멀티맵에 Current 와 Target 의 거리를 구해서 추가한다.
		FindTargetList.insert(
			make_pair(
				MathManager::GetDistance(_Pos, ObjectManager::GetInstance()->GetPlayer()->GetPosition()),	// ** Key
				ObjectManager::GetInstance()->GetPlayer()));	// ** Value

	// ** 만약에 리스트에 아무것도 없다면....
	if (FindTargetList.empty())
		return nullptr;

	// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
	return FindTargetList.begin()->second;
}



















void ObjectManager::Release()
{
	// ** 안전한 삭제.
	::Safe_Delete(pPlayer);

	for (map<string, list<Object*>>::iterator iter = DisableList.begin();
		iter != DisableList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			::Safe_Delete((*iter2));
		}
		iter->second.clear();
	}
	DisableList.clear();

	for (list<Object*>::iterator iter = EnableList.begin();
		iter != EnableList.end(); ++iter)
	{
		::Safe_Delete((*iter));
	}
	EnableList.clear();
}

void ObjectManager::AddBullet(Vector3 _vPos)
{
	BulletList.push_back(
		ObjectFactory<Bullet>::CreateObject(_vPos));
}
