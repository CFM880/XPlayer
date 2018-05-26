//
// Created by 程方明 on 2018/5/25.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
};


#endif //XPLAY_IAUDIOPLAY_H
