#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Code derived from the awesome dots.py by Matt Brown
# His work is located here: https://github.com/1BADragon/Side-Projects
# Requires: graphics.py and Tkinter

from graphics import *
from math import cos, sin
from fileinput import input

window = 500  # Set window size (square)

# Don't mess with these
center = window / 2
radius = center * 0.9
dotSize = 5
    
    
def fromPolar(theta, radius):
    x = radius * cos(theta)
    y = radius * sin(theta)
    return Point(x,y)
    
def scalePoint(point):
    x = (point.getX() * radius) + center
    y = (point.getY() * radius) + center
    return Point(x,y)

def main():    
    
    # Get input from given filename or from standard input
    with input() as inf:
        points = [l.strip(' ,.+') for l in inf] # Remove any junk

    # Create window
    win = GraphWin("My Circle", window, window)

    # Create and draw circle
    c = Circle(Point(window/2, window/2), radius)
    c.draw(win)
    
    for p in points:
        hack = p[4:].strip('\n').split('\t')
        try:
            theta = float(hack[0])
            r = float(hack[1])
        except (ValueError, IndexError):  # For lines without values
            print('Skipping: "%s"' % p[4:].strip('\n'))
            continue
        temp = Circle( scalePoint( fromPolar(theta, r)), dotSize)
        temp.setFill("black")
        temp.draw(win)
    
    try:
        win.getMouse()
    except:
        win.close() # Pause to view result
    win.close() # Close window when done


if __name__ == '__main__':
    main()
