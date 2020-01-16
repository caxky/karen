#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

CircleShape circle(float radius, float posx, float posy, const Color colorInput){
    CircleShape c;
    c.setRadius(radius);
    c.setPosition(posx, posy);
    c.setFillColor(colorInput);

    return c;
}

RectangleShape rect(float posx, float posy, float sizex, float sizey, const Color colorInput){
    RectangleShape r;
    r.setSize(Vector2f(sizex, sizey));
    r.setPosition(posx, posy);
    r.setFillColor(colorInput);

    return r;
}
