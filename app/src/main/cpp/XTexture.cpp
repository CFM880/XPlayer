//
// Created by 程方明 on 2018/5/14.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture:public XTexture{
public:
    XShader sh;
    XTextureType  type;
    virtual bool Init(void *win, XTextureType type){
        this->type = type;
        if(!win){
            XLOGE("XTexture init failed win is NULL");
            return false;
        }
        if(!XEGL::Get()->Init(win)){
            return false;
        }

        sh.Init((XShaderType)(type));
        return true;
    }
    virtual void Draw(unsigned char *data[], int width, int height) {
        sh.GetTexture(0, width, height, data[0]); // Y
        if(type==XTEXTURE_YUV420P){
            sh.GetTexture(1, width / 2, height / 2, data[1]); // U
            sh.GetTexture(2, width / 2, height / 2, data[2]); // V
        } else{
            sh.GetTexture(1, width / 2, height / 2, data[1], true); // UV
        }

        sh.Draw();
        XEGL::Get()->Draw();
    }
};

XTexture *XTexture::Create(){
    return new CXTexture();
}
