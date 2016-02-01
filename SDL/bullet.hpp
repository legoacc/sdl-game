//
//  bullet.hpp
//  SDL
//
//  Created by Andrei Berdnykov on 31.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#ifndef bullet_hpp
#define bullet_hpp

#include <string>
#include <math.h>
#include "base.hpp"

extern LTexture bullet [2];

class Bullet {
    
public:
    //Constructor
    Bullet (int x, int y, double angle, double vel, int color);
    
    
    //Functions
    void move();
    
    void render();
    
    int mPosX, mPosY;
    
    int bColor;
    
    bool rem = false;

private:
    //Variables
    double absVel, velAngle;
    
    int mVelX, mVelY;
    
    
    void checkDestr();
    
    
};

#endif /* bullet_hpp */
