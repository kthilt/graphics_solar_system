///////////////////////////////////////////////////////////////////////////////
//File: solar_system.cpp
//Author: Kevin Hilt
//Date: November 21, 2014
//Course: Computer Graphics
//Instructor: Dr. Weiss
//
//Description: This is the main file for the solar_system program. It handles
//glut initialization and setting up the planet objects with their necessary
//textures, radii, distances, colors, etc. This program was based on orbit.cpp
//by Samuel R. Buss, and his header block is preserved below.
//
//The radii of the four inner planets are their radii from the initial 
//table / 60000. The radii of the four outer planets are their raadii from
//the initial table / 120000.
//The moon uses initial value / 30000.
//The sun was given a radius of 1, which is bigger than all the planets
//but not too large that it makes the model unviewable.
//
//Since the initial distances from the sun ranged from 88 to 60195 and
//such a wide range would have made the viewing experience worse,
//the distances below are semi-arbitrary numbers that convey the relative
//positions of the planets (4 inner, a wide gap, then 4 outer) while
//still keeping everything moderately close.
//
//Name      Radius      Distance        Year        Day
//-----------------------------------------------------------------------------
//Sun       1           0               0           25
//Mercury   0.0407      2               88          1416
//Venus     0.1009      2.5             225         5832
//Earth     0.1063      3               365         24
//Mars      0.0566      3.5             687         24.6
//Jupiter   0.595       6               4332        9.8
//Saturn    0.502       7.5             10761       10.2
//Uranus    0.213       9.5             30682       15.5
//Neptune   0.206       10.5            60195       15.8
///////////////////////////////////////////////////////////////////////////////

/*
* orbit.cpp
*
* Program to demonstrate how to use a local
* coordinate method to position parts of a
* model in relation to other model parts.
*
* Draws a simple solar system, with a sun, planet and moon.
* Based on sample code from the OpenGL programming guide
* by Woo, Neider, Davis.  Addison-Wesley.
*
* Author: Samuel R. Buss
*
* Software accompanying the book
* 3D Computer Graphics: A Mathematical Introduction with OpenGL,
* by S. Buss, Cambridge University Press, 2003.
*
* Software is "as-is" and carries no warranty.  It may be used without
* restriction, but if you modify it, please change the filenames to
* prevent confusion between different versions.
*
* Bug reports: Sam Buss, sbuss@ucsd.edu.
* Web page: http://math.ucsd.edu/~sbuss/MathCG
*
* USAGE:
*    Press "r" key to toggle (off and on) running the animation
*    Press "s" key to single-step animation
*    The up and down array keys control the time step used in the animation rate.
*    Each key press multiplies or divides the times by a factor of two.
*    Press ESCAPE to exit.
*/

// JMW: Minor modifications for CSC433/533 Computer Graphics, Fall 2014.

#include "header.h"

GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_FALSE;
bool is_wireframe = 1;
bool is_flat = 1;
bool is_textured = 0;
double user_resolution = 1;
bool help_on = 0;

planet_object sun, mercury, venus, earth, moon, mars,
              jupiter, saturn, uranus, neptune, stars;
ring rings;
              
user_view view; //Holds camera position values
float white_color[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat no_emission[4] = {0.0, 0.0, 0.0, 1.0};

//Helper function prototypes
void OpenGLInit( void );
void initialize_menu();
void menu_handler(int item);
void initialize_planet(planet_object &planet, string filename, string name, 
                       double radius, float distance_from_sun, 
                       float resoltuion, float red, float green, float blue,
                       float total_days, float total_hours);
bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
void displayImage( int x, int y, int w, int h, unsigned char* image );
void load_texture(string filename, GLuint &id, int rows, int columns, unsigned char* image);

// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
    // Need to double buffer for animation
    glutInit( &argc, argv );   
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    
    // Create and position the graphics window
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 800, 500 );
    glutCreateWindow("Solar System");

    // Initialize OpenGL.
    OpenGLInit();

    // Set up callback functions for key presses
    glutKeyboardFunc( KeyPressFunc );
    glutSpecialFunc( SpecialKeyFunc );

    // Set up the callback function for resizing windows
    glutReshapeFunc( ResizeWindow );

    // Callback for graphics image redrawing
    glutDisplayFunc( Animate );
    
    //Initialize the right click menu with all application functions
    initialize_menu();

    //Initialize planets
    //Arguments:
    //1: planet_object to initialize
    //2: texture image filename
    //3: display name for planet label
    //4: radius of planet
    //5: radius of planet's orbital  (distance from the sun)
    //6: resolution of planet (slices and stacks of gluSphere)
    //7-9: red, green, and blue values for untexture planet color
    //10: total number of days in a year
    //11: total number of hours in a day
    initialize_planet(sun, "./images/sun.bmp", "Sun", 1, 0.0, 15, 
                      1.0, 1.0, 0.0, 1, 25);
    initialize_planet(mercury, "./images/mercury.bmp", "Mercury", 0.0407, 2, 5,
                      0.7, 0.7, 0.7, 88, 1416);
    initialize_planet(venus, "./images/venus.bmp", "Venus", 0.1009, 2.5, 10,
                      1.0, 0.7, 0.4, 225, 5832);
    initialize_planet(earth, "./images/earth.bmp", "Earth", 0.1063, 3, 10, 
                      0.2, 0.2, 1.0, 365, 24); 
    initialize_planet(moon, "./images/moon.bmp", "Moon", 0.0435, 0.3, 5, 
                      0.4, 0.4, 0.4, 27.3, 27.3);
    initialize_planet(mars, "./images/mars.bmp", "Mars", 0.0566, 3.5, 5, 
                      1.0, 0.2, 0.0, 687, 24.6);
    initialize_planet(jupiter, "./images/jupiter.bmp", "Jupiter", 0.595, 6, 15, 
                      0.3, 0.9, 0.5, 4332, 9.8);
    initialize_planet(saturn, "./images/saturn.bmp", "Saturn", 0.502, 7.5, 15, 
                      0.7, 0.6, 0.0, 10761, 10.2);
    initialize_planet(uranus, "./images/uranus.bmp", "Uranus", 0.213, 9.5, 15, 
                      0.0, 0.5, 1.0, 30682, 15.5);
    initialize_planet(neptune, "./images/neptune.bmp", "Neptune", 0.206, 10.5, 15, 
                      0.7, 0.0, 1.0, 30682, 15.5);
    int rows = 0, columns = 0;
    load_texture("./images/saturnrings.bmp", rings.id, rows, columns, rings.image);
    rings.cylinder = gluNewQuadric();
    
    //Large sphere that envelopes the entire space and will display a
    //star image when textured
    initialize_planet(stars, "./images/stars.bmp", "", 20, 0, 40, 
                      0.0, 0.0, 0.0, 0, 0);
    stars.texture_rotate_y = 60;
    stars.texture_rotate_z = 90;
    
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;
}

//Initialize OpenGL's rendering modes
//This function is from the original orbit.cpp
void OpenGLInit( void )
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    
    //Planets are wireframe initially
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //Enable lighting
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    //Set light values and position
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {2, 2, 2, 1.0};
    GLfloat position[] = {0, 0, -8, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    Key_spacebar(); //Turns on the help menu
}

//This function loads a texture from the passed filename and stores
//information about that texture in the other passed variables
void load_texture(string filename, GLuint &id, int rows, int columns, unsigned char* image)
{
    if( !LoadBmpFile(filename.c_str(), 
        rows, columns, image) )
    {
        cerr << "Could not load " << filename << "\nExiting.\n";
        exit(-1);
    }
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &id); //Create the texture and store id
    glBindTexture(GL_TEXTURE_2D, id); //Edit the new texture
    
    //Fill texture with planet.image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, columns, rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image);
                 
    glDisable(GL_TEXTURE_2D);
}

//Takes passed information and assigns it to the appropriate variables
//in that planet's planet_object.
//It also initializes the texture for that planet.
//Exits the program if there is a file error
void initialize_planet(planet_object &planet, string filename, string name,
                       double radius, float distance_from_sun, 
                       float resolution, float red, float green, float blue,
                       float total_days, float total_hours)
{
    load_texture(filename, planet.id, planet.rows, planet.columns, planet.image);
    
    /*
    if( !LoadBmpFile(filename.c_str(), 
        planet.rows, planet.columns, planet.image) )
    {
        cerr << "Could not load " << filename << "\nExiting.\n";
        exit(-1);
    }
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &planet.id); //Create the texture and store id
    glBindTexture(GL_TEXTURE_2D, planet.id); //Edit the new texture
    
    //Fill texture with planet.image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, planet.columns, planet.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, planet.image);
                 
    glDisable(GL_TEXTURE_2D);
    
    */
    
    //Store information in the planet
    planet.sphere = gluNewQuadric(); //Store a quadric object in sphere
    planet.name = name;
    planet.radius = radius;
    planet.distance_from_sun = distance_from_sun;
    planet.resolution = resolution;
    planet.emission[0] = planet.color[0] = red;
    planet.emission[1] = planet.color[1] = green;
    planet.emission[2] = planet.color[2] = blue;
    planet.total_days = total_days;
    planet.total_hours = total_hours;
    planet.animate_increment = total_hours;
    
}

//This function was taken from Dr. Weiss' course website
//It draws a bitmap string of passed color at passed position
//Author: Dr. Weiss
//Source: http://www.mcs.sdsmt.edu/csc433/Code/OpenGLDemo.cpp
void DrawBitmapString( const char *string, float x, float y, float color[] )
{
    glColor3fv( color );
    glRasterPos2f( x, y );
    glutBitmapString( GLUT_BITMAP_8_BY_13, (const unsigned char *)string );
}

