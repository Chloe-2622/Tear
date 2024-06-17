#include "Level.h"
#include "iostream"
#include <random>


using namespace std;

int randint(int const nMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nMin, nbMax);
	return distribution(engine);
}

Level::Level(int levelNumber) {
	for (int i = 0; i < levelNumber; i++) {
		lenght += lenght * 10 / 100;
	}
}

#pragma region Initialize Level
sf::View Level::initView(float const windowWidth, float const windowLenght) {
	// Set view
	view.reset(sf::FloatRect(0, 0, windowWidth, windowLenght));

	//Put view at the right place
	view.move(0, static_cast<float>(lenght));

	cout << view.getCenter().x << ", " << view.getCenter().y << "\n";
	return view;
}

void Level::buildLevel(vector<unique_ptr<Patern>> const& paterns, float const windowWidth, float const windowLenght) {
	// Choose random patern
	//int paternId = randint(0, static_cast<int>(paterns.size()) - 1);
	int paternId = 1;

	// Choose random location
	auto offset_x = static_cast<double>(randint(0, static_cast<int>(windowWidth - paterns[paternId]->getMaxSpawnable_x(windowWidth))));
	auto offset_y = lenght;

	//cout << "id: " << paternId << " offset: " << offset_x << ", offset max: " << paterns[paternId]->getMaxSpawnable_x(windowDimensions.x) << "\n";

	spawnPatern(*paterns[paternId], { offset_x, offset_y });
}

void Level::spawnPatern(Patern const& patern, Vector2 const& offset) {
	std::vector<std::unique_ptr<Tear>> newTears = patern.copyTears();
	
	for (auto& tear : newTears) {
		tear->move(offset);

		gameObjects.push_back(std::move(tear));
	}
}
#pragma endregion Initialize Level

sf::View Level::UpdateView(double const deltaTime) {
	// cout << "view: " << view.getCenter().y << "\n";
	if (view.getCenter().y > 0) {
		view.move(0, -static_cast<float>(scrollingSpeed*deltaTime));

		if (view.getCenter().y < 0) {
			view.move(0, -view.getCenter().y);
		}
	}
	return view;
}

void Level::Update(double deltaTime, float windowLenght) {

	auto it = gameObjects.begin();
	while (it != gameObjects.end()) {
		auto const& gameObject = *it;
		if (gameObject->isOutofView(view.getCenter().y + windowLenght)) {
			scrollingSpeed += gameObject->exitView();
			it = gameObjects.erase(it);
		}
		else {
			++it;
		}
	}

}

void Level::Render(sf::RenderWindow& window) const {
	for (auto const& gameObject : gameObjects) {
		gameObject->Render(window);
	}
}

