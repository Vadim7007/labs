#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Download_config.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/Main_scene.h"

class Game_scene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void winScene();

    void update(float delta);

    friend int interpritation_x(const int x);
    friend int interpritation_y(const int y);
    friend int interpritation_x_1(const int x);
    friend int interpritation_y_1(const int y);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event *event);
    void onMouseDownMA(cocos2d::Event* event, cell& c);
    void onKeyReleasedFinish(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void ActionShip(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event,
        std::shared_ptr<ship> s);
    void ActionAircraft(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event,
        aircraft* a);

    void display_map();
    void display_unit1();
    void display_unit2();
    /*
    friend void display_map(Scene* sc);
    friend void display_unit1(Scene* sc);
    friend void display_unit2(Scene* sc);
    */
    cocos2d::EventListenerKeyboard* listener;
    cocos2d::EventListenerMouse* _mouseListener;

    cocos2d::Label* label_damage;
    
    static mission* ptr;
    bool win = false;

    CREATE_FUNC(Game_scene);
};
