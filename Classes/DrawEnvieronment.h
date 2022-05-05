#include "LevelFBH.h"

inline void Sceneone::drawBack() {
    auto spriteFondo = cocos2d::Sprite::create("layers/bg1.png");
    auto spriteFondo2 = cocos2d::Sprite::create("layers/bg2.png");
    auto spriteFondo3 = cocos2d::Sprite::create("layers/bg3.png");
    auto spriteFondo4 = cocos2d::Sprite::create("layers/bg4.png");
    auto spriteFondo5 = cocos2d::Sprite::create("layers/bg5.png");
    obstacleLayer = cocos2d::Sprite::create("layers/obstacle.png");
    _player = cocos2d::Sprite::create("layers/player.png");

    //auto spriteFondo = cocos2d::Sprite::create("layers/bg1.png");
    spriteFondo->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo->setScaleX(1.8);
    spriteFondo->setScaleY(1.9);
    addChild(spriteFondo, 0);

    spriteFondo2->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo2->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo2->setScaleX(2);
    spriteFondo2->setScaleY(3);
    addChild(spriteFondo2, 1);

    spriteFondo3->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo3->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo3->setScaleX(1.8);
    spriteFondo3->setScaleY(1.9);
    addChild(spriteFondo3, 0);

    spriteFondo4->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo4->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo4->setScaleX(1.8);
    spriteFondo4->setScaleY(1.9);
    addChild(spriteFondo4, 0);

    spriteFondo5->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo5->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo5->setScaleX(3.5);
    spriteFondo5->setScaleY(1.9);
    addChild(spriteFondo5, 0);

   // _player->setAnchorPoint(cocos2d::Vec2::ZERO);
    _player->setPosition(cocos2d::Vec2(50, 50));
    _player->setScaleX(0.3);
    _player->setScaleY(0.3);
    auto spriteBody = cocos2d::PhysicsBody::createBox(_player->getContentSize(), cocos2d::PhysicsMaterial(0, 0, 0));
    spriteBody->setCollisionBitmask(1);
    spriteBody->setContactTestBitmask(true);
    spriteBody->setMass(1);

    _player->setPhysicsBody(spriteBody);
    addChild(_player, 10);

    obstacleLayer->setPosition(cocos2d::Vec2(1080, 50));
    obstacleLayer->setScaleX(0.4);
    obstacleLayer->setScaleY(0.4);
    obstacleLayer->setParent(obstacleLayer);
    auto spriteBody2 = cocos2d::PhysicsBody::createBox((obstacleLayer->getContentSize())*2/3, cocos2d::PhysicsMaterial(0, 0, 0));
    spriteBody2->setCollisionBitmask(2);
    spriteBody2->setContactTestBitmask(true);
    obstacleLayer->setPhysicsBody(spriteBody2);
    addChild(obstacleLayer, 10);



    // drawBack();

   

    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Sceneone::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

