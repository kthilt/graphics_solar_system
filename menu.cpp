///////////////////////////////////////////////////////////////////////////////
//File: menu.cpp
//Author: Kevin Hilt
//Date: November 21, 2014
//Course: Computer Graphics
//Instructor: Dr. Weiss
//
//Description: These functions declare the menu structure and speicfy how
//choices from the main and submenus should be handled, calling the
//associated Key_ function.
///////////////////////////////////////////////////////////////////////////////

#include "header.h"

//Handles the user choice for the shape options submenu
void shape_handler(int item)
{
    switch(item)
    {
        //Toggle wireframe/polygon (p)
        case 0:
            Key_p();
            break;
            
        //Toggle flat/smooth shading (f)
        case 1:
            Key_f();
            break;
            
        //Toggle texture mapping (t)
        case 2:
            Key_t();
            break;
        
        //Increase wireframe resolution (N)
        case 3:
            Key_N();
            break;
            
        //Decrease wireframe resolution (n)
        case 4:
            Key_n();
            break;
    }
}

//Handles the user choice for the view options submenu
void view_handler(int item)
{
    switch(item)
    {
        //Zoom in (+)
        case 0:
            Key_plus();
            break;
            
        //Zoom out (-)
        case 1:
            Key_minus();
            break;
            
        //Rotate up (up arrow)
        case 2:
            Key_up();
            break;
            
        //Rotate down (down arrow)
        case 3:
            Key_down();
            break;
        
        //Rotate left (left arrow)   
        case 4:
            Key_left();
            break;
            
        //Rotate right (right arrow)
        case 5:
            Key_right();
            break;
        
        //Rotate clockwise (Z)
        case 6:
            Key_z();
            break;
            
        //Rotate counter-clockwise (z)
        case 7:
            Key_Z();
            break;
        
        //Pan left (x)
        case 8:
            Key_x();
            break;
        
        //Pan right (X)
        case 9:
            Key_X();
            break;
            
        //Pan up (Y)
        case 10:
            Key_Y();
            break;
            
        //Pan down (y)
        case 11:
            Key_y();
            break;
            
        //Reset camera view (e)
        case 12:
            Key_e();
            break;
    }
}

//Handles the user choice for the animation options submenu
void animation_handler(int item)
{
    switch(item)
    {
        //Speed up animation (A)
        case 0:
            Key_A();
            break;
            
        //Slow down animation (a)
        case 1:
            Key_a();
            break;
            
        //Suspend/resume animation (r)
        case 2:
            Key_r();
            break;
            
        //Single step mode (s)
        case 3:
            Key_s();
            break;  
    }
}

//Handles the user choice from the right click menu
void menu_handler(int item)
{   
    switch(item)
    {
        //Toggle help menu (spacebar)
        case 0:
            Key_spacebar();
            break;
            
        //Quit (esc)
        case 1:
            exit(0);
            break;    
    }
}

//Creates the main and submenus with the application controls
void initialize_menu()
{
    int value = 0; //Menu item id
    
    //Create submenu for shape options
    int shape = glutCreateMenu(shape_handler);
    glutAddMenuEntry("Toggle wireframe/polygon (p)", value++);
    glutAddMenuEntry("Toggle flat/smooth shading (f)", value++);
    glutAddMenuEntry("Toggle texture mapping (t)", value++);
    glutAddMenuEntry("Increase wireframe resolution (N)", value++);
    glutAddMenuEntry("Decrease wireframe resolution (n)", value++);
    
    //Create submenu for view options
    value = 0;
    int view = glutCreateMenu(view_handler);
    glutAddMenuEntry("Zoom in (+)", value++);
    glutAddMenuEntry("Zoom out (-)", value++);
    glutAddMenuEntry("Rotate up (up arrow)", value++);
    glutAddMenuEntry("Rotate down (down arrow)", value++);
    glutAddMenuEntry("Rotate left (left arrow)", value++);
    glutAddMenuEntry("Rotate right (right arrow)", value++);
    glutAddMenuEntry("Rotate clockwise (Z)", value++);
    glutAddMenuEntry("Rotate counter-clockwise (z)", value++);
    glutAddMenuEntry("Pan left (x)", value++);
    glutAddMenuEntry("Pan right (X)", value++);
    glutAddMenuEntry("Pan up (Y)", value++);
    glutAddMenuEntry("Pan down (y)", value++);
    glutAddMenuEntry("Reset camera view (e)", value++);
    
    //Create submenu for animation options
    value = 0;
    int animation = glutCreateMenu(animation_handler);
    glutAddMenuEntry("Speed up animation (A)", value++);
    glutAddMenuEntry("Slow down animation (a)", value++);
    glutAddMenuEntry("Suspend/resume animation (r)", value++);
    glutAddMenuEntry("Single step mode (s)", value++);
    
    //Create main menu
    value = 0;
    glutCreateMenu(menu_handler);
    glutAddSubMenu("Shape", shape);
    glutAddSubMenu("View", view);
    glutAddSubMenu("Animation", animation);
    glutAddMenuEntry("Toggle help menu (spacebar)", value++);
    glutAddMenuEntry("Quit (esc)", value++);
    
    //The menu displays with a right click
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

