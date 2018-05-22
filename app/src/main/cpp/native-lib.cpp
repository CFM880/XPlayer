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

class TestObs : public IObserver{
public:
    void Update(XData d){
//        XLOGI("TestObs size %d", d.size);
    }
};

IVideoView *view = NULL;
extern "C"
JNIEXPORT jstring
JNICALL
Java_com_cfm880_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    TestObs *obs = new TestObs();
    IDemux *de = new FFDemux();
//    de->AddObs(obs);
    de->Open("/sdcard/v1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);


    de->Start();
    vdecode->Start();
    adecode->Start();
//    for (;;){
//        XData d = de->Read();
//        XLOGI("Read Package size %d", d.size);
//    }

    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_cfm880_xplay_XPlay_initView__Ljava_lang_Object_2(JNIEnv *env, jobject instance,
                                                          jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    view->SetRender(win);
//    XEGL::Get()->Init(win);
//    XShader shader;
//    shader.Init();

//     view-
}