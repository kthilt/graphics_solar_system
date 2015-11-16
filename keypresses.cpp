///////////////////////////////////////////////////////////////////////////////
//File: keypresses.cpp
//Author: Kevin Hilt
//Date: November 21, 2014
//Course: Computer Graphics
//Instructor: Dr. Weiss
//
//Description: These are the actions that are executed when the user presses
//a key with an assigned command.
///////////////////////////////////////////////////////////////////////////////

#include "header.h"

//The r key pauses or resumes animation based on the current state
//This function is from the original orbit.cpp
void Key_r( void )
{
    if ( singleStep )	// restart animation
    {
        singleStep = GL_FALSE;
        spinMode = GL_TRUE;     
    }
    else				// toggle animation on and off
    {
        spinMode = !spinMode;   
    }
}

//The s key sets single step mode to true. It is turned off with the r key.
//This function is from the original orbit.cpp
void Key_s( void )
{
    singleStep = GL_TRUE;
    spinMode = GL_TRUE;
}

//Increases the animation speed
void Key_A( void )
{
    sun.animate_increment *= 2.0;
    mercury.animate_increment *= 2.0;
    venus.animate_increment *= 2.0;
    earth.animate_increment *= 2.0;
    mars.animate_increment *= 2.0;
    jupiter.animate_increment *= 2.0;
    saturn.animate_increment *= 2.0;
    uranus.animate_increment *= 2.0;
    neptune.animate_increment *= 2.0;
}

//Decreases the animation speed
void Key_a( void )
{
    sun.animate_increment /= 2.0;
    mercury.animate_increment /= 2.0;
    venus.animate_increment /= 2.0;
    earth.animate_increment /= 2.0;
    mars.animate_increment /= 2.0;
    jupiter.animate_increment /= 2.0;
    saturn.animate_increment /= 2.0;
    uranus.animate_increment /= 2.0;
    neptune.animate_increment /= 2.0;
}

//Toggles wireframe/polygon view
void Key_p(void)
{
    if(is_wireframe == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        is_wireframe = 0;
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        is_wireframe = 1;
    }
}
//Toggles flat/smooth shading
void Key_f(void)
{
    if(is_flat == 1)
    {
        glShadeModel(GL_SMOOTH);
    }
    else
    {
        glShadeModel(GL_FLAT);       
    }
    
    is_flat = !is_flat; //Toggle flag
}

//Toggles texture mapping
void Key_t(void)
{
    is_textured = !is_textured;
}

///////////////Beginning of view update functions
//These functions update the variables in the view struct
//so that the gluLookAt() call in the display function
//displays the correct camera position.

//Zooms in by adjusting the gluPerspective call by a smaller view.zoom_factor
void Key_plus(void)
{
    view.zoom_factor = view.zoom_factor / 1.1;
    
    //Call resize to adjust the perspective by view.zoom_factor
    ResizeWindow(view.screen_width, view.screen_height);
}

//Zooms out by adjusting the gluPerspective call by a larger view.zoom_factor
void Key_minus(void)
{
    if(view.zoom_factor < 2)
    {
        view.zoom_factor = view.zoom_factor * 1.1;
    }
    
    
    //Call resize to adjust the perspective by view.zoom_factor
    ResizeWindow(view.screen_width, view.screen_height);
}

//Rotates up by increasing the angle of rotation around the x axis
void Key_up(void)
{   
    view.rotate_positive(view.camera_rotation_x);
}

//Rotates down by decreasing the angle of rotation around the x axis
void Key_down(void)
{
    view.rotate_negative(view.camera_rotation_x);
}

//Rotates left by decreasing the angle of rotation around the y axis
void Key_left(void)
{
    view.rotate_positive(view.camera_rotation_y);
}

//Rotates right by increasing the angle of rotation around the y axis
void Key_right(void)
{
    view.rotate_negative(view.camera_rotation_y);
}

//Pans left by decreasing both the user's x and the "origin" x
void Key_x(void)
{
    view.eye_x -= .1;
    view.reference_x -= .1;
}

//Pans right by increasing both the user's x and the "origin" x
void Key_X(void)
{
    view.eye_x += .1;
    view.reference_x += .1;
}

//Pans up by increasing both the user's y and the "origin" y
void Key_Y(void)
{
    view.eye_y += .1;
    view.reference_y += .1;
}

//Pans down by decreasing both the user's y and the "origin" y
void Key_y(void)
{
    view.eye_y -= .1;
    view.reference_y -= .1;
}

//Rotates clockwise by increasing the angle of rotation around the z axis
void Key_z(void)
{   
    view.rotate_positive(view.camera_rotation_z);
}

//Rotates counter-clockwise by decreasing the angle of rotation around the z axis
void Key_Z(void)
{
    view.rotate_negative(view.camera_rotation_z);
}

//Resets to the initial view
void Key_e(void)
{
    view.reset();
    
    //Call resize to adjust the perspective by view.zoom_factor
    ResizeWindow(view.screen_width, view.screen_height);
}
///////////////End of view update functions

//Increases wireframe resolution
void Key_N(void)
{
    if(user_resolution < 20)
    {
        user_resolution *= 2;
    }
}

//Decreases wireframe resoltion
void Key_n(void)
{
    if(user_resolution > 0.25)
    {
        user_resolution /= 2;
    }
}

//Toggles help
void Key_spacebar(void)
{
    if(help_on == 0)
    {
        help_on = 1;
        
        glDisable(GL_LIGHTING);
        
        //Change to ortogonal perspective
        ResizeWindow(view.screen_width, view.screen_height);
    }
    else
    {
        help_on = 0;
        
        glEnable(GL_LIGHTING);
        
        //Go back to the perspective projection
        ResizeWindow(view.screen_width, view.screen_height);
    }
}

