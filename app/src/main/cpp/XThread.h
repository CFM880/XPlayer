//
// Created by 程方明 on 2018/5/1.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

void XSleep(int mis);

// c++ 11 的线程库
class XThread {
public:
    // 启动线程
    virtual bool  Start();
    // 通过isExit安全停止线程（不一定成功）
    virtual void  Stop();
    // 主函数入口
    virtual void  Main() {};
protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};


#endif //XPLAY_XTHREAD_H
