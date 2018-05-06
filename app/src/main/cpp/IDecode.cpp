//
// Created by 程方明 on 2018/5/3.
//

#include "IDecode.h"
#include "XLog.h"

void IDecode::Update(XData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }
    while (!isExit) {
        packsMutex.lock();
        packs.push_back(pkt);
        packsMutex.unlock();
        // 阻塞
        if (packs.size() > maxList) {
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }
}
void IDecode::Main() {
    while (!isExit){
        packsMutex.lock();
        if (packs.empty()){
            packsMutex.unlock();
            XSleep(1);
            continue;
        }
        // 取出packet
        XData pack = packs.front();
        packs.pop_front();
        // 发送数据到解码线程，一次发送数据包，可能解码多个结果
        if ( this->SendPacket(pack)){
            while (!isExit){
                // 获取解码数据
                XData frame = RecvFrame();
                if (!frame.data) break;
                // 发送数据到观察者；
                XLOGE("Recv %d ", frame.size);
                this->Notify(frame);
            }

        }
        pack.Drop();
        packsMutex.unlock();

    }

}