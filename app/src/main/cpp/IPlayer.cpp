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

void IPlayer::Main() {
    while (!isExit){
        mux.lock();
        if (audioPlay && !vdecode){
            mux.unlock();
            XSleep(2);
            continue;
        }
        // 同步
        // 获取音频的pts,告诉视频
        int apts = audioPlay->pts;
        XLOGE("apts = %d", apts);
        vdecode->synPts = apts;
        mux.unlock();
        XSleep(2);
    }

}

IPlayer* IPlayer::Get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}

void  IPlayer::Close() {
    mux.lock();
    //1.先关闭主体，再清理观察者
    // 同步线程
    XThread::Stop();
    // 解封清理
    if (demux){
        demux->Stop();
    }
    // 解码清理
    if (vdecode){
        vdecode->Stop();
    }
    if (adecode){
        adecode->Stop();
    }

    //2.清理缓冲队列
    if (vdecode){
        vdecode->Clear();
    }
    if (adecode){
        adecode->Clear();
    }
    if (audioPlay){
        audioPlay->Clear();
    }
    //3.清理资源
    if (audioPlay){
        audioPlay->Close();
    }
    if (videoView){
        videoView->Close();
    }
    if (vdecode){
        vdecode->Close();
    }
    if (adecode){
        adecode->Close();
    }
    if (demux){
        demux->Close();
    }
    mux.unlock();

}
/**
 * 打开和开始分开
 * @param path
 * @return
 */
bool IPlayer::Open(const char *path){
    Close();
    mux.lock();
    if (!demux || !demux->Open(path)){
        XLOGE("dmeux->Open %s failed!", path);
        mux.unlock();
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
    mux.unlock();
    return true;
}
/**
 * 先启动解码线程
 * 和音频播放视频
 * 如果解封装先启动
 * 而解码器未启动会直接丢掉前面解码的内容
 * @return
 */
bool IPlayer::Start(){

    if (audioPlay){
        audioPlay->StartPlay(outPara);
    }

    if (vdecode){
        vdecode->Start();
    }

    if (adecode){
        adecode->Start();
    }
    mux.lock();
    if (!demux || !demux->Start()){
        XLOGE("demex->Start failed");
        mux.unlock();
        return false;
    }
    XThread::Start();
    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView){
        videoView->SetRender(win);
    }
}

void IPlayer::InitHard(void *vm) {

}