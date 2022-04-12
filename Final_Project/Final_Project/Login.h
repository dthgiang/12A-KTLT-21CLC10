#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "windows.h"
#include "Graphics.h"
#include "ConsoleGUI.h"
#include <stdio.h> 
#include <conio.h> 

using namespace std;

void LoginGUI(User &User);

void InsertUserName(string& Username);

void InsertPassword(string& Password);

int CheckStatusLogin(User& user);

void LoginLoop(User& User);