///////////////////////////////////////////////////////////////////////////////
//File: header.h
//Author: Kevin Hilt
//Date: November 21, 2014
//Course: Computer Graphics
//Instructor: Dr. Weiss
//
//Description: This header includes the libraries needed by the other files
//and declares the structs and extern instances referenced in those files.
///////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <GL/freeglut.h>
#include <string>

using namespace std;

//Keypress prototypes
void Key_r( void );
void Key_s( void );
void Key_A( void );
void Key_a( void );
void Key_p(void);
void Key_f(void);
void Key_t(void);
void Key_plus(void);
void Key_minus(void);
void Key_up(void);
void Key_down(void);
void Key_left(void);
void Key_right(void);
void Key_Y(void);
void Key_y(void);
void Key_N(void);
void Key_n(void);
void Key_X(void);
void Key_x(void);
void Key_Z(void);
void Key_z(void);
void Key_e(void);
void Key_spacebar(void);

//Glut callback prototypes
void Animate( void );
void ResizeWindow( int w, int h );
void KeyPressFunc( unsigned char Key, int x, int y );
void SpecialKeyFunc( int Key, int x, int y );

//Helper function prototypes
void DrawBitmapString( const char *string, float x, float y, float color[] );
void DrawEllipse( float xRadius, float yRadius, int x, int y, float color[] );

// global variables
extern GLenum spinMode;
extern GLenum singleStep;
extern bool is_wireframe;
extern bool is_flat; //Shading model
extern bool is_textured; 
extern double user_resolution; //Resolution factor controlled by the user
extern float white_color[4];
extern GLfloat no_emission[4];
extern bool help_on;

struct ring
{
    unsigned char* image;
    GLuint id;
    GLUquadric* cylinder;
};
extern ring rings;


//Struct to hold information for a planet
struct planet_object
{
    string name;
    float color[3] = {1.0, 1.0, 1.0}; //Color of planet when not textured
    float emission[4] = {1.0, 1.0, 1.0, 1.0}; ///Will be planet color
    float radius; //Radius of the planet iteself
    float distance_from_sun; //Radius or planet's orbital
    float hour = 0;
    float total_hours;
    float day = 0;
    float total_days;
    float animate_increment;
    float resolution; //How many slices and stacks the planet has
    unsigned char* image;
    int rows, columns;
    GLuint id; //The texture id set in glGenTextures
    GLUquadric* sphere;
    int texture_rotate_x = -90;
    int texture_rotate_y = 0;
    int texture_rotate_z = 0;
    
    //Draws the planet at the correct position
    void draw()
    {
        if(is_textured)
        {
            glColor3f( 1, 1, 1 );
            //Load the texture to be displayed with approproate settings  
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            
            glPushMatrix(); //Save matrix to rotate only the texture
            glRotatef(texture_rotate_x, 1.0, 0.0, 0.0);
            glRotatef(texture_rotate_y, 0.0, 1.0, 0.0);
            glRotatef(texture_rotate_z, 0.0, 0.0, 1.0);
            gluQuadricTexture(sphere, 1); //Put texture on planet
            gluSphere(sphere, radius, 
                      (resolution * user_resolution), 
                      (resolution * user_resolution));
            glDisable(GL_TEXTURE_2D);
            glPopMatrix(); //Reload matrix before texture rotate
        }
        else //Draw untextured sphere
        {
            glColor3f(color[0], color[1], color[2]);
            gluSphere(sphere, radius, 
                      (resolution * user_resolution), 
                      (resolution * user_resolution)); 
        }
    }
    
    //Performs the whole drawing routine to draw the planet with
    //its position given the day and hour
    void draw_with_position()
    {
        //Place in proper position given the roation at that day of the year
        glRotatef( 360.0 * day / total_days, 0.0, 1.0, 0.0 );
        glTranslatef(distance_from_sun, 0.0, 0.0);
        glPushMatrix(); // Save matrix state
        
        print_name(); //Print name label without planet rotation
        
        //Rotate the planet on its axis.
        glRotatef( 360.0 * hour / total_hours, 0.0, 1.0, 0.0 );   
        draw(); //Draw the sphere
            
        glPopMatrix(); // Restore matrix state
    }
    
    //Prints the name of the planet without any lighting
    void print_name()
    {
        glDisable(GL_LIGHTING);
        DrawBitmapString(name.c_str(), radius, radius, white_color);
        glEnable(GL_LIGHTING);
    }
    
    void draw_orbital_path() //Draws the orbital path around the sun
    {
        //Orbital emits light of the planet color
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Path always a line
        
        GLUquadricObj *disk = gluNewQuadric();
        gluDisk(disk, distance_from_sun, distance_from_sun, 40, 1);
        gluDeleteQuadric(disk);
        
        if(is_wireframe == 0) //Change back to fill if not in wireframe view
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        
        //Turn off light emission
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    }
    
    //Updates the day and hour for the planet
    //Changed the variable names from the code in the original orbit.cpp
    void update_animation()
    {
        hour += animate_increment;
        day += animate_increment / total_hours;
        
        hour = hour - ((int)(hour / total_hours)) * total_hours;
        day = day - ((int)(day / total_days)) * total_days;
    }
};

extern planet_object sun, mercury, venus, earth, moon, mars,
                     jupiter, saturn, uranus, neptune, stars;

struct user_view
{
    int screen_width, screen_height;
    float eye_x = 0;
    float eye_y = 2;
    float eye_z = 12;
    float reference_x = 0;
    float reference_y = 0;
    float reference_z = 0;
    float up_x = 0;
    float up_y = 1;
    float up_z = 0;
    int camera_rotation_x = 0;
    int camera_rotation_y = 0;
    int camera_rotation_z = 0;
    float zoom_factor = 1;
    
    //Increases the camera's angle of rotation around the passed axis
    void rotate_positive(int &axis)
    {
        axis += 9;
        
        //Never more than 360 degrees
        if(axis == 360)
        {
            axis = 0;
        }
    }
    
    //Decreses the camera's angle of rotation around the passed axis
    void rotate_negative(int &axis)
    {
        axis -= 9;
        
        //Never less than 0 degrees
        if(axis == -9)
        {
            axis = 351;
        }
    }
    
    //Resets the values to their defaults
    void reset()
    {
        eye_x = 0;
        eye_y = 2;
        eye_z = 12;
        reference_x = 0;
        reference_y = 0;
        reference_z = 0;
        up_x = 0;
        up_y = 1;
        up_z = 0;
        camera_rotation_x = 0;
        camera_rotation_y = 0;
        camera_rotation_z = 0;
        zoom_factor = 1; 
    }
};

extern user_view view;

