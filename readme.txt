========
CONTROLS
========
These options are available via either the right click menu or the key commands after each option in parentheses.

Shape options:\n
     Toggle wireframe/polygon (p)
     Toggle flat/smooth shading (f)
     Toggle texture mapping (t)
     Increase wireframe resolution (N)
     Decrease wireframe resolution (n)
View Options:
     Zoom in (+)
     Zoom out (-)
     Rotate up (up arrow)
     Rotate down (down arrow)
     Rotate left (left arrow)
     Rotate right (right arrow)
     Rotate clockwise (z)
     Rotate counter-clockwise (Z)
     Pan left (x)
     Pan right (X)
     Pan up (Y)
     Pan down (y)
     Reset camera view (e)
Animation Options:
     Speed up animation (A)
     Slow down animation (a)
     Suspend/resume animation (r)
     Single step mode (s)
Toggle help menu (spacebar)
Quit (esc)

=====
NOTES
=====
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

Name      Radius      Distance        Year        Day
-----------------------------------------------------------------------------
Sun       1           0               0           25
Mercury   0.0407      2               88          1416
Venus     0.1009      2.5             225         5832
Earth     0.1063      3               365         24
Mars      0.0566      3.5             687         24.6
Jupiter   0.595       6               4332        9.8
Saturn    0.502       7.5             10761       10.2
Uranus    0.213       9.5             30682       15.5
Neptune   0.206       10.5            60195       15.8

Additionally, the stars shown in bas the background image when texture mode is enable are NOT accurate. They are only for ambience and do not accurately depict the location of stars from that viewing position.

=======
CREDITS
=======

- The original code, orbit.cpp, was written by Samuel R. Buss, whose original header block is preserved in solar_system.cpp.
- The code for bmp_read.cpp and the DrawBitmapString() function were written by Dr. Weiss.
- The bmp for the stars background image is from http://www.geckzilla.com/apod/tycho_cyl_glow.png
