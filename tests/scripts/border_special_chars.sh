#!/bin/bash

TEST_RESULTS_DIR="tests/results"
TEST_NAME="border_special_chars"
declare -a results=()

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
        results+=(" $test_id  |   $input   |   PASSED")
    else
        results+=(" $test_id  |   $input   |   FAILED")
    fi
}

# Test cases
run_test '\command' 'minishell$ \\command\nError: Special chars at the beginning or end of the input.' 1
run_test 'command|' 'minishell$ command|\nError: Special chars at the beginning or end of the input.' 2
run_test '<command' 'minishell$ <command\nError: Special chars at the beginning or end of the input.' 3
run_test 'command<' 'minishell$ command<\nError: Special chars at the beginning or end of the input.' 4
run_test '>command' 'minishell$ >command\nError: Special chars at the beginning or end of the input.' 5
run_test 'command>' 'minishell$ command>\nError: Special chars at the beginning or end of the input.' 6
run_test 'command>>' 'minishell$ command>>\nError: Special chars at the beginning or end of the input.' 7

# Print results table
printf "\nTEST: %s" "$TEST_NAME"
printf "\n#id |     TESTS    |   Status\n"
printf -- "%s\n" "${results[@]}"

# Cleanup - Uncomment to remove test outputs after running
# rm "$TEST_RESULTS_DIR"/${TEST_NAME}-test*.out "$TEST_RESULTS_DIR"/expected_${TEST_NAME}-test*.out