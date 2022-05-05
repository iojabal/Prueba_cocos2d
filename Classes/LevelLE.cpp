
#include "LevelLE.h"
//#include "DrawEnvironment.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* SceneTree::createScene(){
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100.)); 
    auto layer = SceneTree::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
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
bool SceneTree::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //setting origin [0,0] on screen
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //[0, 105]

//screen hitbox
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(10000,0,0), 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
//fin screen hitbox

    auto exitButton = MenuItemImage::create("layers/buttonexit.png", "layers/buttonexit.png", CC_CALLBACK_1(SceneTree::goBack, this));
    float x = origin.x + visibleSize.width - exitButton->getContentSize().width / 2;
    float y = origin.y + exitButton->getContentSize().height / 2;
    exitButton->setPosition(Vec2(x, y));




/*BACKGROUND*/
    auto spriteFondo1 = cocos2d::Sprite::create("layers/bg1.png");
    auto spriteFondo2 = cocos2d::Sprite::create("layers/bg2.png");
    auto spriteFondo3 = cocos2d::Sprite::create("layers/bg3.png");
    auto spriteFondo4 = cocos2d::Sprite::create("layers/bg4.png");
    auto spriteFondo5 = cocos2d::Sprite::create("layers/bg5.png");
    obstacleLayer = cocos2d::Sprite::create("layers/obstacle.png");
    _player = cocos2d::Sprite::create("layers/player.png");
    cloned = cocos2d::Sprite::createWithSpriteFrame(obstacleLayer->getSpriteFrame());

    //bg1
    spriteFondo1->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo1->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo1->setScaleX(1.8);
    spriteFondo1->setScaleY(1.8);
    addChild(spriteFondo1, 0);
    //bg2
    spriteFondo2->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo2->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo2->setScaleX(2);
    spriteFondo2->setScaleY(2);
    addChild(spriteFondo2, 5);
    //bg3
    spriteFondo3->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo3->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo3->setScaleX(5);
    spriteFondo3->setScaleY(3);
    addChild(spriteFondo3, 2);
    //bg4
    spriteFondo4->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo4->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo4->setScaleX(5);
    spriteFondo4->setScaleY(2.5);
    addChild(spriteFondo4, 3);
    //bg5
    spriteFondo5->setAnchorPoint(cocos2d::Vec2::ZERO);
    spriteFondo5->setPosition(cocos2d::Vec2::ZERO);
    spriteFondo5->setScaleX(3.5);
    spriteFondo5->setScaleY(1.8);
    addChild(spriteFondo5, 4);
    //player
    //_player->setAnchorPoint(cocos2d::Vec2::ZERO); ahori si esta comentado xd
    _player->setPosition(Vec2(100, 25)); 
    _player->setScaleX(0.25);
    _player->setScaleY(0.25);
    auto spriteBody = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(1, 0, 0));
    spriteBody->setCollisionBitmask(1);
    spriteBody->setContactTestBitmask(true);
    _player->setPhysicsBody(spriteBody);
    addChild(_player, 5);

    //obstacles
    obstacleLayer->setPosition(cocos2d::Vec2(1000, 21));
    obstacleLayer->setScaleX(0.4);
    obstacleLayer->setScaleY(0.4);
    auto spriteBody2 = PhysicsBody::createBox(obstacleLayer->getContentSize()*0.7, PhysicsMaterial(1, 0, 0));
    spriteBody2->setCollisionBitmask(2);
    spriteBody2->setContactTestBitmask(true);
    obstacleLayer->setPhysicsBody(spriteBody2);
    addChild(obstacleLayer, 5);

    cloned->setScale(obstacleLayer->getScaleX(), obstacleLayer->getScaleY());
    auto spriteBody3 = PhysicsBody::createBox(obstacleLayer->getContentSize() / 2, PhysicsMaterial(0, 0, 0));
    spriteBody3->setCollisionBitmask(2);
    spriteBody3->setContactTestBitmask(true);
    cloned->setPosition(obstacleLayer->getPosition() - Vec2(100, 0));
    cloned->setPhysicsBody(spriteBody3);
    addChild(cloned, 4);

/*FIN BACKGROUND*/

    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SceneTree::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
   


    auto* menu = Menu::create(exitButton, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu, 10);

/*AUDIO*/
    initKeyboard();
    this->scheduleUpdate();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/deadlocked.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/deadlocked.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.15);

/*FIN AUDIO*/


    return true;
}

//_playerSpeed = 500;

void SceneTree::update(float delta) {
    //log("valor variable aleatoria: %d ", _player->getPositionY());
    rnd = random(200, 300);
    rnd2 = random(400, 500);
    //log("Posicion del anchor point: %5.2f", _player->getAnchorPointInPoints());
    auto positionx = cloned->getPosition();
    auto position = obstacleLayer->getPosition();
    position.x -= rnd * delta;
    positionx.x -= rnd2 * delta;
    // position.y += 100 * delta;
    if (position.x < 0 - (obstacleLayer->getBoundingBox().size.width / 2)) {
        position.x = this->getBoundingBox().getMaxX() + obstacleLayer->getBoundingBox().size.width / 2;

        //obstacleLayer->removeFromParentAndCleanup(true);
    }
    else if (positionx.x < 0 - (cloned->getBoundingBox().size.width / 2)) {
        positionx.x = this->getBoundingBox().getMaxX() + obstacleLayer->getBoundingBox().size.width / 2;
    }
    obstacleLayer->setPosition(position);
    cloned->setPosition(positionx);


}

bool SceneTree::onContactBegin(cocos2d::PhysicsContact &contact) {
    auto a = contact.getShapeA()->getBody()->getNode();
    auto b = contact.getShapeB()->getBody()->getNode();

    if (1 == a->getPhysicsBody()->getCollisionBitmask() && 2 == b->getPhysicsBody()->getCollisionBitmask() ||
        2 == a->getPhysicsBody()->getCollisionBitmask() && 1 == b->getPhysicsBody()->getCollisionBitmask()) {
       // log("ocurrio una colision");
        _player->removeFromParentAndCleanup(true);
    }
    return true;
}

void SceneTree::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SceneTree::initKeyboard() {
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SceneTree::jumpPlayer, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SceneTree::jumpPlayer(cocos2d::EventKeyboard::KeyCode Keycode, cocos2d::Event* event) {

    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) {
       // log("entra aqi1");
        auto jumpBy = cocos2d::JumpBy::create(1, cocos2d::Vec2(0, 30), 100, 1);
        auto rotate = cocos2d::RotateBy::create(1, 90);
        if (_player->getPositionY() <= 536870913) {
            _player->runAction(jumpBy);
            _player->runAction(rotate);
        }
    }

    /*
    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        auto moveBy = cocos2d::MoveBy::create(1, cocos2d::Vec2(-100, 0), 100, 1);
        _player->runAction(moveBy);
    }
    if (Keycode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        auto moveBy = cocos2d::MoveBy::create(1, cocos2d::Vec2(100, 0), 100, 1);
        _player->runAction(moveBy);
    }
    */

    //log("Tecla presionada %d", Keycode);

}
void SceneTree::goBack(cocos2d::Ref* pSender) {
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mainmusic.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mainmusic.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.15);
    Director::getInstance()->popScene();
}