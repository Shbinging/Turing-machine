//
// Created by 水兵 on 2023/12/30.
//

#include "ConfigCtx.h"
#include <string>
#include <regex>
#include <utility>
#include "parser.h"
#include "MoveRule.h"
#include <cassert>
static string rm_by_regex(const string& input, const string& re){
    std::regex pattern(re);
    std::string output = std::regex_replace(input, pattern, "");
    return output;
}

 vector<string> split_by_regex(string input, const string& re){
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

string strip(const string& input){
    return rm_by_regex(input, R"(^\s+|\s+$)");
}

std::vector<std::string> findGroups(const std::string& str, const std::string & re_st) {
    std::regex re(re_st);
    std::vector<std::string> groups;
    std::smatch match;

    if(std::regex_search(str, match, re)){
        for(size_t i = 1; i < match.size(); ++i){
            groups.push_back(match[i]);
        }
    }

    return groups;
}

string vec_toString(const vector<string>& vec){
    string st = "[";
    if (!vec.empty()){
        st.append("\"");
        st.append(vec[0]);
        st.append("\"");
        for(int i = 1; i < vec.size(); i++){
            st.append(",\"");
            st.append(vec[i]);
            st.append("\"");
        }
    }
    st.append("]");
    return st;
}

int parse(string input, ConfigCtx& ctx, bool verbose){
    //remove notion, if one line is ";123\n", then it will be replaced to "\n"
    input = rm_by_regex(input, R"(;.*)");
    //split file into lines, and empty line will be removed
    vector<string> lines = split_by_regex(input, "\n");
    string re[] = {R"(#Q = \{(\w+(?:,\w+)*)\})",
            R"(#S = \{([^\s,;{}*_]{1}(?:,[^\s,;{}*_]{1})*)\})",
            R"(#G = \{([^\s,;{}*]{1}(?:,[^\s,;{}*]{1})*)\})",
            R"(#q0 = (\w+))",
            R"(#B = _)",
            R"(#F = \{(\w+)\})",
                R"(#N = (\d+))",
                R"((\w+) ([^\s,;{}]+) ([^\s,;{}]+) ([lr*]+) (\w+))"
    };
    int i = 0;
    for(auto &line: lines){
        line = strip(line);
        int idx = min(i, 7);
        if (!regex_match(line, regex(re[idx]))){
            fprintf(stderr, "syntax error\n");
            if (verbose){
                fprintf(stderr, "syntax error, line: %s", line.c_str());
            }
            return -1;
        }else{
            auto g = findGroups(line, re[idx]);
            switch (idx) {
                case 0: //Q
                    assert(g.size() == 1);
                    for(auto& state: split_by_regex(g[0],",")){
                        ctx.Q.insert(state);
                    }
                    break;
                case 1: //S
                    assert(g.size() == 1);
                    for(auto& st: split_by_regex(g[0],",")){
                        assert(st.size() == 1);
                        ctx.S.insert(st[0]);
                    }
                    break;
                case 2: //G
                    assert(g.size() == 1);
                    for(auto& st: split_by_regex(g[0],",")){
                        assert(st.size() == 1);
                        ctx.G.insert(st[0]);
                    }
                    break;
                case 3: //q0
                    assert(g.size() == 1);
                    ctx.q0 = g[0];
                    break;
                case 4:
                    break;
                case 5: //F
                    for(auto &state: g){
                        ctx.F.insert(state);
                    }
                    break;
                case 6: //N
                    assert(g.size() == 1);
                    ctx.N = stoi(g[0]);
                    break;
                case 7: //moveRule
                    assert(g.size() == 5);
                    MoveRule mvR;
                    mvR.old_state = g[0];
                    mvR.new_state = g[4];
                    mvR.read = g[1];
                    mvR.write = g[2];
                    mvR.lrs = g[3];
                    assert(g[1].size() == ctx.N);
                    assert(g[2].size() == ctx.N);
                    assert(g[3].size() == ctx.N);
                    ctx.delta.push_back(mvR);
            }
        }
        i += 1;
    }
    return 0;
}
