FILE(GLOB CORPUS_SOURCES corpus/*.c)
SET(CORPUS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/corpus)
FILE(GLOB SAMPLE_SOURCES sample/*.c)

# This is a little odd, so we want the sources
# in corpus to be de-coupled from the main method
# for testing purposes, test programs needs a main 
# method as well.
INCLUDE_DIRECTORIES(${CORPUS_INCLUDE})
ADD_EXECUTABLE(corpus ${CORPUS_SOURCES} corpus-main.c)

ADD_EXECUTABLE(rand_markov ${SAMPLE_SOURCES})
