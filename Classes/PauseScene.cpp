//
//  PauseScene.cpp
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#include "PauseScene.h"
#include "GameScene.h"
#include "MenuPrincipalScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PauseScene::create();
    scene->addChild(layer);
    return scene;
}

bool PauseScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto resumeMenuItem = MenuItemLabel::create(Label::createWithTTF("Continuar", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(PauseScene::resumeButton, this));
    auto retryMenuItem = MenuItemLabel::create(Label::createWithTTF("Reintentar", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(PauseScene::retryButton, this));
    auto mainMenuMenuItem = MenuItemLabel::create(Label::createWithTTF("Menu principal", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(PauseScene::mainMenuButton, this));
    
    auto menu = Menu::create(resumeMenuItem, retryMenuItem, mainMenuMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);
    
    return true;
}

void PauseScene::resumeButton(cocos2d::Ref* pSender){
    Director::getInstance()->popScene();
}

void PauseScene::retryButton(cocos2d::Ref* pSender){
    auto scene = GameScene::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}

void PauseScene::mainMenuButton(cocos2d::Ref* pSender){
    auto scene = MenuPrincipalScene::createScene();
    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}