#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/Main_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Game_process.h"

USING_NS_CC;


Scene* Game_scene::createScene()
{
    return Game_scene::create();
}

int Game_scene::interpritation_x(const int x) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return 21 + x * (visibleSize.width - 21) / ptr->param.size.first;
}

int Game_scene::interpritation_y(const int y) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return 20 + y * (visibleSize.height - 21) / ptr->param.size.second;
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

    // подготовка кораблей бота
    ptr->player_ready();

    // Вывод всех label & sprite, настройка их
    auto sprite_back = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/sea.jpg");
    sprite_back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite_back, -2);
   
    // вывод карты
    for (size_t i = 0; i < ptr->param.size.first; i++)
    {
        for (size_t k = 0; k < ptr->param.size.second; k++)
        {
            int x = interpritation_x(i);
            int y = interpritation_y(k);
            if (ptr->arena[i][k].state == ground) {
                ptr->arena[i][k].sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cell_earth.jpg"
                );
            }
            else {
                ptr->arena[i][k].sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cell_sea.jpg"
                );
            }
            ptr->arena[i][k].sprite_->setPosition(Vec2(x, y));
            this->addChild(ptr->arena[i][k].sprite_, -1);
        }
    }

    // вывод юнитов
    for (size_t i = 0; i < ptr->GetSize(ptr->p1); i++)
    {
        auto s = ptr->GetShip(ptr->p1, i);
        s->set_current_coord({ 2 * (i / 2), 
            (ptr->param.size.second - 1 - (2 * (i % 2) ))});
        ptr->arena[2 * (i / 2)][(ptr->param.size.second - 1 - (2 * (i % 2)))].
            set_state(busy);
        switch (s->type)
        {
        case cruiser_t:
            s->sprite_ = Sprite::create(
            "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        case aircraft_carrier_cruiser:
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        case aircraft_carrier:
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        default:
            break;
        }
    }
    for (size_t i = 0; i < ptr->GetSize(ptr->p2); i++)
    {
        auto s = ptr->GetShip(ptr->p2, i);
        s->set_current_coord({ 2 * (i / 2), 2 * (i % 2) });
        ptr->arena[2 * (i / 2)][(2 * (i % 2))].set_state(busy);
        switch (s->type)
        {
        case cruiser_t:
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        case aircraft_carrier_cruiser:
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        case aircraft_carrier:
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            this->addChild(s->sprite_);
            break;
        default:
            break;
        }
    }

    // вывод суммарного урона
    std::string str = std::to_string(ptr->p1.get_damage());
    this->label_damage = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 18);
    this->label_damage->setPosition(Vec2(visibleSize.width / 1.1 - origin.x,
        visibleSize.height / 1.1 - origin.y));
    this->addChild(this->label_damage, 1);

    // обработка действий
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Game_scene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    // настройка обновлений
    this->scheduleUpdate();
    return true;
}

void Game_scene::update(float delta) {
    for (size_t i = 0; i < ptr->GetSize(ptr->p1); i++)
    {
        auto s = ptr->GetShip(ptr->p1, i);
        s->sprite_->setPosition(Vec2(
            interpritation_x(s->get_coord().first),
            interpritation_y(s->get_coord().second)));
    }
    for (size_t i = 0; i < ptr->GetSize(ptr->p2); i++)
    {
        auto s = ptr->GetShip(ptr->p2, i);
        s->sprite_->setPosition(Vec2(
            interpritation_x(s->get_coord().first),
            interpritation_y(s->get_coord().second)));
    }
    for (size_t i = 0; i < ptr->air.size(); i++)
    {
        auto a = ptr->air[i];
        a->sprite_->setPosition(Vec2(
            interpritation_x(a->get_coord().first),
            interpritation_y(a->get_coord().second)));
    }
    std::string str = std::to_string(ptr->p1.get_damage());
    this->label_damage->setString(str);
}

void Game_scene::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    std::cout << e->getCursorX() << " " << e->getCursorY() << std::endl;
}

void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}