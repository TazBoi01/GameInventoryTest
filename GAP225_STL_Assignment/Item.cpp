#include "Item.h"

#include "Tile.h"

#include <iostream>

Item::Item(const char appearance, const std::string& name, const std::string& description)
	: m_pTile{nullptr}
	, m_appearance{appearance}
	, m_name{name}
	, m_description{description}
{
}

/////////////////////////////////////////////////////
// Collect an item.
/////////////////////////////////////////////////////
void Item::Draw() const
{
	std::cout << m_appearance;
}

/////////////////////////////////////////////////////
// React to being touched by another GameObject.
/////////////////////////////////////////////////////
void Item::OnTouch(GameObject* pToucher)
{
	pToucher->Collect(this);
}
