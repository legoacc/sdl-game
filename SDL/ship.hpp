//
//  ship.hpp
//  SDL
//
//  Created by Andrei Berdnykov on 24.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#ifndef ship_hpp
#define ship_hpp
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "base.hpp"
#include "bullet.hpp"
#include <math.h>
#include <vector>
#include "anim.hpp"

extern LTexture ship [4];
extern LTexture blast [23];
extern Animation blastanim;
//The dot that will move around on the screen
class Ship
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 64;
    static const int DOT_HEIGHT = 64;
    
    //Maximum axis velocity of the dot
    static constexpr double DOT_STEP_VEL = 0.2;
    static const int DOT_MAX_VEL = 10;
    static constexpr double DOT_DRAG = 0.3;
    double ANGLE_CHANGE_STEP = 4;
    
    //Initializes the variables
    Ship();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e);
    
    //Moves the dot
    void move();
    
    void fire();
    
    void moveBullets();
    
    bool alive (std::vector<Bullet> enemybullets);
    
    //Shows the dot on the screen
    void render(std::vector<Bullet> enemybullets);
    
    //The velocity of the dot
    int mVelX, mVelY;
    
    //The absolute velocity and angle
    double absVel, velAngle;
    
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    double ANGLE_CHANGE_VEL;
    
    int state = 0;
    int state1count = 0;
    
    std::vector<Bullet> bullets;
private:
    bool slide= false;
    bool incr = false;
    bool decr = false;
    double fixed_velAngle;
    double CURR_DRAG;
    double slide_counter = 1;
    bool count = false;
    
    bool status = true;
    
    
    int counter = 10;
};

#endif /* ship_hpp */
