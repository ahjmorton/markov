#!/usr/bin/python

from sys import argv
import subprocess

command = argv[1]
input_path = argv[2]

with open(input_path, "r") as input_file : 
    corpus_output = subprocess.check_output([command], stdin=input_file)

def _process_output(output_text) :
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


corpus_result = _process_output(corpus_output)

total_prob = dict()

for first in corpus_result :
    if first not in total_prob :
        total_prob[first] = float(0)
    first_corpus = corpus_result[first]
    for second in first_corpus :
        if second not in total_prob :
            total_prob[second] = float(0)
        total_prob[first] = total_prob[first] + first_corpus[second]


"""Returns whether the number is between 0.99999999995 and 1.00000000005.

The reason for this is because for large inputs we may be bumping up against
whatever precision limitations are present on the platform we're operating 
on, so assume "as close to one as makes no odds" is good enough.

If you need more than 10 decimal places worth of accuracy then patches welcome. 
"""
def _is_one(num) :
    return 0.99999999995 <= num <= 1.00000000005

for character in total_prob :
    assert _is_one(total_prob[character]), "Value for {0} should be close to 1.0 but is {1!r}".format(character, total_prob[character])
