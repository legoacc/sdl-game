//
//  anim.cpp
//  SDL
//
//  Created by Andrei Berdnykov on 31.01.16.
//  Copyright © 2016 Andrei Berdnykov. All rights reserved.
//

#include "anim.hpp"

std::vector<Animation> AnimationManager::curr;
std::vector<int> AnimationManager::xs;
std::vector<int> AnimationManager::ys;

bool AnimationManager::playAnimation(int x, int y, Animation& animation) {
    if (animation.counter2==animation.betweenFrameCount && animation.counter != animation.length) {
        animation.counter++;
        animation.counter2=0;
    }
    else animation.counter2++;
    if (animation.counter != animation.length) {
        animation.frames[animation.counter].render(x, y, NULL, 0, NULL);
        return true;
    }
    else return false;
}

void AnimationManager::addAnimation (int x, int y, Animation animation) {
    curr.push_back(animation);
    xs.push_back(x);
    ys.push_back(y);
}

void AnimationManager::playFrames () {
    for (int i=0;i<curr.size();i++) {
        if (!playAnimation(xs[i], ys[i], curr[i])) {
            curr.erase(curr.begin()+i);
            ys.erase(ys.begin()+i);
            xs.erase(xs.begin()+i);
            curr.shrink_to_fit();
            xs.shrink_to_fit();
            ys.shrink_to_fit();
        }
    }
}






void Animation::getFromArray(LTexture arr [], std::string sname, int len) {
    for (int i=0;i<len;i++) {
        frames.push_back(arr[i]);
    }
    name = sname;
    length =len;
}
