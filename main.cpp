#include <iostream>
#include <string>
#include <vector>

#include "inputParser.h"
#include "executeCommand.h"

using namespace std;

int main(){
    string command;

    while (true){
        cout << "hetah> ";

        if(!getline(cin, command))
            break;

        vector<string> parsedInput = parser(command);

        if(parsedInput.empty())
            continue;

        cout << executeCommand(parsedInput) << endl;
    }

    return 0;
}
