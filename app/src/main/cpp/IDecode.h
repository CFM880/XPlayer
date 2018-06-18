//
// Created by 程方明 on 2018/5/3.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

// 解码接口，支持硬解码
class IDecode: public IObserver {
public:
    static void InitHard(void *vm);
    // 打开解码器
    virtual bool Open(XParameter para, bool isHard = false) = 0;
    // future模型，发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;
    // 从线程中获取解码结果, 再次调用会互用上次空间，线程不安全
    virtual XData RecvFrame() = 0;
    // 主体阻塞
    void Update(XData pkt);

    bool isAudio = false;

    // 最大队列缓冲
    int maxList = 100;
    // 同步时间，再次打开文件要清理
    int synPts = 0;
    int  pts = 0;

protected:
    void Main();
    // 读取缓冲帧
    std::list<XData> packs;

    std::mutex packsMutex;

};


#endif //XPLAY_IDECODE_H
