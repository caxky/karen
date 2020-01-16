#include <SFML/Graphics.hpp> //includes SFML libraries
#include "shapeCreator.h"
#include "spriteCreator.h"
#include "textCreator.h"
#include <iostream>

using namespace std;
using namespace sf; //for graphics

int main()
{
    RenderWindow window(VideoMode(1024,768),"Karen");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    //menus (start and level)
    bool startOn = false;

    Texture menuTexture = textr("sprites/Titlescreen_Karen.png");
    Sprite menu = sprite(menuTexture);

    Texture levelsTexture = textr("sprites/Level_select.png");
    Sprite levels = sprite(levelsTexture);

    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        if (startOn == false && Mouse::isButtonPressed(Mouse::Left) && 8 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 257 && 668 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 755){
            startOn = true;
        }

        window.clear(); //clears the screen
        if (startOn){
            window.draw(levels);
        } else {
            window.draw(menu);
        }
        window.display();   //displays everything on the video card to the monitor
    }   //ends the game loop

    return 0;
}

