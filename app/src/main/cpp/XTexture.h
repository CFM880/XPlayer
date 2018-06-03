//
// Created by 程方明 on 2018/5/14.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H
enum XTextureType{
    XTEXTURE_YUV420P = 0,   // Y 4 u 1 v1
    XTEXTURE_NV12= 25,      // Y4 uv1
    XTEXTURE_NV21 = 26
};

class XTexture {
public:
    static XTexture *Create();
    virtual bool Init(void *win, XTextureType type=XTEXTURE_YUV420P) = 0;
    virtual void Draw(unsigned char *data[], int width, int height) = 0;

};


#endif //XPLAY_XTEXTURE_H
