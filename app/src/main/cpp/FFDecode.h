//
// Created by 程方明 on 2018/5/3.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct  AVCodecContext;

class FFDecode: public IDecode {
public:
    bool Open(XParameter para);

protected:
    AVCodecContext *codec = 0;
};


#endif //XPLAY_FFDECODE_H
