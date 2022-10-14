#pragma once

#include "PlayerCharacter.h"
#include "Item.h"

class Tile;

class CollectorGame
{
public:
	enum class Mode
	{
		kWorld,
		kInventory
	};

private:
	const size_t m_width;
	const size_t m_height;
	std::vector<Tile*> m_pTilesVector;

	Mode m_currentMode;

	Inventory m_playerInventory;
	PlayerCharacter m_player;
	Item* m_pItems;

public:
	CollectorGame(size_t w, size_t h);
	~CollectorGame();

	void Play();
	void SetMode(Mode mode) { m_currentMode = mode; }

	size_t GetWidth() const { return m_width; }
	size_t GetHeight() const { return m_height; }

	Tile* GetTile(size_t index) { return m_pTilesVector.at(index); }
	void SetTile(Tile* pTile, GameObject* pObject);

	Item* GetItem(size_t index) { return &m_pItems[index]; }
private:
	

	void ProcessWorldMode();
	void MovePlayer(int dx, int dy);

	void ProcessInventoryMode();
};

