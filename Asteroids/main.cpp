#include "PushdownMachine.h"
#include "GameIntroUI.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "LHG Code Exercise");
    sf::Clock GameClock;

    PushdownMachine mainGameMachine(new GameIntroUI(window));

    while (window.isOpen())
    {
        // Get the delta time for the game update
        sf::Time dt = GameClock.restart();

        // Poll for window being closed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Reset the window
        window.clear();

        //-----------------------------------------------------------------------------------
        // Game logic can go here      

        if (mainGameMachine.Update(dt.asSeconds()))
            mainGameMachine.Draw();

        //-----------------------------------------------------------------------------------
        // Display the updated game state
        window.display();
    }

    return 0;
}