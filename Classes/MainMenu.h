#pragma once
#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void update(float delta) override;
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

    cocos2d::Sprite* _player;
    cocos2d::Sprite* title;
    cocos2d::Sprite* mySprite;
    void lvl1(Ref* pSender);
    void lvl2(Ref* pSender);
    void lvl3(Ref* pSender);

};

