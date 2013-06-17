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
#include "corpus-data.h"

#ifndef HEADER_CORPUS_GENERATOR
#define HEADER_CORPUS_GENERATOR

corpus_root * generate_chain(chain_options * options);

void free_chain(corpus_root *);

chain_options * create_default_ops(void);

void free_options(chain_options *);

#endif
