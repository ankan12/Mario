#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include "Sprite.h"
using namespace std;

int main(int argc, char ** argv)
{
    cout << "Hello world!" << endl;

    SDL_Plotter p(500, 500);

    ifstream inFile;

    Sprite sprite("example_sprite", inFile);

    sprite.setLocation(250, 250);

    sprite.setScale(4);

    sprite.draw(p);

    while (!p.getQuit()){

        if (p.kbhit()){

            switch (p.getKey()){

            case ' ':
                p.clear();
                sprite.nextFrame();
                sprite.draw(p);
                break;

            }

        }

        p.update();

    }

    return 0;
}
