#ifndef PLAYER_HPP__
#define PLAYER_HPP__

#include <memory>
#include "runaway/GameObject/GameObject.hpp"

// DONE

class Player : public GameObject
{
public:
	Player(pGameWorld world);
	
	// Indicates that this is a "Player" type
	Type GetType() const override
	{
		return Type::Player;
	}
	
	// Overrides the parent class's UpdateActions() to implement behaviors such as moving, jumping, and shooting here
	void UpdateActions() override;
	
private:
	int  m_bulletCooldown; // Records the cooldown duration for player's shooting (10 frames)
	bool m_isJumping;      // Records whether the player is jumping
	int  m_jumpTimer;      // How many frames the jump will still last
	int  m_velocityY;      // Vertical velocity (pixels/frame)
};

#endif // !PLAYER_HPP__

