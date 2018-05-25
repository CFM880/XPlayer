//
// Created by 程方明 on 2018/4/27.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H
/**
 * 数据类型
 */
enum XDataType{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

struct XData {
    int type = 0;
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    int width =0;
    int height = 0;
    int size = 0;
    void Drop();
    bool Alloc(int size, const char *d=0);
    bool isAudio = false;
};


#endif //XPLAY_XDATA_H
