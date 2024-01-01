//
// Created by 水兵 on 2023/12/31.
//

#ifndef TMP_TMCTX_H
#define TMP_TMCTX_H

#include "TMTape.h"
#include "string"
using namespace std;
class TmCtx {
public:
    vector<TMTape> tapes;
    string state;
    int n;
    TmCtx(int n){
        tapes.resize(n);
        this->n = n;
    }
};


#endif //TMP_TMCTX_H
