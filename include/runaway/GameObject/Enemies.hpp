#ifndef ENEMIES_HPP__
#define ENEMIES_HPP__

#include <memory>

#include "runaway/GameObject/GameObject.hpp"

// Defines the Goblin class, inheriting from GameObject
class Goblin : public GameObject
{
public:
	Goblin(pGameWorld world, int startX, int startY)
	: GameObject(
		ImageID::GOBLIN,           // Texture ID
		startX, startY,            // x, y
		LayerID::ENEMIES,          // Display layer
		20, 48,                    // width=20, height=48
		world,
		5,                         // HP
		1,                         // Attack (close-range damage to player)
		AnimID::IDLE
		),
	m_throwTimer(20),             // Initialized to 20 frames, interval before first axe throw
	m_isThrowing(false),
	m_throwAnimCount(0)
	{
	}
	
	// Indicates that this is an "Enemy" type
	Type GetType() const override
	{
		return Type::Enemy;
	}
	
	void UpdateActions() override;
	
private:
	// Used to calculate the time interval for throwing axes
	int m_throwTimer;
	bool m_isThrowing;
	int m_throwAnimCount; // Remaining ticks for THROW animation playback
};

#endif // !ENEMIES_HPP__

