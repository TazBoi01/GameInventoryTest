#include "Tile.h"
#include "GameObject.h"

#include <iostream>

Tile::Tile(size_t x, size_t y)
	: m_x{x}
	, m_y{y}
	, m_pContents{nullptr}
{
}

////////////////////////////////////////////////
// Draw this Tile's contents, if there are any.
// If not, draw the empty tile.
////////////////////////////////////////////////
void Tile::Draw() const
{
	if (m_pContents)
		m_pContents->Draw();
	else
		std::cout << '.';
}

/////////////////////////////////////////////////////
// If there is a GameObject here, it will be touched.
/////////////////////////////////////////////////////
void Tile::OnEnter(GameObject* pEnteringObject)
{
	if (m_pContents)
		m_pContents->OnTouch(pEnteringObject);
}
