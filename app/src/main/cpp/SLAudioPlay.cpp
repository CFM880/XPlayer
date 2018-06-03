//
// Created by 程方明 on 2018/5/25.
//

#include "SLAudioPlay.h"
#include "XLog.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
/**
 * 开始播放
 * @param out
 * @return
 */
/**
 * 静态是本cpp文件有效
 */
static SLObjectItf  engineSL = NULL;
static SLEngineItf eng = NULL;
static SLObjectItf mix = NULL;

static SLObjectItf  player = NULL;
static SLPlayItf    iplayer = NULL;
static SLAndroidSimpleBufferQueueItf pcmQue = NULL;
SLAudioPlay::SLAudioPlay() {
    buf = new unsigned char[1024 * 1024];
}

SLAudioPlay::~SLAudioPlay() {
    delete buf;
    buf = 0;
}
static SLEngineItf  CreateSL(){
    SLresult re;
    SLEngineItf en;
    re = slCreateEngine(&engineSL, 0, 0, 0, 0 ,0);
    if (re != SL_RESULT_SUCCESS){
        return NULL;
    }
    re = (*engineSL)->Realize(engineSL, SL_BOOLEAN_FALSE);
    if (re != SL_RESULT_SUCCESS){
        return NULL;
    }

    re = (*engineSL)->GetInterface(engineSL, SL_IID_ENGINE, &en);
    if (re != SL_RESULT_SUCCESS){
        return NULL;
    }
    return en;
}
void SLAudioPlay::PlayCall(void *bufq){
    if (!bufq)
        return;
    SLAndroidSimpleBufferQueueItf bf = (SLAndroidSimpleBufferQueueItf) bufq;
    XLOGI("SLAudioPlay::PlayCall success");
    // 阻塞的
    XData d = GetData();
    if (d.size <= 0){
        XLOGE("GetData() size is 0");
        return;
    }
    if (!buf){
        return;
    }
    memcpy(buf, d.data, d.size);
    (*bf)->Enqueue(bf, buf, d.size);
    d.Drop();

}
static void PcmCall(SLAndroidSimpleBufferQueueItf bf, void *contex){
    SLAudioPlay *ap = (SLAudioPlay *) contex;
    if (!ap){
        XLOGE("PcmCall SLAudioPlay is NULL");
        return;
    }
    ap->PlayCall((void *)bf);
}
bool SLAudioPlay::StartPlay(XParameter out) {
    // 创建引擎接口
    eng = CreateSL();
    if (eng){
        XLOGI("CreateSL SUCCESS");
    } else {
        XLOGE("CreateSL error");
        return false;
    }
    // 创建混音器
    SLresult re = 0;
    re = (*eng)->CreateOutputMix(eng, &mix, 0, 0, 0);
    if (re != SL_RESULT_SUCCESS){
        XLOGE("CreateOutputMix failed");
        return false;
    }
    re = (*mix)->Realize(mix, SL_BOOLEAN_FALSE); // 阻塞式等待
    if (re != SL_RESULT_SUCCESS){
        XLOGE("Mix Realize failed");
        return false;
    }

    SLDataLocator_OutputMix outmix = {SL_DATALOCATOR_OUTPUTMIX, mix};
    SLDataSink audioSink = {&outmix, 0};

    // 配置音频信息
    // 缓冲队列
    SLDataLocator_AndroidSimpleBufferQueue que =  {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};

    // 音频格式
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32) out.channels, // 声道数
            (SLuint32) out.sample_rate*1000,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN// 字节序，小端
    };

    SLDataSource ds = {&que, &pcm};

    // 4.创建播放器

    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_TRUE};
    re = (*eng)->CreateAudioPlayer(eng, &player, &ds, &audioSink, sizeof(ids)/sizeof(SLInterfaceID), ids, req);
    if (re != SL_RESULT_SUCCESS){
        XLOGE("CreateAudioPlayer failed");
        return false;
    } else {
        XLOGI("CreateAudioPlayer success");
    }
    (*player)->Realize(player, SL_BOOLEAN_FALSE);//阻塞式
    // 获得player接口
    re = (*player)->GetInterface(player, SL_IID_PLAY, &iplayer);
    if (re != SL_RESULT_SUCCESS){
        XLOGE("player GetInterface failed");
        return false;
    }

    // 获取缓冲数据接口
    re = (*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQue);
    if (re != SL_RESULT_SUCCESS){
        XLOGE("pcmQue GetInterface failed");
        return false;
    }

    // 设置回调函数，播放队列空调用
    (*pcmQue)->RegisterCallback(pcmQue, PcmCall, this);

    // 设置为播放状态
    (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_PLAYING);
    // 启动队列回调
    (*pcmQue)->Enqueue(pcmQue,"",1);
    XLOGI("SLAudioPlay::StartPlay success!");
    return true;
}