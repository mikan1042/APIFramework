#pragma once
#include "Headers.h"

class Bitmap;
class Object
{
protected:
	// ** 오브젝트의 기본 Transform
	Transform TransInfo;

	// ** 충돌체의  기본 Transform
	Transform Collider;
	Vector3 Offset;

	string strKey;
	string DrawKey;
	bool Active;
	bool Chat;
	bool GodMode;
	bool BossMode;
	bool BossOn;
	bool Player_Swap;
	bool Win;
	float Speed;
	float Hp;


	int Power, Boom;
	int Chat1;
	// ** 출력 이미지 보관
	static map<string, Bitmap*> ImageList;
	//Object* Target;

public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

	virtual Object* Clone()PURE;
public:
	void SetHp(float _h) { Hp = _h; }
	float GetHp() { return Hp; }

	void SetPower(float _P) { Power = _P; }
	int GetPower() { return Power; }

	void SetBoom(float _B) { Boom = _B; }
	int GetBoom() { return Boom; }

	bool GetChat() { return Chat; }
	void SetChat(bool _Chat) { Chat = _Chat; }

	bool GetGodMode() { return GodMode; }
	void SetGodMode(bool _GodMode) { GodMode = _GodMode; }

	bool GetBossMode() { return BossMode; }
	void SetBossMode(bool _BossMode) { BossMode = _BossMode; }

	bool GetBossOn() { return BossOn; }
	void SetBossOn(bool _BossOn) { BossOn = _BossOn; }

	bool GetPlayer_Swap() { return Player_Swap; }
	void SetPlayer_Swap(bool _Player_Swap) { Player_Swap = _Player_Swap; }

	bool GetWin() { return Win; }
	void SetWin(bool _Win) { Win = _Win; }

	int GetChat1() { return Chat1; }
	void SetChat1(int _Chat1) { Chat1 = _Chat1; }


	void SetDrawKey(string _D) { DrawKey = _D; }
	string GetDrawKey() { return DrawKey; }

	// ** map으로 생성된 Image 보관 컨테이너틑 Setting
	static void SetImageList(const map<string, Bitmap*>& _ImageList) { ImageList = _ImageList; }

	// ** map으로 생성된 Image 보관 컨테이너틑 out
	static map<string, Bitmap*> GetImageList() { return ImageList; }

	// ** 이미지를 출력하는데 사용하는 Key 값을 out
	string GetKey() const { return strKey; }

	// ** 좌표를 Setting (Vector3)
	void SetPosition(Vector3 _position) { TransInfo.Position = _position; }


	// ** 좌표를 Setting (_x, _y)
	void SetPosition(float _x, float _y) { TransInfo.Position.x = _x; TransInfo.Position.y = _y; }

	void SetDirection(Vector3 _direction) { TransInfo.Direction = _direction; }

	void SetScale(float _x, float _y) { TransInfo.Scale.x = _x; TransInfo.Scale.y = _y; }
	void SetScale(Vector3 _Scale) { TransInfo.Scale = _Scale; }

	void SetSpeed(float _Speed) { Speed = _Speed; }

	// ** 좌표를 Vector3로 out
	Vector3 GetPosition() { return TransInfo.Position; }

	Vector3 GetDirection() { return TransInfo.Direction; }

	// ** 크기를 Vector3로 out
	Vector3 GetScale() { return TransInfo.Scale; }

	// ** 충돌체를 out.
	RECT GetCollider();
	
	Vector3 GetColliderPosition() { return Collider.Position; }
	Transform GetColliderTransform() { return Collider; }

	// ** 충돌체를 Setting
	void SetColliderPosition(float _x, float _y) { Collider.Position.x = _x; Collider.Position.y = _y; }
	
	// ** 충돌체의 Top 좌표를 반환.
	// ** 오브젝트가 지면과 닿는 이벤트 발생시 사용가능.
	float GetRectTop() { return TransInfo.Position.y - (TransInfo.Scale.y / 2); }

	// ** 지면이 이중으로 있는경우 아래쪽 지면에서 위쪽의 또다른 지면으로 점프이동 혹은
	// ** 일반 이동시에 지면의 하단부분과 충돌을 감지할 수 있음.
	float GetRectBottom() { return TransInfo.Position.y + (TransInfo.Scale.y / 2); }

	// ** 오브젝트의 활성/비활성 을 [확인] 하기 위해 만들었지만 현재 사용하지 않고있음. 
	bool GetActive() const { return Active; }

	// ** 오브젝트의 활성/비활성 을 [Setting] 하기 위해 만들었지만 현재 사용하지 않고있음. 
	void SetActive(const bool& _Active) { Active = _Active; }
public:
	Object();
	Object(const Transform& _rTransInfo) : TransInfo(_rTransInfo) { }
	virtual ~Object();
};

