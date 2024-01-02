#include "ConfigCtx.h"
#include "parser.h"
#include <string>
#include <algorithm>
#include <fstream>
#include"TmCtx.h"
#include"executor.h"
using namespace std;
int main(int argc, char* argv[]){
    if (argc < 2){
        printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>");
        return 0;
    }
    bool verbose = false;
    for(int i = 1; i < argc; i++){
        string st(argv[i]);
        if (st == "-h"){
            printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>");
            return 0;
        }
        if (st == "-v"){
            verbose = true;
        }
    }
    string file_name;
    string input;
    if(verbose){
        file_name = string(argv[2]);
        input = string(argv[3]);
    }else{
        file_name = string(argv[1]);
        input = string(argv[2]);
    }
    std::ifstream file(file_name);
    if (!file) {
        fprintf(stderr, "Can't open file");
        return -1;
    }
    std::string tm_prog;
    char ch;
    while(file.get(ch)) {
        tm_prog.push_back(ch);
    }
    ConfigCtx ctx;
    if (parse(tm_prog, ctx, verbose) != 0) return -1;
    TmCtx tmCtx(ctx.N);
    tmCtx.state = ctx.q0;
    if (!input.empty()) {
        //checkInput
        int chi = 0;
        for(auto& ch : input){
            if (ctx.S.find(ch) == ctx.S.end()){
                if (verbose){
                    fprintf(stderr, "Input:\t %s\n", input.c_str());
                    fprintf(stderr, "==================== ERR ====================\n");
                    fprintf(stderr, "error: Symbol \"%c\" in input is not defined in the set of input symbols\n", ch);
                    fprintf(stderr, "Input:\t %s\n", input.c_str());
                    fprintf(stderr, "     \t ");
                    for(int j = 0; j < chi; j++) fprintf(stderr, " ");
                    fprintf(stderr, "^\n");
                    fprintf(stderr, "==================== END ====================\n");
                }else{
                    fprintf(stderr, "illegal input string\n");
                }
                return -1;
            }
            chi += 1;
        }
        tmCtx.tapes[0].setTape(0, input.size() - 1, input);
    }
    if (verbose){
        printf("Input:\t %s\n", input.c_str());
        printf("====================RUN====================\n");
    }
    int accept = execute(ctx, tmCtx, verbose);
    if (verbose){
        if (accept) printf("ACCEPTED\n");
        else printf("UNACCEPTED\n");
        printf("Result: %s\n",  tmCtx.tapes[0].getFinalTape().c_str());
        printf("==================== END ====================\n");
    }else{
        if (accept) printf("(ACCEPTED)");
        else printf("(UNACCEPTED)");
        printf(" %s\n", tmCtx.tapes[0].getFinalTape().c_str());
    }
    return 0;
}