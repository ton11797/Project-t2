#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
#include "select.h"
#include "Menu.h"
#include "inventory.h"
#include "gamestart.h"
using namespace std;
int main()
{
    gamestart gm;
    gm.run();
    return 0;
}
