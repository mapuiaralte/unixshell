#include <iostream>
#include <string>
#include <vector>

#include "inputParser.h"
#include "executeCommand.h"
#include "builtin.h"

using namespace std;

int main(){

    initializeBuiltins();

    string command;

    while (true){
        cout << "hetah> ";

        if (!getline(cin, command))
            break;

        vector<string> parsedInput = parser(command);

        if (parsedInput.empty())
            continue;

        executeCommand(parsedInput);
    }
    return 0;
}