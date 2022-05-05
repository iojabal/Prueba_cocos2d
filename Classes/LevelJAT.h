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
#ifndef __LevelJAT_H__
#define __LevelJAT_H__
#include "cocos2d.h"

class SceneTwo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void drawBack();
    virtual void update(float delta) override;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void goBack(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneTwo);

private:
    cocos2d::Sprite* _player;
    cocos2d::Sprite* obstacleLayer;
    cocos2d::PhysicsWorld *sceneWorld;
    cocos2d::Sprite* cloned;

    int rnd;
    int rnd2;

    void jumpPlayer(cocos2d::EventKeyboard::KeyCode Keycode, cocos2d::Event* event);
    void initKeyboard();
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {sceneWorld = world;}
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //int _playerSpeed = 100;

};

#endif