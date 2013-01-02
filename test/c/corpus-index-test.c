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

#include "corpus-data.h"
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

static corpus_chain * create_chain(int value) {
    corpus_chain * chain = (corpus_chain *)calloc(1, sizeof(corpus_chain));
    chain->value = value;
    return chain;
}

static corpus_node * create_node(int value) {
    corpus_node * node = (corpus_node *)calloc(1, sizeof(corpus_node));
    node->other = value;
    return node;
}

START_TEST(test_index_creation_not_null) 
{
   fail_unless(subject != NULL, "Subject is null");
}
END_TEST

START_TEST(test_index_add_key) 
{
    int key = (int)'a';
    corpus_chain * to_add = create_chain(key);
    corpus_index_key * index_key = add_index_key(subject, to_add);   

    fail_unless(index_key != NULL, "Returned key is null");
    fail_unless(index_key->key == key, "Value of index is not the same");
    fail_unless(index_key->chain == to_add, "Chain link is not the same as the one added");

    free(to_add);
}
END_TEST

START_TEST(test_index_find_key_present) 
{
    int key = (int)'a';
    corpus_chain * to_add = create_chain(key);
    add_index_key(subject, to_add);   

    corpus_index_key * index_key = find_index_key(subject, key);
    fail_unless(index_key != NULL, "Found key was null");
    fail_unless(index_key->key == key, "Key of index is not the same");
    fail_unless(index_key->chain == to_add, "Chain link is not the same as the one added");

    free(to_add);
}
END_TEST

START_TEST(test_index_find_key_missing) 
{
    int key = (int)'a';
    corpus_index_key * index_key = find_index_key(subject, key);
    fail_unless(index_key == NULL, "Found a key in an empty index");
}
END_TEST

START_TEST(test_index_add_value) 
{
    int key = (int)'a';
    int value = (int)'b';
    corpus_chain * to_add = create_chain(key);
    corpus_index_key * index_key = add_index_key(subject, to_add);   
  
    corpus_node * to_add_value = create_node(value);
    corpus_index_value * index_value = add_index_value(index_key, to_add_value);
    fail_unless(index_value != NULL, "Index value is null");
    fail_unless(index_value->value == value, "Index value is not the same as input");
    fail_unless(index_value->node == to_add_value, "Node pointer is wrong");

    free(to_add);      
    free(to_add_value);
}
END_TEST

START_TEST(test_index_find_value_present) 
{
    int key = (int)'a';
    int value = (int)'b';
    corpus_chain * to_add = create_chain(key);
    corpus_index_key * index_key = add_index_key(subject, to_add);   
  
    corpus_node * to_add_value = create_node(value);
    add_index_value(index_key, to_add_value);
    corpus_index_value * index_value = find_index_value(index_key, value); 
    fail_unless(index_value != NULL, "Index value is null");
    fail_unless(index_value->value == value, "Index value is not the same as input");
    fail_unless(index_value->node == to_add_value, "Node pointer is wrong");

    free(to_add);      
    free(to_add_value);
}
END_TEST

START_TEST(test_index_find_value_missing) 
{
     int key = (int)'a';
    int value = (int)'b';
    corpus_chain * to_add = create_chain(key);
    corpus_index_key * index_key = add_index_key(subject, to_add);   
  
    corpus_index_value * index_value = find_index_value(index_key, value); 
    fail_unless(index_value == NULL, "Key is missing and should be null");
 
    free(to_add);
} 
END_TEST

static Suite * corpus_index_suite(void) {
    Suite * s = suite_create("corpus-index");

    TCase * tc_index = tcase_create("corpus-index-case");
    tcase_add_checked_fixture(tc_index, setup, teardown);
    tcase_add_test(tc_index, test_index_creation_not_null);
    tcase_add_test(tc_index, test_index_add_key);
    tcase_add_test(tc_index, test_index_find_key_present);
    tcase_add_test(tc_index, test_index_find_key_missing);
    tcase_add_test(tc_index, test_index_add_value);
    tcase_add_test(tc_index, test_index_find_value_present);
    tcase_add_test(tc_index, test_index_find_value_missing);
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
