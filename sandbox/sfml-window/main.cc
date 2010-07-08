#include <SFML/Window.hpp>

int main()
{
 // Declare and create a new window
 sf::Window window(sf::VideoMode(800, 600), "SFML window");

 // The main loop - ends as soon as the window is closed
 while (window.IsOpened())
 {
    // Event processing
    sf::Event event;
    while (window.GetEvent(event))
    {
        // Request for closing the window
        if (event.Type == sf::Event::Closed)
            window.Close();
    }

    // Activate the window for OpenGL rendering
    window.SetActive();

    // OpenGL drawing commands go here...

    // End the current frame and display its contents on screen
    window.Display();
 }

}
