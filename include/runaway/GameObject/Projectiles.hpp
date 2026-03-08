#ifndef PROJECTILES_HPP__
#define PROJECTILES_HPP__

#include "runaway/GameObject/GameObject.hpp"

// DONE

// Player Bullet Class
class Bullet : public GameObject
{
public:
	// Specify the spawn coordinates during construction
	Bullet(pGameWorld world, int startX, int startY)
	: GameObject(
		ImageID::BULLET,         // Texture ID
		startX, startY,          // x, y
		LayerID::PROJECTILES,    // Display layer
		10, 10,                  // width=10, height=10
		world,
		1,                       // HP
		1,                       // Attack=1
		AnimID::NO_ANIMATION)
	{
	}
	
	// Used to distinguish type: player's projectile
	Type GetType() const override
	{
		return Type::ProjectilePlayer;
	}
	
	void UpdateActions() override
	{
		// If already dead, do not perform movement or other logic
		if (!IsAlive())
			return;
		
		// Move 10 pixels to the right each frame
		MoveTo(GetX() + 10, GetY());
		
		// If it flies out of the screen's right boundary, it dies
		if (GetX() >= WINDOW_WIDTH)
		{
			SetHP(0);
		}
	}
};

// Goblin Axe Class
class Axe : public GameObject
{
public:
	Axe(pGameWorld world, int startX, int startY)
	: GameObject(
		ImageID::AXE,            // Texture ID
		startX, startY,          // x, y
		LayerID::PROJECTILES,    // Display layer
		25, 25,                  // width=25, height=25
		world,
		1,                       // HP
		1,                       // Attack=1
		AnimID::NO_ANIMATION)
	{
	}
	
	// Used to distinguish type: enemy's projectile
	Type GetType() const override
	{
		return Type::ProjectileEnemy;
	}
	
	void UpdateActions() override
	{
		// If already dead, do not perform movement or other logic
		if (!IsAlive())
			return;
		
		// Move 10 pixels to the left each frame
		MoveTo(GetX() - 10, GetY());
		
		// If it flies out of the screen's left boundary, it dies
		if (GetX() <= 0)
		{
			SetHP(0);
		}
	}
};

#endif // !PROJECTILES_HPP__

