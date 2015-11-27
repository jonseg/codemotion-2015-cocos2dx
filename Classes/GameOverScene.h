//
//  GameOverScene.h
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#ifndef GameOverScene_h
#define GameOverScene_h

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    
    void retryButton(cocos2d::Ref* pSender);
    void mainMenuButton(cocos2d::Ref* pSender);
    
};

#endif /* GameOverScene_h */
