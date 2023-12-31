//
// Created by 水兵 on 2023/12/30.
//

#ifndef TMP_TMCTX_H
#define TMP_TMCTX_H

#include <unordered_set>
#include <string>
#include <vector>
#include "MoveRule.h"
using namespace std;
class TmCtx {
public:
    unordered_set<string> Q, F;
    unordered_set<char> S,G;
    string q0;
    int N{};
    vector<MoveRule> delta;

    TmCtx();
};


#endif //TMP_TMCTX_H
