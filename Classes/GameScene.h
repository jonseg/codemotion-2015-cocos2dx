//
//  GameScene.h
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);
    
    void pauseButton(cocos2d::Ref* pSender);

    void update(float dt);
    void generateAsteroid(float dt);
    void generateBullet(float dt);
    
private:
    cocos2d::Sprite *player;
    
    std::vector<cocos2d::Sprite *> asteroids;
    std::vector<cocos2d::Sprite *> bullets; 
};

#endif /* GameScene_h */
