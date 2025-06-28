# B-Tree Test Suite

## Overview
This test suite provides comprehensive testing for the B-Tree implementation located in the parent directory.

## Test Coverage

### Core Functionality Tests
- **Initialization**: Tests proper initialization and cleanup of B-Tree structures
- **Single Insertion**: Validates basic insertion functionality 
- **Multiple Insertions**: Tests insertion of multiple values with validation
- **Sequential Insertions**: Tests performance with ordered data insertion
- **Search Operations**: Tests both successful and unsuccessful search operations
- **Basic Deletion**: Tests deletion functionality
- **Tree Structure**: Validates internal B-Tree structure and balancing

### Test Details

| Test Function | Purpose | Coverage |
|---------------|---------|----------|
| `test_initialization()` | Verifies proper B-Tree initialization | BTree_initialize(), BTree_finalize() |
| `test_single_insertion()` | Basic insertion and retrieval | BTree_add(), BTree_get(), BTree_validate() |
| `test_multiple_insertions()` | Multiple value operations | BTree_add(), BTree_get(), BTree_validate() |
| `test_sequential_insertions()` | Ordered data handling | BTree_add(), BTree_get(), BTree_validate() |
| `test_not_found()` | Search failure cases | BTree_get() with non-existent values |
| `test_basic_deletion()` | Deletion operations | BTree_delete(), BTree_get() |
| `test_tree_structure()` | Internal structure validation | BTree_dump(), BTree_validate() |

## Running Tests

### Build and Run
```bash
# From the test directory
make clean
make
make test
```

### Expected Output
The test suite will output:
- Individual test results (PASS/FAIL)
- Tree structure dumps for verification
- Final test summary with pass/fail counts

### Test Results
A successful run will show:
```
Test Results: 37/37 tests passed
All tests PASSED!
```

## Test Framework

The test suite uses a simple custom framework with:
- `test_assert()` function for assertions
- Test counting and reporting
- Structured test output with clear sections

## API Functions Tested

### Covered Functions
- `BTree_initialize()` - Initialize B-Tree structure
- `BTree_finalize()` - Clean up B-Tree structure  
- `BTree_add()` - Insert values into B-Tree
- `BTree_get()` - Search for values in B-Tree
- `BTree_delete()` - Remove values from B-Tree
- `BTree_validate()` - Validate B-Tree structure integrity
- `BTree_dump()` - Display B-Tree structure

### Test Safety
The test suite is designed to be robust and avoid segmentation faults by:
- Using conservative test data sizes
- Proper cleanup of all test instances
- Validation calls after structure modifications
- Graceful handling of expected failure cases

## Notes
- Tests are designed to work with the BTREE_NODE_ENTRY_MAX setting of 4
- The test suite validates B-Tree properties and structure integrity
- All memory is properly cleaned up to avoid leaks