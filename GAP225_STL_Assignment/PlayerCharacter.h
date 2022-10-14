#pragma once
#include "GameObject.h"

#include "Inventory.h"

class Tile;

class PlayerCharacter :
	public GameObject
{
private:
	Tile* m_pTile;
	Inventory* const m_pInventory;

public:
	PlayerCharacter(Inventory* pInventory);

	virtual void SetTile(Tile* pTile) final { m_pTile = pTile; }
	virtual Tile* GetTile() const final { return m_pTile; }

	virtual void Draw() const final;
	virtual void Collect(Item* pItem) final;
};

