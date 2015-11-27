//
//  GameScene.cpp
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#include "GameScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
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
    
    player = Sprite::create("player.png");
    player->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + player->getContentSize().height));
    this->addChild(player);
    
    this->schedule(schedule_selector(GameScene::generateAsteroid), 1.0);
    this->schedule(schedule_selector(GameScene::generateBullet), 1.0);
    this->scheduleUpdate();
    
    auto pauseMenuItem = MenuItemLabel::create(Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(GameScene::pauseButton, this));
    pauseMenuItem->setPosition(Vec2(origin.x + visibleSize.width - pauseMenuItem->getContentSize().width, origin.y + visibleSize.height - pauseMenuItem->getContentSize().height));
    
    auto menu = Menu::create(pauseMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void GameScene::generateAsteroid(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *asteroid = Sprite::create("asteroid.png");
    
    int xRandomPosition = (arc4random() % (int)(visibleSize.width - (asteroid->getContentSize().width / 2)));
    
    asteroid->setPosition(Vec2(xRandomPosition + origin.x, origin.y + visibleSize.height + asteroid->getContentSize().height/2));
    

    auto rotateAction = RotateBy::create(3, 360);
    auto repeatForeverAction = RepeatForever::create(rotateAction);
    asteroid->runAction(repeatForeverAction);
    auto moveAction = MoveTo::create(3.0, Point(asteroid->getPosition().x, -asteroid->getContentSize().height/2));
    
    asteroid->runAction(moveAction);
    
    asteroids.push_back(asteroid);
    this->addChild(asteroids[asteroids.size() - 1], 1);
}


void GameScene::generateBullet(float dt) {
    Sprite *bullet = Sprite::create("laser.png");
    bullet->setPosition(player->getPosition().x, player->getPosition().y + player->getContentSize().height/2);
    bullets.push_back(bullet);
    this->addChild(bullet);
}


void GameScene::update(float dt)
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        if (asteroids[i]->getPosition().y <= -asteroids[i]->getContentSize().height/2)
        {
            this->removeChild(asteroids[i]);
            asteroids.erase(asteroids.begin() + i);
        }
    }
    
    for (int i = 0; i < asteroids.size(); i++)
    {
        if (player->getBoundingBox().intersectsRect(asteroids[i]->getBoundingBox()))
        {
            this->unscheduleUpdate();
            this->unschedule(schedule_selector(GameScene::generateAsteroid));
            this->unschedule(schedule_selector(GameScene::generateBullet));
            this->removeChild(asteroids[i]);
            asteroids.erase(asteroids.begin() + i);
            this->removeChild(player);
            auto gameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, gameOverScene));
        }
        
    }
    
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float bulletSpeed = 500 * dt;
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->setPosition(Vec2(bullets[i]->getPosition().x, bullets[i]->getPosition().y + bulletSpeed));
        
        if (bullets[i]->getPosition().y > visibleSize.height + bullets[i]->getContentSize().height)
        {
            this->removeChild(bullets[i]);
            bullets.erase(bullets.begin() + i);
        }
        else{

            for (int j = 0; j < asteroids.size(); j++)
            {
                if (bullets[i]->getBoundingBox().intersectsRect(asteroids[j]->getBoundingBox()))
                {
                    this->removeChild(bullets[i]);
                    bullets.erase(bullets.begin() + i);
                    this->removeChild(asteroids[j]);
                    asteroids.erase(asteroids.begin() + j);
                }
                
            }
        }
    }
}


void GameScene::pauseButton(cocos2d::Ref* pSender){
    auto pauseScene = PauseScene::createScene();
    Director::getInstance()->pushScene(pauseScene);
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
    return player->getBoundingBox().containsPoint(convertTouchToNodeSpace(touch));
}

void GameScene::onTouchMoved(cocos2d::Touch *touch,cocos2d::Event * event)
{
    auto touchPoint = touch->getLocation();
    player->setPosition(Vec2(touchPoint.x, player->getPosition().y));
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
    //isTouching = false;
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event)
{
    onTouchEnded(touch, event);
}
