#if !defined Ofw_Error_H_
#define Ofw_Error_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

typedef int32_t Ofw_Error_t;

/**
 * Bit structure
 * 0   8 Reason(sub) (free to use in application)
 * 8  12 Reason(main)
 * 20  4 argument number (0: not specified)
 * 24  4 (reserved)
 * 28  1 temporary flag (1:temporary 0:permanent)
 * 29  2 owner (0:errno 1:Ofw 2:user 3:reserved)
 * 31  1 (sign flag)(reserved)
 */

#define Ofw_Error_toMask(bit, base) (((1 << (bit)) - 1) << (base))

#define Ofw_Error_OWNER_BASE (29)
#define Ofw_Error_OWNER_BIT (2)
#define Ofw_Error_OWNER_MASK (Ofw_Error_toMask(Ofw_Error_OWNER_BIT, Ofw_Error_OWNER_BASE))
#define Ofw_Error_getOwner(e) ((e) & Ofw_Error_OWNER_MASK)

#define Ofw_Error_OWNER_ERRNO (0)
#define Ofw_Error_OWNER_Ofw (1 << Ofw_Error_OWNER_BASE)
#define Ofw_Error_OWNER_USER (2 << Ofw_Error_OWNER_BASE)

#define Ofw_Error_isOwnerErrno(e) (((e) & Ofw_Error_OWNER_MASK) == Ofw_Error_OWNER_ERRNO)
#define Ofw_Error_isOwnerOfw(e) (((e) & Ofw_Error_OWNER_MASK) == Ofw_Error_OWNER_Ofw)
#define Ofw_Error_isOwnerUser(e) (((e) & Ofw_Error_OWNER_MASK) == Ofw_Error_OWNER_USER)

#define Ofw_Error_REASON_MAIN_BASE (8)
#define Ofw_Error_REASON_MAIN_BIT (12)
#define Ofw_Error_REASON_MAIN_MASK (Ofw_Error_toMask(Ofw_Error_REASON_MAIN_BIT, Ofw_Error_REASON_MAIN_BASE))
#define Ofw_Error_getReasonMain(e) ((e) & Ofw_Error_REASON_MAIN_MASK)

#define Ofw_Error_REASON_SUB_BASE (0)
#define Ofw_Error_REASON_SUB_BIT (8)
#define Ofw_Error_REASON_SUB_MASK (Ofw_Error_toMask(Ofw_Error_REASON_SUB_BIT,Ofw_Error_REASON_SUB_BASE))
#define Ofw_Error_getReasonSub(e) ((e) & Ofw_Error_REASON_SUB_MASK)

#define Ofw_Error_REASON_MASK (Ofw_Error_REASON_MAIN_MASK | Ofw_Error_REASON_SUB_MASK)
#define Ofw_Error_getReason(e) ((e) & Ofw_Error_REASON_MASK)

#define Ofw_Error_getOwnerReasonMain(e) ((e) & (Ofw_Error_OWNER_MASK | Ofw_Error_REASON_MAIN_MASK))

#define Ofw_Error_PARAM_BASE (20)
#define Ofw_Error_PARAM_BIT (4)
#define Ofw_Error_PARAM_MASK (Ofw_Error_toMask(Ofw_Error_PARAM_BIT,Ofw_Error_PARAM_BASE))
#define Ofw_Error_getParam(e) ((e) & Ofw_Error_PARAM_MASK)
#define Ofw_Error_setParam(e, param) (((e) & ~Ofw_Error_PARAM_MASK) | (param))

#define Ofw_Error_PARAM1 (0x1<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM2 (0x2<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM3 (0x3<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM4 (0x4<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM5 (0x5<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM6 (0x6<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM7 (0x7<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM8 (0x8<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM9 (0x9<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM10 (0xa<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM11 (0xb<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM12 (0xc<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM13 (0xd<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM14 (0xe<<Ofw_Error_PARAM_BASE)
#define Ofw_Error_PARAM15 (0xf<<Ofw_Error_PARAM_BASE)

#define Ofw_Error_getParam(e) ((e) & Ofw_Error_PARAM_MASK)

/** No error. */
#define Ofw_Error_NO_ERROR (0)

/**
 * Temporary flag.
 */
#define Ofw_Error_TEMPORARY_BASE (28)

#define Ofw_Error_TEMPORARY (1<<Ofw_Error_TEMPORARY_BASE)

#define Ofw_Error_isTemporary(x) (((x) & Ofw_Error_TEMPORARY) != 0)

/**
 * Declare error main reason.
 */
#define Ofw_Error_declReasonMain(n) (Ofw_Error_OWNER_Ofw | ((n)<<Ofw_Error_REASON_MAIN_BASE))

/**
 * Error.
 */
#define Ofw_Error_ERROR (Ofw_Error_declReasonMain(1))

/**
 * Failed.
 * Not error, but failed.
 */
#define Ofw_Error_FAILED (Ofw_Error_declReasonMain(2))

/**
 * Not implemented.
 */
#define Ofw_Error_NOT_IMPLEMENTED (Ofw_Error_declReasonMain(3))

/**
 * Invalid parameter.
 */
#define Ofw_Error_INVALID_PARAM (Ofw_Error_declReasonMain(4))

/**
 * Invalid setting.
 */
#define Ofw_Error_INVALID_SETTING (Ofw_Error_declReasonMain(5))

/**
 * Not initialized.
 */
#define Ofw_Error_NOT_INITALIZED (Ofw_Error_declReasonMain(6))

/**
 * Invalid state.
 */
#define Ofw_Error_INVALID_STATE (Ofw_Error_declReasonMain(7))

/**
 * NULL Pointer detected.
 */
#define Ofw_Error_NULL_POINTER (Ofw_Error_declReasonMain(8))

/**
 * Invalid object.
 */
#define Ofw_Error_INVALID_OBJECT (Ofw_Error_declReasonMain(9))

/**
 * Invalid request.
 */
#define Ofw_Error_INVALID_REQUEST (Ofw_Error_declReasonMain(10))

/**
 * Processing denied.
 * (No processing has been done yet.)
 */
#define Ofw_Error_DENIED (Ofw_Error_declReasonMain(11))

/**
 * Not authorized.
 */
#define Ofw_Error_NO_AUTH (Ofw_Error_declReasonMain(12))

/**
 * Not permitted.
 * The requested operation is not allowed.
 */
#define Ofw_Error_NO_PERMIT (Ofw_Error_declReasonMain(13))

/**
 * You aren't owner.
 */
#define Ofw_Error_NOT_OWNER (Ofw_Error_declReasonMain(14))

/**
 * In use by others.
 */
#define Ofw_Error_IN_USE (Ofw_Error_declReasonMain(15))

/**
 * Not supported.
 * Functionality is there, but the required capabilities are not.
 */
#define Ofw_Error_NOT_SUPPORTED (Ofw_Error_declReasonMain(16))

/**
 * Not in service.
 */
#define Ofw_Error_NOT_IN_SERVICE (Ofw_Error_declReasonMain(17))

/**
 * Device offline.
 */
#define Ofw_Error_OFFLINE (Ofw_Error_declReasonMain(18))

/**
 * Not ready.
 */
#define Ofw_Error_NOT_READY (Ofw_Error_declReasonMain(19))

/**
 * Busy.
 */
#define Ofw_Error_BUSY (Ofw_Error_declReasonMain(20))

/**
 * Already closed.
 */
#define Ofw_Error_ALREADY_CLOSED (Ofw_Error_declReasonMain(21))

/**
 * Function error.
 * There was an unrepairable error on the lower level function.
 */
#define Ofw_Error_FUNCTION_ERROR (Ofw_Error_declReasonMain(22))

/**
 * Out of resource.
 */
#define Ofw_Error_OUT_OF_RESOURCE (Ofw_Error_declReasonMain(23))

/**
 * Out of slot.
 */
#define Ofw_Error_OUT_OF_SLOT (Ofw_Error_declReasonMain(24))

/**
 * Out of memory.
 */
#define Ofw_Error_OUT_OF_MEMORY (Ofw_Error_declReasonMain(25))

/**
 * Out of storage space.
 */
#define Ofw_Error_OUT_OF_STORAGE_SPACE (Ofw_Error_declReasonMain(26))

/**
 * Canceled.
 * (User cancel the process. the process is not started.)
 */
#define Ofw_Error_CANCELED (Ofw_Error_declReasonMain(27))

/**
 * Aborted.
 * (User aborted the process. the process has started.)
 */
#define Ofw_Error_ABORTED (Ofw_Error_declReasonMain(28))

/**
 * Interrupted.
 * (Signal received.)
 */
#define Ofw_Error_INTERRUPTED (Ofw_Error_declReasonMain(29))

/**
 * Timed out.
 */
#define Ofw_Error_TIMEDOUT (Ofw_Error_declReasonMain(30))

/**
 * Disconnected.
 */
#define Ofw_Error_DISCONNECTED (Ofw_Error_declReasonMain(31))

/**
 * Termination requested.
 * (The user requested termination.)
 */
#define Ofw_Error_TERMINATE_REQUESTED (Ofw_Error_declReasonMain(32))

/**
 * Not exists.
 */
#define Ofw_Error_NOT_EXISTS (Ofw_Error_declReasonMain(33))

/**
 * Already exists.
 */
#define Ofw_Error_ALREADY_EXISTS (Ofw_Error_declReasonMain(34))

/**
 * Already in that state
 */
#define Ofw_Error_ALREADY_STATE (Ofw_Error_declReasonMain(35))

/**
 * Invalid format.
 */
#define Ofw_Error_INVALID_FORMAT (Ofw_Error_declReasonMain(36))

/**
 * Out of range.
 */
#define Ofw_Error_OUT_OF_RANGE (Ofw_Error_declReasonMain(37))

/**
 * Too big.
 */
#define Ofw_Error_TOO_BIG (Ofw_Error_declReasonMain(38))

/**
 * Too small.
 */
#define Ofw_Error_TOO_SMALL (Ofw_Error_declReasonMain(39))

/**
 * Overflow.
 */
#define Ofw_Error_OVERFLOW (Ofw_Error_declReasonMain(40))

/**
 * Underflow.
 */
#define Ofw_Error_UNDERFLOW (Ofw_Error_declReasonMain(41))

/**
 * Empty.
 */
#define Ofw_Error_EMPTY (Ofw_Error_declReasonMain(42))

/**
 * Full.
 */
#define Ofw_Error_FULL (Ofw_Error_declReasonMain(43))

/**
 * Start of data.
 */
#define Ofw_Error_START_OF_DATA (Ofw_Error_declReasonMain(44))

/**
 * End of data.
 */
#define Ofw_Error_END_OF_DATA (Ofw_Error_declReasonMain(45))

/**
 * Deadlock detected.
 */
#define Ofw_Error_DEADLOCK (Ofw_Error_declReasonMain(46))

/**
 * Interface inconsistency.
 */
#define Ofw_Error_INTERFACE_INCONSISTENCY (Ofw_Error_declReasonMain(47))


/**
 * convert errno to Ofw_Errno_t.
 */
#define Ofw_Error_convErrno(errno) (errno)

#endif /* Ofw_Error_H_ */
