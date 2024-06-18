#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"
#include <Player.h>
#include <Patern.h>
#include <iostream>


TEST(TestCase, TestName) {
    EXPECT_EQ(true, false);
}

// Mouvement
TEST(Movement, Gauche) {
    Player player{ {{360 , 540}, {100, 100}, 0}, 200, "" };
	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));


	player.handleInput(sf::Keyboard::Q, true);

    player.Update(0.1, view, windowSize, player.getPosition());

	Vector2 position{ 360-20, 540 };
	EXPECT_EQ(player.getPosition(), position);
}

TEST(Movement, Bas) {
	Player player{ {{360 , 540}, {100, 100}, 0}, 200, "" };
	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

	player.handleInput(sf::Keyboard::S, true);

	player.Update(0.1, view, windowSize, player.getPosition());

	Vector2 position{ 360 , 540 + 20 };
	EXPECT_EQ(player.getPosition(), position);
}

TEST(Movement_Bloque, Droite) {
	Player player{ {{605, 540}, {100, 100}, 0}, 200, "" };
	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

	player.handleInput(sf::Keyboard::D, true);

	player.Update(0.1, view, windowSize, player.getPosition());

	Vector2 position{ 605, 540 };
	EXPECT_EQ(player.getPosition(), position);
}

TEST(Movement_Bloque, Haut) {
	Player player{ {{360 , 15}, {100, 100}, 0}, 200, "" };
	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

	player.handleInput(sf::Keyboard::Z, true);

	player.Update(0.1, view, windowSize, player.getPosition());

	Vector2 position{ 360 , 15 };
	EXPECT_EQ(player.getPosition(), position);
}

// Shoot Projectiles
TEST(ShootMissile, CooldownOff) {
	Player player{ {{360 , 540}, {100, 100}, 0}, 200, "" };
	
	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

	player.handleInput(sf::Keyboard::Space, true);

	auto newObject = player.Update(0.01, view, windowSize, player.getPosition());

	EXPECT_FALSE(newObject == nullptr);
}

TEST(ShootMissile, CooldownOn) {
	Player player{ {{360 , 540}, {100, 100}, 0}, 200, "" };

	Vector2 windowSize{ 720, 1080 };
	sf::View view;
	view.reset(sf::FloatRect(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

	player.handleInput(sf::Keyboard::Space, true);

	player.Update(0.01, view, windowSize, player.getPosition());
	auto newObject = player.Update(0.01, view, windowSize, player.getPosition());

	EXPECT_TRUE(newObject == nullptr);
}

// Load Patern
TEST(LoadPatern, Single) {
	std::string s = R"(<?xml version = "1.0"?>
						<Patern id="0" name="Single Drop">
							<Tear_Basic x="0" y="0" size_x="40" size_y="80"/>
						</Patern>)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)

	Patern p { doc.child("Patern") };

	std::string p_dump_ref =
		R"(id: 0 Name: Single Drop Size: 40, 80
Basic Tear, HP: 100

)";

	EXPECT_EQ(p.dump(), p_dump_ref);
}