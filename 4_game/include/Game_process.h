#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"

class Game_scene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float delta);

    int interpritation_x(const int x);
    int interpritation_y(const int y);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event *event);

    cocos2d::EventListenerKeyboard* listener_k;
    cocos2d::EventListenerMouse* _mouseListener;

    cocos2d::Label* label_damage;
    
    static mission* ptr;

    CREATE_FUNC(Game_scene);
};
