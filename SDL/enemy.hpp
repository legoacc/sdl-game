//
//  enemy.hpp
//  SDL
//
//  Created by Andrei Berdnykov on 30.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "base.hpp"
#include "ship.hpp"
#include <stdio.h>
#include <math.h>
#include "anim.hpp"

extern LTexture enemy;

class Enemy {
  
public:
    
    Enemy();
    //Constants
    static const int FIRING_ANGLE = 45;
    
    static const int SPEED = 5;
    
    static const int FIRING_DELAY = 15;
    
    static const int MOVE_ANGLE = 90;
    
    static const int E_ANGLE_CH_STEP = 4;
    
    static const int ENEMY_WIDTH = 64;
    static const int ENEMY_HEIGHT = 64;
    
    //Vars
    int mVelX, mVelY;
    
    double absVel, velAngle;
    
    int mPosX, mPosY;
    
    int counter = 17;
    
    std::vector<Bullet> bullets;
    
    //Functions
    void render(std::vector<Bullet> enemybullets);
    
    void moveTowards(int x, int y);
    
    void fire();
    
    void moveBullets();
    
    bool alive (std::vector<Bullet> enemybullets);
    
    bool status = true;
};

#endif /* enemy_hpp */
