#include "Main_scene.h"

USING_NS_CC;

#define PIC_PATH "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/"

mission* Ready_scene::ptr;

void Main_scene::start_game(const float dif) {
    param_mission p;
    mode_mission m;
    config c;
    download_info(c, p, m);
    p.difficult = dif;
    auto M = new mission(m, p, c);
    ::Ready_scene::ptr = M;
    Director::getInstance()->replaceScene(::Ready_scene::createScene());
}

Scene* Main_scene::createScene()
{
    return Main_scene::create();
}

bool Main_scene::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    auto closeItem = MenuItemImage::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/quit.png",
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/quit.png",
        CC_CALLBACK_1(Main_scene::menuCloseCallback, this));

    auto startItem = MenuItemImage::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/start.png",
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/start.png",
        CC_CALLBACK_1(Main_scene::menuStart, this));

    float x = origin.x + visibleSize.width / 4 + closeItem->getContentSize().width;
    float y = origin.y + visibleSize.height / 5 + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    x = origin.x + visibleSize.width / 4 + closeItem->getContentSize().width;
    y = origin.y + visibleSize.height / 3 + closeItem->getContentSize().height;
    startItem->setPosition(Vec2(x, y));

    auto menu = Menu::create(closeItem, startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto label = Label::createWithTTF("Sea War", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
    
    auto sprite = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_menu.png");

    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.4 + origin.y));

    this->addChild(sprite, 0);

    auto sprite2 = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/sea.jpg");
    
    sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(sprite2, -1);

    return true;
}

void Main_scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void Main_scene::menuStart(Ref* pSender)
{
    this->removeAllChildren();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Sea War", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 0);

    auto sprite = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_menu.png");

    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.4 + origin.y));

    this->addChild(sprite, -1);

    auto sprite2 = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/sea.jpg");

    sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(sprite2, -2);

    auto label1 = Label::createWithTTF("Choose difficult", "fonts/Marker Felt.ttf", 24);

    label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height/2 - label1->getContentSize().height));

    this->addChild(label1, 1);


    float dif = 0;

    auto button1 = ui::Button::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/button.png");
    button1->setTitleText("Easy");
    button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            dif = 0.8;
            start_game(dif);
            break;
        default:
            break;
        }
    });
    button1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100,
        origin.y + visibleSize.height / 3 - label1->getContentSize().height));
    this->addChild(button1);

    auto button2 = ui::Button::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/button.png");
    button2->setTitleText("Medium");
    button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            dif = 1;
           start_game(dif);
        }
    });
    button2->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3 - label1->getContentSize().height));
    this->addChild(button2);

    auto button3 = ui::Button::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/button.png");
    button3->setTitleText("Hard");
    button3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            dif = 1.2;
            start_game(dif);
            break;
        default:
            break;
        }
        });
    button3->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100,
        origin.y + visibleSize.height / 3 - label1->getContentSize().height));
    this->addChild(button3);

    return;
}