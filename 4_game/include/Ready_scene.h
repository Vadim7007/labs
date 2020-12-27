#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"

class Ready_scene: public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleasedM(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleasedW(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void update(float delta);

    static mission* ptr;

    cocos2d::Label* label_money;
    cocos2d::Label* label1;
    cocos2d::Label* label2;
    cocos2d::Label* label3;
    cocos2d::Label* label1num;   
    cocos2d::Label* label2num;
    cocos2d::Label* label3num;
    cocos2d::Label* label_help;

    cocos2d::EventListenerKeyboard* listener;

    CREATE_FUNC(Ready_scene);
};