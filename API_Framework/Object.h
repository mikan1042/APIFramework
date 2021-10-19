#pragma once
#include "Headers.h"

class Bitmap;
class Object
{
protected:
	// ** ������Ʈ�� �⺻ Transform
	Transform TransInfo;

	// ** �浹ü��  �⺻ Transform
	Transform Collider;
	Vector3 Offset;

	string strKey;
	string DrawKey;
	bool Active;
	bool Chat;
	bool GodMode;
	bool BossMode;
	bool BossOn;
	bool Win;
	float Speed;
	float Hp;


	int Power, Boom;
	int Chat1;
	// ** ��� �̹��� ����
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

	bool GetWin() { return Win; }
	void SetWin(bool _Win) { Win = _Win; }

	int GetChat1() { return Chat1; }
	void SetChat1(int _Chat1) { Chat1 = _Chat1; }

	void SetDrawKey(string _D) { DrawKey = _D; }
	string GetDrawKey() { return DrawKey; }

	// ** map���� ������ Image ���� �����̳ʺz Setting
	static void SetImageList(const map<string, Bitmap*>& _ImageList) { ImageList = _ImageList; }

	// ** map���� ������ Image ���� �����̳ʺz out
	static map<string, Bitmap*> GetImageList() { return ImageList; }

	// ** �̹����� ����ϴµ� ����ϴ� Key ���� out
	string GetKey() const { return strKey; }

	// ** ��ǥ�� Setting (Vector3)
	void SetPosition(Vector3 _position) { TransInfo.Position = _position; }


	// ** ��ǥ�� Setting (_x, _y)
	void SetPosition(float _x, float _y) { TransInfo.Position.x = _x; TransInfo.Position.y = _y; }

	void SetDirection(Vector3 _direction) { TransInfo.Direction = _direction; }

	void SetScale(float _x, float _y) { TransInfo.Scale.x = _x; TransInfo.Scale.y = _y; }
	void SetScale(Vector3 _Scale) { TransInfo.Scale = _Scale; }

	void SetSpeed(float _Speed) { Speed = _Speed; }

	// ** ��ǥ�� Vector3�� out
	Vector3 GetPosition() { return TransInfo.Position; }

	Vector3 GetDirection() { return TransInfo.Direction; }

	// ** ũ�⸦ Vector3�� out
	Vector3 GetScale() { return TransInfo.Scale; }

	// ** �浹ü�� out.
	RECT GetCollider();
	
	Vector3 GetColliderPosition() { return Collider.Position; }
	Transform GetColliderTransform() { return Collider; }

	// ** �浹ü�� Setting
	void SetColliderPosition(float _x, float _y) { Collider.Position.x = _x; Collider.Position.y = _y; }
	
	// ** �浹ü�� Top ��ǥ�� ��ȯ.
	// ** ������Ʈ�� ����� ��� �̺�Ʈ �߻��� ��밡��.
	float GetRectTop() { return TransInfo.Position.y - (TransInfo.Scale.y / 2); }

	// ** ������ �������� �ִ°�� �Ʒ��� ���鿡�� ������ �Ǵٸ� �������� �����̵� Ȥ��
	// ** �Ϲ� �̵��ÿ� ������ �ϴܺκа� �浹�� ������ �� ����.
	float GetRectBottom() { return TransInfo.Position.y + (TransInfo.Scale.y / 2); }

	// ** ������Ʈ�� Ȱ��/��Ȱ�� �� [Ȯ��] �ϱ� ���� ��������� ���� ������� �ʰ�����. 
	bool GetActive() const { return Active; }

	// ** ������Ʈ�� Ȱ��/��Ȱ�� �� [Setting] �ϱ� ���� ��������� ���� ������� �ʰ�����. 
	void SetActive(const bool& _Active) { Active = _Active; }
public:
	Object();
	Object(const Transform& _rTransInfo) : TransInfo(_rTransInfo) { }
	virtual ~Object();
};

