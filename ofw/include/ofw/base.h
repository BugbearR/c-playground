#if !defined Ofw_Base_H_
#define Ofw_Base_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

/** simple result code (r<0: error, r>=0: no error) */
typedef int32_t Ofw_Result_t;

// FAIL, FAILED, FAILURE, ERROR
#define Ofw_Result_FAILED (-1)
// SUCCEED, SUCCEEDED, SUCCESS, SUCCESSFUL, OK
#define Ofw_Result_SUCCEEDED (0)

#define Ofw_Result_isFailed(result) (result < 0)
#define Ofw_Result_isSucceeded(result) (result >= 0)

#endif /* Ofw_Base_H_ */
