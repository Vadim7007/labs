#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"

class Game_scene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float delta);

    friend int interpritation_x(const int x);
    friend int interpritation_y(const int y);
    friend int interpritation_x_1(const int x);
    friend int interpritation_y_1(const int y);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event *event);
    void onMouseDownM(cocos2d::Event* event, cell& c);
    /*
    void display_map();
    void display_unit1();
    void display_unit2();
    */
    friend void display_map(Scene* sc);
    friend void display_unit1(Scene* sc);
    friend void display_unit2(Scene* sc);

    cocos2d::EventListenerKeyboard* listener;
    cocos2d::EventListenerMouse* _mouseListener;

    cocos2d::Label* label_damage;
    
    static mission* ptr;

    CREATE_FUNC(Game_scene);
};
