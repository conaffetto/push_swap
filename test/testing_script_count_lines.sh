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

# NOTE: this command allows for displaying each commmand before its execution
set -x


# TESTING: INVALID cases that should output an error:

# TESTING: cases with one single argument, which is a valid *number* per se,
# but which should still output an error since it is an integer overflow
$PROGRAM "2147483648"

$PROGRAM -2147483650

# TESTING: Cases containing at least one argument string which has no number
# within it at all - either an empty string or only whitespace. These should
# be treated as an error, since the input is there, but it cannot be considered
# as valid!
$PROGRAM "" ""

$PROGRAM "" "" ""

$PROGRAM "" 5 "" 1 "" 0

$PROGRAM "" "42 999 -51"

$PROGRAM "               " "                   "

$PROGRAM 32 10 "			             " 3


# TESTING: An empty string, but other arguments ARE valid!
$PROGRAM 3 9 8 -4 -20 -551 900 "" 42 -42

$PROGRAM "" "15" "30" "-4242" "0" "-9" "-2" "-7"


# TESTING: DUPLICATES: (careful with memory leaks!)
$PROGRAM 42 42

$PROGRAM 1 5 8 90 1

$PROGRAM 7 -4 -901 -7890 -4

# integer -18015 is duplicated
$PROGRAM -18593 -10054 -7342 -5363 4202 -17062 2228 -11345 \
	-14894 -18309 1074 5832 5591 -16512 -10477 -8500 -2139 4235 -17831 -16291 \
	-14128 5319 -8694 -12674 1777 -12884 -6294 -13287 -5020 -16507 -10809 \
	-17082 -242 -15976 4356 837 -752 -3020 -14661 -13378 -6433 -1011 -13128 \
	-12166 4531 -16071 -9917 -11909 -16886 -9583 -1535 -12390 -5988 -1304 \
	-7699 -10539 -3094 -14433 -15710 -6877 5949 -9810 -2989 -3479 -491 -15875 \
	-13161 -1795 -1530 -17649 1812 1070 -16566 -10479 -14521 -6711 -14461 \
	-18670 4245 -7153 -18108 -17625 643 -4262 -4152 -81 -14899 1864 -7045 \
	-7520 -18015 -16843 1331 -8482 5963 -6604 -14411 -12683 1019 -2351 -10878 \
	-15285 -12679 -4850 -4310 -984 -167 1133 -2534 -16459 -15402 3263 -777 \
	-10628 -17699 -17051 -13101 1551 -13748 5972 -15497 -7082 -15492 1317 \
	-10436 -14724 2326 -13120 -9034 2799 -17133 -18920 -15977 -3951 2052 3390 \
	-6018 -18874 5561 -7405 -18609 -12780 -3224 -4465 -3675 -14144 -15259 \
	-10900 3837 -8641 -1323 -11673 -18015 3 42 999999 10000

# integer 9 is duplicated, even though duplication is prefixed with zeroes
$PROGRAM 1 0 9 4 5 000009 3 -4

# 333 has a duplicate, but one of the iterations is prefixed with a '+' sign
$PROGRAM 0 -42 -8945 333 7 120 +333 444  +21 1

# integer 42 is duplicated, duplication prefixed by zeroes (strings version)
$PROGRAM "42" "00042" "15"

# integer 42 is duplicated once more, this time the duplication occurs in a
# string with multiple arguments, but the first appearence is not within the
# same set of double-quotes
$PROGRAM "42" "900" "15" "13 098 42"

# integer 908903 is repeated, but within one set of double quotes
$PROGRAM "1 3 5 123 908903 12123 1111 2222 -1111 -2222 \
-113 0 444 908903 -44 -66 -99 -100 -12223 +9874"

# Invalid duplicate cases, with the duplicate being part of the quick sort
# pivot selection process
$PROGRAM 5 2 241 -341 5

$PROGRAM 5 2 5 -341 9

$PROGRAM 9 2 5 -341 5

# cases that have struggled with my initial write of double pivot quick sort,
# because of their duplicates
$PROGRAM 8 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 234 -214321 333 999 \
	91123 34 -21455 -21344324 55 89 1234 0987 65432 -54321 2

$PROGRAM 8 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 234 -214321 333 999 \
	91123 34 -21455 -21344324 55 89 1234 0987 65432 -54321 8

$PROGRAM 8 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 234 -214321 333 999 \
	91123 34 -21455 -21344324 55 89 1234 0987 65432 -54321 234

$PROGRAM 234 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 234 -214321 333 999 \
	91123 34 -21455 -21344324 55 89 1234 0987 65432 -54321 8 234

$PROGRAM 8 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 2 -214321 333 999 91123 \
	34 -21455 -21344324 55 89 1234 0987 65432 -54321 234

$PROGRAM 8 2 7 6 1 9 4 5 2424 -234 -12 -1444 -90 -3 8 -214321 333 999 91123 \
	34 -21455 -21344324 55 89 1234 0987 65432 -54321 234

# TESTING: Cases where letters or other invalid characters are involved
$PROGRAM "42abc" 19 32

$PROGRAM 42abc 19 32 798

$PROGRAM "19 32 798 12412423F"

$PROGRAM "what's up"

$PROGRAM "5 15 0 -98 -1234 90\$2"

# TESTING: Cases where '+' or '-' are not followed by integers in a valid way
$PROGRAM "+"

$PROGRAM "513 789 +"

$PROGRAM "4409+123"

$PROGRAM 4409+123

$PROGRAM 21-123 3 7 8 0

$PROGRAM "21-123 3 7 8 0"

$PROGRAM "42 -42 -"

$PROGRAM "-"

$PROGRAM "	  -    "

$PROGRAM "++32"

$PROGRAM --4242

$PROGRAM "++  555"


# TESTING: Cases where at least one number is outside the range of int:
# These cases are important to be checked, especially for memory leaks, because
# even though this input is invalid and should display "Error\n" on stderr,
# this push_swap implementation is using malloc() in those situations

# Cases where at least one number is outside the range of long (64-bit
# architecture context only)
$PROGRAM +41 30 99 1000 +51987 922337203685477580732 4 0 \
	-5 -9 -2

$PROGRAM "+41 30 99 1000 +51987 92233720368547758074 4 -5 \
-9 -2"

$PROGRAM +1 0 -9 -2 678 -9223372036854775808 3 -3 -6 -444 8888

# NOTE: two sets of double-quotes here!
$PROGRAM "+1 0 -9 -2 678 -9223372036854775808" "3 -3 -6 -444 8888"


# Cases where one number is outside int's range but within long's range
# (64-bit architecture context only)
$PROGRAM +41 30 99 1000 +51987 +2 +1 0 -9 -2 678 \
	214748364742 3 -3 -6

$PROGRAM -3147483647422 93 312 18754 -2 -5 2 98 -4 -89

$PROGRAM "0 444 12948 -1243 -999 -10 -42 -3455563647422"

# cases with 1 number overflowing int's range by 1:
$PROGRAM "    12948 2147483648 -1243   1 -999 -10 -42"

$PROGRAM " 2 3 0   -2147483649 1   12948 2525 -621"


# TESTING: Cases which hold INT_MAX or INT_MIN (in their STRING representation)
# We do not expect pur push_swap program to handle those in this case

$PROGRAM 3 9 5 0 2 INT_MAX -7 -9 -20 20912

$PROGRAM -124535 -123 +24232 +1 +9 INT_MIN -142 -42 +42




# TESTING: VALID cases:


# TESTING: Valid integers with '+' or '-' signs

$PROGRAM +519 +10 +0 +7342 +1 | wc -l

$PROGRAM "+519 +10 +0 +7342 +1" | wc -l

$PROGRAM -42 +42 +900 -1500 +1 -0 | wc -l

$PROGRAM "-42 +42 +900 -1500 +1 -0 -1979" | wc -l


# TESTING: Total of 5 valid integers, but plenty of whitespace characters
# surrounding them! One of the only ways to test this is by using the syntax:
# with echo and -e and ' ' within a $ sign variable........
$PROGRAM "$(echo -e '\t -124124 \t \n \v\f 2\r\n\t 5 \n 0\t \v\r-85\n')" \
	| wc -l


# TESTING: Cases which hold INT_MAX or INT_MIN (in their NUMERICAL form);
$PROGRAM 3 99 -23432 2147483647 0 -8 -10 1 -42 | wc -l

$PROGRAM 83611 0 -8 -809 1 -42 -2147483648 9099 123 -21341 | wc -l


# TESTING: Peculiar edge case here, apparantly this is interpreted by the shell
# as argc = 2, argv[1] = 532; so it seems like it ignores the empty string
# entirely. Ideally, I would have liked my push_swap program to treat this as
# an invalid input, following the above logic regarding empty strings / only
# whitespace string arguments, but I suppose this is beyond the scope of the
# push_swap project, and it is not up to this program to handle internal shell
# behaviour...
$PROGRAM ""532 | wc -l

# shell interpretation: argc = 2; argv[1] = "(whitespace)-4242" (same as above)
$PROGRAM "					      "-4242 | wc -l


# TESTING: Cases that are already sorted. These should not print anything on
# the screen! Even if the moves you output end up sorting the array again
# anyways... It would not make sense
$PROGRAM $(seq -s " " -42 42) | wc -l

$PROGRAM $(seq -s " " 0 10) | wc -l

$PROGRAM $(seq -s " " -320 179) | wc -l


# TESTING: Case with zero arguments: should not do anything and return the
# prompt to the user

$PROGRAM | wc -l


# TESTING: Other cases that should not do anything and return the prompt to
# the user, without claiming there is an error, because there is only 1 integer

$PROGRAM "100" | wc -l

$PROGRAM 14213 | wc -l

$PROGRAM "			-213" | wc -l


# TESTING: Valid, 'normal' random combinations that need to be sorted!


# TESTING: Multiple strings passed as arguments, some containing more than
# one valid integer
$PROGRAM " 4 2 8 92 1234 324524 234234 -324 -124 -5345 " "-42" " -2421 \
	023421 0433 -654 -66 -77 -44 " "-233 -2221 -111 -543 -1342 \
	-111111" "0" | wc -l

# TESTING: random 2 integer stacks (important edge case to check!)

$PROGRAM 2147483647 -2147483648 | wc -l

$PROGRAM 3 -432 | wc -l

$PROGRAM 1 42 | wc -l

$PROGRAM 42 888 | wc -l


# TESTING: random 4 integer stacks (there could be issues with all kinds of
# rather smalll stacks, because of how the chunks are splitted, and so this
# testing script incudes a number of those, to avoid bad surprises)

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 4 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l


# TESTING: random 6 integer stacks
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 6 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l


# TESTING: random 7 integer stacks
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 7 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l


# TESTING: random 8 integer stack
#
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
$PROGRAM $(seq -234234 +2342341 | $SHUF -n 8 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l


# TESTING: push_swap benchmark stacks

# TESTING: random 3 integer stacks

$PROGRAM 2147483647 -2147483648 -2147483645 | wc -l

$PROGRAM -2147483648 -2147483645 2147483647 | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 3 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l



# TESTING: random 5 integer stacks

$PROGRAM 2147483647 -2147483630 2147483643 -2147483648 -2147483645 | wc -l

$PROGRAM -2147483630 2147483643 -2147483648 2147483647 -2147483645 | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -8 +3 | $SHUF -n 5 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l



# TESTING: random 100 integer stacks

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -450 +3 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -450 +3 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -450 +3 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -450 +3 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -450 +3 | $SHUF -n 100 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l



# TESTING: random 500 integer stacks

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -234234 +2342341 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l

$PROGRAM $(seq -200 800 | $SHUF -n 500 | awk '{val=sprintf("%d", $1); if (!seen[val]++) printf "%d ", val}') | wc -l
