#include "ItemBirdge.h"

class Boom : public ItemBirdge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;


public:
	Boom();
	virtual ~Boom();
};