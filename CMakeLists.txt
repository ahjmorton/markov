cmake_minimum_required(VERSION 2.6)

project(markov)

FILE(GLOB CORPUS_SOURCES src/corpus/*.c)
FILE(GLOB RANDOM_CHAIN_SOURCES src/rand-markov/*.c)

ADD_EXECUTABLE(corpus ${CORPUS_SOURCES})
ADD_EXECUTABLE(rand_markov ${RANDOM_CHAIN_SOURCES})
