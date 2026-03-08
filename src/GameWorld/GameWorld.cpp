#include "runaway/GameWorld/GameWorld.hpp"
#include <cmath>    // abs and other functions
#include <iterator> // std::next
#include <string>   // std::to_string

#include "runaway/Framework/TextBase.hpp"
#include "runaway/GameObject/Background.hpp"
#include "runaway/GameObject/Player.hpp"
#include "runaway/GameObject/Enemies.hpp"
#include "runaway/GameObject/Projectiles.hpp"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	// Using unique_ptr, no need for manual delete
}

void GameWorld::Init()
{
	// First, clean up any residual content from the previous game
	CleanUp();
	
	// Place the background object
	Instantiate(std::make_shared<Background>(shared_from_this()));
	
	// Initialize data
	clock = 0;
	score = 0;
	
	// Create the score display text
	// Switched to using unique_ptr:
	scoreText = std::make_unique<TextBase>(
		WINDOW_WIDTH - 160, 
		8, 
		"Score: 0", 
		1.0, 
		1.0, 
		1.0, 
		false
		);
	
	// Create the player's HP text
	hpText = std::make_unique<TextBase>(
		10, 
		8, 
		"HP: 3", 
		1.0, 
		1.0, 
		1.0, 
		false
		);
	
	// New: Gameplay instructions text, placed at the top center
	instructionsText = std::make_unique<TextBase>(
		WINDOW_WIDTH / 2,
		WINDOW_HEIGHT - 30,
		"Controls: K/Space - Jump | J - Fire",
		1.0,
		1.0,
		1.0,
		true
		);
	
	// Create the player object
	auto player = std::make_shared<Player>(shared_from_this());
	Instantiate(player);
}

LevelStatus GameWorld::Update()
{
	// Increment clock each frame
	clock++;
	
	// Generate a goblin every 240 frames
	if (clock % 240 == 0)
	{
		auto goblin = std::make_shared<Goblin>(shared_from_this(), WINDOW_WIDTH - 1, 120);
		Instantiate(goblin);
	}
	
	// 1) Let all objects perform Update()
	for (auto &obj : m_gameObjects)
	{
		obj->Update();
	}
	
	// 2) Detect collisions (bullets vs enemies, axes vs players, enemies vs players)
	for (auto itA = m_gameObjects.begin(); itA != m_gameObjects.end(); ++itA)
	{
		auto A = *itA;
		if (!A->IsAlive())
			continue;
		
		for (auto itB = std::next(itA); itB != m_gameObjects.end(); ++itB)
		{
			auto B = *itB;
			if (!B->IsAlive())
				continue;
			
			int dx = std::abs(A->GetX() - B->GetX());
			int dy = std::abs(A->GetY() - B->GetY());
			int halfW = (A->GetWidth() / 2) + (B->GetWidth() / 2);
			int halfH = (A->GetHeight() / 2) + (B->GetHeight() / 2);
			if (dx < halfW && dy < halfH)
			{
				// Collision detected
				auto typeA = A->GetType();
				auto typeB = B->GetType();
				
				// Bullet vs Goblin
				if (
					(typeA == GameObject::Type::ProjectilePlayer && typeB == GameObject::Type::Enemy) ||
					(typeB == GameObject::Type::ProjectilePlayer && typeA == GameObject::Type::Enemy)
					)
				{
					if (typeA == GameObject::Type::ProjectilePlayer)
					{
						B->TakeDamage(A->GetAttack());
						A->TakeDamage(A->GetHP()); // Immediately destroy the bullet
						if (!B->IsAlive())
						{
							score++;
						}
					}
					else
					{
						A->TakeDamage(B->GetAttack());
						B->TakeDamage(B->GetHP());
						if (!A->IsAlive())
						{
							score++;
						}
					}
				}
				// Axe vs Player
				if (
					(typeA == GameObject::Type::ProjectileEnemy && typeB == GameObject::Type::Player) ||
					(typeB == GameObject::Type::ProjectileEnemy && typeA == GameObject::Type::Player)
					)
				{
					if (typeA == GameObject::Type::ProjectileEnemy)
					{
						B->TakeDamage(A->GetAttack());
						A->TakeDamage(A->GetHP());
					}
					else
					{
						A->TakeDamage(B->GetAttack());
						B->TakeDamage(B->GetHP());
					}
				}
				// Goblin vs Player
				if (
					(typeA == GameObject::Type::Enemy && typeB == GameObject::Type::Player) ||
					(typeB == GameObject::Type::Enemy && typeA == GameObject::Type::Player)
					)
				{
					if (typeA == GameObject::Type::Enemy)
					{
						B->TakeDamage(A->GetAttack()); // Player HP -1
						A->TakeDamage(A->GetHP());     // Goblin dies immediately
					}
					else
					{
						A->TakeDamage(B->GetAttack());
						B->TakeDamage(B->GetHP());
					}
				}
			}
		}
	}
	
	// 3) Remove dead objects
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); )
	{
		if (!(*it)->IsAlive())
		{
			it = m_gameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	// 4) Check if the player is dead
	bool playerAlive = false;
	int playerHP = 0; // Used to update in hpText below
	for (auto &obj : m_gameObjects)
	{
		if (obj->GetType() == GameObject::Type::Player)
		{
			playerAlive = obj->IsAlive();
			playerHP = obj->GetHP();
			break;
		}
	}
	if (!playerAlive)
	{
		// When the player dies, hpText displays "HP: 0"
		if (hpText)
		{
			hpText->SetText("HP: 0");
		}
		return LevelStatus::LOSING;
	}
	
	// 5) Update text displays: Score and player HP
	if (scoreText)
	{
		scoreText->SetText("Score: " + std::to_string(score));
	}
	if (hpText)
	{
		hpText->SetText("HP: " + std::to_string(playerHP));
	}
	
	// Gameplay instructionsText do not need real-time updates
	
	// Continue the game
	return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
	// Clear the list of game objects
	m_gameObjects.clear();
	
	// unique_ptr automatically manages memory, no need to delete
	scoreText.reset();
	hpText.reset();
	instructionsText.reset();
}

void GameWorld::Instantiate(std::shared_ptr<GameObject> newGameObject)
{
	m_gameObjects.push_back(newGameObject);
}

