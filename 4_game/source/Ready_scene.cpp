#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Ready_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/Main_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Game_process.h"

USING_NS_CC;

Scene* Ready_scene::createScene()
{
    return Ready_scene::create();
}

bool Ready_scene::init()
{
    // Создание сцены
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Вывод всех label & sprite, настройка их
    auto label = Label::createWithTTF("Sea War", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);


    std::string help = "";
    this->label_help = Label::createWithTTF(help, "fonts/Marker Felt.ttf", 22);
    this->label_help->setPosition(Vec2(origin.x + visibleSize.width /1.5,
        origin.y + visibleSize.height / 1.7));
    this->addChild(this->label_help, 0);


    auto sprite1 = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cruiser.png");

    sprite1->setPosition(Vec2(visibleSize.width / 3 - origin.x,
        visibleSize.height / 4 + origin.y));

    this->addChild(sprite1, 0);

    auto sprite2 = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_cruiser.png");

    sprite2->setPosition(Vec2(visibleSize.width / 3 - origin.x, 
        visibleSize.height / 2.45 + origin.y));

    this->addChild(sprite2, 0);

    auto sprite3 = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier.png");

    sprite3->setPosition(Vec2(visibleSize.width / 3 - origin.x, 
        visibleSize.height / 1.7 + origin.y));

    this->addChild(sprite3, 0);

    std::string str1 = "x";
    str1 += std::to_string(ptr->count_if(cruiser_t));
    this->label1 = Label::createWithTTF(str1, "fonts/Marker Felt.ttf", 22);

    this->label1->setPosition(Vec2(visibleSize.width / 3 - origin.x,
        visibleSize.height / 4 + origin.y));

    this->addChild(this->label1, 0);

    std::string str2 = "x";
    str2 += std::to_string(ptr->count_if(aircraft_carrier_cruiser));
    this->label2 = Label::createWithTTF(str2, "fonts/Marker Felt.ttf", 22);

    this->label2->setPosition(Vec2(visibleSize.width / 3 - origin.x,
        visibleSize.height / 2.45 + origin.y));

    this->addChild(this->label2, 1);

    std::string str3 = "x";
    str3 += std::to_string(ptr->count_if(aircraft_carrier));
    this->label3 = Label::createWithTTF(str3, "fonts/Marker Felt.ttf", 22);

    this->label3->setPosition(Vec2(visibleSize.width / 3 - origin.x,
        visibleSize.height / 1.7 + origin.y));

    this->addChild(this->label3, 1);


    std::string str1num;
    str1num = ptr->print_if(cruiser_t);
    this->label1num = Label::createWithTTF(str1num, "fonts/Marker Felt.ttf", 22);

    this->label1num->setPosition(Vec2(visibleSize.width / 3 - origin.x / 2,
        visibleSize.height / 4.6 + origin.y));

    this->addChild(this->label1num, 0);

    std::string str2num;
    str2num = ptr->print_if(aircraft_carrier_cruiser);
    this->label2num = Label::createWithTTF(str2num, "fonts/Marker Felt.ttf", 22);

    this->label2num->setPosition(Vec2(visibleSize.width / 3 - origin.x / 2,
        visibleSize.height / 2.66 + origin.y));

    this->addChild(this->label2num, 0);

    std::string str3num;
    str3num = ptr->print_if(aircraft_carrier);
    this->label3num = Label::createWithTTF(str3num, "fonts/Marker Felt.ttf", 22);

    this->label3num->setPosition(Vec2(visibleSize.width / 3 - origin.x / 2,
        visibleSize.height / 1.8 + origin.y));

    this->addChild(this->label3num, 0);


    std::string str = std::to_string(ptr->p1.get_money());

    this->label_money = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 20);

    this->label_money->setPosition(Vec2(visibleSize.width/1.1 - origin.x,
        visibleSize.height/1.1 - origin.y));

    this->addChild(this->label_money, 2);


    auto sprite_back = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/sea.jpg");

    sprite_back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(sprite_back, -1);

    // настройка действий с клавиатурой
    this-> listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // настройка обновлений
    this->scheduleUpdate();
    return true;
}

void Ready_scene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
   
    std::string str = "Z - Buy cruiser\nX - Buy aircraft carrier cruiser\n";
                str +="C - Buy aircraft carrier\nA - Buy fighter\n";
                str +="S - Buy front bomber\nD - Buy bomber\nQ - Buy ammunations\n";
                str +="W - Buy weapon\nE - Sell ship\nM - modificate parametrs";
    this->label_help->setString(str);

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE: {
        Director::getInstance()->replaceScene(::Main_scene::create());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: {
        Director::getInstance()->replaceScene(::Game_scene::createScene());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_Z: {
        ptr->buy_ship(ptr->p1, cruiser_t);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_X: {
        ptr->buy_ship(ptr->p1, aircraft_carrier_cruiser);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_C: {
        ptr->buy_ship(ptr->p1, aircraft_carrier);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_M: {
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleasedM, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_A: {
        ptr->buy_aircraft(ptr->p1, fighter_t, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_S: {
        ptr->buy_aircraft(ptr->p1, front_bomber_t, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_D: {
        ptr->buy_aircraft(ptr->p1, bomber_t, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_Q: { // боеприпасы
        ptr->buy_ammunations(ptr->p1, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_W: { // оружие
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleasedW, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_E: { // продать
        ptr->sell_ship(ptr->p1, ptr->GetLastId());
        break;
    }
    default:
        break;
    }
}

void Ready_scene::onKeyReleasedM(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

    std::string str = "0 - HP\n1 -speed\n3 - range\n4 - storage\n5 - max_weapon";
                str +="\n6 - max_aircraft\n7 -Damage\n8 - Rate";
    this->label_help->setString(str);

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE: {
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleased, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: {
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleased, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_0: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)0);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_1: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)1);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_2: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)2);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_3: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)3);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_4: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)4);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_5: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)5);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_6: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)6);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_7: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)7);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_8: {
        ptr->modificate(ptr->p1, ptr->GetLastId(), (modificated_parametrs)8);
        break;
    }
    default:
        break;
    }
}

void Ready_scene::onKeyReleasedW(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

    std::string str = "0 - light\n1 - middle\n2 - heavy";
    this->label_help->setString(str);

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE: {
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleased, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: {
        this->listener->onKeyReleased = CC_CALLBACK_2(Ready_scene::onKeyReleased, this);
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_0: {
        ptr->buy_weapons(ptr->p1, light, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_1: {
        ptr->buy_weapons(ptr->p1, middle, ptr->GetLastId());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_2: {
        ptr->buy_weapons(ptr->p1, heavy, ptr->GetLastId());
        break;
    }
    default:
        break;
    }
}

void Ready_scene::update(float delta) {
    std::string str1 = "x";
    str1 += std::to_string(ptr->count_if(cruiser_t));
    this->label1->setString(str1);

    std::string str2 = "x";
    str2 += std::to_string(ptr->count_if(aircraft_carrier_cruiser));
    this->label2->setString(str2);

    std::string str3 = "x";
    str3 += std::to_string(ptr->count_if(aircraft_carrier));
    this->label3->setString(str3);


    std::string str1num = ptr->print_if(cruiser_t);
    this->label1num->setString(str1num);

    std::string str2num = ptr->print_if(aircraft_carrier_cruiser);
    this->label2num->setString(str2num);

    std::string str3num = ptr->print_if(aircraft_carrier);
    this->label3num->setString(str3num);

    std::string str = std::to_string(ptr->p1.get_money());
    this->label_money->setString(str);
}