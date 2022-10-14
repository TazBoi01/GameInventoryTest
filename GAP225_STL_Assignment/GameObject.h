#pragma once

class Item;
class Tile;

// An interface for grid-based game objects.
class GameObject
{
public:
	virtual ~GameObject() {}

	// Update the Tile that this GameObject sits on.
	virtual void SetTile(Tile* pTile) = 0;

	// Retrieve the Tile that this GameObject sits on.
	virtual Tile* GetTile() const = 0;

	// Draw this GameObject.
	virtual void Draw() const = 0;

	// React to being touched by another GameObject.
	virtual void OnTouch(GameObject* pToucher) {}

	// Collect an item.
	virtual void Collect(Item* pItem) {}
};