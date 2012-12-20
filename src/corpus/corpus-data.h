/*
This file is part of markov.

markov is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

markov is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with markov.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef HEADER_CORPUS_DATA_GENERATOR
#define HEADER_CORPUS_DATA_GENERATOR

typedef struct
{
    int other;
    int seen;
} corpus_node;

typedef struct corpus_chain
{
    int value;
    int corpus_amount;
    int seen_total;
    corpus_node * corpus;
} corpus_chain;

typedef struct 
{
    int amount;
    corpus_chain * root;
} corpus_root;

#endif
