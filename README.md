# GLSort
Visualises various sort algorithms using OpenGL. 

## History
Originally implemented in C ("glsort") and then ported to C++ ("glsort2") during my studies as a fun project in the late 90ies - this is code archaeology, folks :)

It used "raw" OpenGL (2.x at best, I guess) and a GL utility library called GLUT:

https://www.opengl.org/resources/libraries/glut/glut_downloads.php#2

Quote: "Download the GLUT 3.7 beta source distribution (shift Left in Netscape)" - oh dear, you know that you are knee-deep in history when a website still mentions "Netscape" ;)

## Original Screenshots
The following screenshots are from the original "glsort", running on Linux:

![Bubble sort](./img/bubble-sort.png "Bubble Sort")
![Online help](./img/help.png "Onlne Help")
![Merge sort](./img/merge-sort.png "Merge Sort")

## Plans
There are none. But perhaps the idea to:
- Make the code compile again (somehow)
- Get rid of the original makefiles (use CMake instead)
- Port it to "modern C++" and 
- Perhaps use Qt as toolkit (I am sceptical about getting GLUT to work ;))
