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

#include <stdlib.h>
#include <check.h>

#include "corpus-index.h"

static corpus_index * subject;

void setup(void) {
   subject = create_index();
}

void teardown(void) {
   if(subject != NULL) {
       free_index(subject);
   } 
}

START_TEST(test_index_creation_not_null) 
{
   fail_unless(subject != NULL);
}
END_TEST


static Suite * corpus_index_suite(void) {
    Suite * s = suite_create("corpus-index");

    TCase * tc_index = tcase_create("corpus-index-case");
    tcase_add_checked_fixture(tc_index, setup, teardown);
    tcase_add_test(tc_index, test_index_creation_not_null);
    suite_add_tcase(s, tc_index);

    return s;
}

int main(void) {
    Suite * s = corpus_index_suite();
    SRunner * sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
