//
//  main.cpp
//  Terminal
//
//  Created by Justin Chudley on 9/14/17.
//  Copyright © 2017 Justin Chudley. All rights reserved.
//

#include <iostream>
#include <string>
#include <unistd.h> //Allows for getcwd

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
    
    std::cout << ptr;
}

void exec_error()
{
    std::cout << "Error: command not found." << std::endl;
}

std::string get_command()
{
    std::string input;
    std::cout << ">";
    std::getline(std::cin, input);
    return input;
}

void read_cmd(std::string cmd)
{
    int SIZE = 4;
    std::string current_commands[SIZE];
    current_commands[0] = "help";
    current_commands[1] = "echo";
    current_commands[2] = "exit";
    current_commands[3] = "pwd";
    
    if(cmd == current_commands[0])
        exec_help(SIZE, current_commands);
    
    else if(cmd == current_commands[1])
        exec_echo();
    
    else if(cmd == current_commands[2])
        exec_exit();
    
    else if(cmd == current_commands[3])
        exec_pwd();
    
    else
        exec_error();
}

void terminal_loop(std::string cmd)
{
    cmd = get_command();
    read_cmd(cmd);
}
int main(int argc, const char * argv[]) {
    std::string command;

    while(GLOBAL_EXIT == 0)
        terminal_loop(command);
    
    return 0;
}
