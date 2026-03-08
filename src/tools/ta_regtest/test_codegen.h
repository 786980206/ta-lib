#ifndef TEST_CODEGEN_H
#define TEST_CODEGEN_H

#include "ta_error_number.h"
#include "ta_test_priv.h"

/* Run codegen verification tests.
 * Starts ta_codegen serve, sends JSON-RPC requests for each supported
 * function, compares results against C reference.
 * functionFilter: CSV list of function names to test (NULL = test all)
 */
ErrorNumber test_codegen(const TA_History *history, const char *functionFilter);

#endif
