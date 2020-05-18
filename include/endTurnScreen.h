#include "screen.h"
#include "textBox.h"

class EndTurnScreen : public Screen {
public:
    EndTurnScreen(sf::RenderWindow& window, ScreenHolder& screen_holder);

    bool update(sf::Time dt);
    bool draw();
private:
    sf::Time timeLeft;
    sf::RectangleShape background;
    TextBox top_text;
    TextBox bottom_text;
};