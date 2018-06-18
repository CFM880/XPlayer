//
// Created by 程方明 on 2018/6/17.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H


#include "IPlayer.h"
#include <mutex>

class IPlayerProxy: public IPlayer {
public:
    static IPlayerProxy *Get(){
        static IPlayerProxy px;
        return &px;
    }
    virtual void Init(void *vm);
    virtual bool Open(const char *path);
    virtual void InitView(void *win);
    virtual bool Start();

protected:
    IPlayerProxy(){}
    IPlayer *player = 0;
    std::mutex mux;
};


#endif //XPLAY_IPLAYERPROXY_H
