#include <SFML/Graphics.hpp> //includes SFML libraries
#include <SFML/Audio.hpp>
#include "shapeCreator.h"
#include "spriteCreator.h"
#include "textCreator.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;
using namespace sf; //for graphics

int main()
{
    RenderWindow window(VideoMode(1024,768),"Karen");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    //menus (start and level)
    bool startOn = false;
    int counter = 0;

    Texture menuTexture = textr("sprites/Titlescreen_Karen.png");
    Sprite menu = sprite(menuTexture);

    Texture levelsTexture = textr("sprites/Level_select.png");
    Sprite levels = sprite(levelsTexture);


    //introduction slides
    bool introOn = true;

    Texture introTexture = textr("sprites/Level_select.png");
    Sprite intro = sprite(introTexture);


    //main character
    bool playerFreeze = false;

    Texture playerTexture = textr("sprites/main_player.png");
    Sprite player = sprite(playerTexture, 8, 8);
    player.setTextureRect(IntRect(0, 0, 16, 16));


    //lost souls and npcs
    Texture lostSoulTexture1 = textr("sprites/lostsoul_1.png");
    Sprite lostSoul1 = sprite(lostSoulTexture1, 4, 4);
    lostSoul1.setTextureRect(IntRect(0, 0, 16, 16));

    Texture lostSoulTexture2 = textr("sprites/lostsoul_2.png");
    Sprite lostSoul2 = sprite(lostSoulTexture2, 4, 4, 100);
    lostSoul2.setTextureRect(IntRect(0, 0, 16, 16));

    Texture lostSoulTexture3 = textr("sprites/lostsoul_2.png");
    Sprite lostSoul3 = sprite(lostSoulTexture3, 4, 4, 200);
    lostSoul3.setTextureRect(IntRect(0, 0, 16, 16));


    //walls and objects
    vector<RectangleShape>globalwall;
    vector<RectangleShape>object;



    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        counter++;

        if (startOn == false && Mouse::isButtonPressed(Mouse::Left) && 8 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 257 && 668 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 755){
            startOn = true;
        }

        if (playerFreeze == false)
        {
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.setTextureRect(IntRect(counter/16%4*16, 32, 16, 16));
                player.move(3, 0);

                for (int i = 0; i < globalwall.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                        player.move(-3, 0);
                }

                for (int i = 0; i < object.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                        player.move(-3, 0);
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.setTextureRect(IntRect(counter/16%4*16, 48, 16, 16));
                player.move(-3, 0);

                for (int i = 0; i < globalwall.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                        player.move(3, 0);
                }

                for (int i = 0; i < object.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                        player.move(-3, 0);
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.setTextureRect(IntRect(counter/16%4*16, 16, 16, 16));
                player.move(0, -3);

                for (int i = 0; i < globalwall.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                        player.move(0, 3);
                }

                for (int i = 0; i < object.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                        player.move(-3, 0);
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.setTextureRect(IntRect(counter/16%4*16, 0, 16, 16));
                player.move(0, 3);

                for (int i = 0; i < globalwall.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                        player.move(0, -3);
                }

                for (int i = 0; i < object.size(); i++)
                {
                    if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                        player.move(-3, 0);
                }
            }
        }

        if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A))
            player.setTextureRect(IntRect(0, 0, 16, 16));




        window.clear(); //clears the screen

        if (startOn){
            window.draw(levels);
        } else {
            window.draw(menu);
        }

        window.draw(lostSoul1);
        window.draw(lostSoul2);
        window.draw(lostSoul3);
        window.draw(player);
        window.display();   //displays everything on the video card to the monitor
    }   //ends the game loop

    return 0;
}

