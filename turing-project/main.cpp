#include <iostream>
#include "TmCtx.h"
#include "parser.h"

using namespace std;
int main(int argc, char* argv[]){

    std::string input;
    std::string line;

    // 从标准输入读取多行内容
    int n;
    cin >> n;
    int i = 1;
    while (i <= n && std::getline(std::cin, line)) {
        input += line + "\n";
        i += 1;
    }

    TmCtx ctx;
    parse(input, ctx, true);
}