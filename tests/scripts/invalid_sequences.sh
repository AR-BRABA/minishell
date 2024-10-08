#!/bin/bash

TEST_RESULTS_DIR="tests/results"
TEST_NAME="invalid_sequences.sh"
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
        results+=("$(printf "%-4s | %-15s | ${GREEN}%-7s${NC}" "$test_id" "$input" "PASSED")")
    else
        #results+=(" $test_id  |   $input   |   FAILED")
        results+=("$(printf "%-4s | %-15s | ${RED}%-7s${NC}" "$test_id" "$input" "FAILED")")
    fi
}

# Test cases
run_test '<|' 'minishell$ <|\nError' 1
run_test '<|   ' 'minishell$ <|   \nError' 2
run_test 'anything<|' 'minishell$ anything<|\nError' 3
run_test 'anything<|   ' 'minishell$ anything<|   \nError' 4
run_test 'anything <|' 'minishell$ anything <|\nError' 5
run_test 'anything <|   ' 'minishell$ anything <|   \nError' 6
run_test '<|anything' 'minishell$ <|anything\nError' 7
run_test '<| anything' 'minishell$ <| anything\nError' 8

run_test '< |' 'minishell$ < |\nError' 9
run_test '< |   ' 'minishell$ < |   \nError' 10
run_test 'anything< |' 'minishell$ anything< |\nError' 11
run_test 'anything< |   ' 'minishell$ anything< |   \nError' 12
run_test 'anything < |' 'minishell$ anything < |\nError' 13
run_test 'anything < |   ' 'minishell$ anything < |   \nError' 14
run_test '< |anything' 'minishell$ < |anything\nError' 15
run_test '< | anything' 'minishell$ < | anything\nError' 16

run_test '|<' 'minishell$ |<\nError' 17
run_test '|<   ' 'minishell$ |<   \nError' 18
run_test 'anything|<' 'minishell$ anything|<\nError' 19
run_test 'anything|<   ' 'minishell$ anything|<   \nError' 20
run_test 'anything |<' 'minishell$ anything |<\nError' 21
run_test 'anything |<   ' 'minishell$ anything |<   \nError' 22
run_test '|<anything' 'minishell$ |<anything\nError' 23
run_test '|< anything' 'minishell$ |< anything\nError' 24

run_test '| <' 'minishell$ | <\nError' 25
run_test '| <   ' 'minishell$ | <   \nError' 26
run_test 'anything| <' 'minishell$ anything| <\nError' 27
run_test 'anything| <   ' 'minishell$ anything| <   \nError' 28
run_test 'anything | <' 'minishell$ anything | <\nError' 29
run_test 'anything | <   ' 'minishell$ anything | <   \nError' 30
run_test '| <anything' 'minishell$ | <anything\nError' 31
run_test '| < anything' 'minishell$ | < anything\nError' 32


# Print results table
printf "\nTEST: %s" "$TEST_NAME"
printf "\n%-4s | %-15s | %s\n" "#id" "TESTS" "Status"
printf -- "%s\n" "${results[@]}"

# Cleanup - Uncomment to remove test outputs after running
# rm "$TEST_RESULTS_DIR"/${TEST_NAME}-test*.out "$TEST_RESULTS_DIR"/expected_${TEST_NAME}-test*.out
