#pragma once

class GameObject;

class Tile
{
private:
	const size_t m_x;
	const size_t m_y;
	GameObject* m_pContents;

public:
	Tile(size_t x, size_t y);

	size_t GetX() const { return m_x; }
	size_t GetY() const { return m_y; }

	void SetContents(GameObject* pContents) { m_pContents = pContents; }
	GameObject* GetContents() { return m_pContents; }

	void Draw() const;
	void OnEnter(GameObject* pEnteringObject);
};

