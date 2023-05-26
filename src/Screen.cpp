#include "Screen.h"
#include "Screen.h"
#include "Camera.h"
#include "Shapes/Line3D.h"
#include "Shapes/XYZAxes.h"
#include "Shapes/Cube.h"
#include "Shapes/CubeFloor.h"
#include "World.h"
#include "Shapes/CustomShape3D.h"
#include "Transformations.h"



int Screen::width = 1;
int Screen::height = 1;


void Screen::gameLoop() {
    Camera camera(width, height);
       
    XYZAxes axes;

    CubeFloor floor(10);

    CustomShape3D groud("src\\OBJFiles\\Groud.obj",
        Transformations::getTranslationMatrix(0, 10, 0) * 
        Transformations::getScaleMatrix(10));

    CustomShape3D diamond("src\\OBJFiles\\Diamond.obj",
        Transformations::getTranslationMatrix(100, 10, 0));

    World world(this, &camera);


    world.push_back((Object3D*) &axes);
    world.push_back((Object3D*) &diamond);

    

    sf::Vector2i shift;
    sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), *window);
        

    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.moveRight(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.moveLeft(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.moveForward(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.moveBackward(1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            camera.lookLeftRight(0.01f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            camera.lookLeftRight(-0.01f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            camera.lookUpDown(0.01f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            camera.lookUpDown(-0.01f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            world.remove((Object3D*)&diamond);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            world.push_back((Object3D*)&diamond);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            world.remove((Object3D*)&groud);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            world.push_back((Object3D*)&groud);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            world.remove((Object3D*)&floor);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            world.push_back((Object3D*)&floor);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            camera.backToOrigin();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }

        shift = sf::Mouse::getPosition(*this->window) - sf::Vector2i(width/2,height/2);
        sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), *this->window);

        camera.lookLeftRight((float) -shift.x / 500);
        camera.lookUpDown((float) -shift.y / 500);


        // drawing section
        window->clear(sf::Color::Black);

        world.drawAll();

        // end of current frame
        // draws everything from hidden buffer to screen
        window->display();
    }
}