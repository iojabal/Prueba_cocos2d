#include "MainMenu.h"
#include "LevelJAT.h"
#include "LevelFBH.h"
#include "LevelLE.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene =Scene::create();

    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenu::init() {

    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    title = Sprite::create("layers/gd.png");
    title->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 4) * 3.5));
    title->setScale(1);
    this->addChild(title, 1);

    auto exitButton = MenuItemImage::create("layers/buttonexit.png", "layers/buttonexit.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    float x = origin.x + visibleSize.width - exitButton->getContentSize().width / 2;
    float y = origin.y + exitButton->getContentSize().height / 2;
    exitButton->setPosition(Vec2(x, y));


    mySprite = Sprite::create("layers/bg001.png");
    mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    mySprite->setScale(2.2);
    this->addChild(mySprite);

    auto menu_item_1 = MenuItemFont::create("Level 1", CC_CALLBACK_1(MainMenu::lvl1, this));
    auto menu_item_2 = MenuItemFont::create("Level 2", CC_CALLBACK_1(MainMenu::lvl2, this));
    auto menu_item_3 = MenuItemFont::create("Level 3", CC_CALLBACK_1(MainMenu::lvl3, this));

  //  auto menu_item_2 = MenuItemFont::create("Died", CC_CALLBACK_1(MainMenu::Died, this));
    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1));


    _player = cocos2d::Sprite::create("layers/player.png");
    _player->setPosition(Vec2(100, 25));
    _player->setScaleX(0.25);
    _player->setScaleY(0.25);
    addChild(_player, 5);


    this->scheduleUpdate();


    auto  *menu= Menu::create(menu_item_1, menu_item_2, menu_item_3,exitButton, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);


    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mainmusic.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mainmusic.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.15);

    return true;

}

void MainMenu::lvl1(cocos2d::Ref* pSender) {
    log("lvl1");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    auto scene = SceneTwo::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::lvl2(cocos2d::Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    auto scene = Sceneone::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::lvl3(cocos2d::Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    log("lvl3");
    auto scene =SceneTree::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainMenu::update(float delta) {
   
    auto position = _player->getPosition();
    position.x += 200 * delta;
    // position.y += 100 * delta;
    if (position.x > 1080 - (_player->getBoundingBox().size.width / 2)) {
        position.x = this->getBoundingBox().getMinX() - _player->getBoundingBox().size.width / 2;

        //obstacleLayer->removeFromParentAndCleanup(true);
    }
    _player->setPosition(position);
}