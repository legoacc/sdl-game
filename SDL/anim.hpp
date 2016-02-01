//
//  anim.hpp
//  SDL
//
//  Created by Andrei Berdnykov on 31.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#ifndef anim_hpp
#define anim_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "base.hpp"
#include <iostream>




class Animation {
    
public:
    void getFromArray(LTexture arr [], std::string sname, int len);
    
    std::string name;
    
    std::vector<LTexture> frames;
    
    int length;
    
    int betweenFrameCount;
    
    int counter = 0;
    int counter2 = 0;
};


class AnimationManager {

public:
    static bool playAnimation(int x, int y, Animation& animation);
    
    static void addAnimation (int x, int y, Animation animation);
    
    static void playFrames();
    
private:
    static std::vector<Animation> curr;
    static std::vector<int> xs;
    static std::vector<int> ys;
};


#endif /* anim_hpp */
