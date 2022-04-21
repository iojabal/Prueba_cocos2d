/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "DrawEnvieronment.h"
#include "stdlib.h"
#include "time.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100));

    auto layer = HelloWorld::create();
    layer->SetPhysiscWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin(); //[0. 0]
   
  /*HitBox Scenario*/
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1000, 0, 0), 5);
    auto edgeNode = Node::create();
    edgeBody->setDynamic(false);
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
  /*Fin Hitbox Scenario*/

    


/*

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

 //   _player->setAnchorPoint(cocos2d::Vec2::ZERO);
    _player->setPosition(cocos2d::Vec2(50, 50));
    _player->setScaleX(0.3);
    _player->setScaleY(0.3);
    auto spriteBody = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(0, 0, 0));
    spriteBody->setCollisionBitmask(1);
    spriteBody->setContactTestBitmask(true);
    spriteBody->setMass(1);
   
    _player->setPhysicsBody(spriteBody);
    addChild(_player, 10);

    obstacleLayer->setPosition(cocos2d::Vec2(1080, 50));
    obstacleLayer->setScaleX(0.4);
    obstacleLayer->setScaleY(0.4);
    auto spriteBody2 = PhysicsBody::createBox(obstacleLayer->getContentSize()/ 2, PhysicsMaterial(0, 0, 0));
    spriteBody2->setCollisionBitmask(2);
    spriteBody2->setContactTestBitmask(true);
    obstacleLayer->setPhysicsBody(spriteBody2);
    addChild(obstacleLayer, 10);
    
    

   // drawBack();
   
    this->scheduleUpdate();
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);*/


    initKeyboard();
    drawBack();
    this->scheduleUpdate();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/audio2.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/audio2.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
    
    return true;
}

void HelloWorld::update(float delta) {
    log("Posicion en Y: %5.2f ", _player->getPositionY());
    log("Posicion del anchor point: %5.2f", _player->getAnchorPointInPoints());
    auto position = obstacleLayer->getPosition();
    position.x -= 100 * delta;
   // position.y += 100 * delta;
    if (position.x < 0 - (obstacleLayer->getBoundingBox().size.width / 2)) {
        position.x = this->getBoundingBox().getMaxX() + obstacleLayer->getBoundingBox().size.width / 2;
    }
    obstacleLayer->setPosition(position);

    //int rnd = 0 + rand() % (11 - 0);
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact) {
    auto a = contact.getShapeA()->getBody()->getNode();
    auto b = contact.getShapeB()->getBody()->getNode();

    if (1 == a->getPhysicsBody()->getCollisionBitmask() && 2 == b->getPhysicsBody()->getCollisionBitmask() ||
        2 == a->getPhysicsBody()->getCollisionBitmask() && 1 == b->getPhysicsBody()->getCollisionBitmask()) {
        log("ocurrio una colisioon");
        _player->removeFromParentAndCleanup(true);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


void HelloWorld::jumpPlayer(cocos2d::EventKeyboard::KeyCode Keycode, cocos2d::Event* event)\
{
    isGrounded = _player->getPositionY() <= 32.1;

    log("Tecla presionada %d", Keycode);
    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        auto moveBy = cocos2d::MoveBy::create(1, cocos2d::Vec2(-100, 0));
        _player->runAction(moveBy);
    }
    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        auto moveBy = cocos2d::MoveBy::create(1, cocos2d::Vec2(100, 0));
        _player->runAction(moveBy);
    } 
    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) {
        auto jumpBy = cocos2d::JumpBy::create(1, Vec2(00, 50), 150, 1);
        auto rotate = cocos2d::RotateBy::create(1, 90);
        if (isGrounded == true) {
            _player->runAction(jumpBy);
            _player->runAction(rotate);
        }
          
    }
}

void HelloWorld::initKeyboard()
{
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::jumpPlayer, this);
    //listener->onKeyReleased
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
