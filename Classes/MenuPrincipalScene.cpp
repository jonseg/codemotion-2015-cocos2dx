//
//  MenuPrincipalScene.cpp
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#include "MenuPrincipalScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MenuPrincipalScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuPrincipalScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuPrincipalScene::init()
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
    
    Label *gameTitle = Label::createWithTTF("Space Invaders", "fonts/Marker Felt.ttf", 80);
    gameTitle->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - gameTitle->getContentSize().height*2));
    this->addChild(gameTitle);
    
    auto playMenuItem = MenuItemLabel::create(Label::createWithTTF("JUGAR", "fonts/Marker Felt.ttf", 65), CC_CALLBACK_1(MenuPrincipalScene::playButton, this));
    playMenuItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3));
    
    auto menu = Menu::create(playMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    
    return true;
}


void MenuPrincipalScene::playButton(cocos2d::Ref* pSender){
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, gameScene));
}

