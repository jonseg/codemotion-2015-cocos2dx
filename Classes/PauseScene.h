//
//  PauseScene.h
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#ifndef PauseScene_h
#define PauseScene_h

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PauseScene);
    
    void resumeButton(cocos2d::Ref* pSender);
    void retryButton(cocos2d::Ref* pSender);
    void mainMenuButton(cocos2d::Ref* pSender);
    
};

#endif /* PauseScene_h */
