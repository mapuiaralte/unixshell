#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>

using namespace std;
using namespace std::filesystem;

string get_current_directory(){
    try{
        return current_path().string();
    }
    catch(const filesystem_error &e){
        return "Error retrieving directory: " + string(e.what());
    }
}

int main(int argc, char *argv[]){
    if (argc < 2){
        cerr << "No command provided. Error.";
        return 1;
    }
    string command = argv[1];
    if (command == "echo"){
        string text;
        for (int i = 2; i < argc; i++){
            text += argv[i];
            if (i < argc - 1){
                text += " ";
            }
        }
        cout << text << "\n";
    }
    else if (command == "pwd"){
        string currentDir = get_current_directory();
        cout << currentDir << "\n";
    }
    else if (command == "touch"){
        fstream fout;
        for(int i=2;i<argc;i++){
            fout.open(argv[i], ios::app);
            if(!fout.is_open()){
                return 1;
            }
            fout.close();
        }
    }
    else if (command == "rm"){
        for(int i=2;i<argc;i++){
            if(remove(argv[i]) != 0){
                return 1;
            }
        }
    }
    else if (command == "clear"){
        //ASCII ESCAPE SEQUENCES ATM
        cout << "\033[2J\033[H" << flush;
    }
}
