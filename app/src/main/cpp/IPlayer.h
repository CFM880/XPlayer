//
// Created by 程方明 on 2018/6/5.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H

#include <sys/types.h>
#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IDecode;
class IResample;
class IVideoView;
class IAudioPlay;

class IPlayer : public XThread {
public:
    static IPlayer *Get(unsigned char index = 0);
    virtual bool Open(const char *path);
    virtual void InitView(void *win);
    virtual bool Start();
    // 是否视频硬解码
    bool isHardDecode = true;
    // 音频输出参数
    XParameter outPara;

    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    IPlayer(){}
};


#endif //XPLAY_IPLAYER_H
