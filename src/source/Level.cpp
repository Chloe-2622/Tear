#include "iostream"
#include <random>
#include "Game.hpp"

using namespace std;

int randint(int const nMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nMin, nbMax);
	return distribution(engine);
}

// Constructeur
Level::Level(int levelNumber, Game* game) : game(game) {
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

	int paternSpawnNumber = static_cast<int>(lenght / windowSize.y) * 5;

	for (int i = 0; i < paternSpawnNumber - 2; i++) {
		// Choose random patern
		int paternId = randint(0, static_cast<int>(paterns.size()) - 1);

		// Choose random location
		std::cout << "window size" << windowSize.x << " " << windowSize.y << std::endl;
		double offset_x = static_cast<double>(randint(0, static_cast<int>(paterns[paternId]->getMaxSpawnable_x(windowSize.x))));
		double offset_y = lenght - i * (windowSize.y / 5);

		spawnPatern(*paterns[paternId], { offset_x, offset_y });
	}

	// // Choose random patern
	// int paternId = randint(0, static_cast<int>(paterns.size()) - 1);

	// // Choose random location
	// auto offset_x = static_cast<double>(randint(0, static_cast<int>(windowSize.x - paterns[paternId]->getMaxSpawnable_x(windowSize.x))));
	// auto offset_y = lenght;

	// //cout << "id: " << paternId << " offset: " << offset_x << ", offset max: " << paterns[paternId]->getMaxSpawnable_x(windowDimensions.x) << "\n";

	// spawnPatern(*paterns[paternId], { offset_x, offset_y });
	

	// Build backgrounds
	int backgroundSize = 1080;
	int nbBackgrounds = static_cast<int>(lenght / backgroundSize) + 1;
	for (int i = 0; i < nbBackgrounds; i++) {
		backgroundsPositions.push_back({ 0, i * backgroundSize });
	}
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
		Vector2 cameraMovement{ 0, -scrollingSpeed * deltaTime };

		view.move(static_cast<float>(cameraMovement.x), static_cast<float>(cameraMovement.y));

		cout << scrollingSpeed * deltaTime << "\n";

		for (auto const& gameObject : gameObjects) {
			gameObject->followView(cameraMovement);
		}
		player->followView(cameraMovement);

		// La première fois qu'on atteint le bout
		if (view.getCenter().y - windowSize.y / 2 <= 0) {
			hasReachedEnd = true;

			float offsetY = view.getCenter().y - static_cast<float>(windowSize.y / 2);

			// On fixe la cam�ra au bon endroit
			view.move(0, -offsetY);
			
			
			
			// On red�cale tout les objets pour pas qu'il y a de saut de position apparente
			for (auto const& gameObject : gameObjects) {
				gameObject->supressViewOffset({ 0, -offsetY });
			}
		}
	}
}

sf::View Level::Update(double deltaTime) {

	UpdateView(deltaTime);

	//std::cout << "Number of gameObjects: " << gameObjects.size() << std::endl;
	auto it = gameObjects.begin();

	const vector<unique_ptr<GameObject>>* gameObjectsPtr;
	gameObjectsPtr = &gameObjects;
	
	while (it != gameObjects.end()) {
		auto const& gameObject = *it;

		// Check if a new gameObject (a projectile) has been created
		if (auto newGameObject = gameObject->Update(deltaTime, view, windowSize, player->getPosition()); newGameObject != nullptr) {
			gameObjects.push_back(move(newGameObject));
		}
		
		// Check if something has been hit by the object
		if (auto itHit = gameObject->hasHitSomething(gameObjectsPtr); itHit != gameObjects.end() && gameObject->doDamage(**itHit, player->getDamageMultiplier())) {
			// Si la cible est tu�e
			gameObjects.erase(itHit);

			if (itHit < it) { it--; } // Si on supprime dans la liste avant it, on doit red�caler it
		}
		
		// Check if the player has been hit by the object
		if (gameObject->hasHitObject(*player)) {
			cout << "Touche\n";

			if (gameObject->doDamage(*player, player->getDamageMultiplier())) {
				// Si la cible est tu�e
				cout << "Fin de la Partie" << endl;
			}
		}

		/*
		Check if the object is outside the view
		For the projectiles, it means that they are above the view, and for the tears, they are outside
		*/
		if (gameObject->isOutofView(view, windowSize)) {
			scrollingSpeed += gameObject->exitViewValue();

			it = gameObjects.erase(it);
		}
		else {
			++it;
		}
	}

	// Finalement, on update le player
	// Check if a new gameObject (a projectile) has been created
	if (auto newGameObject = player->Update(deltaTime, view, windowSize, player->getPosition()); newGameObject != nullptr) {
		gameObjects.push_back(move(newGameObject));
	}

	if (goal->isReached(*player)) {
		cout << "C'est la fin !!!!";
		game->changeState(GameState::SHOP);
	}

	return view;
}
#pragma endregion Update

void Level::renderBackground(sf::RenderWindow& window) const {
	for (auto const& backgroundPosition : backgroundsPositions) {
		sf::Texture texture;
		texture = ResourceManager::getTexture("resources/Sprites/Background.png");

		sf::Sprite sprite;
		sprite.setTexture(texture);

		sprite.setScale(static_cast<float>(windowSize.x/texture.getSize().x) , static_cast<float>(windowSize.y / texture.getSize().y));
		sprite.setPosition(backgroundPosition.first, backgroundPosition.second);

		//Draw the sprite
		window.draw(sprite);
	}
}

// Getter
Player& Level::getPlayerPtr() { return *player; }

// Render
void Level::Render(sf::RenderWindow& window) const {
	renderBackground(window);
	for (auto const& gameObject : gameObjects) {
		gameObject->Render(window);
	}
	goal->Render(window);
	player->Render(window);
}