/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** project header
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #include "my_dico.h"
    #include "mysh_struct.h"
    #include <fcntl.h>
    #include <stdbool.h>
    #include <sys/types.h>

/**
** @brief print help for mysh
**
** @param exe argv[0]
**
** @return status code 0
**/
int print_help(const char exe[]);

/**
** @brief parse char *const env[] var to dict
**
** @param env environment variable
**
** @return dict corresponding to env
**/
dico_t *parse_env(char *const env[]);

/**
** @brief print a nice prompt message
**
** @param shell shell structure of the current shell
**
** @return 0
**/
int print_prompt(shell_t *shell);

/**
** @brief parse input to command
**
** @param string user input
** @param shell shell structure of the current shell
**
** @return 0
**/
int parse_commands(char *string, shell_t *shell);

/**
** @brief the core loop of the shell
**
** @param shell shell structure of the current shell
**
** @return status code of the last command executed
**/
int loop(shell_t *shell);

/**
** @brief entry point after main()
**
** @param env environment variable
**
** @return status code to return
**/
int entry_point(dico_t *env, bool is_file);

/**
** @brief split in list with delim but take quote escape
**
** @param str string to split
** @param delim delimiter for the spliter
**
** @return {
** NULL : str ot delim is NULL,
** NULL : malloc failed,
** list_t *: str has been split
** }
**/
list_t *my_strsplit(char *str, const char *delim);

/**
** @brief get file to input to the binary
**
** @param string string representing the command
** @param is_error ptr to int set to 1 if there is an error
**
** @return {
** NULL : if there is an error,
** "" : there is no file,
** "******" : the file to use
** }
**/
char *get_file_to_input(char *string, int *is_error, command_t *cm);

/**
** @brief get file in wich to redirect the output
**
** @param string string representing the command
** @param is_error set is_error to 1 if there is an error
**
** @return {
** NULL : if there is an error
** "" : there is no file
** "*******" : the file to use
** }
**/
char *get_redirect_to_file(char *string, int *is_error, command_t *cm);

/**
** @brief get binary path of the command
**
** @param string string representing the command
** @param shell shell structure
**
** @return {
** NULL : PATH is NULL,
** NULL : malloc failed,
** char *: path to the executable
** }
**/
char *get_binary_path(char *string, shell_t *shell);

/**
** @brief parse a 'single' command input
**
** @param string the command to execute
** @param shell shell
**
** @return {
** NULL : any error has occurred with the command,
** NULL : malloc failed,
** command_t *: the input has been parsed
** }
**/
command_t *parse_single_command(const char *string, shell_t *shell);

/**
** @brief parse single command with pipe
**
** @param input input command
** @param shell shell structure
**
** @return {
** NULL : input or shell is NULL,
** NULL : malloc failed,
** NULL : ambiquous parsing
** list_t *: commands has been parsed
** }
**/
list_t *parse_pipe(char *input, shell_t *shell);

/**
** @brief get array of arguments from input
**
** @param input input of the command
**
** @return {
** NULL : input is NULL,
** NULL : malloc failed,
** NULL : no arguments,
** char **: arguments has been parsed
** }
**/
char **get_arguments_array(char *input);

/**
** @brief free a command
**
** @param command command to free
**
** @return NULL
**/
void *free_command(command_t *command);

/**
** @brief destroy a shell structure
**
** @param shell shell to destroy
**/
void destroy_shell(shell_t *shell);

/**
** @brief get arr from dico env
**
** @param dico dico to trasnform
**
** @return {
** NULL : dico is NULL,
** NULL : malloc failed;
** char **: the env trasnformed
** }
**/
char **get_env_from_dico(dico_t *dico);

/**
** @brief execute single command
**
** @param shell shell structure
** @param string string representing command
**
** @return status of the command
**/
int execute_command(shell_t *shell, char *string);

/**
** @brief execute all commands in shell command list
**
** @param shell shell structure
**
** @return last exit status code of the command
**/
int execute_all(shell_t *shell);

/**
** @brief put message 'exe: str'
**
** @param exe exe that is error
** @param str message error
**
** @return number of byte writen
**/
int my_puterror(const char *exe, const char *str);

/**
** @brief check if string is builtins command
**
** @param string string to check
**
** @return false if not builtins; true otherwise
**/
bool check_if_builtins(const char *string);

/**
** @brief execute a builtins command
**
** @param shell shell structure
** @param command command builtins
**
** @return status code of shell->status_code
**/
int exec_builtins(shell_t *shell, command_t *command);

/**
** @brief execute a command as a genitor of the fork
**
** @param pid_child pid of the child created
** @param cm command that is been executed by the child process
** @param shell shell structure
**
** @return the status of the child process
**/
//int execute_command_genitor(pid_t pid_child, command_t *cm, shell_t *shell);

/**
** @brief execute a command as a child process
**
** @param cm command to execute
** @param shell shell structure
**/
int execute_command_child(command_t *cm, shell_t *shell, bool is_fork);

/**
** @brief remove quote in str (quote mark : '")
**
** @param str str to unquote
**
** @return the new str (old str is free)
**/
char *remove_quotes(char *str);

/**
** @brief split but with no call to remove quote
**
** @param str str to split
** @param delim delims to use
**
** @return list of malloced strings
**/
list_t *strsplit_not_rec(char *str, const char *delim);

/**
** @brief funnction for split str to add oonly if ok
**
** @param list list to add to
** @param to_add add this char
**
** @return NULL if there is an error; list otherwise
**/
list_t *split_str_add_to_list(list_t *list, char *to_add, int *is_first);

/**
** @brief setup redirection needed for the programm
**
** @param cm command to use
**
** @return {
** 0 : redirection has been setup
** -1 : error appears
** }
**/
int setup_redirection(command_t *cm);

/**
** @brief ends redirection of command
**
** @param cm command to ends
**
** @return {
** 0 : end of redirection has been done
** -1 : error appears
** }
**/
int ends_redirection(command_t *cm);

/**
** @brief execute a command that has been already parsed
**
** @param shell shell structure
** @param cms list of commands
**
** @return status code of the last command
**/
int execute_command_parsed(shell_t *shell, list_t *cms);

int kill_inferior_commands(shell_t *shell, int wstatus, list_t *cms,
    list_t *last);

/**
** @brief return list with no empty strings
**
** @param list list to copy and destroy
**
** @return {
** NULL : list is NULL,
** NULL : new list is empty,
** list *: new list with no empty strings
** }
**/
list_t *remove_empty_commands(list_t *list);

/**
** @brief check if there is null command in list
**
** @param pipes_str list of char *
** @param shell shell structure
**
** @return false if there are some invalid null command; true otherwise
**/
bool check_null_command(list_t *pipes_str, shell_t *shell);

/**
** @brief check if there is missing name in redirect
**
** @param pipes_str list of char *
** @param shell shell structure
**
** @return false if there are some missing name; true otherwise
**/
bool check_missing_name(list_t *pipes_str, shell_t *shell);

/**
** @brief correct env (if it is empty, add pwd and user)
**
** @param env environment already parsed char **env
**
** @return {
** NULL : could not add user and pwd
** dico_t *: env
** }
**/
dico_t *correct_env(dico_t *env);

/**
** @brief display prompt
**
** @param env environment already parsed char **env
** @param ps string to parse and display as prompt (usually env variable PS*)
**/
void display_prompt(dico_t *env, const char *ps);

void change_alias(list_t *cm, list_t *alias, int change, char **tmp);

char **remove_quotes_command(char **arr);

/**
** @brief return env value
**
** @param env environment already parsed char **env
** @param str command line
**
** @return modified str with $env changed by its value
**/
char *replace_value_env(dico_t *dico, char *str);

#endif
