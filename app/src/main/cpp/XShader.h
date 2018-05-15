//
// Created by 程方明 on 2018/5/14.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

protected:
    unsigned  int vsh = 0;
    unsigned  int fsh = 0;
    unsigned  int program = 0;




};


#endif //XPLAY_XSHADER_H
