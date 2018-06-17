//
// Created by 程方明 on 2018/6/5.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IAudioPlay.h"
#include "IResample.h"
#include "IVideoView.h"
#include "XLog.h"

IPlayer* IPlayer::Get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}
/**
 * 打开和开始分开
 * @param path
 * @return
 */
bool IPlayer::Open(const char *path){
    if (!demux || !demux->Open(path)){
        XLOGE("dmeux->Open %s failed!", path);
        return false;
    }
    XLOGE("dmeux->Open %s 成功!", path);
    // 解码可能不需要，可能解封装后就是原始数据
    if (!vdecode || !vdecode->Open(demux->GetVPara(), isHardDecode)){
        XLOGE("adecode->Open %s failed!", path);
    }
    // 解码可能不需要，可能解封装后就是原始数据
   if (!adecode || !adecode->Open(demux->GetAPara())){
        XLOGE("adecode->Open %s failed!", path);
    }

    // 重采样有可能不需要，解码码后或者解封装后可能是音频原始数据直接可以播放
    if (outPara.sample_rate <= 0){
        outPara = demux->GetAPara();
    }
    outPara = demux->GetAPara();
    if (!resample || !resample->Open(demux->GetAPara(), outPara)){
        XLOGE(" resample->Open %s failed!", path);
    }
//    if ()
    return true;
}
bool IPlayer::Start(){
    if (!demux || !demux->Start()){
        XLOGE("demex->Start failed");
        return false;
    }
    if (adecode){
        adecode->Start();
    }
    if (audioPlay){
        audioPlay->StartPlay(outPara);
    }
    if (vdecode){
        vdecode->Start();
    }

    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView){
        videoView->SetRender(win);
    }
}

void IPlayer::InitHard(void *vm) {

}