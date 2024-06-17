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
	windowSize = { windowWidth , windowLenght };

	// Set view
	view.reset(sf::FloatRect(0, 0, windowWidth, windowLenght));

	//Put view at the right place
	view.move(0, static_cast<float>(lenght));

	cout << view.getCenter().x << ", " << view.getCenter().y << "\n";
	return view;
}

void Level::buildLevel(vector<unique_ptr<Patern>> const& paterns) {

	spawnPlayer();
	spawnGoal();

	// Choose random patern
	//int paternId = randint(0, static_cast<int>(paterns.size()) - 1);
	int paternId = 1;

	// Choose random location
	auto offset_x = static_cast<double>(randint(0, static_cast<int>(windowSize.x - paterns[paternId]->getMaxSpawnable_x(windowSize.x))));
	auto offset_y = lenght;

	//cout << "id: " << paternId << " offset: " << offset_x << ", offset max: " << paterns[paternId]->getMaxSpawnable_x(windowDimensions.x) << "\n";

	spawnPatern(*paterns[paternId], { offset_x, offset_y });
}

void Level::spawnPlayer() {

	Transform initPlayerTransform = { {windowSize.y / 2, lenght - 100 + windowSize.y}, {100, 100}, 0 };
	this->player = std::make_unique<Player>(initPlayerTransform, 5, "resources/Sprites/Tetine.png");
}

void Level::spawnGoal() {
	double goalSize = 100;
	goal = make_unique<Goal>(Transform{ {windowSize.x - (goalSize / 2), 0}, {goalSize, goalSize}, 0 }, "resources/Sprites/Bebe.png");
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

	if (!hasReachedEnd) {
		view.move(0, -static_cast<float>(scrollingSpeed*deltaTime));
		player.get()->move({ 0, -static_cast<float>(scrollingSpeed*deltaTime) });
	}
	return view;
}

void Level::Update(double deltaTime) {

	if (view.getCenter().y - windowSize.y / 2 <= 0 && !hasReachedEnd) {
		hasReachedEnd = true;
		float offsetY = view.getCenter().y;
		view.setCenter(view.getCenter().x, windowSize.y / 2);
		offsetY -= view.getCenter().y;
		player.get()->setPosition({ player.get()->getPosition().x, player.get()->getPosition().y - offsetY});
	}

	player->UpdatePlayer(deltaTime, scrollingSpeed, view.getCenter().y - windowSize.y / 2, windowSize.y, windowSize.x);

	auto it = gameObjects.begin();
	while (it != gameObjects.end()) {
		auto const& gameObject = *it;
		gameObject->Update(deltaTime, scrollingSpeed, view.getCenter().y - windowSize.y / 2, windowSize.y, player->getPosition());

		// Check if object is still ont the screen (below screen for tears, above for projectiles)
		if (gameObject->isOutofView(static_cast<float>(view.getCenter().y + windowSize.y / 2))) {
			scrollingSpeed += gameObject->exitView();
			it = gameObjects.erase(it);
		}

		// Check if object collide with the player or another object
		/*if (gameObject->hit(*player->getPosition(), gameObjects)) {
			cout << "Hit " << gameObject->dump();
		}*/








		else {
			++it;
		}
	}

	

}

void Level::Render(sf::RenderWindow& window) const {
	for (auto const& gameObject : gameObjects) {
		gameObject->Render(window);
	}
	player->Render(window);
	goal->Render(window);
}

