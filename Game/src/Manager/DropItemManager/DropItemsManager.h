#pragma once
#include "ObjectPool.h"
class DropItems;

class DropItemsManager : public IGameObject
{
public:
	DropItemsManager();
	~DropItemsManager() override;
	bool Start() override;
	void Update() {};
	void DropItemSet(const Vector3& position, int itemType);


private:
	ObjectPool<DropItems> m_dorpItemsPool;
	int m_maxDropItemNum = 20;
};

