//
// Created by 程方明 on 2018/4/27.
//

#include "XData.h"
extern "C"{
#include <libavcodec/avcodec.h>
}

void XData::Drop() {
    if(!data) return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}
