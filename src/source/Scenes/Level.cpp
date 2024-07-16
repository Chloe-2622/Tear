#include <random>
#include <iostream>
#include "Scenes/Level.h"

using namespace std;

int randint(int const nMin, int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(nMin, nbMax);
	return distribution(engine);
}

// Constructeur
#pragma region Constructeurs
Level::Level(Game* game, int levelNumber) :
	Scene(game, "resources/Sprites/Background.png")
{
	for (int i = 0; i < levelNumber; i++) {
		lenght += lenght * 50 / 100;
	}
}

Level::Level(Game* game, int levelNumber, Player* player) :
	Scene(game, "resources/Sprites/Background.png"),
	player{ move(player) }
{
	for (int i = 0; i < levelNumber; i++) {
		lenght += lenght * 50 / 100;
	}
}
#pragma endregion Constructeurs

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

	if (player == nullptr) { spawnPlayer(); }
	spawnGoal();

	int paternSpawnNumber = static_cast<int>(lenght / windowSize.y) * 5;

	for (int i = 0; i < paternSpawnNumber - 2; i++) {
		// Choose random patern
		int paternId = randint(0, static_cast<int>(paterns.size()) - 1);

		// Choose random location
		std::cout << "window size" << windowSize.x << " " << windowSize.y << std::endl;
		auto offset_x = static_cast<double>(randint(0, static_cast<int>(paterns[paternId]->getMaxSpawnable_x(windowSize.x))));
		double offset_y = lenght - i * (windowSize.y / 5);

		spawnPatern(*paterns[paternId], { offset_x, offset_y });
	}	

	// Build backgrounds
	int backgroundSize = 1080;
	int nbBackgrounds = static_cast<int>(lenght / backgroundSize) + 2;
	for (int i = 0; i < nbBackgrounds; i++) {
		backgroundsPositions.push_back({ 0, i * backgroundSize });
	}
}

void Level::spawnPlayer() {

	Transform initPlayerTransform = { {windowSize.y / 2, lenght - 100 + windowSize.y}, {100, 100}, 0 };
	player = std::make_unique<Player>(initPlayerTransform, 250, "resources/Sprites/Tetine.png");
}

void Level::spawnGoal() {
	double goalSize = 200;
	goal = make_unique<Goal>(Transform{ {(windowSize.x - goalSize) / 2, 0}, {goalSize, goalSize}, 0 }, "resources/Sprites/Bebe.png");
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
				gameObject->followView({ 0, -offsetY });
			}
		}
	}
}

sf::View Level::Update(double deltaTime) {
	struct LevelUpdateValues levelUpdateValues;
	struct PlayerModifiersValue playerModifiersValue { player->getDamageMultiplier(), player->getGoldMultiplier() };

	//cout << "Start : Gold: " << levelUpdateValues.goldEarned << " scrolling: " << levelUpdateValues.scrollingPenalty << "player killed: " << levelUpdateValues.playerKilled << endl;

	// Update the level view
	UpdateView(deltaTime);

	// Update du Player
	player->Update(deltaTime, view, windowSize, player->getPosition(), &gameObjects, &levelUpdateValues);

	// Update de tous les gameObjects
	for (auto const& gameObject : gameObjects) {

		// Update the gameObject
		gameObject->Update(deltaTime, view, windowSize, player->getPosition(), &gameObjects, &levelUpdateValues);

		// Handle collisions with all gameObjects
		gameObject->handleCollisions(&gameObjects, playerModifiersValue, &levelUpdateValues);

		// Handle collision with the player
		gameObject->handleCollision(*player, playerModifiersValue, &levelUpdateValues);
	}

	//cout << "End : Gold: " << levelUpdateValues.goldEarned << " scrolling: " << levelUpdateValues.scrollingPenalty << "player killed: " << levelUpdateValues.playerKilled << endl;

	// If player is killed
	if (levelUpdateValues.playerKilled) {
		cout << "GAMEOVER" << endl;
		game->changeState(GameState::GAMEOVER);
	}

	// Apply level updates
	scrollingSpeed += levelUpdateValues.scrollingPenalty;
	
	// Supprimer les objets détruits de la liste gameObjects
	// Marquer les objets à supprimer
	auto it = ranges::remove_if(gameObjects.begin(), gameObjects.end(),
		[&](const std::unique_ptr<GameObject>& obj) {
			return ranges::find(levelUpdateValues.killedObjects.begin(), levelUpdateValues.killedObjects.end(), obj.get()) != levelUpdateValues.killedObjects.end();
		});

	// Supprimer les objets marqués
	gameObjects.erase(it.begin(), it.end());

	// Add rewards to player
	player->addGold(levelUpdateValues.goldEarned);

	// 
	if (goal->isReached(*player)) {
		game->changeState(GameState::VICTORY);

		ResourceManager::playSound("resources/Audio/Applause.wav");
		ResourceManager::playSound("resources/Audio/Baby_Sound.wav");
		
		player->setPosition({ goal->getPosition().x+53, goal->getPosition().y + 140});

		//game->changeState(GameState::SHOP);
	}

	return view;
}
#pragma endregion Update

// Render
void Level::renderBackground(sf::RenderWindow& window) const {
	for (auto const& backgroundPosition : backgroundsPositions) {
		sf::Texture texture;
		texture = ResourceManager::getTexture(getBackgroundPath());

		sf::Sprite sprite;
		sprite.setTexture(texture);

		sprite.setScale(static_cast<float>(windowSize.x/texture.getSize().x) , static_cast<float>(windowSize.y / texture.getSize().y));
		sprite.setPosition(static_cast<float>(backgroundPosition.first), static_cast<float>(backgroundPosition.second));

		//Draw the sprite
		window.draw(sprite);
	}
}

void Level::Render(sf::RenderWindow& window) const {
	renderBackground(window);
	for (auto const& gameObject : gameObjects) {
		gameObject->Render(window);
	}
	goal->Render(window);
	player->Render(window);
}

// Handle input
void Level::handleInput(sf::Keyboard::Key key, bool isPressed) {
	player->handleInput(key, isPressed);
}

// Getter
unique_ptr<Player> Level::getPlayerPtr() { return std::move(player); }