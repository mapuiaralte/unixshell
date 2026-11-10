#include "executeCommand.h"
#include "builtin.h"

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

void executeCommand(const vector<string> &input){
    if (input.empty())
        return;
    if (executeBuiltin(input)){
        return;
    }
    // External command execution
    pid_t pid = fork();

    if (pid == 0){
        // Convert vector<string> into char* arguments for execvp()
        vector<char *> args;

        for (const string &arg : input){
            args.push_back(const_cast<char *>(arg.c_str()));
        }

        // execvp expects a NULL-terminated argument array
        args.push_back(nullptr);

        execvp(args[0], args.data());

        perror("execvp failed");
        _exit(EXIT_FAILURE);
    }

    else if (pid > 0){
        int status;

        if (waitpid(pid, &status, 0) == -1){
            perror("waitpid failed");
        }
    }
    else{
        perror("fork failed");
    }
}