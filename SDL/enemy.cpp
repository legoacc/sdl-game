//
//  enemy.cpp
//  SDL
//
//  Created by Andrei Berdnykov on 30.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#include "enemy.hpp"

Enemy::Enemy() {
    
    mVelX = 0;
    mVelY = 0;
    
    mPosX = (int)SCREEN_WIDTH/3 - ENEMY_WIDTH;
    mPosY = (int)SCREEN_HEIGHT/2 - ENEMY_HEIGHT;
    
    absVel = 0;
    velAngle = 0;
}





void Enemy::moveTowards(int x, int y) {
    
    double targetAngleRad = atan2(y - mPosY, x - mPosX);
    double targetAngle = targetAngleRad * 180 / M_PI;
    
    if (velAngle < targetAngle) {
        velAngle += E_ANGLE_CH_STEP;
    }
    
    if (velAngle > targetAngle) {
        velAngle -= E_ANGLE_CH_STEP;
    }
    
    if (fmin((targetAngle-velAngle), (velAngle-targetAngle)) < MOVE_ANGLE) {
        absVel = SPEED;
    }
    else absVel = 0;
    mVelX = cos(velAngle* M_PI/180) * absVel;
    mVelY = sin(velAngle*M_PI/180) * absVel;
    
    mPosX +=mVelX;
    mPosY +=mVelY;
    
    if( ( mPosY < 0 ) || ( mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        absVel = -absVel*0.5;
    }
    
    if( ( mPosX < 0 ) || ( mPosX + ENEMY_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        absVel = -absVel*0.5;
    }
    
    
    
}



void Enemy::fire() {
    if (counter == 0) {
        bullets.push_back(Bullet(mPosX+31, mPosY+31, velAngle, 10, 1));
        counter = 17;
    }
    else counter--;
}

void Enemy::moveBullets() {
    //    for (auto b = bullets.begin(); b != bullets.end();b++) {
    //        b->move();
    //        b->render();
    //        if (b->rem) {
    //            b = bullets.erase(b);
    //        }
    //    }
    for (int i=0;i<bullets.size(); i++) {
        bullets[i].move();
        bullets[i].render();
        if(bullets[i].rem) bullets.erase(bullets.begin() + i);
    }
}




void Enemy::render(std::vector<Bullet> enemybullets) {
    if (alive(enemybullets) && status) {
    enemy.render( mPosX, mPosY, NULL, velAngle, NULL);
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
    
}

bool Enemy::alive (std::vector<Bullet> enemybullets) {
    for (int i=0;i<enemybullets.size(); i++) {
        if (enemybullets[i].mPosX > this->mPosX && enemybullets[i].mPosX < this->mPosX+64 && enemybullets[i].mPosY > this->mPosY && enemybullets[i].mPosY < this->mPosY + 64) {
            return false;
        }
        
        
    }
    
    
    return true;
}