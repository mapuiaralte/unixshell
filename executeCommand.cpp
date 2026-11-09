#include "executeCommand.h"
#include "builtin.h"
#include<iostream>
#include<unistd.h>
#include <cstdlib>
#include <sys/wait.h>

void executeCommand(vector<string> input){
    if(input.empty()) return "";

    if(executeBuiltin(input)){
        return;
    }
    else{
        pid_t pid = fork();
        if(pid == 0){
            char *args[input.size() + 1]; //NULL POINTER
            for(size_t i=0; i<input.size();i++){
                args[i] = const_cast<char *>(input[i].c_str());
            }
            args[input.size()] = NULL;

            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        }
        else if(pid > 0){
            int status;
            waitpid(pid, &status, 0);
        }
        else{
            perror("fork failed");
        }
    }
    return "";
}
