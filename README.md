# Gravity-Simulation-OpenGL
# Assignment 2 for computer graphics class work 
this is a simulation of gravity between particles according to their masses as newton's law of universal gravitation
![img](http://www.calctool.org/CALC/phys/astronomy/gravity.png)

initially a big particle is created at the origin with infinity mass that will attrackt any new particle creatd by left clicking on the mouse by the user as the new particle is smaller than the big mass so the gravitation force accelerate the small particles towards the origin (Big mass)

 * change in velocity on x and y axis
# - p.vx += 0.0003 * p1.m / (d*d)  * (p1.x - p.x) / d
# - p.vy += 0.0003 * p1.m / (d*d)  * (p1.y - p.y) / d;

events:<br />
left click --> add samll particle at the mouse position<br />
right click ---> add big particle at the mouse position<br />
scroll click --> remove all the particles from the screen<br />


# Sample View
![sample](https://user-images.githubusercontent.com/19196061/47176964-47f8db00-d317-11e8-999a-15333e7ec260.gif)

