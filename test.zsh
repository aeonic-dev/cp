#!/bin/zsh
# Usage: ./test.zsh file|directory [-f] [out_extension]
# If -f is provided, break at the first failure
# out_extension is "ans" by default

COL_RESET="\033[0m"
COL_PASS="\033[1;32m"
COL_FAIL="\033[1;31m"
COL_CASE="\033[0;33m"

ext_out=${3:-"ans"}

case_header() {
    echo $1 | awk -F'/' "{printf \"Case $COL_CASE\" \$NF \".in$COL_RESET: \"}"
}

test_case() {
    _case=$1
    _hard_fail=$2

    # Print without directory
    _diff=$(
        ./main <$_case.in \
            | diff \
                --color=always \
                - $_case.$ext_out \
            | tail -n +2
    )

    if [ -z "$_diff" ]; then
        case_header $_case
        echo "${COL_PASS}pass$COL_RESET"
    else
        echo; case_header $_case
        echo "${COL_FAIL}fail$COL_RESET"
        echo "$_diff"; echo
        if [ $_hard_fail -eq 1 ]; then
            exit 1
        fi
    fi
}

# Compile
g++ -std=c++17 -g main.cpp -o main

# Check if $1 is a directory
maybe_dir=${1:-debug/data}
hard_fail=0
if [ $2 ]; then hard_fail=1; fi
if [ $maybe_dir = "-f" ]; then
    maybe_dir="debug/data"
    hard_fail=1
fi

if [ -d $maybe_dir ]; then
    # Do the thing many times
    for case in $(
        ls -rt $maybe_dir/* \
            | grep -E '.*\.in' \
            | sed 's/\.in//' \
            | sort -n
    ); do
        test_case $case $hard_fail
    done
else
    # Do the thing once
    test_case $maybe_dir $hard_fail
fi
