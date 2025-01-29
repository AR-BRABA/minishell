#!/bin/bash

run_test() {
    command="$1"
    echo "Running test: $command"

    touch bash_output.txt
    # Run command in minishell
    echo "$command" | ./minishell | tail -n +2 | sed 's/^minishell\$ //' > minishell_output.txt 2>&1
    minishell_status=$?

    # Run command in bash
    echo "$command" | bash > bash_output.txt 2>&1
    bash_status=$?

    # Compare outputs
    if diff minishell_output.txt bash_output.txt > /dev/null && [ $minishell_status -eq $bash_status ]; then
        echo "Test passed: $command"
    else
        echo "Test failed: $command"
        # echo "Expected output:"
        # cat bash_output.txt
        # echo "Got:"
        # cat minishell_output.txt
        echo "Expected status: $bash_status, Got: $minishell_status"
    fi

    # Clean up
    rm minishell_output.txt bash_output.txt
}

# Test cases
# CD
run_test "cd nonexistentdirectory | ls"
run_test "cd | ls"
run_test "cd 42 | ls"
run_test "cd ~ | ls"
run_test "cd - | ls"
run_test "cd 42 notadir | ls"

# ECHO
run_test "echo"
run_test "echo Hello, World!"
run_test "echo -n"
run_test "echo -n Hello!"
run_test "echo -n -n Hello!"
run_test "echo -n -n -n Hello!"
run_test "echo \"tes'te\""
run_test "echo \'te\"st\'"

# PWD
run_test "pwd"
run_test "pwd 42"

# EXPORT
run_test "export | env"
run_test "export 42 | env | grep 42"
run_test "export 42=42 | env | grep 42"
run_test "export var= | env | grep var"
run_test "export var=42 | env | grep var"
run_test "export var=42=27 | env | grep var"

# INVALID COMMAND

run_test "echo Hello, World!"
run_test "pwd"
run_test "invalidcommand"
run_test "ls -l"
run_test "exit"

# Add more test cases as needed

echo "All tests completed."