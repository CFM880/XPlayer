//
// Created by 程方明 on 2018/5/23.
//

#ifndef XPLAY_IRESAMPLE_H
#define XPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver{
public:
    /**
     *
     * @param in 解封装器可以获得
     * @param out
     * @return
     */
    virtual bool Open(XParameter in, XParameter out = XParameter()) = 0;

    virtual XData  Resample(XData indata) = 0;

    virtual void Update(XData data);

    int outChannels = 2;

    int outFormat = 1;

};


#endif //XPLAY_IRESAMPLE_H
