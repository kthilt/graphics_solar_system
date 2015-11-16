#Solar System using OpenGL

###Author
Kevin Hilt, with external code contained and documented in orbit.cpp
###Date
November 21, 2014
###Course
Computer Graphics
###Instructor
Dr. Weiss

###Description
This is the main file for the solar_system program. It handles
glut initialization and setting up the planet objects with their necessary
textures, radii, distances, colors, etc. This program was based on orbit.cpp
by Samuel R. Buss.

The radii of the four inner planets are their radii from the initial 
table / 60000. The radii of the four outer planets are their raadii from
the initial table / 120000.
The moon uses initial value / 30000.
The sun was given a radius of 1, which is bigger than all the planets
but not too large that it makes the model unviewable.

Since the initial distances from the sun ranged from 88 to 60195 and
such a wide range would have made the viewing experience worse,
the distances below are semi-arbitrary numbers that convey the relative
positions of the planets (4 inner, a wide gap, then 4 outer) while
still keeping everything moderately close.

See readme.txt for a table of these distances and a list of controls.


