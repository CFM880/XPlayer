//
// Created by 程方明 on 2018/5/14.
//

#ifndef XPLAY_GLVIDEOVIEW_H
#define XPLAY_GLVIDEOVIEW_H


#include "XData.h"
class XTexture;
class GLVideoView {
public:
    virtual void SetRender(void *win);
    virtual void Render(XData data);

protected:
    void *view = 0;
    XTexture *txt = 0;
};


#endif //XPLAY_GLVIDEOVIEW_H
