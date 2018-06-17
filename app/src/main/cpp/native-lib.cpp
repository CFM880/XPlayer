#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"

class TestObs : public IObserver{
public:
    void Update(XData d){
//        XLOGI("TestObs size %d", d.size);
    }
};
IVideoView *view = NULL;
extern "C"
JNIEXPORT
jint  JNI_OnLoad(JavaVM *vm, void *res){
    FFDecode::InitHard(vm);

    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
//    de->Open("/sdcard/v1080.mp4");

    IDecode *vdecode = new FFDecode();
    //vdecode->Open(de->GetVPara(), true);
//    vdecode->Open(de->GetVPara(), false);

    IDecode *adecode = new FFDecode();
//    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
    XParameter outPara = de->GetAPara();

//    resample->Open(de->GetAPara(),outPara);
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
//    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);


    //vdecode->Open();
    // de->Start();
    // vdecode->Start();
    // adecode->Start();
    // 注入
    IPlayer::Get()->demux = de;        // 解封装
    IPlayer::Get()->adecode = adecode;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;
    IPlayer::Get()->Open("/sdcard/v1080.mp4");
    IPlayer::Get()->Start();
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT jstring
JNICALL
Java_com_cfm880_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    //XLOGI("S begin!");
    //XSleep(3000);
    //XLOGI("S end!");
    //return env->NewStringUTF(hello.c_str());


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_cfm880_xplay_XPlay_initView(JNIEnv *env, jobject instance,
                                                          jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayer::Get()->InitView(win);
}