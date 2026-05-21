#! /bin/bash

# NOTE: Remember to run this shell script with the command:
# "./testing_script.sh > <output_filename> 2>&1"
# The push_swap program writes error messages to the stderr (fd 2). In order to
# be able to display them in the output file, you have to redirect stderr into
# stdout. "2>&1" does the trick!

# executable variable
PROGRAM="./bin/push_swap"

# variable for 'shuf' command, which on Mac is replaced by 'gshuf'
SHUF=$(command -v shuf || command -v gshuf)
if [ -z "$SHUF" ]; then
	echo "Error: missing required command 'shuf'."
	echo "MacOS: brew install coreutils (provides 'gshuf' substitution)"
	echo "Linux: install coreutils package"
	exit 1
fi

log_title() {
	printf "\n\n\n================ %s ================\n\n\n\n" "$1"
}

log_test() {
	printf "\n\n\n=== RUNNING TEST: %s ===\n\n" "$1"
}

# Since the script is mostly running in subshells, to ensure that the tests
# are printed to the console, but without "set -x" / "set +x" or other irrelevant
# commands being printed - trying to abort the script with Ctrl + c does not
# work. Therefore, a bash signal handler ('trap' command) is used for SIGINT.
trap "echo -e '\n[!] Testing aborted by user.'; exit 1" INT



# TESTING: VALID cases:
log_title "VALID CASES"

# TESTING: Cases that are already sorted. These should not print anything on
# the screen! Even if the moves you output end up sorting the array again
# anyways... It would not make sense
log_test "Already sorted!"
( set -x; $PROGRAM $(seq -s " " -42 42) | wc -l )

log_test "Already sorted!"
( set -x; $PROGRAM $(seq -s " " 0 10) | wc -l )

log_test "Already sorted!"
( set -x; $PROGRAM $(seq -s " " -320 179) | wc -l )


# TESTING: Case with zero arguments: should not do anything and return the
# prompt to the user
log_test "Zero arguments: nothing to do"
( set -x; $PROGRAM | wc -l )


# TESTING: Other cases that should not do anything and return the prompt to
# the user, without claiming there is an error, because there is only 1 integer

log_test "Already sorted: single integer version"
( set -x; $PROGRAM "100" | wc -l )

log_test "Already sorted: single integer version"
( set -x; $PROGRAM 14213 | wc -l )

log_test "Already sorted: single integer version"
( set -x; $PROGRAM "			-213" | wc -l )



# TESTING: random 2 integer stacks (important edge case to check!)

log_test "2 values (INT_MAX & INT_MIN)"
( set -x; $PROGRAM 2147483647 -2147483648 | wc -l )

log_test "2 values"
( set -x; $PROGRAM 3 -432 | wc -l )

log_test "2 values: already sorted"
( set -x; $PROGRAM 1 42 | wc -l )

log_test "2 values: already sorted"
( set -x; $PROGRAM 42 888 | wc -l )


# TESTING: random 4 integer stacks (there could be issues with all kinds of
# rather small stacks, because of how the chunks are splitted, and so this
# testing script incudes a number of those, to avoid bad surprises)
# NOTE: On certain environments, 'shuf' can output big numbers in scientific
# notation. These would be refused by push_swap, unfortunately...
# The 'awk' command, paired with its 'seen' feature which can check for duplicate
# values and trim away the repeated ones, allows this command to ensure valid input.

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 4 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 \
		| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )


# TESTING: random 6 integer stacks
log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 6 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )


# TESTING: random 7 integer stacks
log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 7 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )


# TESTING: random 8 integer stack
#
log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 8 values"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )


log_title "BENCHMARK TESTING"
# TESTING: push_swap benchmark stacks

# TESTING: random 3 integer stacks

log_test "3 values"
( set -x; $PROGRAM 2147483647 -2147483648 -2147483645 | wc -l )

log_test "3 values"
( set -x; $PROGRAM -2147483648 -2147483645 2147483647 | wc -l )

log_test "Random 3 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 3 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 3 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )



# TESTING: random 5 integer stacks

log_test "5 values (maximal values)"
( set -x; $PROGRAM 2147483647 -2147483630 2147483643 -2147483648 -2147483645 | wc -l )

log_test "5 values (maximal values)"
( set -x; $PROGRAM -2147483630 2147483643 -2147483648 2147483647 -2147483645 | wc -l )

log_test "Random 5 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 5 values: small range"
( set -x; $PROGRAM $(seq -8 +3 | $SHUF -n 5 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )



# TESTING: random 100 integer stacks

log_test "Random 100 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: small range"
( set -x; $PROGRAM $(seq -450 +3 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: small range"
( set -x; $PROGRAM $(seq -450 +3 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: small range"
( set -x; $PROGRAM $(seq -450 +3 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: small range"
( set -x; $PROGRAM $(seq -450 +3 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 100 values: small range"
( set -x; $PROGRAM $(seq -450 +3 | $SHUF -n 100 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )



# TESTING: random 500 integer stacks

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values: massive range"
( set -x; $PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )

log_test "Random 500 values"
( set -x; $PROGRAM $(seq -200 800 | $SHUF -n 500 \
	| awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l )
