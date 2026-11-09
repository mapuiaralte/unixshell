#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include <functional>
#include<filesystem>

using namespace std;

using BuiltinFunc = function<int(const vector<string> &)>;

void initializeBuiltins();
bool executeBuiltin(const vector<string> &args);

int pwd(const vector<string> &args);
int echo(const vector<string> &args);
int cd(const vector<string> &args);
int exits(const vector<string> &args);
int clear(const vector<string> &args);