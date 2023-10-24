#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color

if [[ $1 != 'd' ]]; then
    echo -e "${GREEN}Done. Run SmartCalc? y/n${NC}"

    read run

    if [[ $run == 'y' ]]
    then
        echo -e "${GREEN}Running...${NC}"
        ./SmartCalc
    fi
fi

