#include "screen.h"
#include "textBox.h"
#include "team.h"

class EndTurnScreen : public Screen {
public:
    EndTurnScreen(sf::RenderWindow& window, ScreenHolder& screen_holder, std::shared_ptr<Team> team);

    bool update(sf::Time dt);
    bool draw();
private:
    sf::Time timeLeft;
    sf::RectangleShape background;
    TextBox top_text;
    TextBox bottom_text;
    std::shared_ptr<Team> next_team;
};