//
// Created by 程方明 on 2018/5/14.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::SetRender(void *win){
    view = win;
}
void GLVideoView::Render(XData data){
    if(!view){
        return;
    }
    if(!txt){
        // 创建texture
        txt = XTexture::Create();
        txt->Init(view);
    }
    txt->Draw(data.datas, data.width, data.height);
}