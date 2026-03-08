#include "runaway/GameObject/Enemies.hpp"
#include "runaway/GameObject/Projectiles.hpp"
#include "runaway/GameWorld/GameWorld.hpp"

// Implements the Goblin's UpdateActions function
void Goblin::UpdateActions()
{
	// If already dead, do not execute subsequent logic
	if (!IsAlive())
	{
		return;
	}
	
	// Move 3 pixels to the left each frame
	MoveTo(GetX() - 3, GetY());
	
	// If currently in "throwing axe animation"
	if (m_isThrowing)
	{
		// Continue playing animation, countdown
		m_throwAnimCount--;
		if (m_throwAnimCount <= 0)
		{
			// Animation completed, now actually generate an axe
			auto w = GetWorld();
			// Generate axe at goblin's current position
			auto axe = std::make_shared<Axe>(w, GetX(), GetY());
			w->Instantiate(axe);
			
			// After playback ends, restore IDLE animation
			PlayAnimation(AnimID::IDLE);
			m_isThrowing = false;
			
			// Next time you want to throw an axe, need to wait 80 frames
			m_throwTimer = 80;
		}
		return;
	}
	
	// If not currently in "throwing axe animation", start countdown until 0 to play animation
	m_throwTimer--;
	if (m_throwTimer <= 0)
	{
		// Play THROW animation and maintain for 20 frames
		PlayAnimation(AnimID::THROW);
		m_isThrowing = true;
		m_throwAnimCount = 20; // THROW animation duration
		
		// Set the interval before the next axe throw to 80 frames
		// Adjust here if a different interval is needed before throwing an axe
	}
}

