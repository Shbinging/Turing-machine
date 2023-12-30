#include <iostream>
#include "TmCtx.h"
#include "parser.h"

using namespace std;
int main(int argc, char* argv[]){

    std::string input;
    std::string line;

    // 从标准输入读取多行内容
    int i = 1;
    while (i <= 1 && std::getline(std::cin, line)) {
        input += line + "\n";
        i += 1;
    }

    TmCtx ctx;
    parse(input, ctx);
}