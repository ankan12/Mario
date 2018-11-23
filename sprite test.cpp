#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include <string>
#include "turtle.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    SDL_Plotter g(600, 600);
    const int SIZE=289;
    int a, b, c;
    int x=0;
    int y=0;
    int countn=0;
    Turt RTURT1[SIZE];
    Turt RTURT2[SIZE];
    Turt ALLTURTLES[289][18];
    int index=0;

    int imageHeight= 17;

    Turt imageGrid[imageHeight][429];

    int turtBegin[18] = {7, 31, 56, 79, 101, 123, 146, 168, 192, 216, 234, 254, 278, 302, 327,
                            351, 382, 407};
    int turtEnd[18] = {22, 46, 71, 95, 117, 138, 161, 181, 206, 225, 245, 268, 293, 317, 338,
                            373, 396, 431};



    string blank1, blank2, blank3, blank4;
    ifstream inputFile;
    inputFile.open("testline.txt");

//these are here to tell the program to ignore the first three lines
    getline(inputFile, blank1);
    getline(inputFile, blank2);
    getline(inputFile, blank3);

/*

            for (int y= 0; y < 17; y++)
            {
                for (int x=0; x < 17; x++)
                {
                    inputFile >> a >> b >> c;

                    RTURT1[index].x =x;
                    RTURT1[index].y =y;
                    RTURT1[index].a =a;
                    RTURT1[index].b =b;
                    RTURT1[index].c =c;

                    index++;
                }

                getline(inputFile, blank4);
            }

            inputFile.close();

            for (int index=0; index < 289; index++)
            {
                x=RTURT1[index].x;
                y=RTURT1[index].y;
                a=RTURT1[index].a;
                b=RTURT1[index].b;
                c=RTURT1[index].c;
           //     g.plotPixel(x, y, a, b, c);


            }
/*
        g.update();

        g.Sleep(100);

       g.clear();

*/

/*

This loop structure makes the picture move across the screen by changing
xinc. Xinc controls how much it moves, sleep controls the pause before it updates
and the loop control controls where it moves to

*/


     for(int xinc=1; xinc < 100; xinc++)
       {
          g.Sleep(100);
          g.clear();
          index=0;

        for (y= 0; y < 17; y++)
            {
                for (x= 0+xinc; x < 17+xinc; x++)
                {
                        a=RTURT1[index].a;
                        b=RTURT1[index].b;
                        c=RTURT1[index].c;

                        g.plotPixel(x, y, a, b, c);

                        index++;
                }


            }

            g.update();
       }

/*

This loop structure will read in the line from the file and save it into
an array.

*/


            inputFile.open("testline.txt");

            index =0;

            for (int y= 0; y < imageHeight; y++)
            {

                for (int x= 0; x < 429; x++)
                {
                    inputFile >> a >> b >> c;

                    imageGrid[y][x].x =x;
                    imageGrid[y][x].y =y;
                    imageGrid[y][x].a =a;
                    imageGrid[y][x].b =b;
                    imageGrid[y][x].c =c;

                    index++;

               }

            }

/*

This loop structure will transfer the images from the master line to
the allturtles array. This will save the individual turtles into different
array indexes so that only the turtle images exist in this array

*/

            for (int z=0; z < 18; z++)
            {
                index =0;

                for(y=0; y < imageHeight; y++)
                {
                    for(x= (turtBegin[z]-7); x < (turtBegin[z]-7)+17; x++)
                        {

                            ALLTURTLES[index][z].x=imageGrid[y][x].x;
                            ALLTURTLES[index][z].y=imageGrid[y][x].y;
                            ALLTURTLES[index][z].a=imageGrid[y][x].a;
                            ALLTURTLES[index][z].b=imageGrid[y][x].b;
                            ALLTURTLES[index][z].c=imageGrid[y][x].c;

                            index++;
                        }
                    }
                }

/*

This loop structure will save the individual turtle pictures into
its own array name

*/
            for(index=0; index < 289; index++)
            {
                RTURT2[index].x=ALLTURTLES[index][0].x;
                RTURT2[index].y=ALLTURTLES[index][0].y;
                RTURT2[index].a=ALLTURTLES[index][0].a;
                RTURT2[index].b=ALLTURTLES[index][0].b;
                RTURT2[index].c=ALLTURTLES[index][0].c;

            }


            for(index=0; index < 289; index++)
            {
                RTURT2[index].x=ALLTURTLES[index][5].x;
                RTURT2[index].y=ALLTURTLES[index][5].y;
                RTURT2[index].a=ALLTURTLES[index][5].a;
                RTURT2[index].b=ALLTURTLES[index][5].b;
                RTURT2[index].c=ALLTURTLES[index][5].c;

                g.plotPixel(RTURT2[index].x, RTURT2[index].y, RTURT2[index].a, RTURT2[index].b, RTURT2[index].c);

            }


         g.update();


    while(!g.getQuit())
    {
    }



    return 0;
}

