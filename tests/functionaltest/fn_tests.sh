#!/bin/bash

NB_TESTS=0
NB_FAILED=0

echo "ls" | tcsh &> /dev/null
if [[ "$?" != 0 ]];
then
    echo ">> you have not tcsh, exit"
    exit 1
fi

echo 'echo "ls" | '"$1"
resul=$(echo "ls" | tcsh)
tests=$(echo "ls" | $1)
NB_TESTS=$(($NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> you provide:"
    echo "$tests"
    echo ">> but true result:"
    echo "$resul"
fi

echo 'echo "cd .. ; ls" | '"$1"
resul=$(echo "cd .. ; ls" | tcsh)
tests=$(echo "cd .. ; ls" | $1)
NB_TESTS=$(($NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> you provide:"
    echo "$tests"
    echo ">> but true result:"
    echo "$resul"
fi

echo 'echo "cd .. ; cd - ; ls" | '"$1"
resul=$(echo "cd .. ; cd - ; ls" | tcsh)
tests=$(echo "cd .. ; cd - ; ls" | $1)
NB_TESTS=$(($NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> you provide:"
    echo "$tests"
    echo ">> but true result:"
    echo "$resul"
fi

echo 'echo "ls;ls" | '"$1"
resul=$(echo "ls;ls" | tcsh)
tests=$(echo "ls;ls" | $1)
NB_TESTS=$(($NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> you provide:"
    echo "$tests"
    echo ">> but true result:"
    echo "$resul"
fi

# echo 'echo "env | grep USER" | '"$1"
# resul=$(echo "env | grep USER" | tcsh)
# tests=$(echo "env | grep USER" | $1)
# NB_TESTS=$(($NB_TESTS+1))
# if [[ "$resul" != "$tests" ]];
# then
#     NB_FAILED=$((NB_FAILED+1))
#     echo ">> you provide:"
#     echo "$tests"
#     echo ">> but true result:"
#     echo "$resul"
# fi

echo 'echo "cat /dev/urandom | head -c 1000" | '"$1"
echo "cat /dev/urandom | head -c 1000" | timeout 10s $1 > /dev/null
error="$?"
NB_TESTS=$(($NB_TESTS+1))
if [[ "$error" != "0" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> maybe it is a timeout"
fi

echo 'echo "cat /dev/urandom | head -c 1000 | wc -l" | '"$1"
echo "cat /dev/urandom | head -c 1000 | wc -l" | timeout 10s $1 > /dev/null
error="$?"
NB_TESTS=$(($NB_TESTS+1))
if [[ "$error" != "0" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo ">> maybe it is a timeout"
fi

echo 'echo "       ls" | '"$1"
resul=$(echo "       ls" | tcsh)
tests=$(echo "       ls" | $1)
NB_TESTS=$((NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo "you provide:"
    echo "$tests"
    echo "but true result:"
    echo "$resul"
fi

echo 'echo "       ls      " | '"$1"
resul=$(echo "       ls      " | tcsh)
tests=$(echo "       ls      " | $1)
NB_TESTS=$((NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo "you provide:"
    echo "$tests"
    echo "but true result:"
    echo "$resul"
fi

echo 'echo "ls > testfileturfu; ls; cat testfileturfu ;rm testfileturfu ;ls" | '"$1"
resul=$(echo "ls > testfileturfu; ls; cat testfileturfu ;rm testfileturfu ;ls" | tcsh)
tests=$(echo "ls > testfileturfu; ls; cat testfileturfu ;rm testfileturfu ;ls" | $1)
NB_TESTS=$((NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo "you provide:"
    echo "$tests"
    echo "but true result:"
    echo "$resul"
fi

#echo 'echo "cd ..; env | grep OLDPWD" | '"$1"
#resul=$(echo "cd ..; env | grep OLDPWD" | tcsh)
#tests=$(echo "cd ..; env | grep OLDPWD" | $1)
#NB_TESTS=$((NB_TESTS+1))
#if [[ "$resul" != "$tests" ]];
#then
#    NB_FAILED=$((NB_FAILED+1))
#    echo "you provide:"
#    echo "$tests"
#    echo "but true result:"
#    echo "$resul"
#fi

echo 'echo "cat < Makefile | cat | cat | grep mysh" | '"$1"
resul=$(echo "cat < Makefile | cat | cat | grep mysh" | tcsh)
tests=$(echo "cat < Makefile | cat | cat | grep mysh" | $1)
NB_TESTS=$((NB_TESTS+1))
if [[ "$resul" != "$tests" ]];
then
    NB_FAILED=$((NB_FAILED+1))
    echo "you provide:"
    echo "$tests"
    echo "but true result:"
    echo "$resul"
fi

echo "nb tests : $NB_TESTS"
echo "nb failed : $NB_FAILED"

if [[ "$NB_FAILED" != "0" ]];
then
    exit 1
fi
exit 0
