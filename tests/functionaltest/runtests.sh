#!/bin/bash

RED="\033[31m"
MAGENTA="\033[35m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
BLUE="\033[34m"
RESET="\033[0m"
YELLOW_BOLD="\033[1;33m"
BLEU_BOLD="\033[1;34m"
NB_SUCCESS=0
NB_FAILED=0
EXEC_BINARY="./$1"

clear

echo -e "${BLEU_BOLD}
  _______ _____  _    _  _____ _    _
 |__   __|  __ \| |  | |/ ____| |  | |
    | |  | |__) | |  | | (___ | |__| |
    | |  |  _  /| |  | |\___ \|  __  |
    | |  | | \ \| |__| |____) | |  | |
    |_|  |_|  \_|\____/|_____/|_|  |_|
${RESET}"


function test_this_command()
{
	echo -e "${YELLOW}------------------${RESET}"
	echo -e "${YELLOW}Testing:[$@]${RESET}"

	MYSH=$(echo -e "$@" | $EXEC_BINARY 2>&1)
	MYRETURNVALUE=$?
	TCSH=$(echo -e "$@" | tcsh 2>&1)
	TCSHRETURNVALUE=$?

	if [ "$MYSH" == "$TCSH" ] && [ "$MYRETURNVALUE" == "$TCSHRETURNVALUE" ]
		then
			NB_SUCCESS=$(($NB_SUCCESS+1))
			echo -e "${GREEN}OK${RESET}"
		else
			NB_FAILED=$((NB_FAILED+1))
			echo -e "${RED}KO${RESET}"
			echo -e "${MAGENTA} MYSH STDOUT = ${CYAN}$MYSH${RESET}"
			echo -e "${MAGENTA} 	MYSH RETURN VALUE = ${BLUE}$MYRETURNVALUE${RESET}"
			echo -e "${MAGENTA} TCSH STDOUT = ${CYAN}$TCSH${RESET}"
			echo -e "${MAGENTA}     TCSH RETURN VALUE = ${BLUE}$TCSHRETURNVALUE${RESET}"
			echo
		fi
	sleep 0.1
}

echo -e "${YELLOW_BOLD}ECHO TESTS${RESET}"

test_this_command 'echo test'
test_this_command 'echo test test test'
test_this_command 'echo     test   space        tab 		'
test_this_command 'echo 	 	 test 	 	with	 	space 	 and 	 tab  	'
test_this_command 'echo  	 	 test; echo with; echo 	 points; echo salut 	'
test_this_command 'echo 	 	 test; echo  	 		with 	 	 	;  		 	echo 	 points 	 	;  	 	 echo salut  		'
test_this_command 'echo test\n  echo 	other test 	  	 	\n 	 echo	 other 	 	 other 	 	 other 	 	 test 	 	 	\n 	 echo	 	with 	 	 backslashn 	 	 	 \n 	echo 	 test'
test_this_command './tests/functionaltest/test_args abc "def def"'

echo -e "${YELLOW_BOLD}REDIRECTIONS TESTS${RESET}"

test_this_command 'touch testfile; echo salut > testfile ; cat testfile; rm testfile'
test_this_command 'echo salut > testfile ; cat testfile; rm testfile'
test_this_command 'echo salut >> testfile; echo salut >> testfile ; cat testfile; rm testfile'
test_this_command 'echo cringe > test >> test >> test'
test_this_command 'echo ls > ls > ls > ls'
test_this_command '> file echo test salut; cat file; rm file'
test_this_command 'touch file2; rm file2'
test_this_command 'ls < echo coucou'
test_this_command 'cat < lse'
test_this_command 'rm file'
test_this_command 'echo coucou > file; cat file; rm file'
test_this_command 'ls > file; cat -e file; rm file'
test_this_command 'echo salut > §fichier; cat §fichier; rm §fichier'
test_this_command '> fichiertest ls -a; cat -e fichiertest; rm fichiertest'
test_this_command 'ls > file\n ls >> file\n cat -e file\n ls > file\n cat -e file; rm file'

echo -e "${YELLOW_BOLD}EXIT TESTS${RESET}"

test_this_command 'exit 0'
test_this_command 'exit 5'
test_this_command 'exit 535 242 242'
test_this_command 'exit 646636356356436344636436646436'
test_this_command 'exit letters'
test_this_command 'exit z'
test_this_command 'exit +2'
test_this_command 'exit 2\n echo salut'
test_this_command 'exit ++0'
test_this_command 'exit exit --0'
test_this_command 'exit exit ++2000000'
test_this_command 'exit _0'
test_this_command 'exit ++0'
test_this_command 'exit untrucfaux  	mdr'
test_this_command 'exit 0 1 2 3 4 5 6 7 8 9        '

echo -e "${YELLOW_BOLD}42SHtests${RESET}"

test_this_command 'exit 4 || echo salut'
test_this_command 'exit 4 && echo salut'
test_this_command 'exit 4 || echo salut && echo salut'
test_this_command 'ls *.txt || echo salut'
test_this_command 'echo $PATH'
test_this_command 'echo $PATH || echo salut'
test_this_command 'echo $PATH && echo salut'

echo -e "${YELLOW_BOLD}SYNTAX ERROR TESTS${RESET}"

test_this_command '> test'
test_this_command ';;;;;;'
test_this_command ' 	 	;;; 	 	ls 	 	;;; 	 	e'
test_this_command ' 	 	;; 	 	;; 	 	;;'
test_this_command ' 	 >>;; 	w	;; 	<	;;'
test_this_command '< ls'
test_this_command 'ls > <'
test_this_command 'ls | |'
test_this_command 'cd | |'
test_this_command 'cd |  fzfz zf|' 2> /dev/null
test_this_command 'cd eaze' 2> /dev/null
test_this_command 'ls |'
test_this_command 'ls | ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls | '
test_this_command '<'
test_this_command '<<'
test_this_command '>'
test_this_command '>>'
test_this_command ';; echo test'
test_this_command '| test'
test_this_command '| test |'

echo -e "${YELLOW_BOLD}OTHER TESTS${RESET}"

test_this_command 'touch test; cd test; rm test' 2> /dev/null
test_this_command 'ls -lah | noexistcommand'
test_this_command 'ls -TEST'
test_this_command 'cd EGIJJEGI' 2> /dev/null
test_this_command 'cd EGIJJEGI; cd EGIJJEGI' 2> /dev/null
test_this_command 'PWD; cd -; env | grep PATH' 2> /dev/null
test_this_command 'echo yo'
test_this_command 'echo des    bons    espaces   et  		   des  			  tabulations 	 	'
test_this_command 'touch _ ; _ ; rm _'
test_this_command 'touch a b c d; mkdir m1 m2 m3; ls -l | cat -e ; rm a b c d ; rmdir m1 m2 m3'
test_this_command './tests/functionaltest/segcd' 2> /dev/null
test_this_command './tests/functionaltest/hello'
test_this_command './tests/functionaltest/divzerocd' 2> /dev/null
test_this_command '/bin/ls'
test_this_command 'ls -l < test.c < ./a.out'
test_this_command 'ls -l > test >> ./a.out'
test_this_command 'ls -ijgejg'
test_this_command 'cd -' 2> /dev/null

echo -e "${YELLOW_BOLD}CD TESTS${RESET}"

test_this_command 'cd /usr ; pwd'
test_this_command 'cd /bin/ls'
test_this_command 'cd /bin/ls ; pwd'
test_this_command 'cd /usr ; ls -lah'
test_this_command 'cd / ; pwd'
test_this_command 'cd fail' 2> /dev/null
test_this_command 'cd /usr ; ls -lah | cat -e'
test_this_command 'cd /usr/bin; env | grep PATH'
test_this_command 'cd .. ; pwd'
test_this_command 'cd ~'
test_this_command 'cd ~; cd -' 2> /dev/null
test_this_command 'cd ~'
test_this_command 'cd toto tata' 2> /dev/null
test_this_command 'cd -' 2> /dev/null
test_this_command 'cd ../'
test_this_command 'cd filequiexistepas' 2> /dev/null
test_this_command 'mkdir test_folder ; cd test_folder ; cd ../ ; rmdir test_folder'
test_this_command 'pwd\nls -l\ncd\nls -l'

echo -e "${YELLOW_BOLD}ENV TESTS${RESET}"

test_this_command 'setenv test testeee'
test_this_command 'setenv 8toto tata'
test_this_command 'setenv toto tata titi tutu tjtj tztzt'
test_this_command 'setenv <toto= tata'
test_this_command 'setenv test7 tata'
test_this_command 'setenv utut9876543'
test_this_command 'setenv testsimple'
test_this_command 'setenv Test Test'
test_this_command 'setenv salut tutu\n setenv tata toto\n unsetenv salut'
test_this_command 'setenv | grep HOSTNAME'
test_this_command 'unsetenv caexistepas'

echo -e "${YELLOW_BOLD}PIPES TESTS${RESET}"
test_this_command 'ls | cat -e'
test_this_command 'ls | cat -e | cat -e'
test_this_command 'pwd\nls -l\ncd\nls -l'
test_this_command 'ls | echo test'
test_this_command '| ls'
test_this_command 'ls |'
test_this_command 'pwd; ls | cat -e | wc -c'
test_this_command 'cd\nls | cat -e | wc -c\necho test'

rm $EXEC_BINARY

echo -e "\n${GREEN}You pass $NB_SUCCESS tests${RESET}"
echo -e "\n${RED}You fail $NB_FAILED tests${RESET}"
