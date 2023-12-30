//
// Created by 水兵 on 2023/12/30.
//

#include "TmCtx.h"
#include <string>
#include <regex>
#include <stdio.h>
#include "parser.h"
static string rm_by_regex(string input, string re){
    std::regex pattern(re, std::regex::multiline);
    std::string output = std::regex_replace(input, pattern, "");
    return output;
}

static vector<string> split_by_regex(string input, string re){
    std::regex pattern(re);
    std::vector<std::string> result;

    std::sregex_token_iterator iter(input.begin(), input.end(), pattern, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        if (*iter != "") {
            result.push_back(*iter);
        }
        ++iter;
    }
    return result;
}

int parse(string input, TmCtx& ctx){
    //remove notion, if one line is ";123\n", then it will be replaced to "\n"
    input = rm_by_regex(input, ";.*$");
    //split file into lines, and empty line will be removed
    vector<string> lines = split_by_regex(input, "\n");
    string re = R"(#Q = \{[a-zA-Z0-9_]+(,[a-zA-Z0-9_]+)*\})";
    for(auto &line: lines){
        if (regex_match(line, regex(re))){
            printf("%s\n", line.c_str());
        }
    }
}
