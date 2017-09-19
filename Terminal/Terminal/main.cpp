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
#include <sstream> //Used for splitting strings

bool GLOBAL_EXIT = 0; //Using this in order to have exec_exit properly close program by ending the while loop in main

void exec_help(int arr_size, std::string curr_cmds[])
{
    std::cout << "The current commands available in this shell are: " << std::endl;
    for(int i = 0; i < arr_size; i++)
    {
        std::cout << curr_cmds[i] << std::endl;
    }
}

void exec_echo(std::string echo_input)
{
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

void exec_cd(std::string destination)
{
    chdir(destination.c_str());
}

void exec_error()
{
    std::cout << "Error: command not found." << std::endl;
}

void exec_ls()
{
    
}

std::string get_command()
{
    std::string input;
    std::cout << ">";
    std::getline(std::cin, input);
    return input;
}

std::string trim(std::string str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::string splitString(std::string str)
{
    std::string split;
    std::istringstream iss{str};
    iss >> split;
    
    std::ostringstream oss;
    oss << iss.rdbuf();
    split = oss.str();
    return split;
}

std::string get_first(std::string str)
{
    std::string first_word = str.substr(0, str.find(" "));
    return first_word;
}

void read_cmd(std::string cmd)
{
    std::string first_cmd = get_first(cmd); //This way the actual command is seperate from extra words (e.g. echo "this")
    std::string after_first = splitString(cmd); //Used to split the string into the first word and the rest
    after_first = trim(after_first);
    int NUM_COMMANDS = 6; //Manually update this as commands are added, used for passing to the help func
    std::string current_commands[] = {"help","echo","exit","pwd","cd", "ls"};
    
    if(first_cmd == current_commands[0])
        exec_help(NUM_COMMANDS, current_commands);
    
    else if(first_cmd == current_commands[1])
        exec_echo(after_first);
    
    else if(first_cmd == current_commands[2])
        exec_exit();
    
    else if(first_cmd == current_commands[3])
        exec_pwd();
    
    else if(first_cmd == current_commands[4])
        exec_cd(after_first);
    
    else if(first_cmd == current_commands[5])
        exec_ls();
    
    else
        exec_error();
}

void terminal_loop()
{
    std::string cmd = get_command();
    read_cmd(cmd);
}
int main(int argc, const char * argv[]) {
    std::string command;
    
    while(GLOBAL_EXIT == 0)
        terminal_loop();
    
    return 0;
}
