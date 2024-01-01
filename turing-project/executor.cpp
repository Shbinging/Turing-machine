//
// Created by 水兵 on 2023/12/31.
//


#include "ConfigCtx.h"
#include "TmCtx.h"

bool matchRead(char need, char actual){
    if(need == '*' && actual != '_') return true;
    else return need == actual;
}

MoveRule* getMoveRule(ConfigCtx& configCtx, TmCtx& tmCtx){
        for(auto& moveCond: configCtx.delta){
            if (!(moveCond.getOldState() == tmCtx.state)) continue;
            bool check = true;
            for(int i = 0; i < configCtx.N; i++){
                if (!matchRead(moveCond.getROfIdx(i), tmCtx.tapes[i].Read())){
                    check = false;
                    break;
                }
            }
            if (check) return &moveCond;
        }
        return nullptr;
}

char getWrite(char r, char w, char st){
    if (w != '*') return w;
    if (r == '*') return st;
    assert(false);
}

void moveTm(TmCtx& tmCtx, MoveRule& moveCond){
    tmCtx.state = moveCond.getNewState();
    for(int i = 0; i < tmCtx.n; i++){
        tmCtx.tapes[i].Write(getWrite(moveCond.getROfIdx(i), moveCond.getWOfIdx(i), tmCtx.tapes[i].Read()));
        if (moveCond.getLROfIdx(i) == 'l') tmCtx.tapes[i].MoveLeft();
        if (moveCond.getLROfIdx(i) == 'r') tmCtx.tapes[i].MoveRight();
    }
}

void printTape(TMTape& tape, int tape_idx){
    vector<string> idx_list;
    auto r = tape.getRange();
    for(int i = r.first; i <= r.second; i++){
        idx_list.push_back(to_string(abs(i)));
    }
    int n = idx_list.size();
    vector<int> pos_idx;
    pos_idx.push_back(0);
    for(int i = 0; i < n; i++){
        pos_idx.push_back(pos_idx[i] + idx_list[i].size() + 1);
    }
    //Index0
    printf("Index%d\t:", tape_idx);
    for(int i = 0; i < n; i++){
        printf(" %s", idx_list[i].c_str());
    }
    printf("\n");
    //Tape0
    printf("Tape%d\t: ", tape_idx);
    auto iter = tape.getTapeIter();
    for(int i = 0; i < n; i++){
        char ch = *iter;
        printf("%c", ch);
        if (i < n){
            for(int j = pos_idx[i] + 1; j < pos_idx[i + 1]; j++) printf(" ");
        }
        iter++;
    }
    printf("\n");
    //Head0
    printf("Head%d\t: ", tape_idx);
    for(int i = 0; i < n; i++){
        if (tape.getCur() == i) printf("^");else printf(" ");
        if (i < n){
            for(int j = pos_idx[i] + 1; j < pos_idx[i + 1]; j++) printf(" ");
        }
    }
    printf("\n");
}
void printTm(TmCtx& tmCtx, int step, int accept){
    printf("Step\t: %d\n", step);
    printf("State\t: %s\n", tmCtx.state.c_str());
    string acc = accept ? "Yes" : "No";
    printf("Acc\t\t: %s\n", acc.c_str());
    for(int i = 0; i < tmCtx.n; i++){
        printTape(tmCtx.tapes[i], i);
    }
    printf("---------------------------------------------\n");
}

int execute(ConfigCtx& configCtx, TmCtx& tmCtx, bool verbose){
    int accept = 0;
    int step = 0;
    while(true){
        if (configCtx.F.find(tmCtx.state) != configCtx.F.end()){
            accept = 1;
        }
        if (verbose){
            printTm(tmCtx, step, accept);
        }
        auto mr_p = getMoveRule(configCtx, tmCtx);
        if (mr_p == nullptr) break;
        moveTm(tmCtx, *mr_p);
        step += 1;
    }
    return accept;
}