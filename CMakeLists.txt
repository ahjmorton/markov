cmake_minimum_required(VERSION 2.6)

project(markov)

FILE(GLOB CORPUS_SOURCES src/corpus/*.c)
FILE(GLOB SAMPLE_SOURCES src/sample/*.c)

ADD_EXECUTABLE(corpus ${CORPUS_SOURCES})
ADD_EXECUTABLE(rand_markov ${SAMPLE_SOURCES})
