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
    virtual bool Init(void *win){
        if(!win){
            XLOGE("XTexture init failed win is NULL");
            return false;
        }
        if(!XEGL::Get()->Init(win)){
            return false;
        }
        sh.Init();
        return true;
    }
};

XTexture *XTexture::Create(){
    return new CXTexture();
}
