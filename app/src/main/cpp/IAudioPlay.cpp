//
// Created by 程方明 on 2018/5/25.
//

#include "IAudioPlay.h"
#include "XLog.h"
void IAudioPlay::Clear() {
    framesMutex.lock();
    while (!frames.empty()){
        frames.front().Drop();
        frames.pop_front();
    }
    pts = 0;
    framesMutex.unlock();
}

XData IAudioPlay::GetData() {
    XData d;
    while (!isExit){
        framesMutex.lock();
        if (!frames.empty()){
            // 有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            pts = d.pts;
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    pts = d.pts;
    // 未获取数据
    return d;
}

void IAudioPlay::Update(XData data) {
    XLOGE("IAudioPlay::Update %d", data.size);
    // 压入缓冲队列
    if (data.size <= 0 || !data.data){
        return;
    }
    while (!isExit){
        framesMutex.lock();
        if (frames.size() > maxFrame){
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }

}