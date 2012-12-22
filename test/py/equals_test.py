#!/usr/bin/python

from sys import argv
import subprocess

command = argv[1]
input_path = argv[2]
check_path = argv[3]

with open(input_path, "r") as input_file : 
    corpus_output = subprocess.check_output([command], stdin=input_file)

def process_output(output_text) :
    result = dict()
    if isinstance(output_text, str) :
        output_text = output_text.split("\n")
    for aline in output_text :
        if not aline :
            continue

        first, second, prob = aline.split(":")

        if first not in result :
            result[first] = dict()
        
        assert second not in result[first], "Cannot have duplicate rows"
            
        result[first][second] = float(prob)
    return result


corpus_result = process_output(corpus_output)

with open(check_path, "r") as check_file :
    check_result = process_output(check_file.readlines())

assert corpus_result == check_result, "Output [{0}] does not match expected [{1}] don't match".format(corpus_result, check_result)
