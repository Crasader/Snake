//
//  GUserCache.h
//  OnlineGame
//
//  Created by guang on 16/10/1.
//
//

#ifndef GUserCache_h
#define GUserCache_h

#define _T(str) GCache::getInstance()->getFont(str)

#include "cocos2d.h"

#include "model/GUser.h"
#include "model/GBullet.h"

class GCache : public cocos2d::Ref
{
private:
    GCache(){};
public:
    static GCache* getInstance();
    
    void init();
    void initFont();
    
    std::string getLang();
    
    void setUser(GUser* user);
    GUser* getUser();
    
    void setBullets(std::vector<GBullet*> bullets);
    GBullet* getBullet(int _id);
    void setBulletId(int bulletId);
    int getBulletId();
    
    void setRoomWidth(int roomWidth);
    int getRoomWidth();
    
    void setRoomHeight(int roomHeight);
    int getRoomHeight();
    
    void setMapId(int mapId);
    int getMapId();
    
    void setMapPosX(float mapPosX);
    float getMapPosX();
    
    void setMapPosY(float mapPosY);
    float getMapPosY();
    
    void setExps(std::string exps);
    int getExp(int level);
    
    void setGrows(std::string grows);
    float getGrow(int level);
    
    int getLevel(int exp);
    
    void setSkins(std::string skins);
    std::string getSkins();
    void setSkinNum(int skinNum);
    int getSkinNum();
    
    void setNames(std::string names);
    std::string getName();
    
    void setBubble(std::string bubble);
    std::string getBubble();
    
    void setShareAward(int shareAward);
    int getShareAward();
    
    void setKillMeUid(std::string killMeUid);
    std::string getKillMeUid();
    
    static int getMapPlitNum();
    
    std::string getFont(const std::string &key);
    void destory();
    
public:
    void setUid(std::string uid);
    std::string getUid();
    static void setMusic(bool music);
    static bool isMusic();
    static void setSound(bool sound);
    static bool isSound();
    static void setHandStyle(bool isRight);
    static bool isRightHand();
    
    static void setMaxLen(int maxLen);
    static int getMaxLen();
private:
    std::string lang;
    GUser* _user;
    int bulletId;
    int roomWidth;
    int roomHeight;
    int mapId;
    float mapPosX;
    float mapPosY;
    std::vector<GBullet*> bullets;
    cocos2d::ValueMap v_font;
    std::vector<std::string> exps;
    std::vector<std::string> grows;
    std::vector<std::string> names;
    std::string skins;
    std::string killMeUid;
    std::string bubble;
    int shareAward;
    int skinNum;
};

#endif /* GUserCache_h */
