//
// Created by 程方明 on 2018/4/27.
//

#include "FFDemux.h"
#include "XLog.h"
extern "C" {
#include <libavformat/avformat.h>
}


// 打开文件或者流媒体 rtmp, http, rtsp
bool FFDemux::Open(const char *url){
    XLOGI("Open file % s begin", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDmeux open %s failed", url);
    }
    XLOGI("FFDmeux open %s success!", url);
    // 读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("avformat_find_stream_info open %s failed", url);
    }
    this->totalMs = ic->duration / (AV_TIME_BASE/1000);
    XLOGI("total ms = %d!", this->totalMs);
    return true;
}
// 读取一帧数据，数据由调用者清理
XData FFDemux::Read(){
    if (!ic){
        return XData();
    }
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0){
        av_packet_free(&pkt);
        return XData();
    }
//    XLOGI("pack size is %d ptss %lld", pkt->size, pkt->pts);
    d.data = (unsigned char *)(pkt);
    d.size = pkt->size;


    return d;
}

XParameter FFDemux::GetVPara() {
    if (!ic){
        return XParameter();
    }
    // 获取视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0){
        XLOGE("av_find_best_stream failed");
        return XParameter();
    }
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    return para;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst){
        isFirst = false;
        // 注册所有封装器
        av_register_all();
        // 注册所有的解码器
        avcodec_register_all();
        // 初始化网络
        avformat_network_init();

        XLOGI("register all");
    }
}