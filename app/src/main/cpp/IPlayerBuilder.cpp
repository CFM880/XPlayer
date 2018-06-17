//
// Created by 程方明 on 2018/6/17.
//


#include "IPlayerBuilder.h"

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IAudioPlay.h"
#include "IResample.h"
#include "IVideoView.h"
IPlayer *IPlayerBuilder::BuiderPlayer(unsigned char index){

    IPlayer *play = CreatePlayer(index);
    // 解封装
    IDemux *de = CreateDemux();
    // 视频解码器
    IDecode *vdecode = CreateDecode();
    // 音频解码器
    IDecode *adecode = CreateDecode();
    // 解码器观察解封装
    de->AddObs(vdecode);
    de->AddObs(adecode);
    // 显示观察视频解码器
    IVideoView *view = CreateVideoView();
    vdecode->AddObs(view);
    // 重采样观察音频解码器
    IResample *resample = CreateResample();
    XParameter outPara = de->GetAPara();
    adecode->AddObs(resample);
    // 音频播放观察重采样
    IAudioPlay *audioPlay = CreateAudioPlay();
    resample->AddObs(audioPlay);

    play->demux = de;        // 解封装
    play->adecode = adecode;
    play->vdecode = vdecode;
    play->videoView = view;
    play->resample = resample;
    play->audioPlay = audioPlay;
    return play;
}
