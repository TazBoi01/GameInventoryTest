#pragma once
#include "GameObject.h"

#include <string>

class Tile;

class Item :
	public GameObject
{
private:
	Tile* m_pTile;
	char m_appearance;
	std::string m_name;
	std::string m_description;

public:
	Item(char appearance, const std::string& name, const std::string& description);
	
	virtual void SetTile(Tile* pTile) final { m_pTile = pTile; }
	virtual Tile* GetTile() const final { return m_pTile; }
	//////////////////////////////////////////////////////
	// Added Getters
	//////////////////////////////////////////////////////
	virtual std::string GetName() const final { return m_name; }

	virtual std::string GetDescription() const final { return m_description; }
	//////////////////////////////////////////////////////
	virtual void Draw() const final;
	virtual void OnTouch(GameObject* pToucher) final;
};

