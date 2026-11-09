#include "builtin.h"

namespace{
    unordered_map<string, BuiltinFunc> commands;
}

void initializeBuiltins(){
    commands["pwd"] = pwd;
    commands["echo"] = echo;
    commands["cd"] = cd;
    commands["exits"] = exits;
    commands["clear"] = clear;
}

bool executeBuiltin(const vector<string> &args){
    if (args.empty())
        return false;

    auto it = commands.find(args[0]);

    if (it == commands.end()){
        return false;
    }

    it->second(args);

    return true;
}

int echo(const vector<string>& args){
    string text;
    for (int i = 1; i < args.size(); i++){
        text += args[i];
        if (i < args.size() - 1){
            text += " ";
        }
    }
}

int pwd(const vector<string> &args)
{
    try{
        cout << filesystem::current_path().string() << "\n";
        return 0;
    }
    catch (const filesystem::filesystem_error &e){
        cerr << "pwd: " << e.what() << "\n";
        return 1;
    }
}
int cd(const vector<string> &args){
    
}