//
//  GHomeScene.cpp
//  OnlineGame
//
//  Created by guang on 16/10/2.
//
//

#include "GHomeScene.h"
#include "data/GCache.h"
#include "protocol_model/GModeUser.h"
#include "ui/GUserInfo.h"
#include "ui/GSetting.h"
#include "ui/GRule.h"
#include "ui/GSkin.h"
#include "ui/GShare.h"
#include "tools/GTools.h"
#include "common/GCommon.h"
#include "ui/GNumber.h"

USING_NS_CC;

Scene* GHomeScene::createScene()
{
    auto layer = GHomeScene::create();
    layer->setName("scene");
    
    return layer;
}

bool GHomeScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }
    
    initUI();
    
    GModeUser::infos();
    
    startHeartBeat();
    this->runAction(Sequence::create(DelayTime::create(1),
                                     CallFunc::create(CC_CALLBACK_0(GHomeScene::updateUI, this)),NULL));
    GTools::playMusic(MUSIC_MIAN);

    return true;
}

void GHomeScene::initUI()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto bg1 = Sprite::create("jm-souyeBJ1.png");
    bg1->setPosition(s.width/2, s.height/2);
    bg1->setScale(2);
    uiLayer->addChild(bg1, 1);
    
    auto bg = Layer::create();
    uiLayer->addChild(bg, 1);
    
    
    auto logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(s.width/2,s.height*0.7f));
    bg->addChild(logo);
 
    auto t_kill = Sprite::create("jm-souyeWZ2.png");
    t_kill->setPosition(Vec2(s.width/2-30,s.height*0.32f));
    bg->addChild(t_kill);

    n_kill = GNumber::create(GCache::getInstance()->getUser()->maxKill);
    n_kill->setColor(Color3B(109,244,78));
    n_kill->setAnchorPoint(Vec2(0,0.5));
    n_kill->setPosition(t_kill->getPositionX()+t_kill->getContentSize().width/2 + 20, t_kill->getPositionY());
    bg->addChild(n_kill);
    
    Button* btn = Button::create("an-annniu3-1.png","an-annniu3-2.png");
    btn->setName("start");
    btn->setScale9Enabled(true);
    btn->setContentSize(Size(250,100));
    btn->setPosition(Vec2(s.width/2,s.height*0.15f));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    bg->addChild(btn);
    
    auto t = Sprite::create("jm-souyeWZ1.png");
    t->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
    btn->addChild(t);
    
    
    //左上角
    auto name_bg = Button::create("jm-souye1.png","jm-souye1.png");
    name_bg->setAnchorPoint(Vec2(0,1));
    name_bg->setPosition(Vec2(20, s.height-20));
    name_bg->setName("info");
    name_bg->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    bg->addChild(name_bg);
    
    auto head_bg = Sprite::create("jm-souye1-1.png");
    head_bg->setAnchorPoint(Vec2(0.5,0.5));
    head_bg->setPosition(head_bg->getContentSize().width/2+5, name_bg->getContentSize().height/2+5);
    name_bg->addChild(head_bg);
    
    char c[7];
    sprintf(c, "%d",GCache::getInstance()->getUser()->skinId);

    std::string skinId = c;
    std::string path = "juese";
    std::string path1 = path + skinId + std::string("-1.png");
    
    head = Sprite::create(path1);
//    head->setAnchorPoint(Vec2(0, 0));
    head->setPosition(head_bg->getPosition());
    head->setScale(1);
    name_bg->addChild(head);

    
//    auto stencil = Sprite::create("jm-souye2.png");
//    stencil->setAnchorPoint(Vec2(0.5,0.5));
//    stencil->setPosition(0, 0);
//    stencil->setScale(74/stencil->getContentSize().width);
//
//    auto clipper = ClippingNode::create();
//    clipper->setContentSize(stencil->getContentSize()*stencil->getScale());
//    clipper->setAnchorPoint(Vec2(0, 0));
//    clipper->setPosition(head_bg->getPosition());
//    clipper->setAlphaThreshold(0);
//    clipper->setInverted(false);
//    name_bg->addChild(clipper,2);
//    clipper->setStencil(stencil);
//    
//    char c[7];
//    sprintf(c, "%d",GCache::getInstance()->getUser()->headId);
//    std::string headPath = "head_";
//    headPath = headPath + c + std::string(".png");
//    head = Sprite::create(headPath);
//    head->setAnchorPoint(Vec2(0.5,0.5));
//    float r = MIN(head->getContentSize().width, head->getContentSize().height);
//    head->setScale(clipper->getContentSize().width/r);
//    clipper->addChild(head);
    
    std::string userName = GCache::getInstance()->getUser()->name;
    if(GCache::getInstance()->getUser()->visitor)
        userName = _T("visitor") + userName;
    
    std::string showName = userName;
    int len = GTools::gbkStrLen(showName);
    if(len > 8)
    {
        int to = 4;
        if(showName.length() >= 21)
            to = 2;
        std::string name_head = GTools::gbkSubStr(showName, 0, to);
        std::string name_end = GTools::gbkSubStr(showName, len-2, len);
        showName = name_head + ".." + name_end;
    }

    name = Text::create(showName, "", 26);
    name->setColor(Color3B::WHITE);
    name->enableOutline(Color4B::BLACK);
    name->setAnchorPoint(Vec2(0,0.5));
    name->setPosition(Vec2(120,name_bg->getContentSize().height/2));
    name_bg->addChild(name);
    
    //右边
    //分享
    Vec2 btnVec(s.width-20,s.height-20);
    btn = Button::create("jm-souyeanniu1-1.png","jm-souyeanniu1-2.png");
    btn->setName("share");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(btnVec);
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    bg->addChild(btn);
    //规则
//    btn = Button::create("jm-souyeanniu2-1.png","jm-souyeanniu2-2.png");
//    btn->setName("rule");
//    btn->setAnchorPoint(Vec2(1,1));
//    btn->setPosition(btnVec + Vec2(0,-170));
//    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
//    bg->addChild(btn);
    //设置
    btn = Button::create("jm-souyeanniu3-1.png","jm-souyeanniu3-2.png");
    btn->setName("setting");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(btnVec + Vec2(0,-170*1));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    bg->addChild(btn);
    //皮肤
    btn = Button::create("jm-souyeanniu4-1.png","jm-souyeanniu4-2.png");
    btn->setName("skin");
    btn->setAnchorPoint(Vec2(1,1));
    btn->setPosition(Vec2(btnVec.x+5,s.height*0.24f));
    btn->addTouchEventListener(CC_CALLBACK_2(GHomeScene::touchEvent, this));
    bg->addChild(btn);
}

void GHomeScene::updateUI()
{
    char c[7];
    
    std::string userName = GCache::getInstance()->getUser()->name;
    if(GCache::getInstance()->getUser()->visitor)
        userName = _T("visitor") + userName;
    std::string showName = userName;
    int len = GTools::gbkStrLen(showName);
    if(len > 8)
    {
        int to = 4;
        if(showName.length() >= 21)
            to = 2;
        std::string name_head = GTools::gbkSubStr(showName, 0, to);
        std::string name_end = GTools::gbkSubStr(showName, len-2, len);
        showName = name_head + ".." + name_end;
    }

    name->setString(showName);
    
//    sprintf(c, "%d",GCache::getInstance()->getUser()->headId);
//    std::string headPath = "head_";
//    headPath = headPath + c + std::string(".png");
//    head->initWithFile(headPath);
    
    sprintf(c, "%d",GCache::getInstance()->getUser()->skinId);
    
    std::string skinId = c;
    std::string path = "juese";
    std::string path1 = path + skinId + std::string("-1.png");
    
    Node* name_bg = head->getParent();
    Vec2 p = head->getPosition();
    head->removeFromParent();
    head = Sprite::create(path1);
//    head->setAnchorPoint(Vec2(0, 0));
    head->setPosition(p);
    head->setScale(1);
    name_bg->addChild(head);
    
    n_kill->setNum(GCache::getInstance()->getUser()->maxKill);
    
    GUserInfoUpdate* info = dynamic_cast<GUserInfoUpdate*>(uiLayer->getChildByName("UserInfoUpdate")) ;
    if(info)
    {
        info->updateUI();
    }
    
    GUserInfoUpdateHead* infoHead = dynamic_cast<GUserInfoUpdateHead*>(uiLayer->getChildByName("UserInfoUpdateHead")) ;
    if(infoHead)
    {
        infoHead->updateUI();
    }
    
    GSkin* skin = dynamic_cast<GSkin*>(uiLayer->getChildByName("skin")) ;
    if(skin)
    {
        skin->updateUI();
    }
}

void GHomeScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    Button* btn = (Button*)pSender;
    std::string name = btn->getName();
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            GTools::playSound(SOUND_BUTTON);
            break;
            
        case Widget::TouchEventType::MOVED:
            break;
            
        case Widget::TouchEventType::ENDED:
            
            if(name == "start")
            {
                GModeUser::enterRoom();
            }
            else if(name == "info")
            {
                auto info = GUserInfo::create();
                uiLayer->addChild(info,2);
            }
            else if(name == "setting")
            {
                uiLayer->addChild(GSetting::create(),2);
            }
            else if (name == "rule")
            {
                uiLayer->addChild(GRule::create(),2);
            }
            else if (name == "skin")
            {
                uiLayer->addChild(GSkin::create(),2);
            }
            else if (name == "share")
            {
                uiLayer->addChild(GShare::create(),2);
            }
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
    
}
