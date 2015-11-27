#include "AppDelegate.h"
#include "MenuPrincipalScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Codemotion", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Codemotion");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto fileUtils = FileUtils::getInstance();
    auto screenSize = glview->getFrameSize();
    std::vector<std::string> resDirOrders;
    
    // Soporte multi-resolucion
    if ( 2048 == screenSize.width || 2048 == screenSize.height ) // iPad retina
    {
        log("iPad retina");
        resDirOrders.push_back("res/ipadhd");
        resDirOrders.push_back("res/ipad");
        resDirOrders.push_back("res/iphonehd6p");
        resDirOrders.push_back("res/iphonehd6");
        resDirOrders.push_back("res/iphonehd5");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(1536, 2048, ResolutionPolicy::NO_BORDER);
    }
    else if ( 1024 == screenSize.width || 1024 == screenSize.height ) // iPad no retina
    {
        log("iPad no retina");
        resDirOrders.push_back("res/ipad");
        resDirOrders.push_back("res/iphonehd6p");
        resDirOrders.push_back("res/iphonehd6");
        resDirOrders.push_back("res/iphonehd5");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
    }
    else if ( 1920 == screenSize.width || 1920 == screenSize.height ) // iPhone retina (6+ y 6S+)
    {
        log("iPhone retina (6+ y 6S+)");
        resDirOrders.push_back("res/iphonehd6p");
        resDirOrders.push_back("res/iphonehd6");
        resDirOrders.push_back("res/iphonehd5");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::NO_BORDER);
    }
    else if ( 1334 == screenSize.width || 1334 == screenSize.height ) // iPhone retina (6 y 6S)
    {
        log("iPhone retina (6 y 6S)");
        resDirOrders.push_back("res/iphonehd6");
        resDirOrders.push_back("res/iphonehd5");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(750, 1334, ResolutionPolicy::NO_BORDER);
    }
    else if ( 1136 == screenSize.width || 1136 == screenSize.height ) // iPhone retina (5 y 5S)
    {
        log("iPhone retina (5 y 5S)");
        resDirOrders.push_back("res/iphonehd5");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::NO_BORDER);
    }
    else if ( 960 == screenSize.width || 960 == screenSize.height ) // iPhone retina (4 y 4S)
    {
        log("iPhone retina (4 y 4S)");
        resDirOrders.push_back("res/iphonehd");
        resDirOrders.push_back("res/iphone");
        
        glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
    }
    else // iPhone no retina y dispositivos Android
    {
        // Si es portrait, comprobar el height. Si es landscape, comprobar el width.
        if ( 1080 < screenSize.height ) // Dispositivos Android de alta resolucion
        {
            log("Dispositivos Android de alta resolucion");
            resDirOrders.push_back("res/iphonehd");
            resDirOrders.push_back("res/iphone");
            
            glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
        }
        else // iPhone no retina y dispositivos Android de baja resolucion
        {
            log("iPhone no retina y dispositivos Android de baja resolucion");
            resDirOrders.push_back("res/iphone");
            glview->setDesignResolutionSize(320, 480, ResolutionPolicy::NO_BORDER);
        }
    }
    
    fileUtils->setSearchPaths(resDirOrders);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MenuPrincipalScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
