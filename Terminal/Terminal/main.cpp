//
//  main.cpp
//  Terminal
//
//  Created by Justin Chudley on 9/14/17.
//  Copyright © 2017 Justin Chudley. All rights reserved.
//Replication of a shell but with limited commands.

#include <iostream>
#include <string>
#include <unistd.h> //Allows for getcwd
#include <cstring> //Allows for strtok

bool GLOBAL_EXIT = 0; //Using this in order to have exec_exit properly close program by ending the while loop in main

void exec_help(int arr_size, std::string curr_cmds[])
{
    std::cout << "The current commands available in this shell are: " << std::endl;
    for(int i = 0; i < arr_size; i++)
    {
        std::cout << curr_cmds[i] << std::endl;
    }
}

void exec_echo()
{
    std::string echo_input;
    std::cout << "Enter echo statement." << std::endl << ">";
    std::cin.ignore(1000, '\n'); //Clears the buffer of leftover inputs so getline will read the echo.
    std::getline (std::cin, echo_input);
    std::cout << ">" << echo_input << std::endl;
}

void exec_exit()
{
    std::cout << "Terminating shell." << std::endl;
    GLOBAL_EXIT = 1;
}

void exec_pwd()
{
    long size;
    char *buf; //buffer holder
    char *ptr; //where the current directory will be saved to
    
    
    size = pathconf(".", _PC_PATH_MAX); //Gets size of path and saves it to size var.
    
    
    if ((buf = (char *)malloc((size_t)size)) != NULL) //Set buff = size of char * allocated size, if not null then get wd
        ptr = getcwd(buf, (size_t)size);
    
    std::cout << ptr << std::endl;
}

void exec_cd()
{
    int BUFFER_SIZE = 1024;
    char *directory;
    directory = new char [BUFFER_SIZE]; //Allocated memory in order to cin to the pointer char
    std::cout << "Enter target directory: " << std::endl << ">";
    std::cin >> directory;
    chdir(directory);
    delete [] directory;
}

void exec_error()
{
    std::cout << "Error: command not found." << std::endl;
}

std::string get_command()
{
    std::string input_str;
    char input[] = "";
    std::cout << ">";
    std::cin >> input;
    return std::string(input);
}

void read_cmd(std::string cmd)
{
    int ARR_SIZE = 5; //Manually update this as commands are added, used for passing to the help func
    std::string current_commands[] = {"help","echo","exit","pwd","cd"};
    
    if(cmd == current_commands[0])
        exec_help(ARR_SIZE, current_commands);
    
    else if(cmd == current_commands[1])
        exec_echo();
    
    else if(cmd == current_commands[2])
        exec_exit();
    
    else if(cmd == current_commands[3])
        exec_pwd();
    
    else if(cmd == current_commands[4])
        exec_cd();
    
    else
        exec_error();
}

void terminal_loop()
{
    std::string cmd;
    cmd = get_command();
    read_cmd(cmd);
}
int main(int argc, const char * argv[]) {
    std::string command;
    
    while(GLOBAL_EXIT == 0)
        terminal_loop();
    
    return 0;
}
