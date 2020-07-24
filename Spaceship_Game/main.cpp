#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <cstdlib>

using namespace sf;
using namespace std;


int main()
{
	//Mengatur angka acak sesuai waktu
	srand(time(NULL));

	//Membuat Window
	RenderWindow window(sf::VideoMode(640, 480), "Dodge the Asteroid - Ghifari Yusuf Abdillah");

	//Melimit frame window menjadi 60 fps
	window.setFramerateLimit(60);

	//Load Font
	Font font;
	font.loadFromFile("Fonts/batmfa.ttf");

	//User Interface
	//Membuat Tulisan Health
	Text healthText;
	healthText.setFont(font);
	healthText.setCharacterSize(20);
	healthText.setFillColor(Color::Green);
	healthText.setPosition(25.f, 445.5f);
	healthText.setString("HEALTH");

	//Membuat Teks Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(225.f, window.getSize().y / 2);
	gameOverText.setString("Game Over!");

	//File Asteroid 
	Texture astTex;
	Sprite asteroid;

	//Load Texture Asteroid
	if (!astTex.loadFromFile("Textures/Asteroid.png"));
	{
		cout << "Couldn't Load Asteroid.png" << endl;
	}

	//Mengatur Tekstur Asteroid
	asteroid.setTexture(astTex);

	//Mengatur Skala Asteroid
	asteroid.setScale(Vector2f(0.25f, 0.25f));

	//Mengatur Spawn Timer Asteroid
	int asteroidSpawnTimer = 24;

	//Mengatur Vector Sprite Asteroid
	vector<Sprite> asteroids;
	asteroids.push_back(Sprite(asteroid));

	//File Spaceship
	Texture spaceTex;
	Sprite spaceship;

	//Mengatur nyawa dari Spaceship
	int health = 10;

	//Mengatur Tampilan Nyawa Spaceship
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Green);
	healthBar.setSize(Vector2f((float)health * 20.f, 20.f));
	healthBar.setPosition(125.f, 450.f);

	//Load Texture Spaceship
	if (!spaceTex.loadFromFile("Textures/Spaceship.png"))
	{
		cout << "Couldn't Load Spaceship.png" << endl;
		system("pause");
	}

	//Mengatur Texture Spaceship
	spaceship.setTexture(spaceTex);

	//Mengatur Skala Spaceship
	spaceship.setScale(Vector2f(0.045f, 0.045f));

	while (window.isOpen() && health > 0)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//Mengatur jika menekan tombol escape, akan keluar window
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		if (health > 0)
		{
			//Update Spaceship
			//Pergerakan Spaceship Menggunakan Keyboard
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				spaceship.move(Vector2f(-3.5f, 0.0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				spaceship.move(Vector2f(6.5f, 0.0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				spaceship.move(Vector2f(0.0f, -5.f));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				spaceship.move(Vector2f(0.0, 5.f));
			}

			//Mengatur Spaceship agar tidak keluar dari Window
			//Window Kiri
			if (spaceship.getPosition().x <= 0)
				spaceship.setPosition(0.f, spaceship.getPosition().y);
			//Window Kanan
			if (spaceship.getPosition().x >= window.getSize().x - spaceship.getGlobalBounds().width)
				spaceship.setPosition(window.getSize().x - spaceship.getGlobalBounds().width, spaceship.getPosition().y);
			//Window Atas
			if (spaceship.getPosition().y <= 0)
				spaceship.setPosition(spaceship.getPosition().x, 0.f);
			//Window Bawah
			if (spaceship.getPosition().y >= window.getSize().y - spaceship.getGlobalBounds().height)
				spaceship.setPosition(spaceship.getPosition().x, window.getSize().y - spaceship.getGlobalBounds().height);

			//Update Asteroid
			//Mengatur Pergerakan Asteroid
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				asteroids[i].move(-8.f, 0.f);

				if (asteroids[i].getPosition().x < 0 - asteroid.getGlobalBounds().width)
					asteroids.erase(asteroids.begin() + i);
			}

			//Mengatur Waktu Spawn Asteroid
			if (asteroidSpawnTimer < 24)
				asteroidSpawnTimer++;

			if (asteroidSpawnTimer >= 24)
			{
				//Mengatur Posisi Awal Asteroid
				asteroid.setPosition(window.getSize().x, rand() % int(window.getSize().y - asteroid.getGlobalBounds().height));
				asteroids.push_back(Sprite(asteroid));
				asteroidSpawnTimer = 0;
			}

			//Mengatur Collision Antar Gambar
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				if (spaceship.getGlobalBounds().intersects(asteroids[i].getGlobalBounds()))
				{
					health--;
					asteroids.erase(asteroids.begin() + i);
				}
			}

			//Update User Interface
			healthBar.setSize(Vector2f((float)health * 20.f, 20.f));
		}

		//Clear Window
		window.clear();

		//Draw Spaceship
		window.draw(spaceship);

		//Draw Asteroid
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			window.draw(asteroids[i]);
		}

		//Draw User Interface
		//Menampilkan Tulisan Health
		window.draw(healthText);

		//Menampilkan Bar Darah
		window.draw(healthBar);

		//Menampilkan Tulisan Gameover
		if (health <= 0)
			window.draw(gameOverText);

		//Display Window
		window.display();
	}
	return 0;
}