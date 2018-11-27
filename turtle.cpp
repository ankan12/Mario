
#include <iostream>
#include <iomanip>
#include <fstream>
#include "turtle.hpp"

using namespace std;

Turtle::Turtle(){

int a, b, c;
    int x=0;
    int y=0;
    int countn=0;

    const int SIZE=289;
    Turt RTURT1[SIZE];
    Turt RTURT2[SIZE];
    Turt RTURT3[SIZE];
    Turt RTURT4[SIZE];
    Turt RTURT5[SIZE];
    Turt RTURT6[SIZE];
    Turt TTURT7[SIZE];
    Turt TTURT8[SIZE];
    Turt TTURT9[SIZE];
    Turt BTURT10[SIZE];
    Turt BTURT11[SIZE];
    Turt BTURT12[SIZE];
    Turt BTURT13[SIZE];
    Turt BTURT14[SIZE];
    Turt BTURT15[SIZE];
    Turt BTURT16[SIZE];
    Turt BTURT17[SIZE];
    Turt BTURT18[SIZE];


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

This loop structure will read in the line from the file and save it into
an array.

*/

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
                RTURT1[index].x=ALLTURTLES[index][0].x;
                RTURT1[index].y=ALLTURTLES[index][0].y;
                RTURT1[index].a=ALLTURTLES[index][0].a;
                RTURT1[index].b=ALLTURTLES[index][0].b;
                RTURT1[index].c=ALLTURTLES[index][0].c;

            }


            for(index=0; index < 289; index++)
            {
                RTURT2[index].x=ALLTURTLES[index][1].x;
                RTURT2[index].y=ALLTURTLES[index][1].y;
                RTURT2[index].a=ALLTURTLES[index][1].a;
                RTURT2[index].b=ALLTURTLES[index][1].b;
                RTURT2[index].c=ALLTURTLES[index][1].c;

            }

            for(index=0; index < 289; index++)
            {
                RTURT3[index].x=ALLTURTLES[index][2].x;
                RTURT3[index].y=ALLTURTLES[index][2].y;
                RTURT3[index].a=ALLTURTLES[index][2].a;
                RTURT3[index].b=ALLTURTLES[index][2].b;
                RTURT3[index].c=ALLTURTLES[index][2].c;

            }

            for(index=0; index < 289; index++)
            {
                RTURT4[index].x=ALLTURTLES[index][3].x;
                RTURT4[index].y=ALLTURTLES[index][3].y;
                RTURT4[index].a=ALLTURTLES[index][3].a;
                RTURT4[index].b=ALLTURTLES[index][3].b;
                RTURT4[index].c=ALLTURTLES[index][3].c;

            }

            for(index=0; index < 289; index++)
            {
                RTURT5[index].x=ALLTURTLES[index][4].x;
                RTURT5[index].y=ALLTURTLES[index][4].y;
                RTURT5[index].a=ALLTURTLES[index][4].a;
                RTURT5[index].b=ALLTURTLES[index][4].b;
                RTURT5[index].c=ALLTURTLES[index][4].c;

            }

            for(index=0; index < 289; index++)
            {
                RTURT6[index].x=ALLTURTLES[index][5].x;
                RTURT6[index].y=ALLTURTLES[index][5].y;
                RTURT6[index].a=ALLTURTLES[index][5].a;
                RTURT6[index].b=ALLTURTLES[index][5].b;
                RTURT6[index].c=ALLTURTLES[index][5].c;

            }

            for(index=0; index < 289; index++)
            {
                TTURT7[index].x=ALLTURTLES[index][6].x;
                TTURT7[index].y=ALLTURTLES[index][6].y;
                TTURT7[index].a=ALLTURTLES[index][6].a;
                TTURT7[index].b=ALLTURTLES[index][6].b;
                TTURT7[index].c=ALLTURTLES[index][6].c;

            }


            for(index=0; index < 289; index++)
            {
                TTURT8[index].x=ALLTURTLES[index][7].x;
                TTURT8[index].y=ALLTURTLES[index][7].y;
                TTURT8[index].a=ALLTURTLES[index][7].a;
                TTURT8[index].b=ALLTURTLES[index][7].b;
                TTURT8[index].c=ALLTURTLES[index][7].c;

            }

            for(index=0; index < 289; index++)
            {
                TTURT9[index].x=ALLTURTLES[index][8].x;
                TTURT9[index].y=ALLTURTLES[index][8].y;
                TTURT9[index].a=ALLTURTLES[index][8].a;
                TTURT9[index].b=ALLTURTLES[index][8].b;
                TTURT9[index].c=ALLTURTLES[index][8].c;

            }


            for(index=0; index < 289; index++)
            {
                BTURT10[index].x=ALLTURTLES[index][9].x;
                BTURT10[index].y=ALLTURTLES[index][9].y;
                BTURT10[index].a=ALLTURTLES[index][9].a;
                BTURT10[index].b=ALLTURTLES[index][9].b;
                BTURT10[index].c=ALLTURTLES[index][9].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT11[index].x=ALLTURTLES[index][10].x;
                BTURT11[index].y=ALLTURTLES[index][10].y;
                BTURT11[index].a=ALLTURTLES[index][10].a;
                BTURT11[index].b=ALLTURTLES[index][10].b;
                BTURT11[index].c=ALLTURTLES[index][10].c;

            }


            for(index=0; index < 289; index++)
            {
                BTURT12[index].x=ALLTURTLES[index][11].x;
                BTURT12[index].y=ALLTURTLES[index][11].y;
                BTURT12[index].a=ALLTURTLES[index][11].a;
                BTURT12[index].b=ALLTURTLES[index][11].b;
                BTURT12[index].c=ALLTURTLES[index][11].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT13[index].x=ALLTURTLES[index][12].x;
                BTURT13[index].y=ALLTURTLES[index][12].y;
                BTURT13[index].a=ALLTURTLES[index][12].a;
                BTURT13[index].b=ALLTURTLES[index][12].b;
                BTURT13[index].c=ALLTURTLES[index][12].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT14[index].x=ALLTURTLES[index][13].x;
                BTURT14[index].y=ALLTURTLES[index][13].y;
                BTURT14[index].a=ALLTURTLES[index][13].a;
                BTURT14[index].b=ALLTURTLES[index][13].b;
                BTURT14[index].c=ALLTURTLES[index][13].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT15[index].x=ALLTURTLES[index][14].x;
                BTURT15[index].y=ALLTURTLES[index][14].y;
                BTURT15[index].a=ALLTURTLES[index][14].a;
                BTURT15[index].b=ALLTURTLES[index][14].b;
                BTURT15[index].c=ALLTURTLES[index][14].c;

            }


            for(index=0; index < 289; index++)
            {
                BTURT16[index].x=ALLTURTLES[index][15].x;
                BTURT16[index].y=ALLTURTLES[index][15].y;
                BTURT16[index].a=ALLTURTLES[index][15].a;
                BTURT16[index].b=ALLTURTLES[index][15].b;
                BTURT16[index].c=ALLTURTLES[index][15].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT17[index].x=ALLTURTLES[index][16].x;
                BTURT17[index].y=ALLTURTLES[index][16].y;
                BTURT17[index].a=ALLTURTLES[index][16].a;
                BTURT17[index].b=ALLTURTLES[index][16].b;
                BTURT17[index].c=ALLTURTLES[index][16].c;

            }

            for(index=0; index < 289; index++)
            {
                BTURT18[index].x=ALLTURTLES[index][17].x;
                BTURT18[index].y=ALLTURTLES[index][17].y;
                BTURT18[index].a=ALLTURTLES[index][17].a;
                BTURT18[index].b=ALLTURTLES[index][17].b;
                BTURT18[index].c=ALLTURTLES[index][17].c;

            }

//        images.push_back(RTURT1);
//        images.push_back(RTURT2);
//        images.push_back(RTURT3);
//        images.push_back(RTURT5);
//        images.push_back(RTURT6);
//        images.push_back(TTURT7);
//        images.push_back(TTURT8);
//        images.push_back(TTURT9);
//        images.push_back(BTURT10);
//        images.push_back(BTURT11);
//        images.push_back(BTURT12);
//        images.push_back(BTURT13);
//        images.push_back(BTURT14);
//        images.push_back(BTURT15);
//        images.push_back(BTURT16);
//        images.push_back(BTURT17);
//        images.push_back(BTURT18);

}
