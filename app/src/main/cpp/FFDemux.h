//
// Created by 程方明 on 2018/4/27.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H



#include "XData.h"
#include "IDemux.h"
struct AVFormatContext;

class FFDemux: public IDemux {
public:
    // 打开文件或者流媒体 rtmp, http, rtsp
     bool Open(const char *url);

    XParameter GetVPara();
    XParameter GetAPara();
    // 读取一帧数据，数据由调用者清理
    XData Read();

    FFDemux();

private:
    // 无参数的
    AVFormatContext *ic = 0;

    int audioStream = 1;
    int videoStream = 0;
};


#endif //XPLAY_FFDEMUX_H
