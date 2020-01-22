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

    bool levelOne = false;
    bool levelTwo = false;
    bool levelThree = false;


    //introduction slides
    bool introOn = false;
    bool menuOn = true;

    Texture introTexture = textr("sprites/Level_select.png");
    Sprite intro = sprite(introTexture);

    Clock introClock;
    Time introTime;

    /*Music introMusic;
    if (!introMusic.openFromFile(""))
        return -1;
    introMusic.setVolume(20);*/

    int slideNum = 0;
    int fadeCounter = 0;
    int slideChanger = 3;


    //main character
    bool playerFreeze = false;
    float moveInterval = 2;

    Texture playerTexture = textr("sprites/main_player.png");
    Sprite player = sprite(playerTexture, 2, 2, 100, 100);
    player.setTextureRect(IntRect(0, 0, 16, 16));


    //lost souls and npcs
    Texture lostSoulTexture1 = textr("sprites/lostsoul_1.png");
    Sprite lostSoul1 = sprite(lostSoulTexture1, 2, 2, 400, 510);
    lostSoul1.setTextureRect(IntRect(0, 0, 16, 16));

    Texture lostSoulTexture2 = textr("sprites/lostsoul_2.png");
    Sprite lostSoul2 = sprite(lostSoulTexture2, 2, 2, 900, 230);
    lostSoul2.setTextureRect(IntRect(0, 0, 16, 16));

    Texture lostSoulTexture3 = textr("sprites/lostsoul_3.png");
    Sprite lostSoul3 = sprite(lostSoulTexture3, 2, 2, 200, 300);
    lostSoul3.setTextureRect(IntRect(0, 0, 16, 16));


    //walls and objects
    vector<RectangleShape>globalwall;
    vector<RectangleShape>object;

    globalwall.push_back(rect(-10, -10, 1034, 20, Color::Blue));
    globalwall.push_back(rect(-10, -10, 20, 778, Color::Red));
    globalwall.push_back(rect(-10, 758, 1034, 20, Color::Yellow));
    globalwall.push_back(rect(1014, -10, 20, 778, Color::Green));


    //level one
    Texture mapTexture1 = textr("sprites/background_1.png");
    Sprite map1 = sprite(mapTexture1, 5.12, 5.12);


    //level two
    Texture mapTexture2 = textr("sprites/background_1.png");
    Sprite map2 = sprite(mapTexture2, 5.12, 5.12);


    //level three
    Texture mapTexture3 = textr("sprites/background_1.png");
    Sprite map3 = sprite(mapTexture3, 5.12, 5.12);



    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        if (introOn == true)
        {
            introTime = introClock.getElapsedTime();

            if (introTime.asSeconds() < slideChanger)
            {
                fadeCounter=introTime.asSeconds()*(255/slideChanger);
            }
            else if (introTime.asSeconds() >= slideChanger && introTime.asSeconds() < (slideChanger*2))
            {
                fadeCounter=255-((introTime.asSeconds()-slideChanger)*(255/slideChanger));
            }
            else
            {
                slideNum++;

                if (slideNum == 1)
                {
                    intro.setTextureRect(IntRect(65, 275, 200, 150));
                    intro.setPosition(0,60);
                    introClock.restart();
                }
                else if (slideNum == 2)
                {
                    intro.setTextureRect(IntRect(65, 520, 200, 150));
                    intro.setPosition(0,60);
                    introClock.restart();
                }
                else if (slideNum == 3)
                {
                    intro.setTextureRect(IntRect(65, 766, 200, 150));
                    intro.setPosition(0,60);
                    introClock.restart();
                }
                else if (slideNum == 4)
                {
                    intro.setTextureRect(IntRect(65, 1010, 200, 150));
                    intro.setPosition(0,60);
                    introClock.restart();
                }
                else if (slideNum == 5)
                {
                    intro.setTextureRect(IntRect(65, 1227, 200, 350));
                    intro.setPosition(220, 0);
                    intro.setScale(1.8,1.8);
                    slideChanger = 5;
                    introClock.restart();
                }
                else if (slideNum == 6)
                {
                    window.clear();
                    //roommusicsand.play();
                    introOn = false;
                }
            }

            intro.setColor(sf::Color(255, 255, 255, fadeCounter));
            window.clear();
            window.draw(intro);

            window.display();

        }

        else if (menuOn == true) {

            if (startOn == false && Mouse::isButtonPressed(Mouse::Left) && 8 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 257 && 668 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 755){
                startOn = true;
            }

            if (startOn == true && Mouse::isButtonPressed(Mouse::Left) && 35 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 330 && 300 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 500) {
                levelOne = true;
                cout<<"Level one selected"<<endl;

                object.clear();
                object.push_back(rect(81, 2, 10, 278, Color(56, 56, 56)));//building left left
                object.push_back(rect(0, 270, 91, 10, Color(56,56,56)));
                object.push_back(rect(91, 51, 80, 5, Color(122,5,200)));//gate
                object.push_back(rect(175, 2, 10, 278, Color(82, 5, 23))); //building left right
                object.push_back(rect(175, 270, 215, 10, Color(82, 5, 23)));
                object.push_back(rect(380, 2, 10, 278, Color(82, 5, 23)));
                object.push_back(rect(680, 2, 10, 278, Color(230, 200, 62)));//buildings right
                object.push_back(rect(680, 270, 340, 10, Color(230, 200, 62)));

                menuOn = false;
            }
            else if (startOn == true && Mouse::isButtonPressed(Mouse::Left) && 360 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 660 && 300 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 500){
                levelTwo = true;
                cout<<"Level two selected"<<endl;
                object.clear();
                menuOn = false;
            }
            else if (startOn == true && Mouse::isButtonPressed(Mouse::Left) && 690 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 990 && 300 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 500){
                levelThree = true;
                cout<<"Level three selected"<<endl;
                object.clear();
                menuOn = false;
            }

            window.clear();

            if (startOn){
                window.draw(levels);
            } else {
                window.draw(menu);
            }

            window.display();
        }

        else {

            counter++;
            cout<<"Mouse x: "<<Mouse::getPosition(window).x<<"Mouse y: "<<Mouse::getPosition(window).y<<endl;


            if (playerFreeze == false)
            {
                if (Keyboard::isKeyPressed(Keyboard::D))
                {
                    player.setTextureRect(IntRect(counter/16%4*16, 32, 16, 16));
                    player.move(moveInterval, 0);

                    for (int i = 0; i < globalwall.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                            player.move(-moveInterval, 0);
                    }

                    for (int i = 0; i < object.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                            player.move(-moveInterval, 0);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    player.setTextureRect(IntRect(counter/16%4*16, 48, 16, 16));
                    player.move(-moveInterval, 0);

                    for (int i = 0; i < globalwall.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                            player.move(moveInterval, 0);
                    }

                    for (int i = 0; i < object.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                            player.move(moveInterval, 0);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    player.setTextureRect(IntRect(counter/16%4*16, 16, 16, 16));
                    player.move(0, -moveInterval);

                    for (int i = 0; i < globalwall.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                            player.move(0, moveInterval);
                    }

                    for (int i = 0; i < object.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                            player.move(0, moveInterval);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::S))
                {
                    player.setTextureRect(IntRect(counter/16%4*16, 0, 16, 16));
                    player.move(0, moveInterval);

                    for (int i = 0; i < globalwall.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(globalwall[i].getGlobalBounds()))
                            player.move(0, -moveInterval);
                    }

                    for (int i = 0; i < object.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(object[i].getGlobalBounds()))
                            player.move(0, -moveInterval);
                    }
                }
            }

            if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A))
                player.setTextureRect(IntRect(0, 0, 16, 16));



            //level one
            if (levelOne == true && levelTwo == false && levelThree == false){

            }

            //level two
            else if (levelOne == false && levelTwo == true && levelThree == false){

            }

            //level three
            else if (levelOne == false && levelTwo == false && levelThree == true){

            }

            //window drawings
            window.clear(); //clears the screen

            if (levelOne == true){
                window.draw(map1);
                window.draw(lostSoul1);
            }
            else if (levelTwo == true){
                window.draw(map2);
                window.draw(lostSoul2);
            }
            else if (levelThree == true){
                window.draw(map3);
                window.draw(lostSoul3);
            }

            window.draw(player);

            for(int i = 0; i < globalwall.size(); i++){
                window.draw(globalwall[i]);
            }

            for(int i = 0; i < object.size(); i++){
                window.draw(object[i]);
            }

            window.display();   //displays everything on the video card to the monitor
        }   //ends the game loop
    }

    return 0;
}

