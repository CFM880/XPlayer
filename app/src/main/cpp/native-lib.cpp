#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFDemux.h"
#include "FFPlayerBuilder.h"
#include "XLog.h"

#include "XEGL.h"


class TestObs : public IObserver{
public:
    void Update(XData d){
//        XLOGI("TestObs size %d", d.size);
    }
};
//IVideoView *view = NULL;
static IPlayer *player = NULL;
extern "C"
JNIEXPORT
jint  JNI_OnLoad(JavaVM *vm, void *res){
    // FFDecode::InitHard(vm);
    player = FFPlayerBuilder::Get()->BuiderPlayer();
    FFPlayerBuilder::InitHard(vm);

    player->Open("/sdcard/v1080.mp4");
    player->Start();
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
    if (player)
        player->InitView(win);
}