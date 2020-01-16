#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Sprite playerSprite(Texture playerTexture, float posx, float posy, const IntRect rectint(int x1, int y1, int x2, int y2), float scaleX, float scaleY){
    Sprite player;

    player.setTexture(playerTexture);
    player.setPosition(posx, posy);
    player.setTextureRect(rectint);
    player.scale(scaleX, scaleY);

    return player;
}

Texture tex(const string fileName){
    Texture t;

    t.loadFromFile(fileName);

    return t;
}

Sprite otherSprite(Texture otherTexture, float posx, float posy, float scaleX, float scaleY){
    Sprite other;

    other.setTexture(otherTexture);
    other.setPosition(posx, posy);
    other.scale(scaleX, scaleY);

    return other;
}
