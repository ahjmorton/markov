#!/usr/bin/python
#
#This file is part of markov.
#
#markov is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#markov is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with markov.  If not, see <http://www.gnu.org/licenses/>.

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
