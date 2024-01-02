//
// Created by 水兵 on 2023/12/31.
//

#ifndef TMP_TMTAPE_H
#define TMP_TMTAPE_H

#include<vector>
#include<string>
using namespace std;
class TMTape {
private:
    const int baseOff;
    vector<char> tape;
    int cur_idx;
    int left, right;
public:
    TMTape();
    int MoveRight();
    int MoveLeft();
    char Read();
    char Write(char ch);
    vector<char>::const_iterator getTapeIter();
    pair<int, int> getRange();
    void setTape(int l, int r, string chars);
    int getCur();
    string getFinalTape();
};


#endif //TMP_TMTAPE_H
