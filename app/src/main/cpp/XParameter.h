//
// Created by 程方明 on 2018/5/3.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H

struct AVCodecParameters;
class XParameter {
public:
    AVCodecParameters *para = 0;

    // 音频
    int channels = 2;
    int sample_rate = 44100;
};


#endif //XPLAY_XPARAMETER_H
