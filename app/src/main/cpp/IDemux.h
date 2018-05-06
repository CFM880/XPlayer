//
// Created by 程方明 on 2018/4/27.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

// 解封装接口类
class IDemux:public IObserver {
public:
    // 打开文件或者流媒体 rtmp, http, rtsp
    virtual bool Open(const char *url) = 0;
    // 获取视频参数
    virtual XParameter GetVPara() = 0;
    // 获取音频参数
    virtual XParameter GetAPara() = 0;
    // 读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;
    // 总时长
    int totalMs;
protected:
    void Main();
};


#endif //XPLAY_IDEMUX_H
