//
//  enemymanager.cpp
//  SDL
//
//  Created by Andrei Berdnykov on 01.02.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#include "enemymanager.hpp"


std::vector<Bullet> EnemyManager::allbullets;
std::vector<Enemy> EnemyManager::enemies;

void EnemyManager::createEnemy (EnemyType en, int x, int y) {

    Enemy myen;
    myen.mPosX = x;
    myen.mPosY = y;
    
    enemies.push_back(myen);
    
}

void EnemyManager::renderEnemies(int x, int y, std::vector<Bullet> allbullets) {
    for (int i=0;i<enemies.size(); i++) {
        enemies[i].moveTowards(x, y);
        enemies[i].render(allbullets);
        allbullets.reserve(enemies[i].bullets.size()+enemies[i].bullets.size());
        allbullets.insert(allbullets.end(), enemies[i].bullets.begin(), enemies[i].bullets.end());
    }
}

