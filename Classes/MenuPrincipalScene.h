//
//  MenuPrincipalScene.h
//  Codemotion
//
//  Created by Jon Segador on 27/11/15.
//
//

#ifndef MenuPrincipalScene_h
#define MenuPrincipalScene_h

#include "cocos2d.h"

class MenuPrincipalScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuPrincipalScene);
    
    void playButton(cocos2d::Ref* pSender);
};

#endif /* MenuPrincipalScene_h */



