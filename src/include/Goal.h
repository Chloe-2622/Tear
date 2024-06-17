#pragma once

#include "GameObject.h"

class Goal {
	public:
		explicit Goal() = default;
		explicit Goal(Transform const& transform, std::string const& texturePath);

		bool isReached(Vector2 playerPosition) const;
		void Render(sf::RenderWindow& window) const;
	private:
		Transform		transform;
		std::string		texturePath = "resources/Sprites/Bebe.png";
};