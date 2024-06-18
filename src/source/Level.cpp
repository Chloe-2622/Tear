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

// Initialize Level
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
	int paternId = randint(0, static_cast<int>(paterns.size()) - 1);

	// Choose random location
	auto offset_x = static_cast<double>(randint(0, static_cast<int>(windowSize.x - paterns[paternId]->getMaxSpawnable_x(windowSize.x))));
	auto offset_y = lenght;

	//cout << "id: " << paternId << " offset: " << offset_x << ", offset max: " << paterns[paternId]->getMaxSpawnable_x(windowDimensions.x) << "\n";

	spawnPatern(*paterns[paternId], { offset_x, offset_y });
}

void Level::spawnPlayer() {

	Transform initPlayerTransform = { {windowSize.y / 2, lenght - 100 + windowSize.y}, {100, 100}, 0 };
	player = std::make_unique<Player>(initPlayerTransform, 5, "resources/Sprites/Tetine.png");
}

void Level::spawnGoal() {
	double goalSize = 200;
	goal = make_unique<Goal>(Transform{ {(windowSize.x - goalSize ) / 2, 0}, {goalSize, goalSize}, 0 }, "resources/Sprites/Bebe.png");
}

void Level::spawnPatern(Patern const& patern, Vector2 const& offset) {
	std::vector<std::unique_ptr<Tear>> newTears = patern.copyTears();
	
	for (auto& tear : newTears) {
		tear->move(offset);

		gameObjects.push_back(std::move(tear));
	}
}
#pragma endregion Initialize Level

// Update
#pragma region Update
void Level::UpdateView(double const deltaTime) {

	// Si on n'a pas atteint le bout du niveau, on déplace la caméra
	if (!hasReachedEnd) {
		view.move(0, -static_cast<float>(scrollingSpeed * deltaTime));

		// La première fois qu'on atteint le bout
		if (view.getCenter().y - windowSize.y / 2 <= 0) {
			hasReachedEnd = true;

			float offsetY = view.getCenter().x - static_cast<float>(windowSize.y / 2);

			// On fixe la caméra au bon endroit
			view.move(0, -offsetY);
			// On redécale tout les objets pour pas qu'il y a de saut de position apparente
			for (auto const& gameObject : gameObjects) {
				gameObject->supressOffset({ 0, -offsetY });
			}
		}
	}
}

sf::View Level::Update(double deltaTime) {

	UpdateView(deltaTime);

	std::cout << "Number of gameObjects: " << gameObjects.size() << std::endl;
	auto it = gameObjects.begin();


	while (it != gameObjects.end()) {
		auto const& gameObject = *it;

		auto newGameObject = gameObject->Update(deltaTime, view.getViewport(), windowSize, player->getPosition());

		// Check if a new gameObject (a projectile) has been created
		if (newGameObject != nullptr) {
			gameObjects.push_back(move(newGameObject));
		}
		
		// Check if something has be hit by the object
		auto itHit = gameObject->hasHitSomething(gameObjects);

		if (itHit != gameObjects.end()) {
			// Si la cible est tuée
			if (gameObject->doDamage(**itHit, player->getDamageMultiplier())) {

				gameObjects.erase(itHit);

				if (itHit < it) { it--; } // Si on supprime dans la liste avant it, on doit redécaler it
			}
		}

		auto itHit = gameObject->hasHitObject(player)





		/*
		Check if the object is outside the view
		For the projectiles, it means that they are above the view, and for the tears, they are outside
		*/
		if (gameObject->isOutofView(view.getViewport())) {
			scrollingSpeed += gameObject->exitViewValue();

			it = gameObjects.erase(it);
		}
		else {
			++it;
		}
	}



	return view;
}
#pragma endregion Update

// Render
void Level::Render(sf::RenderWindow& window) const {
	for (auto const& gameObject : gameObjects) {
		gameObject->Render(window);
	}
	goal->Render(window);
}