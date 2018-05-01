//
// Created by 程方明 on 2018/5/1.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;
// 启动线程
void  XThread::Start(){
    thread th(&XThread::ThreadMain, this);
    // 放弃对新线程的
    th.detach();
}

void XThread::ThreadMain(){
    XLOGI("线程进入");
    Main();
    XLOGI("线程退出");
}
// 通过isExit安全停止线程（不一定成功）
void  XThread::Stop(){

}
// 主函数入口
void  Main() {};