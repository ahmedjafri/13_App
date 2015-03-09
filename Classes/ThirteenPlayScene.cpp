#include "ThirteenPlayScene.h"

USING_NS_CC;

Scene* ThirteenPlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ThirteenPlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ThirteenPlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ThirteenPlay::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    card = Sprite::create("cards.png",Rect(0.0f, 0.0f, 160.0f, 230.0f));
    card->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height - card->getContentSize().height));
    this->addChild(card, 1);
    
    // create and initialize a label
    auto label = Label::createWithTTF("ThirteenPlay", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // listen for touch events
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Layer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Layer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Layer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(Layer::onTouchesEnded, this);
    this->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

Point ThirteenPlay::touchToPoint(Touch* touch)
{
    // convert the touch object to a position in our cocos2d space
    return CCDirector::getInstance()->convertToGL(touch->getLocationInView());
}

bool ThirteenPlay::isTouchingSprite(Touch* touch)
{
    // here's one way, but includes the rectangular white space around our sprite
    //return CGRectContainsPoint(this->sprite->boundingBox(), this->touchToPoint(touch));
    
    // this way is more intuitive for the user because it ignores the white space.
    // it works by calculating the distance between the sprite's center and the touch point,
    // and seeing if that distance is less than the sprite's radius
    return (this->card->getPosition().getDistance(this->touchToPoint(touch)) < 100.0f);
}

void ThirteenPlay::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    // reset touch offset on beginning new touch event
    this->touchOffset = Point::ZERO;
    
    for( auto touch : touches )
    {
        // if this touch is within our sprite's boundary
        if( touch && this->isTouchingSprite(touch) )
        {
            // calculate offset from sprite to touch point
            this->touchOffset = this->card->getPosition() - this->touchToPoint(touch);
        }
    }
}

void ThirteenPlay::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    for( auto touch : touches )
    {
        // move the card
        if( touch && touchOffset.x && touchOffset.y )
            this->card->setPosition(this->touchToPoint(touch) + this->touchOffset);
    }
}

void ThirteenPlay::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for( auto touch : touches )
    {
        if( touch && touchOffset.x && touchOffset.y  )
        {
            // move card to final position
            this->card->setPosition(this->touchToPoint(touch) + this->touchOffset);
            
            // stop any existing actions and reset the scale
            this->card->stopAllActions();
            this->card->setScale(1.0f);
            
            // animate letting go of the sprite
            this->card->runAction(Sequence::create(
                                                     ScaleBy::create(0.125f, 1.111f),
                                                     ScaleBy::create(0.125f, 0.9f),
                                                     nullptr
                                                     ));
        }
    }
}

void ThirteenPlay::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
