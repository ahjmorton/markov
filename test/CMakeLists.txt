enable_testing()

find_package(Check)
if(${CHECK_FOUND} STREQUAL "TRUE") 

    GET_DIRECTORY_PROPERTY(CORPUS_SOURCES DIRECTORY "${CMAKE_SOURCE_DIR}/src" DEFINITION CORPUS_SOURCES)
    GET_DIRECTORY_PROPERTY(CORPUS_INCLUDE DIRECTORY "${CMAKE_SOURCE_DIR}/src" DEFINITION CORPUS_INCLUDE)

    IF("${CORPUS_SOURCES}" STREQUAL "") 
        message(FATAL_ERROR "Cannot find CORPUS_SOURCES variable under src, failing")
    endif()

    IF("${CORPUS_INCLUDE}" STREQUAL "") 
        message(FATAL_ERROR "Cannot find CORPUS_INCLUDE variable under src, failing")
    endif()

    include_directories(${CHECK_INCLUDE_DIR} ${CORPUS_INCLUDE})

    macro(add_test_executable test_name)
        add_executable(${test_name} "${CMAKE_CURRENT_SOURCE_DIR}/src/${test_name}.c" ${CORPUS_SOURCES} )
        target_link_libraries(${test_name} ${CHECK_LIBRARIES})
        add_test(${test_name} ${test_name})
    endmacro(add_test_executable)

    add_test_executable(corpus-index-test)
else()
    message(WARNING "Check not found, cannot run unit tests")
endif()

find_package(PythonInterp) 
if(${PYTHONINTERP_FOUND} STREQUAL "TRUE")
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
        add_correct_test(LongInputCorrectTest ${TEST_INPUT}/beowulf)
    endif()
else()
    message(WARNING "Cannot find Python libraries, no integration tests can be run")
endif() 


