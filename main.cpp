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

    //initial console stuff
    cout<<"Welcome to Karen!\n"<<endl;
    cout<<"Controls:"<<endl;
    cout<<"WASD - Move player\nE - Interact with NPC\nESC - Close game\nLeft mouse - Select level/play\n\n"<<endl;
    cout<<"Objective of the game is to 'free the lost souls' by completing each levels minigame. First you must find the lost soul you're told to find by Michael the archangel, then you complete the minigame they give you.\n\n"<<endl;
    cout<<"To skip intro, change 'introOn' to false on line 54"<<endl;



    //menus (start, end, and level)
    bool startOn = false;
    int counter = 0;

    Texture menuTexture = textr("sprites/Titlescreen_Karen.png");
    Sprite menu = sprite(menuTexture);

    Texture levelsTexture = textr("sprites/Level_select.png");
    Sprite levels = sprite(levelsTexture);

    bool levelOne = false;
    bool levelTwo = false;

    bool LevelOneCompleted = false;
    bool LevelTwoCompleted = false;

    Texture xtexture1 = textr("sprites/x_level1.png");
    Sprite x_level1 = sprite(xtexture1);
    Texture xtexture2 = textr("sprites/x_level2.png");
    Sprite x_level2 = sprite(xtexture2);

    Texture endscreentexture = textr("sprites/endscreen.png");
    Sprite endScreen = sprite(endscreentexture);


    //introduction slides
    bool introOn = true;
    bool menuOn = true;

    Texture introTexture = textr("sprites/intro.png");
    Sprite intro = sprite(introTexture);

    Clock introClock;
    Time introTime;

    /*Music introMusic;
    if (!introMusic.openFromFile(""))
        return -1;
    introMusic.setVolume(20);*/

    int slideNum = 0;
    int fadeCounter = 0;
    int slideChanger = 5;


    //main character
    bool playerFreeze = false;
    float moveInterval = 2;

    Texture playerTexture = textr("sprites/main_player.png");
    Sprite player = sprite(playerTexture, 2, 2, 100, 100);
    player.setTextureRect(IntRect(0, 0, 16, 16));


    //lost souls and npcs
    Texture lostSoulTexture1 = textr("sprites/lostsoul_1.png");
    Sprite lostSoul1 = sprite(lostSoulTexture1, 2, 2, 644, 311);
    lostSoul1.setTextureRect(IntRect(0, 0, 16, 16));
    Texture lostSoulDialogueTexture1 = textr("sprites/dialogue_1.png");
    Sprite lostSoulDialogue1 = sprite(lostSoulDialogueTexture1);

    bool dialogueLostSoul1 = false;

    Texture lostSoulTexture2 = textr("sprites/lostsoul_2.png");
    Sprite lostSoul2 = sprite(lostSoulTexture2, 2, 2, 900, 230);
    lostSoul2.setTextureRect(IntRect(0, 0, 16, 16));
    Texture lostSoulDialogueTexture2 = textr("sprites/dialogue_2.png");
    Sprite lostSoulDialogue2 = sprite(lostSoulDialogueTexture2);

    bool dialogueLostSoul2 = false;

    Texture lostSoulTexture3 = textr("sprites/lostsoul_3.png");
    Sprite lostSoul3 = sprite(lostSoulTexture3, 2, 2, 200, 300);
    lostSoul3.setTextureRect(IntRect(0, 0, 16, 16));

    Clock dialogueClock;
    Time dialogueTime;



    //walls, objects, and npc collisions
    vector<RectangleShape>globalwall;
    vector<RectangleShape>object;
    vector<RectangleShape>npcCollision;

    globalwall.push_back(rect(-10, -10, 1034, 20, Color::Blue));
    globalwall.push_back(rect(-10, -10, 20, 778, Color::Red));
    globalwall.push_back(rect(-10, 758, 1034, 20, Color::Yellow));
    globalwall.push_back(rect(1014, -10, 20, 778, Color::Green));


    //level one
    Texture mapTexture1 = textr("sprites/background_1.png");
    Sprite map1 = sprite(mapTexture1, 5.12, 5.12);

    Texture minigameMapTexture1 = textr("sprites/minigamemap_1.png");
    Sprite minigameMap1 = sprite(minigameMapTexture1);

    bool minigameOneOn = false;

    vector<RectangleShape>minigameOneGame;
    Clock minigameOneSpawnClock;
    Time minigameOneSpawnTime;

    Texture lostSoulDialogueTexture3 = textr("sprites/dialogue_3.png");
    Sprite lostSoulDialogue3 = sprite(lostSoulDialogueTexture3);

    bool dialogueLostSoul3 = false;



    //level two
    Texture mapTexture2 = textr("sprites/background_2.png");
    Sprite map2 = sprite(mapTexture2, 5.12, 5.12);

    Texture minigameMapTexture2 = textr("sprites/minigamemap_2.png");
    Sprite minigameMap2 = sprite(minigameMapTexture2);

    bool minigameTwoOn = false;

    Texture lostSoulDialogueTexture4 = textr("sprites/dialogue_4.png");
    Sprite lostSoulDialogue4 = sprite(lostSoulDialogueTexture4);

    bool dialogueLostSoul4 = false;



    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        if (LevelOneCompleted == true && LevelTwoCompleted == true){
            window.clear();

            window.draw(endScreen);

            window.display();
        }
        else if (introOn == true)
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
                    intro.setTextureRect(IntRect(0, 768, 1024, 768));
                    introClock.restart();
                }
                else if (slideNum == 2)
                {
                    intro.setTextureRect(IntRect(0, 1536, 1024, 768));
                    introClock.restart();
                }
                else if (slideNum == 3)
                {
                    intro.setTextureRect(IntRect(0, 2304, 1024, 768));
                    introClock.restart();
                }
                else if (slideNum == 4)
                {
                    intro.setTextureRect(IntRect(0, 3072, 1024, 768));
                    introClock.restart();
                }
                else if (slideNum == 5)
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

            if (startOn == true && LevelOneCompleted == false && Mouse::isButtonPressed(Mouse::Left) && 171 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 471 && 297 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 497) {
                levelOne = true;
                cout<<"Level one selected"<<endl;

                npcCollision.clear();
                npcCollision.push_back(rect(657, 325, 5, 5, Color(0, 156, 56)));

                object.clear();
                object.push_back(rect(81, 2, 10, 278, Color(56, 56, 56)));//building left left
                object.push_back(rect(0, 270, 91, 10, Color(56,56,56)));
                object.push_back(rect(91, 51, 80, 5, Color(122,5,200)));//gate
                object.push_back(rect(175, 2, 10, 278, Color(82, 5, 23))); //building left right
                object.push_back(rect(175, 270, 215, 10, Color(82, 5, 23)));
                object.push_back(rect(380, 2, 10, 278, Color(82, 5, 23)));
                object.push_back(rect(680, 2, 10, 278, Color(230, 200, 62)));//buildings right
                object.push_back(rect(680, 270, 340, 10, Color(230, 200, 62)));

                player.setPosition(100, 100);
                minigameOneOn = false;

                dialogueClock.restart();

                menuOn = false;
            }
            else if (startOn == true && LevelTwoCompleted == false && Mouse::isButtonPressed(Mouse::Left) && 550 < Mouse::getPosition(window).x && Mouse::getPosition(window).x < 850 && 297 < Mouse::getPosition(window).y && Mouse::getPosition(window).y < 497){
                levelTwo = true;
                cout<<"Level two selected"<<endl;

                npcCollision.clear();
                npcCollision.push_back(rect(914, 246, 5, 5, Color(0, 156, 56)));

                object.clear();

                player.setPosition(100, 500);
                minigameTwoOn = false;

                dialogueClock.restart();

                menuOn = false;
            }

            window.clear();

            if (startOn){
                window.draw(levels);

                if (LevelOneCompleted == true){
                    window.draw(x_level1);
                }
                if (LevelTwoCompleted == true){
                    window.draw(x_level2);
                }

            } else {
                window.draw(menu);
            }

            window.display();
        }

        else {

            counter++;
            dialogueTime = dialogueClock.getElapsedTime();
            minigameOneSpawnTime = minigameOneSpawnClock.getElapsedTime();
            //cout<<"Mouse x: "<<Mouse::getPosition(window).x<<"Mouse y: "<<Mouse::getPosition(window).y<<endl;


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
            if (levelOne == true && levelTwo == false){
                if (minigameOneOn == false){

                    if (dialogueTime.asSeconds() < 10){
                        playerFreeze = true;
                        dialogueLostSoul3 = true;
                    }
                    else {
                        playerFreeze = false;
                        dialogueLostSoul3 = false;
                    }

                    for (int i = 0; i < npcCollision.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(npcCollision[i].getGlobalBounds())){
                            if (Keyboard::isKeyPressed(Keyboard::E)) {
                                player.setPosition(20, 500);
                                dialogueClock.restart();
                                minigameOneOn = true;
                            }
                        }
                    }

                } else {
                    if (dialogueTime.asSeconds() < 5){
                        playerFreeze = true;
                        dialogueLostSoul1 = true;
                    }
                    else {
                        object.clear();
                        playerFreeze = false;
                        dialogueLostSoul1 = false;

                        if (player.getPosition().x > 980){
                            minigameOneGame.clear();
                            npcCollision.clear();
                            LevelOneCompleted = true;
                            levelOne = false;
                            minigameOneOn = false;
                            menuOn = true;
                            startOn = true;
                        }


                        if (minigameOneSpawnTime.asMilliseconds() > 140){
                            minigameOneGame.push_back(rect(rand() % 600 + 300, 0, 5, 50, Color::White));
                            minigameOneSpawnClock.restart();
                        }

                        for (int i = 0; i < minigameOneGame.size(); i++){
                            if (player.getGlobalBounds().intersects(minigameOneGame[i].getGlobalBounds())) {
                                player.setPosition(20, 500);
                            }

                            minigameOneGame[i].move(0, 5);
                        }
                    }

                }

            }

            //level two
            else if (levelOne == false && levelTwo == true){
                if (minigameTwoOn == false){

                    if (dialogueTime.asSeconds() < 10){
                        playerFreeze = true;
                        dialogueLostSoul4 = true;
                    }
                    else {
                        playerFreeze = false;
                        dialogueLostSoul4 = false;
                    }

                    for (int i = 0; i < npcCollision.size(); i++)
                    {
                        if (player.getGlobalBounds().intersects(npcCollision[i].getGlobalBounds())){
                            if (Keyboard::isKeyPressed(Keyboard::E)) {
                                player.setPosition(20, 500);
                                dialogueClock.restart();

                                object.clear();
                                //ENTER WALL INFORMATION HERE
                                object.push_back(rect(111, 0, 5, 125, Color::Red));
                                object.push_back(rect(111, 189, 5, 125, Color::Red));
                                object.push_back(rect(224, 61, 5, 65, Color::Red));
                                object.push_back(rect(224, 188, 5, 65, Color::Red));
                                object.push_back(rect(169, 317, 5, 65, Color::Red));
                                object.push_back(rect(169, 633, 5, 130, Color::Red));
                                object.push_back(rect(281, 60, 5, 260, Color::Red));
                                object.push_back(rect(281, 505, 5, 65, Color::Red));
                                object.push_back(rect(338, 123, 5, 130, Color::Red));
                                object.push_back(rect(335, 442, 5, 65, Color::Red));
                                object.push_back(rect(335, 567, 5, 130, Color::Red));
                                object.push_back(rect(395, 188, 5, 65, Color::Red));
                                object.push_back(rect(395, 317, 5, 253, Color::Red));
                                object.push_back(rect(393, 700, 5, 70, Color::Red));
                                object.push_back(rect(450, 317, 5, 133, Color::Red));
                                object.push_back(rect(450, 505, 5, 65, Color::Red));
                                object.push_back(rect(504, 319, 5, 65, Color::Red));
                                object.push_back(rect(504, 447, 5, 187, Color::Red));
                                object.push_back(rect(558, 379, 5, 188, Color::Red));
                                object.push_back(rect(558, 631, 5, 65, Color::Red));
                                object.push_back(rect(615, 0, 5, 190, Color::Red));
                                object.push_back(rect(615, 317, 5, 140, Color::Red));
                                object.push_back(rect(615, 503, 5, 260, Color::Red));
                                object.push_back(rect(670, 60, 5, 130, Color::Red));
                                object.push_back(rect(670, 317, 5, 130, Color::Red));
                                object.push_back(rect(670, 505, 5, 130, Color::Red));
                                object.push_back(rect(726, 0, 5, 130, Color::Red));
                                object.push_back(rect(726, 255, 5, 130, Color::Red));
                                object.push_back(rect(783, 0, 5, 130, Color::Red));
                                object.push_back(rect(783, 188, 5, 130, Color::Red));
                                object.push_back(rect(839, 63, 5, 65, Color::Red));
                                object.push_back(rect(839, 188, 5, 190, Color::Red));
                                object.push_back(rect(839, 446, 5, 65, Color::Red));
                                object.push_back(rect(839, 568, 5, 65, Color::Red));
                                object.push_back(rect(890, 123, 5, 190, Color::Red));
                                object.push_back(rect(890, 378, 5, 65, Color::Red));
                                object.push_back(rect(890, 504, 5, 65, Color::Red));
                                object.push_back(rect(890, 633, 5, 65, Color::Red));
                                object.push_back(rect(955, 60, 5, 321, Color::Red));
                                object.push_back(rect(955, 455, 5, 190, Color::Red));

                                //VERTICAL
                                object.push_back(rect(169, 62, 60, 5, Color::Red));
                                object.push_back(rect(282, 62, 332, 5, Color::Red));
                                object.push_back(rect(840, 62, 120, 5, Color::Red));
                                object.push_back(rect(114, 123, 120, 5, Color::Red));
                                object.push_back(rect(335, 123, 240, 5, Color::Red));
                                object.push_back(rect(893, 123, 60, 5, Color::Red));
                                object.push_back(rect(114, 189, 120, 5, Color::Red));
                                object.push_back(rect(395, 189, 180, 5, Color::Red));
                                object.push_back(rect(613, 187, 240, 5, Color::Red));
                                object.push_back(rect(170, 254, 60, 5, Color::Red));
                                object.push_back(rect(281, 253, 60, 5, Color::Red));
                                object.push_back(rect(396, 253, 360, 5, Color::Red));
                                object.push_back(rect(955, 253, 120, 5, Color::Red));
                                object.push_back(rect(172, 320, 180, 5, Color::Red));
                                object.push_back(rect(395, 320, 60, 5, Color::Red));
                                object.push_back(rect(506, 320, 180, 5, Color::Red));
                                object.push_back(rect(172, 320, 180, 5, Color::Red));
                                object.push_back(rect(396, 320, 60, 5, Color::Red));
                                object.push_back(rect(508, 320, 180, 5, Color::Red));
                                object.push_back(rect(172, 376, 240, 5, Color::Red));
                                object.push_back(rect(507, 380, 60, 5, Color::Red));
                                object.push_back(rect(725, 379, 120, 5, Color::Red));
                                object.push_back(rect(169, 444, 180, 5, Color::Red));
                                object.push_back(rect(449, 447, 60, 5, Color::Red));
                                object.push_back(rect(449, 447, 60, 5, Color::Red));
                                object.push_back(rect(668, 447, 300, 5, Color::Red));


                                minigameTwoOn = true;
                            }
                        }
                    }

                } else {
                    if (dialogueTime.asSeconds() < 5){
                        playerFreeze = true;
                        dialogueLostSoul2 = true;
                    }
                    else {
                        playerFreeze = false;
                        dialogueLostSoul2 = false;

                        if (player.getPosition().x < 1000 && 970 < player.getPosition().x && player.getPosition().y < 235 && 205 < player.getPosition().y){
                            npcCollision.clear();
                            LevelTwoCompleted = true;
                            levelTwo = false;
                            minigameTwoOn = false;
                            menuOn = true;
                            startOn = true;
                        }

                    }

                }
            }

            //window drawings
            window.clear(); //clears the screen

            if (levelOne == true && minigameOneOn == false){
                window.draw(map1);
                window.draw(lostSoul1);

                if (dialogueLostSoul3 == true){
                    window.draw(lostSoulDialogue3);
                }

            } else if (levelOne == true && minigameOneOn == true){
                window.draw(minigameMap1);

                if (dialogueLostSoul1 == true){
                    window.draw(lostSoulDialogue1);
                }

                for (int i = 0; i < minigameOneGame.size(); i++){
                    window.draw(minigameOneGame[i]);
                }
            }

            if (levelTwo == true && minigameTwoOn == false){
                window.draw(map2);
                window.draw(lostSoul2);

                if (dialogueLostSoul4 == true){
                    window.draw(lostSoulDialogue4);
                }

            } else if (levelTwo == true && minigameTwoOn == true){
                window.draw(minigameMap2);

                if (dialogueLostSoul2 == true){
                    window.draw(lostSoulDialogue2);
                }
            }

            window.draw(player);

            //TEMP DRAWING FOR BORDERS/COLLISIONS
            /*
            for(int i = 0; i < globalwall.size(); i++){
                window.draw(globalwall[i]);
            }

            for(int i = 0; i < object.size(); i++){
                window.draw(object[i]);
            }

            for(int i = 0; i < npcCollision.size(); i++){
                window.draw(npcCollision[i]);
            }*/

            window.display();   //displays everything on the video card to the monitor
        }   //ends the game loop
    }

    return 0;
}

