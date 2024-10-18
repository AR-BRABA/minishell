#!/bin/bash


TEST_RESULTS_DIR="tests/results"
TEST_NAME="append-mode_syntax"
declare -a results=()


if [[ ! -d "$TEST_RESULTS_DIR" ]]; then
   mkdir -p "$TEST_RESULTS_DIR"
fi


# Table results colors
GREEN='\033[32m'
RED='\033[31m'
NC='\033[0m' # reset colors


# Perform a single test
run_test() {
   local input="$1"
   local expected_output="$2"
   local test_id="$3"
   local result_file="$TEST_RESULTS_DIR/${TEST_NAME}-test${test_id}.out"
   local expected_file="$TEST_RESULTS_DIR/expected_${TEST_NAME}-test${test_id}.out"


   # checks ./minishell path
   printf "MINISHELL path: %s\n" "$MINISHELL" >&2


   # Run the minishell with input and save the output (stdout + stderr)
   echo "$input" | "$MINISHELL" > "$result_file" 2>&1


   # Remove output file's 3rd line
   sed -i '3d' "$result_file"


   # Save the expected output
   echo -e "$expected_output" > "$expected_file"


   # Compare the actual filtered output with the expected output
   if diff "$result_file" "$expected_file" > /dev/null; then
       #results+=(" $test_id  |   $input   |   PASSED")
       results+=("$(printf "%-4s | %-35s | ${GREEN}%-7s${NC}" "$test_id" "$input" "PASSED")")
   else
       #results+=(" $test_id  |   $input   |   FAILED")
       results+=("$(printf "%-4s | %-35s | ${RED}%-7s${NC}" "$test_id" "$input" "FAILED")")
   fi
}


# Test cases
run_test '>>' 'minishell$ >>\nError' 1
run_test '>>   ' 'minishell$ >>\nError' 2
run_test '>>anything' 'minishell$ >>anything\nValid input: >>anything' 3
run_test '>> anything' 'minishell$ >> anything\nValid input: >> anything' 4
run_test 'anything>>' 'minishell$ anything>>\nError' 5
run_test 'anything>>   ' 'minishell$ anything>>   \nError' 6
run_test 'anything >>' 'minishell$ anything >>\nError' 7
run_test 'anything >>   ' 'minishell$ anything >>   \nError' 8
runt_test 'text >> cat'' minishell$ text >> cat\nValid input: text >> cat' 9


# Print results table
printf "\nTEST: %s" "$TEST_NAME"
printf "\n%-4s | %-35s | %s\n" "#id" "TESTS" "Status"
printf -- "%s\n" "${results[@]}"


# Cleanup - Uncomment to remove test outputs after running
# rm "$TEST_RESULTS_DIR"/${TEST_NAME}-test*.out "$TEST_RESULTS_DIR"/expected_${TEST_NAME}-test*.out
