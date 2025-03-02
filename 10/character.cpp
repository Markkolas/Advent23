#include "character.h"

Character::Character(Matrix *world){
    map = world;
    for(int r = 0; r < map->cols; r++){
        for(int c = 0; c < map->rows; c++){
            TILES tile = static_cast<TILES>((*map)[r][c]);
            if(tile == TILES::CHAR){
                x = c;
                y = r;
                curr_tile = tile;
                std::cout << "Found my position! -> x=" << x << " y=" << y << std::endl;
                return;
            }
        }
    }
}

Character::Character(int initx, int inity, Matrix *world):x{initx}, y{inity}{
    map = world;
    curr_tile = static_cast<TILES>((*map)[y][x]);

    if(curr_tile != TILES::CHAR) std::cout << "WARNING: Initial tile does not match with map info" << std::endl;
}

bool Character::goNorth(){
    TILES next_tile = static_cast<TILES>((*map)[y-1][x]);

    if(next_tile == TILES::N_S || next_tile == TILES::S_W || next_tile == TILES::S_E || next_tile == TILES::CHAR){
        curr_tile = next_tile;
        dy = -1;
        dx = 0;
        y += dy;
        steps++;
        return true;
    } else {
        std::cout << "Cant go up!" << std::endl;
        return false;
    }
}

bool Character::goSouth(){
    TILES next_tile = static_cast<TILES>((*map)[y+1][x]);

    if(next_tile == TILES::N_S || next_tile == TILES::N_E || next_tile == TILES::N_W || next_tile == TILES::CHAR){
        curr_tile = next_tile;
        dy = +1;
        dx = 0;
        y += dy;
        steps++;
        return true;
    } else {
        std::cout << "Cant go down!" << std::endl;
        return false;
    }
}

bool Character::goEast(){
    TILES next_tile = static_cast<TILES>((*map)[y][x+1]);

    if(next_tile == TILES::E_W || next_tile == TILES::N_W || next_tile == TILES::S_W || next_tile == TILES::CHAR){
        curr_tile = next_tile;
        dx = +1;
        dy = 0;
        x += dx;
        steps++;
        return true;
    } else {
        std::cout << "Cant go East!" << std::endl;
        return false;
    }
}

bool Character::goWest(){
    TILES next_tile = static_cast<TILES>((*map)[y][x-1]);

    if(next_tile == TILES::E_W || next_tile == TILES::N_E || next_tile == TILES::S_E || next_tile == TILES::CHAR){
        curr_tile = next_tile;
        dx = -1;
        dy = 0;
        x += dx;
        steps++;
        return true;
    } else {
        std::cout << "Cant go West" << std::endl;
        return false;
    }
}

int Character::walk(int ypos, int xpos){
    switch(curr_tile){
        case TILES::N_S:
            if(dx != 0){
                std::cout << "Error, cant move" << std::endl;
                return 2;
            } else {
                if(dy > 0)
                    goSouth();
                else
                    goNorth();
            }
            break;
        case TILES::E_W:
            if(dy != 0){
                std::cout << "Error, cant move" << std::endl;
                return 2;
            } else {
                if(dx > 0)
                    goEast();
                else
                    goWest();
            }
            break;
        case TILES::N_E:
            if(dy > 0 && dx == 0)
                goEast();
            else if(dx < 0 && dy == 0)
                goNorth();
            else{
                std::cout << "Error, cant move" << std::endl;
                return 2;
            }
            break;
        case TILES::N_W:
            if(dy > 0 && dx == 0)
                goWest();
            else if(dx > 0 && dy == 0)
                goNorth();
            else{
                std::cout << "Error, cant move" << std::endl;
                return 2;
            }
            break;
        case TILES::S_E:
            if(dy < 0 && dx == 0)
                goEast();
            else if(dx < 0 && dy == 0)
                goSouth();
            else{
                std::cout << "Error, cant move" << std::endl;
                return 2;
            }
            break;
        case TILES::S_W:
            if(dy < 0 && dx == 0)
                goWest();
            else if(dx > 0 && dy == 0)
                goSouth();
            else{
                std::cout << "Error, cant move" << std::endl;
                return 2;
            }
            break;
        case TILES::CHAR:
            std::cout << "I am in origin position" << std::endl;
            return 3;
        default:
            std::cout << "Oh, I should not be here" << std::endl;
            return 2;
    }

    // std::cout << "My current position:" << std::endl;
    // std::cout << "(" << y << "," << x << ")" << std::endl;

    if(xpos == x && ypos == y){
        std::cout << "Destination reached" << std::endl;
        return 1;
    }

    return 0; // Keep walking
}
