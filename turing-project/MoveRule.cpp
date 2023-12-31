//
// Created by 水兵 on 2023/12/30.
//

#include "MoveRule.h"

MoveRule::MoveRule() {
    read.clear();
    write.clear();
    lrs.clear();
}

string MoveRule::getOldState() {
    return old_state;
}

string MoveRule::getNewState() {
    return new_state;
}

char MoveRule::getROfIdx(int idx) {
    return read[idx];
}

char MoveRule::getWOfIdx(int idx) {
    return write[idx];
}

char MoveRule::getLROfIdx(int idx) {
    return lrs[idx];
}
