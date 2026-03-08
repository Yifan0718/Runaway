#include "runaway/GameObject/Player.hpp"
#include "runaway/GameObject/Projectiles.hpp"
#include "runaway/GameWorld/GameWorld.hpp"
#include "runaway/utils.hpp"

// DONE

Player::Player(pGameWorld world)
: GameObject(
	ImageID::PLAYER,
	200,        // x
	120,        // y
	LayerID::PLAYER,
	20, 48,     // width=20, height=48
	world,
	3,          // HP=3
	1,          // Attack power (close-range)
	AnimID::IDLE
	),
m_bulletCooldown(0),
m_isJumping(false),
m_jumpTimer(0),
m_velocityY(0)
{
}

void Player::UpdateActions()
{
	// If the player is already dead, do not execute further logic
	if (!IsAlive())
	{
		return;
	}
	
	// If bullet cooldown is not zero each frame, no operation needed; otherwise, decrement
	if (m_bulletCooldown > 0)
	{
		m_bulletCooldown--;
	}
	
	// Handle jump kinematics
	if (m_isJumping)
	{
		m_jumpTimer--;
		// Vertical displacement
		int newY = GetY() + m_velocityY;
		// Gravity acceleration
		m_velocityY -= 2;
		
		// If landed
		if (newY <= 120)
		{
			newY = 120;
			m_velocityY = 0;
			m_isJumping = false;
			PlayAnimation(AnimID::IDLE);
		}
		MoveTo(GetX(), newY);
		
		// If jump timer has expired, forcefully end the jump
		if (m_jumpTimer <= 0)
		{
			m_isJumping = false;
			PlayAnimation(AnimID::IDLE);
			MoveTo(GetX(), 120);
		}
	}
	
	// Detect player input
	auto w = GetWorld();
	// If J is pressed or left mouse button (i.e., FIRE1), and bullet cooldown is 0, then shoot
	if (w->GetKeyDown(KeyCode::FIRE1) && m_bulletCooldown == 0)
	{
		// Generate bullet: position is 30 pixels to the right of the player
		auto bullet = std::make_shared<Bullet>(w, GetX() + 30, GetY());
		w->Instantiate(bullet);
		// Set cooldown
		m_bulletCooldown = 10;
	}
	
	// If K is pressed or space (JUMP), and currently not jumping, then start jumping
	if (!m_isJumping && w->GetKeyDown(KeyCode::JUMP))
	{
		m_isJumping = true;
		m_jumpTimer = 24;  // Lasts for 24 frames
		m_velocityY = 23;  // Initial velocity=23
		PlayAnimation(AnimID::JUMP);
	}
}

