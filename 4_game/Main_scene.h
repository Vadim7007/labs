#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Ready_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Game_process.h"


class Main_scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStart(cocos2d::Ref* pSender);
    void start_game(const float dif);

    CREATE_FUNC(Main_scene);
};