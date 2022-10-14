#pragma once
#include <vector>

class CollectorGame;
class Item;

///////////////////////////////////////////////////////////////
// This is where most of your work should be done.
// You are free to change the API in any way you like,
// as long as the functionality described is still implemented.
///////////////////////////////////////////////////////////////
class Inventory
{
private:
	CollectorGame* const m_pGame;
	std::vector<Item*> m_pInventory;
	size_t m_index;

public:
	Inventory(CollectorGame* pGame);

	void Draw() const;
	void ProcessInput();

	void AddItem(Item* pItem);
};

