#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/Main_scene.h"
#include "/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/include/Game_process.h"
#include <numeric>
#include <future>
#include <mutex>

USING_NS_CC;

Scene* Game_scene::createScene()
{
    return Game_scene::create();
}

int interpritation_x(const int x) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return 21 + x * (visibleSize.width - 21) / ::Game_scene::ptr->param.size.first;
}

int interpritation_y(const int y) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return 20 + y * (visibleSize.height - 21) / ::Game_scene::ptr->param.size.second;
}

int interpritation_x_1(const int x_p) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int x = round((x_p - 21) /
        (float)((visibleSize.width - 21) / ::Game_scene::ptr->param.size.first));
    if (x < 0) return 0;
    if (x > ::Game_scene::ptr->param.size.first - 1) return
        ::Game_scene::ptr->param.size.first - 1;
    return x;
}

int interpritation_y_1(const int y_p) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int y = round((y_p - 20) 
        / (float)((visibleSize.height - 21) / ::Game_scene::ptr->param.size.second));
    if (y < 0) return 0;
    if (y > ::Game_scene::ptr->param.size.second - 1) return
        ::Game_scene::ptr->param.size.second - 1;
    return y;
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
    /*
    // вывод карты
    std::future<void> m = std::async([&] {display_map(this); });

    // вывод юнитов
    std::future<void> u1 = std::async([&] {display_unit1(this); });
    std::future<void> u2 = std::async([&] {display_unit2(this); });
    */
    
    display_map();
    display_unit1();
    display_unit2();

    auto sprite_back = Sprite::create(
        "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/sea.jpg");
    sprite_back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite_back, -2);

    // вывод суммарного урона
    std::string str = std::to_string(ptr->p1.get_damage());
    this->label_damage = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 18);
    this->label_damage->setPosition(Vec2(visibleSize.width / 1.1 - origin.x,
        visibleSize.height / 1.1 - origin.y));
    this->addChild(this->label_damage, 1);

   /*
    m.get();
    u1.get();
    u2.get();
    */

    // обработка действий
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Game_scene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    this->listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(Game_scene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
    cell c = ptr->arena[interpritation_x_1(e->getCursorX())]
        [interpritation_y_1(e->getCursorY())];
    if (c.state == busy) {
        _mouseListener->onMouseDown = CC_CALLBACK_1(Game_scene::onMouseDownMA, this, c);
        auto s = ptr->GetByCoord(c);
        if ((bool)s) {
            this->listener->onKeyReleased = CC_CALLBACK_2(Game_scene::ActionShip, this, s);
        }
        else {
            auto a = ptr->GetAirByCoord(c);
            listener->onKeyPressed = CC_CALLBACK_2(Game_scene::ActionAircraft, this, a);
        }
    }
}

void Game_scene::onMouseDownMA(Event* event, cell& c) {
    EventMouse* e = (EventMouse*)event;
    cell to = ptr->arena[interpritation_x_1(e->getCursorX())]
        [interpritation_y_1(e->getCursorY())];
    auto s = ptr->GetByCoord(c);
    if (to.state == busy) {
        auto to_s = ptr->GetByCoord(to);
        if ((bool)s) {
            if ((bool)to_s) {
                s->attack(*to_s);
            }
            else {
                aircraft* to_a = ptr->GetAirByCoord(to);
                s->attack(*to_a);
            }
        }
        else {
            auto a = ptr->GetAirByCoord(c);
            if ((bool)to_s) {
                a->attack(*to_s);
            }
            else {
                aircraft* to_a = ptr->GetAirByCoord(to);
                a->attack(*to_a);
            }
        }
    }

    else{
        if ((bool)s) {
            ptr->arena.move(*s, to);
        }
        else {
            auto a = ptr->GetAirByCoord(c);
            ptr->arena.move(*a, to);
        }
    }
    _mouseListener->onMouseDown = CC_CALLBACK_1(Game_scene::onMouseDown, this);
    listener->onKeyPressed = CC_CALLBACK_2(Game_scene::onKeyReleased, this);
}

void Game_scene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE: {
        Director::getInstance()->replaceScene(::Main_scene::create());
        break;
    }
    case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: {
        ptr->end_turn();
        break;
    }
    default:
        break;
    }
}

void Game_scene::ActionShip(cocos2d::EventKeyboard::KeyCode keyCode, 
    cocos2d::Event* event, std::shared_ptr<ship> s) {

}

void Game_scene::ActionAircraft(cocos2d::EventKeyboard::KeyCode keyCode, 
    cocos2d::Event* event, aircraft* a) {

}

void Game_scene::display_unit1() {
    for (size_t i = 0; i < ptr->GetSize(ptr->p1); i++)
    {
        auto s = ptr->GetShip(ptr->p1, i);
        s->set_current_coord({ 2 * (i / 2),
            (ptr->param.size.second - 1 - (2 * (i % 2))) });
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
}

void Game_scene::display_unit2() {
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
}

void Game_scene::display_map() {
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
}

/*
void display_unit1(Scene* sc) {
    for (size_t i = 0; i < ::Game_scene::ptr->GetSize(::Game_scene::ptr->p1); i++)
    {
        auto s = ::Game_scene::ptr->GetShip(::Game_scene::ptr->p1, i);
        s->set_current_coord({ 2 * (i / 2),
            (::Game_scene::ptr->param.size.second - 1 - (2 * (i % 2))) });
        ::Game_scene::ptr->arena[2 * (i / 2)][(::Game_scene::ptr->param.size.second - 1 - (2 * (i % 2)))].
            set_state(busy);
        std::mutex m;
        switch (s->type)
        {
        case cruiser_t: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();
            break;
        }
        case aircraft_carrier_cruiser: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();
            break; 
        }
        case aircraft_carrier: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();
            break;
        }
        default:
            break;
        }
    }
}

void display_unit2(Scene* sc) {
    for (size_t i = 0; i < ::Game_scene::ptr->GetSize(::Game_scene::ptr->p2); i++)
    {
        auto s = ::Game_scene::ptr->GetShip(::Game_scene::ptr->p2, i);
        s->set_current_coord({ 2 * (i / 2), 2 * (i % 2) });
        ::Game_scene::ptr->arena[2 * (i / 2)][(2 * (i % 2))].set_state(busy);
        std::mutex m;
        switch (s->type)
        {
        case cruiser_t: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();            break;
        }
        case aircraft_carrier_cruiser: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_cruiser_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();            break;
        }
        case aircraft_carrier: {
            s->sprite_ = Sprite::create(
                "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/air_carrier_mini.png"
            );
            s->sprite_->setPosition(Vec2(
                interpritation_x(s->get_coord().first),
                interpritation_y(s->get_coord().second)));
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(s->sprite_);
            m.unlock();            break;
        }
        default:
            break;
        }
    }
}

void display_map(Scene* sc) {
    for (size_t i = 0; i < ::Game_scene::ptr->param.size.first; i++)
    {
        for (size_t k = 0; k < ::Game_scene::ptr->param.size.second; k++)
        {
            int x = interpritation_x(i);
            int y = interpritation_y(k);
            if (::Game_scene::ptr->arena[i][k].state == ground) {
                ::Game_scene::ptr->arena[i][k].sprite_ = Sprite::create(
                    "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cell_earth.jpg"
                );
            }
            else {
                ::Game_scene::ptr->arena[i][k].sprite_ = Sprite::create(
                    "C:/Users/vadim/Desktop/Me/Programming/study/cocos_l4/MyGame/proj.win32/png/cell_sea.jpg"
                );
            }
            ::Game_scene::ptr->arena[i][k].sprite_->setPosition(Vec2(x, y));
            std::mutex m;
            std::lock_guard<std::mutex> g(m);
            m.lock();
            sc->addChild(::Game_scene::ptr->arena[i][k].sprite_, -1);
            m.unlock();
        }
    }

}
*/