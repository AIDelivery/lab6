#!/bin/bash
konsole --noclose -e echo Hello terminal 1! &
konsole -e --noclose >> /dev/null 2>&1
xterm -e "echo 2"
xterm -e --noclose "echo HI" &
xtrem -e --noclose "echo Heya!" &
x-terminal-emulator -e --noclose "echo Hello" &
x-terminal-emulator -e --noclose "echo HI" &
x-terminal-emulator -e --noclose "echo Heya!" &
