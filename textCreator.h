#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Text tex(const Font& fontStyle, float charSize, int posx, int posy, const Color colorInput, const string stringText){
    Text t;

    t.setFont(fontStyle);
    t.setCharacterSize(charSize);
    t.setPosition(posx, posy);
    t.setFillColor(colorInput);
    t.setString(stringText);

    return t;
}
