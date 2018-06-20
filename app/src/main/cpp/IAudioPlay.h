//
// Created by 程方明 on 2018/5/25.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:

    //缓冲满后是阻塞的
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
    // 获取缓冲数据，没有数据则阻塞
    virtual XData GetData();

    virtual void Close() = 0;
    virtual void Clear();

    // 最大帧数
    int maxFrame = 100;
    int pts = 0;
protected:
    std::list <XData> frames;
    std::mutex framesMutex;



};


#endif //XPLAY_IAUDIOPLAY_H
