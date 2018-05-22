//
// Created by 程方明 on 2018/5/14.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H


class XTexture {
public:
    static XTexture *Create();
    virtual bool Init(void *win) = 0;
    virtual void Draw(unsigned char *data[], int width, int height) = 0;

};


#endif //XPLAY_XTEXTURE_H
