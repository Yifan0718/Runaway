#ifndef BACKGROUND_HPP__
#define BACKGROUND_HPP__

#include <memory>
#include "runaway/GameObject/GameObject.hpp"

class Background : public GameObject
{
public:
	Background(pGameWorld world);
	
	GameObject::Type GetType() const override
	{
		return GameObject::Type::UI;
	}
	
	void Update() override;
	void OnClick() override
	{
	}
};

#endif // !BACKGROUND_HPP__

