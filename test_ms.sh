#!/bin/sh
set -e

TEST_CMDS=$(cat << 'EOF'
echo hello
pwd
cd /
pwd
cd -
echo one | wc -l
echo one | cat | wc -l
echo hi > /tmp/ms_out
cat < /tmp/ms_out
echo more >> /tmp/ms_out
cat /tmp/ms_out
rm /tmp/ms_out
export TESTVAR=abc
env | grep TESTVAR
unset TESTVAR
env | grep TESTVAR
/bin/false || echo ok
/bin/true && echo ok2
( /bin/false || echo ok3 )
( echo a && echo b )
/bin/false
echo $?
echo "q $USER"
echo '$USER'
cat << EOF
line1
line2
EOF
exit
EOF
)

printf "%s\n" "$TEST_CMDS" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.readline.supp ./minishell