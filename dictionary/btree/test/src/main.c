#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include <assert.h>

static int test_count = 0;
static int test_passed = 0;

void test_assert(int condition, const char* test_name) {
    test_count++;
    if (condition) {
        test_passed++;
        printf("PASS: %s\n", test_name);
    } else {
        printf("FAIL: %s\n", test_name);
    }
}

void test_initialization() {
    printf("\n=== Testing Initialization ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    test_assert(btree.count == 0, "Initial count is 0");
    test_assert(btree.pRoot == NULL, "Initial root is NULL");

    BTree_finalize(&btree);
}

void test_single_insertion() {
    printf("\n=== Testing Single Insertion ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    int result = BTree_add(&btree, 42);
    test_assert(result == 0, "Single insertion returns success");

    BTree_get_result_t getRes = BTree_get(&btree, 42);
    test_assert(getRes.found == true, "Can find inserted value");
    test_assert(getRes.value == 42, "Retrieved value matches inserted");

    BTree_validate(&btree);
    BTree_finalize(&btree);
}

void test_multiple_insertions() {
    printf("\n=== Testing Multiple Insertions ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    int values[] = {10, 20, 5};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        int result = BTree_add(&btree, values[i]);
        test_assert(result == 0, "Multiple insertion returns success");
        BTree_validate(&btree);
    }

    for (int i = 0; i < num_values; i++) {
        BTree_get_result_t getRes = BTree_get(&btree, values[i]);
        test_assert(getRes.found == true, "Can find all inserted values");
    }

    BTree_finalize(&btree);
}

void test_sequential_insertions() {
    printf("\n=== Testing Sequential Insertions ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    for (int i = 1; i <= 10; i++) {
        int result = BTree_add(&btree, i);
        test_assert(result == 0, "Sequential insertion returns success");
        if (i % 3 == 0) {
            BTree_validate(&btree);
        }
    }

    for (int i = 1; i <= 10; i++) {
        BTree_get_result_t getRes = BTree_get(&btree, i);
        test_assert(getRes.found == true, "Can find sequential values");
    }

    BTree_finalize(&btree);
}

void test_not_found() {
    printf("\n=== Testing Not Found Cases ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    BTree_get_result_t getRes = BTree_get(&btree, 999);
    test_assert(getRes.found == false, "Empty tree returns not found");

    BTree_add(&btree, 42);
    getRes = BTree_get(&btree, 999);
    test_assert(getRes.found == false, "Non-existent value returns not found");

    BTree_finalize(&btree);
}

void test_basic_deletion() {
    printf("\n=== Testing Basic Deletion ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    BTree_add(&btree, 42);
    BTree_get_result_t getRes = BTree_get(&btree, 42);
    test_assert(getRes.found == true, "Value exists before deletion");

    int result = BTree_delete(&btree, 42);
    test_assert(result == 0, "Deletion returns success");

    getRes = BTree_get(&btree, 42);
    test_assert(getRes.found == false, "Value not found after deletion");

    BTree_finalize(&btree);
}

void test_tree_structure() {
    printf("\n=== Testing Tree Structure ===\n");
    BTree_t btree;
    BTree_initialize(&btree);

    for (int i = 1; i <= 15; i++) {
        BTree_add(&btree, i);
        BTree_validate(&btree);
    }

    printf("Tree dump after 15 insertions:\n");
    BTree_dump(&btree);

    test_assert(btree.pRoot != NULL, "Root exists after multiple insertions");

    BTree_finalize(&btree);
}

int main(int argc, char *argv[])
{
    printf("B-Tree Test Suite Starting...\n");
    printf("==============================\n");

    test_initialization();
    test_single_insertion();
    test_multiple_insertions();
    test_sequential_insertions();
    test_not_found();
    test_basic_deletion();
    test_tree_structure();

    printf("\n==============================\n");
    printf("Test Results: %d/%d tests passed\n", test_passed, test_count);

    if (test_passed == test_count) {
        printf("All tests PASSED!\n");
        return EXIT_SUCCESS;
    } else {
        printf("Some tests FAILED!\n");
        return EXIT_FAILURE;
    }
}
