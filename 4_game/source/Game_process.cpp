#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/Main_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Game_process.h"

USING_NS_CC;

Scene* Game_scene::createScene()
{
    return Ready_scene::create();
}

bool Game_scene::init()
{
    // Создание сцены
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Вывод всех label & sprite, настройка их
    auto label = Label::createWithTTF("AAAAAA", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);


   

    // настройка обновлений
    this->scheduleUpdate();
    return true;
}

void Game_scene::update(float delta) {
   
}