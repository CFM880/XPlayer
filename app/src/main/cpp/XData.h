//
// Created by 程方明 on 2018/4/27.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    int width =0;
    int height = 0;
    int size = 0;
    void Drop();
    bool isAudio = false;
};


#endif //XPLAY_XDATA_H
