//
// Created by 水兵 on 2023/12/30.
//

#ifndef TMP_MOVERULE_H
#define TMP_MOVERULE_H

#include <string>
#include <vector>
#include <utility>
using namespace std;
class MoveRule {
public:
    string old_state, new_state;
    string read;
    string write;
    string lrs;

    MoveRule();
};


#endif //TMP_MOVERULE_H
