#include <iostream>
#include "controller/controller.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
int main() {
    stratego::Game game{};
    stratego::View view{game};
    stratego::Controller controller{game, view};
    controller.start();
    return 0;
}
