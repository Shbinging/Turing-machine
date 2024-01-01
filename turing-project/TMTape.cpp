//
// Created by 水兵 on 2023/12/31.
//

#include "TMTape.h"
#include <algorithm>
#include "string"

TMTape::TMTape() : baseOff(10000), tape(baseOff*2, '_') {
    //fixme tape should be auto expanded
    cur_idx = baseOff;
    left = baseOff;
    right = baseOff;
}

int TMTape::MoveRight() {
    cur_idx += 1;
    if (left == cur_idx - 1 && tape[left] == '_'){
        left += 1;
    }
    right = max(right, cur_idx);
    return cur_idx - baseOff - 1;
}

int TMTape::MoveLeft() {
    cur_idx -= 1;
    if (cur_idx + 1== right && tape[right] == '_'){
        right -= 1;
    }
    left = min(left, cur_idx);
    return cur_idx - baseOff + 1;
}

char TMTape::Read() {
    return tape[cur_idx];
}

char TMTape::Write(char ch) {
    char bk = tape[cur_idx];
    tape[cur_idx] = ch;
    return bk;
}

vector<char>::const_iterator TMTape::getTapeIter() {
    return tape.begin() + left;
}

auto TMTape::getRange() -> std::pair<int, int> {
    return {left - baseOff, right - baseOff};
}

void TMTape::setTape(int l, int r, string chars) {
    assert(chars.size() == r - l + 1);
    for(int i = l; i <= r; i++){
        tape[i + baseOff] = chars[i - l];
    }
    cur_idx = baseOff + l;
    left = baseOff + l;
    right = baseOff + r;
}

int TMTape::getCur() {
    return cur_idx - left;
}

string TMTape::getFinalTape() {
    int l = 0;
    int r = tape.size();
    for(int i = 0; i < tape.size(); i++) if (tape[i] != '_') {
        l = i;
        break;
    }
    for(int i = tape.size() -1; i >= 0; i--){
        if (tape[i] != '_'){
            r = i; break;
        }
    }
    string st;
    for(int i = l; i <= r; i++){
        st += tape[i];
    }
    return st;
}




