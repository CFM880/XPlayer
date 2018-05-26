//
// Created by 程方明 on 2018/5/23.
//

#include "IResample.h"

void IResample::Update(XData data){
    XData d = this->Resample(data);
    if (d.size > 0 ){
        this->Notify(data);
    }
}