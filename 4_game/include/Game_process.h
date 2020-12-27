#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"

class Game_scene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float delta);

    static mission* ptr;

    CREATE_FUNC(Ready_scene);
};