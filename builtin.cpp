#include "builtin.h"

using namespace std;
using namespace std::filesystem;

namespace{
    unordered_map<string, BuiltinFunc> commands;
    path oldPath;
}

void initializeBuiltins(){
    commands["pwd"] = pwd;
    commands["echo"] = echo;
    commands["cd"] = cd;
    commands["exit"] = exits;
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

int echo(const vector<string> &args){
    string text;

    for (size_t i = 1; i < args.size(); i++){
        text += args[i];

        if (i < args.size() - 1){
            text += " ";
        }
    }

    cout << text << endl;
    return 0;
}

int pwd(const vector<string> &args){
    try{
        cout << filesystem::current_path().string() << "\n";
        return 0;
    }
    catch (const filesystem_error &e){
        cerr << "pwd: " << e.what() << "\n";
        return 1;
    }
}

int cd(const vector<string> &args){
    try{
        path currentDir = current_path();
        path targetDir;

        const char *home = getenv("HOME");

        if (args.size() == 1 || args[1] == "~"){
            if (!home){
                cerr << "cd: HOME not set\n";
                return 1;
            }

            targetDir = home;
        }
        else if (args[1] == "-"){
            if (oldPath.empty())
            {
                cerr << "cd: OLDPWD not set\n";
                return 1;
            }

            targetDir = oldPath;
            cout << targetDir.string() << "\n";
        }
        else if (args[1].rfind("~/", 0) == 0){
            if (!home)
            {
                cerr << "cd: HOME not set\n";
                return 1;
            }

            targetDir = path(home) / args[1].substr(2);
        }
        else{
            targetDir = args[1];
        }

        current_path(targetDir);
        oldPath = currentDir;

        return 0;
    }
    catch (const filesystem_error &e){
        cerr << "cd: " << e.what() << "\n";
        return 1;
    }
}

int exits(const vector<string> &args){
    std::exit(0);
}