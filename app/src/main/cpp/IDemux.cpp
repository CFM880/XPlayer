//
// Created by 程方明 on 2018/4/27.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {

    while (!isExit){
        XData d = Read();
        XLOGI("IDemux Read %d", d.size);
        if(d.size <= 0){
            break;
        }
    }
}
