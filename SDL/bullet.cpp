//
//  bullet.cpp
//  SDL
//
//  Created by Andrei Berdnykov on 31.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#include "bullet.hpp"

Bullet::Bullet(int x, int y, double angle, double vel, int color) {
    absVel = vel;
    velAngle = angle;
    mPosX = x;
    mPosY = y;
    bColor = color;
    
}

void Bullet::move() {
    mVelX = cos(velAngle* M_PI/180) * absVel;
    mVelY = sin(velAngle*M_PI/180) * absVel;
    
    mPosX +=mVelX;
    mPosY +=mVelY;
    
    checkDestr();
    //render();
}

void Bullet::checkDestr() {
    if( ( mPosY < 0 ) || ( mPosY > SCREEN_HEIGHT ) )
    {
        rem = true;
    }
    
    if( ( mPosX < 0 ) || ( mPosX > SCREEN_WIDTH ) )
    {
        rem = true;
    }
}

void Bullet::render() {
    bullet[bColor].render(mPosX, mPosY, NULL, velAngle, NULL);
}
