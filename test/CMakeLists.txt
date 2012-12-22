enable_testing()

find_package(PythonInterp) 
if(PYTHONINTERP_FOUND STREQUAL "TRUE")
    set(PYTHON_VERSION_NUM ${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
    if(${PYTHON_VERSION_NUM} LESS 26)
        message(WARNING "Python version needs to be newer than 2.6.x")
    else()
        set(CORPUS_CMD ${CMAKE_BINARY_DIR}/src/corpus)

        macro(add_equals_test test_name input_file check_file) 
            add_test(${test_name} ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/py/equals_test.py ${CORPUS_CMD} ${input_file} ${check_file})
        endmacro(add_equals_test)

        macro(add_correct_test test_name input_file) 
            add_test(${test_name} ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/py/correct_test.py ${CORPUS_CMD} ${input_file})
        endmacro(add_correct_test)

        set(TEST_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/test_input)
        set(TEST_CHECK ${CMAKE_CURRENT_SOURCE_DIR}/test_check)

        add_equals_test(SimpleEqualsTest ${TEST_INPUT}/simple ${TEST_CHECK}/simple_check)
        add_correct_test(SimpleCorrectTest ${TEST_INPUT}/simple)
    endif()
endif(PYTHONINTERP_FOUND STREQUAL "TRUE") 

