#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"

class TestObs : public IObserver{
public:
    void Update(XData d){
//        XLOGI("TestObs size %d", d.size);
    }
};
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

    de->Start();
    vdecode->Start();
    adecode->Start();
//    for (;;){
//        XData d = de->Read();
//        XLOGI("Read Package size %d", d.size);
//    }

    return env->NewStringUTF(hello.c_str());
}
