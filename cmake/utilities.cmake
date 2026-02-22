include_guard(DIRECTORY)

function(consume_setup_fn setup_fn)
    cmake_language(CALL ${setup_fn})
    unset(${setup_fn})
endfunction()

function(print_var var)
    message(STATUS "${var}: ${${var}}")
endfunction()
