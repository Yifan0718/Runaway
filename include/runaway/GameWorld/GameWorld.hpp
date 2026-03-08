#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory> // Include smart pointers
#include <utility> // For std::pair

#include "runaway/Framework/WorldBase.hpp"
#include "runaway/Framework/TextBase.hpp"
#include "runaway/GameObject/GameObject.hpp"
#include "runaway/utils.hpp"

class GameWorld 
: public WorldBase
, public std::enable_shared_from_this<GameWorld>
{
public:
	GameWorld();
	virtual ~GameWorld();
	
	void Init() override;
	LevelStatus Update() override;
	void CleanUp() override;
	
	// These overrides are used to demonstrate how to handle input; specific implementation is the same as WorldBase
	bool GetKeyDown(KeyCode key) const override
	{
		return WorldBase::GetKeyDown(key);
	}
	
	bool GetKey(KeyCode key) const override
	{
		return WorldBase::GetKey(key);
	}
	
	std::pair<int, int> GetMousePos() const override
	{
		return WorldBase::GetMousePos();
	}
	
	void Instantiate(std::shared_ptr<GameObject> newGameObject);
	
	// New: Access and modify the score
	int GetScore()
	{
		return score;
	}
	
	void addScore()
	{
		score++;
	}
	
private:
	std::list<std::shared_ptr<GameObject>> m_gameObjects;
	int clock = 0;
	int score = 0;
	
	// Switched to smart pointers
	std::unique_ptr<TextBase> scoreText;
	std::unique_ptr<TextBase> hpText;
	std::unique_ptr<TextBase> instructionsText;
};

#endif // !GAMEWORLD_HPP__

