#!/bin/bash


function start
{
    cd /home/wy/code/rep_spell_correct/bin/
    ./spellCorrect
}

function stop
{
    cd /home/wy/code/rep_spell_correct/bin/
    killall -9 spellCorrect
}

function restart
{
    cd /home/wy/code/rep_spell_correct/bin/
    killall -9 spellCorrect
    ./spellCorrect
}

function stat
{
   ps -ef | grep spellCorrect
}

case $1 in
     start) start;;
     stop) stop;;
     restart) restart;;
     stat) stat;;
     *)  echo "input error";;
esac
