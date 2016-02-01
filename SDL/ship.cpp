//
//  cpp
//  SDL
//
//  Created by Andrei Berdnykov on 24.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#include "ship.hpp"

Ship::Ship()
{
    //Initialize the offsets
    mPosX = SCREEN_WIDTH - SCREEN_WIDTH/3 - DOT_WIDTH/2;
    mPosY = SCREEN_HEIGHT/2 - DOT_HEIGHT/2;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    absVel = 0;
    velAngle = 0;
    ANGLE_CHANGE_VEL = 0;
}

void Ship::handleEvent( SDL_Event& e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                incr = true;
                decr = false;
                slide = false;
                state = 1;
                break;
            case SDLK_DOWN:
                decr = true;
                incr = false;
                slide = false;
                state = 0;
                break;
            case SDLK_LEFT: ANGLE_CHANGE_VEL -=ANGLE_CHANGE_STEP; break;
            case SDLK_RIGHT: ANGLE_CHANGE_VEL +=ANGLE_CHANGE_STEP; break;
        }
    }
    //If a key was released
    else if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: ANGLE_CHANGE_VEL =0; break;
            case SDLK_RIGHT: ANGLE_CHANGE_VEL =0; break;
            case SDLK_UP:
                slide = true;
                incr = false;
                decr = false;
                break;
            case SDLK_DOWN:
                slide = true;
                decr = false;
                incr = false;
                break;
        }
    }
}

void Ship::move()
{
    if (slide) {
        state = 0;
        if (absVel != 0) {
            ANGLE_CHANGE_STEP = 6;
            if (absVel >= DOT_DRAG) absVel -= DOT_DRAG;
            if (absVel > 0 && absVel < DOT_DRAG) absVel = 0;
            if (absVel <= - DOT_DRAG) absVel += DOT_DRAG;
            if (absVel < 0 && absVel > - DOT_DRAG) absVel = 0;
        }
        else {
           slide = false;
            ANGLE_CHANGE_STEP = 4;
        }
    }
    if (incr) {
        if (absVel < DOT_MAX_VEL) {
            absVel += DOT_STEP_VEL;
        }
    }
    if (decr) {
        if (absVel > - DOT_MAX_VEL) {
            absVel -= DOT_STEP_VEL;
        }
    }
    velAngle +=ANGLE_CHANGE_VEL;
    if (velAngle > (double)360) velAngle -=360;
    if (velAngle < (double)0) velAngle =+360;
    if (!slide) {
        mVelX = cos(velAngle* M_PI/180) * absVel;
        mVelY = sin(velAngle*M_PI/180) * absVel;
        fixed_velAngle = velAngle;
    }
    else {
        mVelX = cos(fixed_velAngle* M_PI/180) * absVel;
        mVelY = sin(fixed_velAngle*M_PI/180) * absVel;
    }
    //Move the dot left or right

    mPosX += mVelX;
    
    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        slide=true;
        absVel = -absVel*0.5;
    }
    
    //Move the dot up or down
    mPosY += mVelY;
    
    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        slide=true;
        absVel = -absVel*0.5;
    }
}

void Ship::fire() {
    if (counter == 0) {
        bullets.push_back(Bullet(mPosX+31, mPosY+31, velAngle, 20, 0));
        counter = 10;
    }
    else counter--;
}

void Ship::moveBullets() {
    for (int i=0;i<bullets.size(); i++) {
        bullets[i].move();
        bullets[i].render();
        if(bullets[i].rem) bullets.erase(bullets.begin() + i);
    }
}

bool Ship::alive (std::vector<Bullet> enemybullets) {
    for (int i=0;i<enemybullets.size(); i++) {
        if (enemybullets[i].mPosX > this->mPosX && enemybullets[i].mPosX < this->mPosX+64 && enemybullets[i].mPosY > this->mPosY && enemybullets[i].mPosY < this->mPosY + 64) {
            return false;
        }
        
        
    }
    
    
    return true;
}




void Ship::render(std::vector<Bullet> enemybullets) {
    if (alive(enemybullets) && status) {
        ship[state].render( mPosX, mPosY, NULL, velAngle, NULL);
        moveBullets();
        fire();
    }
    else if (status) {
        AnimationManager::addAnimation(mPosX, mPosY, blastanim);
        status = false;
        moveBullets();
    }
    else {
        moveBullets();
    }
    switch (state) {
        case 0: break;
        case 1:
            if (state1count==10) {
                state = 2;
                state1count = 0;
            }
            else state1count++;
            break;
        case 2:
            state = 3;
            break;
        case 3: state = 2;
    }
}



