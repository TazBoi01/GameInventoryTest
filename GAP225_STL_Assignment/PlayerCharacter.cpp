#include "PlayerCharacter.h"

#include "Item.h"

#include <iostream>

PlayerCharacter::PlayerCharacter(Inventory* pInventory)
	: m_pTile{nullptr}
	, m_pInventory{ pInventory }
{
}

/////////////////////////////////////////////////////
// Draw this GameObject.
/////////////////////////////////////////////////////
void PlayerCharacter::Draw() const
{
	std::cout << '@';
}

/////////////////////////////////////////////////////
// Collect an item.
/////////////////////////////////////////////////////
void PlayerCharacter::Collect(Item* pItem)
{
	m_pInventory->AddItem(pItem);
}
