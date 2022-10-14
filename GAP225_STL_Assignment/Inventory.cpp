#include "Inventory.h"
#include "Item.h"
#include "CollectorGame.h"
#include "Tile.h"

#include <conio.h>
#include <iostream>

constexpr int kMoney = 0;
constexpr int kSleepingBag = 2;

Inventory::Inventory(CollectorGame* pGame)
	: m_pGame{pGame}
	, m_index{ 0 }
{
}

///////////////////////////////////////////////////////
// This should draw the contents of the inventory.
///////////////////////////////////////////////////////
void Inventory::Draw() const
{
	system("cls");

	std::cout << "INVENTORY MODE ('f' To Drop Item)" << std::endl;

	for (int i = 0; i < m_pInventory.size(); i++)
	{
		m_pInventory[i]->Draw();
	}
}

///////////////////////////////////////////////////////
// Allow the user to input commands, then execute them.
///////////////////////////////////////////////////////
void Inventory::ProcessInput()
{
	Item* pSelectedItem = nullptr;

	//if there are items in the inventory, select an item and print an arrow to it with '^', as well as give name/description
	if (m_pInventory.size() > 0)
	{ 
		pSelectedItem = m_pInventory[m_index];

		std::cout << '\n';
		for (int i = 0; i < m_index; i++)
		{
			std::cout << ' ';
		}
		std::cout << '^' << std::endl;
		std::cout << pSelectedItem->GetName() << std::endl;
		std::cout << pSelectedItem->GetDescription() << std::endl;
	}
	//gets player input, increments or decrements index and changes item selected
	char input = _getch();
	//if 'a' or 'd', increment or decrement index, also set pSelectedItem
	switch (input)
	{
	case 'a':
		if (m_index > 0)
		{
			m_index -= 1;
			pSelectedItem = m_pInventory[m_index];
		}
		break;
	case 'd':
		if (m_pInventory.size() > 0 && m_index < (m_pInventory.size() - 1))
		{
			m_index += 1;
			pSelectedItem = m_pInventory[m_index];
		}
		break;
	//If items in inventory, erases current item and places it back on the map, decrements index if possible
	case 'f':
		if (m_pInventory.size() > 0)
		{
			while(true)
			{ 
				if (pSelectedItem != nullptr)
				{
					size_t randX = rand() % m_pGame->GetWidth();
					size_t randY = rand() % m_pGame->GetHeight();
					size_t index = randX + randY * m_pGame->GetWidth();
					Tile* pTile = m_pGame->GetTile(index);
					if (pTile->GetContents() == nullptr)
					{
						m_pGame->SetTile(pTile, pSelectedItem);
						break;
					}
				}
			}
			m_pInventory.erase(m_pInventory.begin() + m_index);
			m_index = 0;
			m_pGame->SetMode(CollectorGame::Mode::kWorld);
		}
		break;
	//if an item is used, evaluate which item it is, erase the item from the index, do function, print details, and reset to world screen.
	case 'e':
		if (pSelectedItem == m_pGame->GetItem(kSleepingBag))
		{
			m_pInventory.erase(m_pInventory.begin() + m_index);
			system("cls");
			std::cout << "You've slept for 8 hours. You feel well rested." << std::endl;
			system("pause");
			m_index = 0;
			m_pGame->SetMode(CollectorGame::Mode::kWorld);
		}
		if (pSelectedItem == m_pGame->GetItem(kMoney))
		{
			m_pInventory.erase(m_pInventory.begin() + m_index);
			m_pInventory.push_back(m_pGame->GetItem(kSleepingBag));
			system("cls");
			std::cout << "You've bought a sleeping bag for 20 dollars!" << std::endl;
			system("pause");
			m_index = 0;
			m_pGame->SetMode(CollectorGame::Mode::kWorld);
		}
		break;
	case 'i':
		m_index = 0;
		m_pGame->SetMode(CollectorGame::Mode::kWorld);
		break;
	}
}

///////////////////////////////////////////////////////
// Adds pItem to this inventory.
///////////////////////////////////////////////////////
void Inventory::AddItem(Item* pItem)
{
	m_pInventory.push_back(pItem);
}
