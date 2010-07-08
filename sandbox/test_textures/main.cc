#include <mln/core/image/image2d.hh>
#include <mln/value/rgb8.hh>
#include <mln/value/int_u8.hh>
#include <mln/io/ppm/load.hh>
#include <mln/io/pgm/load.hh>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
  using namespace mln;

  image2d<value::rgb8> lena = io::ppm::load<value::rgb8>("lena.ppm");
  image2d<unsigned char> lena_pgm = io::pgm::load<unsigned char>("lena.pgm");

 // Declare and create a new window
 sf::Window window(sf::VideoMode(800, 600), "SFML window");

 // Activate the window for OpenGL rendering
 window.SetActive();

 glEnable(GL_TEXTURE_2D);
 glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );

 GLuint tex;
 glGenTextures(1, &tex);
 glBindTexture(GL_TEXTURE_2D, tex);
 glPixelStorei(GL_UNPACK_ALIGNMENT,1);
 glTexImage2D(GL_TEXTURE_2D,
              0, GL_RGB, lena.ncols() + 6, lena.nrows() + 6,
              0, GL_LUMINANCE, GL_UNSIGNED_BYTE, lena_pgm.buffer());
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

 std::cout << gluErrorString(glGetError()) << std::endl;


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
    glViewport(0,0, window.GetWidth(), window.GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1); glVertex2f(0,0);
    glTexCoord2f(0,0); glVertex2f(0,0.5);
    glTexCoord2f(1,0); glVertex2f(0.5,0.5);
    glTexCoord2f(1,1); glVertex2f(0.5,0);
    glEnd();

    // End the current frame and display its contents on screen
    window.Display();
 }

}
