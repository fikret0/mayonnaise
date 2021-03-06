#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <readline/readline.h>
// #include <replxx.hxx>
using namespace std;
// using namespace replxx;

#include "strh.hpp"
#include "runtime.hpp"
#include "file.hpp"
#include "versioncontrol.hpp"
#include "error.hpp"

#pragma region Interpreter Definitions
string mayoVer = getVer();
#pragma endregion

// Replxx inp;

std::string ver_string(int a, int b, int c) {
    std::ostringstream ss;
    ss << a << '.' << b << '.' << c;
    return ss.str();
}

[[noreturn]] void startInterpreter(){
    cout << "Mayonnaise " << mayoVer << " (Copyright 2021 - fikret0)" << endl;

    string true_cxx =
    #ifdef __clang__
        "Clang++";
    #else
        "G++";
    #endif

    string true_cxx_ver =
    #ifdef __clang__
        ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
    #else
        ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #endif
    
    cout << "[" << true_cxx << " " << true_cxx_ver << "]" << endl;

    string definpstr = ">> ";
    string mulinpstr = ".. ";
    string inpstr = definpstr;

    while (true){ // input loop (interpreter)
        // cout << inpstr;
        string userinp = readline(inpstr.c_str());
        //userinp = inp.input(inpstr);
        userinp = trim(userinp);

        if(!userinp.empty()){
            int code = executeExpression(userinp);
            if(code == 1000){
                inpstr = mulinpstr;
            }
            else{
                inpstr = definpstr;
                if(code != 0){
                    cerr << "Unrecognizable code block. Error code: " << code << endl;
                }
            }

            // inp.history_add(userinp);
        }
    }
}

void execFile(string file){
    vector<string> lines = ReadAllLines(file);
    for(int li = 1; li <= lines.size(); li++){
        string cline = trim(lines[li - 1]);
        if(!cline.empty()){
            int code = executeExpression(cline);
            handleError(code);
        }
    }
}

// !! ENTRY POINT !!
int main(int argc, char** argv){
    if(argc > 1){
        execFile(argv[1]);
    }
    else{
        startInterpreter();
    }

    return 0;
}