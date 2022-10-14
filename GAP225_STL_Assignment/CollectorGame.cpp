#include "CollectorGame.h"

#include "Inventory.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "Tile.h"

#include <conio.h>
#include <iostream>
#include <random>
#include <time.h>

CollectorGame::CollectorGame(size_t width, size_t height)
	: m_width{ width }
	, m_height{ height }
	, m_pTilesVector{ std::vector<Tile*>(width * height) }
	, m_currentMode{Mode::kWorld}
	, m_playerInventory{this}
	, m_player{&m_playerInventory}
	, m_pItems{ nullptr }
{
	int index = 0;
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			m_pTilesVector.at(index) = new Tile{ x, y };
			++index;
		}
	}
}

CollectorGame::~CollectorGame()
{
	for (size_t i = 0; i < m_width * m_height; ++i)
	{
		delete m_pTilesVector[i];
	}
	delete[] &m_pTilesVector;
}

///////////////////////////////////////////////////////////////
// Plays the game.
///////////////////////////////////////////////////////////////
void CollectorGame::Play()
{
	SetTile(m_pTilesVector[0], &m_player);

	constexpr size_t itemCount = 3;
	Item items[itemCount]{
		Item{'$', "Twenty-Dollar Bill", "A bill of paper money. Press 'e' to buy a sleeping bag."},
		Item{'^', "Key", "A nondescript brass key."},
		Item{'&', "Sleeping Bag", "A six-foot cocoon of warm cloth. Press 'e' to sleep."}
	};

	m_pItems = items;

	srand((unsigned)time(nullptr));

	for (size_t i = 0; i < itemCount; ++i)
	{
		while (true)
		{
			size_t randX = rand() % m_width;
			size_t randY = rand() % m_height;
			size_t index = randX + randY * m_width;
			Tile* pTile = m_pTilesVector[index];
			if (pTile->GetContents() == nullptr)
			{
				SetTile(pTile, &items[i]);
				break;
			}
		}
		
	}

	while (true)
	{
		switch (m_currentMode)
		{
		case Mode::kWorld: ProcessWorldMode();	break;
		case Mode::kInventory: ProcessInventoryMode(); break;
		}
	}
}

///////////////////////////////////////////////////////////////
// Sets a Tile's content, and sets the content's Tile.
///////////////////////////////////////////////////////////////
void CollectorGame::SetTile(Tile* pTile, GameObject* pObject)
{
	if(pTile != nullptr)
		pTile->SetContents(pObject);

	if(pObject != nullptr)
		pObject->SetTile(pTile);
}

///////////////////////////////////////////////////////////////
// Draws and updates the main game.
///////////////////////////////////////////////////////////////
void CollectorGame::ProcessWorldMode()
{
	system("cls");

	int index = 0;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			m_pTilesVector[index]->Draw();
			++index;
		}
		std::cout << std::endl;
	}
	std::cout << "Press 'i' for inventory";

	char input = _getch();
	switch (input)
	{
	case 'w': MovePlayer(0, -1); break;
	case 's': MovePlayer(0, +1); break;
	case 'a': MovePlayer(-1, 0); break;
	case 'd': MovePlayer(+1, 0); break;
	case 'i': m_currentMode = Mode::kInventory; break;
	}
}

///////////////////////////////////////////////////////////////
// Moves the player dx (horizontal) and dy (vertical).
///////////////////////////////////////////////////////////////
void CollectorGame::MovePlayer(int dx, int dy)
{
	Tile* pCurrentTile = m_player.GetTile();
	size_t currentX = pCurrentTile->GetX();
	size_t currentY = pCurrentTile->GetY();

	int targetX = (int)currentX + dx;
	if (targetX < 0 || targetX >= (int)m_width)
		return;

	int targetY = (int)currentY + dy;
	if (targetY < 0 || targetY >= (int)m_height)
		return;

	Tile* pTargetTile = m_pTilesVector[targetX + targetY * m_width];
	pTargetTile->OnEnter(&m_player);

	SetTile(pCurrentTile, nullptr);
	SetTile(pTargetTile, &m_player);
}

///////////////////////////////////////////////////////////////
// Draws and executes the inventory screen.
///////////////////////////////////////////////////////////////
void CollectorGame::ProcessInventoryMode()
{
	m_playerInventory.Draw();
	m_playerInventory.ProcessInput();
}
