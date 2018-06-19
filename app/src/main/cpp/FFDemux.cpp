//
// Created by 程方明 on 2018/4/27.
//

#include "FFDemux.h"
#include "XLog.h"
extern "C" {
#include <libavformat/avformat.h>
}
// 分数转为浮点数
static  double  r2d(AVRational r){
    return r.num == 0 || r.den == 0?0.:(double) r.num / (double) r.den;
}
// 打开文件或者流媒体 rtmp, http, rtsp
bool FFDemux::Open(const char *url){
    Close();
    mux.lock();
    XLOGI("Open file %s begin", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDmeux open %s failed", url);
        mux.unlock();
        return false;
    }
    XLOGI("FFDmeux open %s success!", url);
    // 读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("avformat_find_stream_info open %s failed", url);
        mux.unlock();
        return false;
    }
    this->totalMs = ic->duration / (AV_TIME_BASE/1000);
    mux.unlock();
    XLOGI("total ms = %d!", this->totalMs);
    GetVPara();
    GetAPara();
    return true;
}

void FFDemux::Close(){
    mux.lock();
    if (ic){
        avformat_close_input(&ic);
    }
    mux.unlock();
}
// 读取一帧数据，数据由调用者清理
XData FFDemux::Read(){
    mux.lock();
    if (!ic){
        mux.unlock();
        return XData();
    }
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0){
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }
//    XLOGI("pack size is %d ptss %lld", pkt->size, pkt->pts);
    d.data = (unsigned char *)(pkt);
    d.size = pkt->size;
    if (pkt->stream_index == audioStream){
        d.isAudio = true;
    } else if(pkt->stream_index == videoStream) {
        d.isAudio = false;
    } else {
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }
    // 转换pts
    pkt->pts = pkt->pts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int)pkt->pts;
    XLOGE("demux pts %d", d.pts);
    mux.unlock();
    return d;
}

XParameter FFDemux::GetVPara() {
    mux.lock();
    if (!ic){
        mux.unlock();
        return XParameter();
    }
    // 获取视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0){
        XLOGE("av_find_best_stream failed");
        mux.unlock();
        return XParameter();
    }
    videoStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    mux.unlock();
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

XParameter FFDemux::GetAPara(){
    mux.lock();
    if (!ic){
        mux.unlock();
        return XParameter();
    }
    // 获取视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (re < 0){
        XLOGE("av_find_best_stream failed");
        mux.unlock();
        return XParameter();
    }
    audioStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.channels = ic->streams[re]->codecpar->channels;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    mux.unlock();
    return para;
}