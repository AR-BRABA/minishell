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
        #results+=(" $test_id  |   $input   |   PASSED")
        results+=("$(printf "%-4s | %-15s | ${GREEN}%-7s${NC}" "$test_id" "$input" "PASSED")")
    else
        #results+=(" $test_id  |   $input   |   FAILED")
        results+=("$(printf "%-4s | %-15s | ${RED}%-7s${NC}" "$test_id" "$input" "FAILED")")
    fi
}

# Test cases
run_test '\command' 'minishell$ \\command\nError' 1
run_test 'command|' 'minishell$ command|\nError' 2
run_test '<command' 'minishell$ <command\nError' 3
run_test 'command<' 'minishell$ command<\nError' 4
run_test '>command' 'minishell$ >command\nError' 5
run_test 'command>' 'minishell$ command>\nError' 6
run_test 'command>>' 'minishell$ command>>\nError' 7
run_test '<<' 'minishell$ <<\nValid input: <<' 8
run_test '<< anything' 'minishell$ << anything\nValid input: <<' 9
run_test '<<anything' 'minishell$ <<anything\nValid input: <<' 10
run_test '|' 'minishell$ |\nError' 11
run_test '|anything' 'minishell$ |anything\nError' 12
run_test '| anything' 'minishell$ | anything\nError' 13
run_test 'anything|' 'minishell$ anything|\nError' 14
run_test 'anything |' 'minishell$ anything |\nError' 15
run_test '<' 'minishell$ <\nError' 16
run_test '< anything' 'minishell$ < anything\nError' 17
run_test 'anything <' 'minishell$ anything <\nError' 18
run_test '<|' 'minishell$ <|\nError' 19
run_test 'anything <|' 'minishell$ anything <|\nError' 20
run_test '<| anything' 'minishell$ <| anything\nError' 21
run_test '< |' 'minishell$ < |\nError' 22
run_test 'anything < |' 'minishell$ anything < |\nError' 23
run_test '< | anything' 'minishell$ < | anything\nError' 24
run_test '<<<' 'minishell$ <<<\nError' 25
run_test 'anything <<<' 'minishell$ anything <<<\nError' 26
run_test '<<< anything' 'minishell$ <<< anything\nError' 27
run_test '< <<' 'minishell$ < <<\nError' 28
run_test 'anything < <<' 'minishell$ anything < <<\nError' 29
run_test '< << anything' 'minishell$ < << anything\nError' 30
run_test '<< <' 'minishell$ << <\nError' 31
run_test 'anything << <' 'minishell$ anything << <\nError' 32
run_test '<< < anything' 'minishell$ << < anything\nError' 33
run_test '< < <' 'minishell$ < < <\nError' 34
run_test 'anything < < <' 'minishell$ anything < < <\nError' 35
run_test '< < < anything' 'minishell$ < < < anything\nError' 36
run_test '>' 'minishell$ >\nError' 37
run_test '> anything' 'minishell$ > anything\nError' 38
run_test 'anything >' 'minishell$ anything >\nError' 39
run_test '>|' 'minishell$ >|\nError' 40
run_test 'anything >|' 'minishell$ anything >|\nError' 41
run_test '>| anything' 'minishell$ >| anything\nError' 42
run_test '> |' 'minishell$ > |\nError' 43
run_test 'anything > |' 'minishell$ anything > |\nError' 44
run_test '> | anything' 'minishell$ > | anything\nError' 45
run_test '>>>' 'minishell$ >>>\nError' 46
run_test 'anything >>>' 'minishell$ anything >>>\nError' 47
run_test '>>> anything' 'minishell$ >>> anything\nError' 48
run_test '> >>' 'minishell$ > >>\nError' 49
run_test 'anything > >>' 'minishell$ anything > >>\nError' 50
run_test '> >> anything' 'minishell$ > >> anything\nError' 51
run_test '>> >' 'minishell$ >> >\nError' 52
run_test 'anything >> >' 'minishell$ anything >> >\nError' 53
run_test '>> > anything' 'minishell$ >> > anything\nError' 54
run_test '> > >' 'minishell$ > > >\nError' 55
run_test 'anything > > >' 'minishell$ anything > > >\nError' 56
run_test '> > > anything' 'minishell$ > > > anything\nError' 57

# Print results table
printf "\nTEST: %s" "$TEST_NAME"
printf "\n%-4s | %-15s | %s\n" "#id" "TESTS" "Status"
printf -- "%s\n" "${results[@]}"

# Cleanup - Uncomment to remove test outputs after running
# rm "$TEST_RESULTS_DIR"/${TEST_NAME}-test*.out "$TEST_RESULTS_DIR"/expected_${TEST_NAME}-test*.out