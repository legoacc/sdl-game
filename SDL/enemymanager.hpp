//
//  enemymanager.hpp
//  SDL
//
//  Created by Andrei Berdnykov on 01.02.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#ifndef enemymanager_hpp
#define enemymanager_hpp

#include <stdio.h>
#include "enemy.hpp"
#include "bullet.hpp"
#include <vector>



class EnemyManager {
    
public:
    //DO NOT USE
    
    //USE
    static void createEnemy (EnemyType en, int x, int y);
    
    static void renderEnemies(int x, int y, std::vector<Bullet> enemybullets, bool cd);
    
    static std::vector<Bullet> allbullets;
    
private:
    
    static std::vector<Enemy> enemies;
};
#endif /* enemymanager_hpp */
