#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_cfm880_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux *de = new FFDemux();
    de->Open("/sdcard/video.mp4");
    for (;;){
        XData d = de->Read();
        XLOGI("Read Package size %d", d.size);
    }
    return env->NewStringUTF(hello.c_str());
}
