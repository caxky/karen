#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Texture textr(const string& fileName){
    Texture t;

    t.loadFromFile(fileName);

    return t;
}

Sprite sprite(const Texture& playerTexture, float posx = 0, float posy = 0, float scaleX = 1, float scaleY = 1){
    Sprite s;

    s.setTexture(playerTexture);
    s.setPosition(posx, posy);
    s.scale(scaleX, scaleY);

    return s;
}


