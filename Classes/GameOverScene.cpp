//
//  GameOverScene.cpp
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#include "GameOverScene.h"
#include "GameScene.h"
#include "MenuPrincipalScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *background = Sprite::create("background.png");
    background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(background);
    
    auto retryMenuItem = MenuItemLabel::create(Label::createWithTTF("Reintentar", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(GameOverScene::retryButton, this));
    auto mainMenuMenuItem = MenuItemLabel::create(Label::createWithTTF("Menu principal", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(GameOverScene::mainMenuButton, this));
    
    auto menu = Menu::create(retryMenuItem, mainMenuMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);
    
    return true;
}

void GameOverScene::retryButton(cocos2d::Ref* pSender){
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameOverScene::mainMenuButton(cocos2d::Ref* pSender){
    auto scene = MenuPrincipalScene::createScene();
    Director::getInstance()->replaceScene(scene);
}