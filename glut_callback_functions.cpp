///////////////////////////////////////////////////////////////////////////////
//File: glut_callback_functions.cpp
//Author: Kevin Hilt
//Date: November 21, 2014
//Course: Computer Graphics
//Instructor: Dr. Weiss
//
//Description: This file holds the callback functions invoked for routines
//like updating the display and resizing the window. The actions for the
//individual keypresses are broken out into keypresses.cpp.
///////////////////////////////////////////////////////////////////////////////

#include "header.h"

string help_string = "KEY COMMANDS (spacebar toggles this screen)\n\n"
                     "Shape options:\n"
                     "    Toggle wireframe/polygon (p)\n"
                     "    Toggle flat/smooth shading (f)\n"
                     "    Toggle texture mapping (t)\n"
                     "    Increase wireframe resolution (N)\n"
                     "    Decrease wireframe resolution (n)\n"
                     "\nView Options:\n"
                     "    Zoom in (+)\n"
                     "    Zoom out (-)\n"
                     "    Rotate up (up arrow)\n"
                     "    Rotate down (down arrow)\n"
                     "    Rotate left (left arrow)\n"
                     "    Rotate right (right arrow)\n"
                     "    Rotate clockwise (Z)\n"
                     "    Rotate counter-clockwise (z)\n"
                     "    Pan left (x)\n"
                     "    Pan right (X)\n"
                     "    Pan up (Y)\n"
                     "    Pan down (y)\n"
                     "    Reset camera view (e)\n"
                     "\nAnimation Options:\n"
                     "    Speed up animation (A)\n"
                     "    Slow down animation (a)\n"
                     "    Suspend/resume animation (r)\n"
                     "    Single step mode (s)\n"
                     "\nToggle help menu (spacebar)\n"
                     "Quit (esc)\n";
                     
//Helper function prototypes
void displayImage( int x, int y, int w, int h, unsigned char* image );
void DrawBitmapString( const char *string, float x, float y, float color[] );

// glutKeyboardFunc is called to set this function to handle normal key presses
void KeyPressFunc( unsigned char Key, int x, int y )
{
    //cerr << "Pressed key " << Key << "\n";
    
    switch ( Key )
    {
        case 'R':
        case 'r':
            Key_r();
            break;
            
        case 'S':
        case 's':
            Key_s();
            break;
       
       case 'A':
            Key_A(); //Increases animation speed
            break;
       
       case 'a':
            Key_a(); //Decreases animation speed
            break;
            
       case 'P':
       case 'p':
            Key_p(); //Toggles wireframe/polygon
            break;
       
       case 'F':
       case 'f':
            Key_f(); //Toggles flat/smooth shading
            break;
        
        case 'T':
        case 't':
            Key_t(); //Toggles texture mapping
            break;
       
        case 'Y':
            Key_Y(); //Pans up
            break;
        
        case 'y':
            Key_y(); //Pans down
            break;
        
        case 'N':
            Key_N(); //Increases wireframe resolution
            break;
        
        case 'n':
            Key_n(); //Decreases wireframe resolution
            break;
            
        //Plus key zooms in
        case 61:
            Key_plus();
            break;
        
        //Minus key zooms out
        case 45:
            Key_minus();
            break;
        
        case 'X':
            Key_X(); //Pans left
            break;
        
        case 'x':
            Key_x(); //Pans right
            break;
            
        case 'Z':
            Key_Z(); //Rotates counter-clockwise
            break;
        
        case 'z':
            Key_z(); //Rotates clockwise
            break;
        
        case 'e':
            Key_e(); //Resets the camera to the default view
            break;
        
        case ' ':
            Key_spacebar(); //Toggles help
            break;
            
        case 27:    // Escape key
            exit(0); //Exit the program
    }
}

// glutSpecialFunc is called to set this function to handle all special key presses
// (see glut.h for names of special keys)
void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key )
    {
        case GLUT_KEY_UP:
            Key_up(); //Rotates up
            break;
            
        case GLUT_KEY_DOWN:
            Key_down(); //Rotates down
            break;
        
        case GLUT_KEY_LEFT:
            Key_left(); //Rotates left
            //Key_,();
            break;
        
        case GLUT_KEY_RIGHT:
            Key_right(); //Rotates right
            break;
    }
}

//glutDisplayFunc() callback to display the graphics window contents
void Animate( void )
{
    // Clear the redering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    if(help_on == 1) //Display help menu over the scene
    {
        DrawBitmapString(help_string.c_str(), 10, 
                         view.screen_height - 20, white_color);
        
        glFlush();
        glutSwapBuffers();

        glutPostRedisplay();
        return;
    }

    if ( spinMode )
    {
        // Update the animation state
        sun.update_animation();
        mercury.update_animation();
        venus.update_animation();
        earth.update_animation();
        mars.update_animation();
        jupiter.update_animation();
        saturn.update_animation();
        uranus.update_animation();
        neptune.update_animation();
    }

    // Clear the current matrix (Modelview)
    glLoadIdentity();

    //Look at the user's currently specified reference point
    //from user's currently specified position
    //with user's currently specified rotation (up direction)
    //Defatul is "Back off eight units to be able to view from the origin."
    //glTranslatef ( 0.0, 0.0, -8.0 );
    
    gluLookAt(view.eye_x, view.eye_y, view.eye_z, //User viewpoint
              view.reference_x, view.reference_y, view.reference_z, //Updated "origin" to rotate around
              view.up_x, view.up_y, view.up_z); //Which direction is up
              
    //glScalef(view.zoom_factor, view.zoom_factor, view.zoom_factor);
    
    glRotatef(view.camera_rotation_x, 1.0, 0.0, 0.0);
    glRotatef(view.camera_rotation_y, 0.0, 1.0, 0.0);
    glRotatef(view.camera_rotation_z, 0.0, 0.0, 1.0);    
        
    //Draw orbital paths for the planets, excluding the sun and moon
    //Rotate only the paths -90 degrees
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    mercury.draw_orbital_path();
    venus.draw_orbital_path();
    earth.draw_orbital_path();
    mars.draw_orbital_path();
    jupiter.draw_orbital_path();
    saturn.draw_orbital_path();
    uranus.draw_orbital_path();
    neptune.draw_orbital_path();
    glPopMatrix();
    
    //Sun emits a yellow light
    GLfloat emission[] = {1.0, 1.0, 0.0, 1.0};
    
    //If textured, make it a white light so the texture colors aren't tinted
    if(is_textured == 1)
    {
        emission[2] = 1.0;
    }
    
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    
    //sun.print_name();
    glPushMatrix();
    sun.draw_with_position();
    glPopMatrix();
    
    //Turn off light emission for other planets
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

    stars.texture_rotate_y = 60;
    stars.draw();

    //Draw Mercury
    glPushMatrix();
    mercury.draw_with_position();
    glPopMatrix();
    
    //Draw Venus
    glPushMatrix();
    venus.draw_with_position();
    glPopMatrix();
    
    //Draw Mars
    glPushMatrix();
    mars.draw_with_position();
    glPopMatrix();
    
    //Draw Jupiter
    glPushMatrix();
    jupiter.draw_with_position();
    glPopMatrix();
    
    //Draw Saturn
    glPushMatrix();
       
    //Place in proper position given the roation at that day of the year
    glRotatef( 360.0 * saturn.day / saturn.total_days, 0.0, 1.0, 0.0 );
    glTranslatef(saturn.distance_from_sun, 0.0, 0.0);
    glPushMatrix(); // Save matrix state
    
    saturn.print_name(); //Print name label without planet rotation
    
    //Rotate the planet on its axis.
    glRotatef( 360.0 * saturn.hour / saturn.total_hours, 0.0, 1.0, 0.0 );   
    saturn.draw(); //Draw the sphere
    
    //Draw Saturn's rings
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    
    if(is_textured)
    {
        glColor3f( 1, 1, 1 );
        //Load the texture to be displayed with approproate settings  
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, rings.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        gluQuadricTexture(rings.cylinder, 1); //Put texture on planet
        gluCylinder(rings.cylinder, 1.167, .75, 0, 40 * user_resolution, 1);
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        gluCylinder(rings.cylinder, 1.167, .75, 0, 40 * user_resolution, 1);
    }
    glPopMatrix();
        
    glPopMatrix(); // Restore matrix state
    
    glPopMatrix();
    
    //Draw Uranus
    glPushMatrix();
    uranus.draw_with_position();
    glPopMatrix();
    
    //Draw Neptune
    glPushMatrix();
    neptune.draw_with_position();
    glPopMatrix();

    //Draw Earth
    earth.draw_with_position();
    
    //Draw the moon. Use Earth's day to control its rotation around the earth
    glRotatef( 360.0 * 12.0 * earth.day / 365.0, 0.0, 1.0, 0.0 );
    glTranslatef(moon.distance_from_sun, 0.0, 0.0 );
    moon.print_name();
    moon.draw();

    // Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();

    if ( singleStep ) spinMode = GL_FALSE;

    glutPostRedisplay();        // Request a re-draw for animation purposes
    
}

// ResizeWindow is called when the window is resized
void ResizeWindow( int w, int h )
{
    view.screen_width = w;
    view.screen_height = h;
    
    if(help_on)
    {
        //Set up a simple orthogonal projection for the help menu
        glViewport( 0, 0, view.screen_width, view.screen_height );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( 0.0, view.screen_width, 0.0, view.screen_height );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        return;
    }
    
    float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );   // View port uses whole window
    aspectRatio = ( float ) w / ( float ) h;

    // Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( (60.0 * view.zoom_factor), aspectRatio, 1.0, 60.0 );

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}

