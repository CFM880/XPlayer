//
// Created by 程方明 on 2018/4/29.
//

#ifndef XPLAY_XLOG_H
#define XPLAY_XLOG_H




class XLog {

};
#include <android/log.h>
#define XLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "XPlay", __VA_ARGS__)
#define XLOGI(...) __android_log_print(ANDROID_LOG_INFO, "XPlay", __VA_ARGS__)
#define XLOGE(...) __android_log_print(ANDROID_LOG_ERROR, "XPlay", __VA_ARGS__)
#endif //XPLAY_XLOG_H
