#!/bin/bash

TEST_RESULTS_DIR="tests/results"
TEST_SCRIPTS_DIR="tests/scripts"
MINISHELL="$(pwd)/minishell"

# Export MINISHELL variable so it will be available to child processes
export MINISHELL

# Ensure directories exist
if [[ ! -d "$TEST_RESULTS_DIR" ]]; then
    mkdir -p "$TEST_RESULTS_DIR"
fi

run_test_script() {
    local test_script; test_script="$1"
    local test_name; test_name=$(basename "$test_script" .sh)
    local result_file; result_file="$TEST_RESULTS_DIR/${test_name}_result.out"

    # Run the test script and save it's results in a specific file
    if ! ./"$test_script" > "$result_file"; then
        printf "Failed to execute %s\n" "$test_script" >&2
        return 1
    fi

    printf "Executed %s\nResults saved in %s\n" "$test_script" "$result_file"
    cat "$result_file"
}

main() {
    local test_scripts=(
        "$TEST_SCRIPTS_DIR/border_special_chars.sh"
    )

    for test_script in "${test_scripts[@]}"; do
        if ! run_test_script "$test_script"; then
            printf "Error occurred while running %s\n" "$test_script" >&2
        fi
    done
}

main