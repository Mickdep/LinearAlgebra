// LineaireAlgebra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MatrixFactory.h"
#include "CVector3d.h"
#include "CMatrix3d.h"
#include "Cube.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Camera.h"

int main()
{
	//Initialize memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Initialize the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "LINAL vectors", sf::Style::Default, settings);
	window.setFramerateLimit(30);

	//Vector with all the game objects in it
	std::vector<std::shared_ptr<GameObject>> game_objects;
	game_objects.reserve(300);

	//Create your own space ship and the target
	auto space_ship = std::make_shared<SpaceShip>();
	auto target = std::make_shared<Cube>();

	//Add them to the object list
	game_objects.push_back(space_ship);
	game_objects.push_back(target);

	//Create a camera. All the relevant vectors are inside the constructor.
	Camera camera;

	//Create a camera and perspective matrix.
	const auto perspective_projection_matrix = MatrixFactory::get_perspective_projection_matrix(1, 6000, 90);

	bool perpendicular_toggled = true;


	sf::Clock clock; // starts the clock
	while (window.isOpen())
	{
		const sf::Time time_elapsed = clock.getElapsedTime();
		if (target) {
			target->pulsate(time_elapsed);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::J) {
					if (perpendicular_toggled) {
						space_ship->add_perpendicular();
					}
					else {
						space_ship->remove_perpendicular();
					}
					perpendicular_toggled = !perpendicular_toggled;
				}
			}
		}

		//BARREL ROLL LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//Get the axis of rotation by making an axis that goes straight through the ship. Front and back form the axis.
			const auto axis = std::make_shared<CVector3d>(space_ship->get_back()->x - space_ship->get_front()->x, space_ship->get_back()->y - space_ship->get_front()->y, space_ship->get_back()->z - space_ship->get_front()->z);
			space_ship->rotate_around_axis(axis, -10);

		}
		//BARREL ROLL RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Get the axis of rotation by making an axis that goes straight through the ship. Front and back form the axis.
			const auto axis = std::make_shared<CVector3d>(space_ship->get_back()->x - space_ship->get_front()->x, space_ship->get_back()->y - space_ship->get_front()->y, space_ship->get_back()->z - space_ship->get_front()->z);
			space_ship->rotate_around_axis(axis, 10);
		}
		//GO UP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			const auto transformation_matrix = MatrixFactory::get_translation_matrix_3d(0, -4, 0);
			space_ship->transform(transformation_matrix);
		}
		//GO DOWN
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			const auto transformation_matrix = MatrixFactory::get_translation_matrix_3d(0, 4, 0);
			space_ship->transform(transformation_matrix);
		}
		//MOVE LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//Calculate two vectors by subtracting 2 points.
			const auto vector1 = std::make_shared<CVector3d>(space_ship->vectors[2].x - space_ship->vectors[4].x, space_ship->vectors[2].y - space_ship->vectors[4].y, space_ship->vectors[2].z - space_ship->vectors[4].z);
			const auto vector2 = std::make_shared<CVector3d>(space_ship->vectors[3].x - space_ship->vectors[4].x, space_ship->vectors[3].y - space_ship->vectors[4].y, space_ship->vectors[3].z - space_ship->vectors[4].z);

			//Get the out-product/cross-product and normalize it
			const auto outproduct = vector1->get_out_product(vector2)->normalize();

			//Get the translation matrix
			const auto transformation_matrix = MatrixFactory::get_translation_matrix_3d(-outproduct->x * 10, -outproduct->y * 10, -outproduct->z * 10);

			//Transform it
			space_ship->transform(transformation_matrix);
		}
		//MOVE RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Calculate two vectors by subtracting 2 points.
			const auto vector1 = std::make_shared<CVector3d>(space_ship->vectors[2].x - space_ship->vectors[4].x, space_ship->vectors[2].y - space_ship->vectors[4].y, space_ship->vectors[2].z - space_ship->vectors[4].z);
			const auto vector2 = std::make_shared<CVector3d>(space_ship->vectors[3].x - space_ship->vectors[4].x, space_ship->vectors[3].y - space_ship->vectors[4].y, space_ship->vectors[3].z - space_ship->vectors[4].z);

			//Get the out-product/cross-product and normalize it
			const auto outproduct = vector1->get_out_product(vector2)->normalize();

			//Get the translation matrix
			const auto transformation_matrix = MatrixFactory::get_translation_matrix_3d(outproduct->x * 10, outproduct->y * 10, outproduct->z * 10);

			//Transform it
			space_ship->transform(transformation_matrix);
		}
		//ROTATE X-AXIS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			space_ship->rotate_around_x_axis(4);
		}
		//ROTATE Y-AXIS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			space_ship->rotate_around_y_axis(4);
		}
		//ROTATE X-AXIS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			space_ship->rotate_around_x_axis(-4);
		}
		//ROTATE Y-AXIS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			space_ship->rotate_around_y_axis(-4);
		}
		//REVERSE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			//Calculate direction vector
			const auto direction = space_ship->get_perp();
			space_ship->move_in_direction(direction);
		}
		//ACCELERATE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			//Calculate direction vector
			const auto direction = space_ship->get_perp();
			direction->x = -direction->x;
			direction->y = -direction->y;
			direction->z = -direction->z;
			space_ship->move_in_direction(direction);
		}
		//SHOOT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//Create a new bullet
			auto bullet = std::make_shared<Bullet>();

			//Get the vector that is perpendicular to the ship(it is normalized already).
			bullet->direction = space_ship->get_perp();
			//Create 2 points for the bullet so it has a body
			const auto vec = CVector3d(space_ship->vectors[3].x, space_ship->vectors[3].y, space_ship->vectors[3].z);
			const auto vec2 = CVector3d(space_ship->vectors[3].x + (bullet->direction->x * 30), space_ship->vectors[3].y + (bullet->direction->y * 30), space_ship->vectors[3].z + (bullet->direction->z * 30));
			//Add the points to the bullet
			bullet->vectors.push_back(vec);
			bullet->vectors.push_back(vec2);
			//Add the bullet to the game objects so it gets drawn
			game_objects.push_back(bullet);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			camera.move_forward();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			camera.move_backwards();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			camera.rotate_right();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			camera.rotate_left();
		}
		window.clear();

		//Execute the projection and camera matrix here
		std::vector<std::shared_ptr<GameObject>> projection_game_objects;

		//Holds the bullets that need to be removed from the game
		std::vector<std::shared_ptr<GameObject>> game_objects_to_remove;


		//Create the transformation matrix used for perspective and camera
		const auto transformation_matrix = *perspective_projection_matrix * camera.camera_matrix;

		for (const auto object : game_objects)
		{
			//Clone the object so it's real values dont get edited
			auto copied_object = object->clone();
			copied_object->transform(transformation_matrix);

			//Naberekening
			for (auto i = 0; i < copied_object->vectors.size(); i++)
			{
				copied_object->vectors[i].x = (800 / 2) + ((copied_object->vectors[i].x + 1) / copied_object->vectors[i].w) * 800 * 0.5;
				copied_object->vectors[i].y = (600 / 2) + ((copied_object->vectors[i].y + 1) / copied_object->vectors[i].w) * 600 * 0.5;
				copied_object->vectors[i].z = -copied_object->vectors[i].z;
			}
			projection_game_objects.push_back(copied_object);
			//Try to cast the object to a bullet.
			std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(object);
			//If it was cast successfully we know its a bullet.
			if (bullet)
			{
				//If it goes past one of these z coords: remove it from the game
				if (bullet->vectors[0].z <= -4000 || bullet->vectors[0].z >= 450)
				{
					game_objects_to_remove.push_back(bullet);
				}
				else
				{
					//Translate the bullet
					const auto bullet_translation_matrix = MatrixFactory::get_translation_matrix_3d(20 * -bullet->direction->x, 20 * -bullet->direction->y, 20 * -bullet->direction->z);
					bullet->transform(bullet_translation_matrix);
					//Check for bullet hit here.
					if (target) {
						if (bullet->vectors[0].x >= target->vectors[0].x && bullet->vectors[0].x <= target->vectors[3].x) {
							if (bullet->vectors[0].y >= target->vectors[0].y && bullet->vectors[0].y <= target->vectors[4].y) {
								if (bullet->vectors[0].z <= target->vectors[0].z && bullet->vectors[0].z >= target->vectors[1].z) {
									std::cout << "You hit the target!" << std::endl;
									game_objects_to_remove.push_back(target);
									target = nullptr;
								}
							}
						}
					}
				}
			}
		}

		//Remove all bullets that were queued in this vector.
		for (const auto object : game_objects_to_remove)
		{
			game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), object), game_objects.end());
		}
		for (auto i = 0; i < projection_game_objects.size(); i++)
		{
			for (auto j = 0; j < projection_game_objects[i]->indices.size(); j += 2)
			{
				sf::Vertex line[2];
				line[0] = sf::Vertex(sf::Vector2f(projection_game_objects[i]->vectors[projection_game_objects[i]->indices[j]].x, projection_game_objects[i]->vectors[projection_game_objects[i]->indices[j]].y));
				line[1] = sf::Vertex(sf::Vector2f(projection_game_objects[i]->vectors[projection_game_objects[i]->indices[j + 1]].x, projection_game_objects[i]->vectors[projection_game_objects[i]->indices[j + 1]].y));
				window.draw(line, 2, sf::Lines);
				//window.draw(projection_game_objects[i]->vectors[projection_game_objects[i]->indices[j]].get_vector_notation());
			}
		}
		window.display();
	}

	return EXIT_SUCCESS;
}

