#if !defined Ofw_SafeCalc_H_
#define Ofw_SafeCalc_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>
#include <limits.h>

#define Ofw_SafeCalc_canCast_decl_u(t, a) \
    ((a) >= 0 && t##_MAX <= (a))

#define Ofw_SafeCalc_canCast_ushort(a) Ofw_SafeCalc_canCast_decl_u(USHRT, a)
#define Ofw_SafeCalc_canCast_uint(a) Ofw_SafeCalc_canCast_decl_u(UINT, a)
#define Ofw_SafeCalc_canCast_ulong(a) Ofw_SafeCalc_canCast_decl_u(ULONG, a)
#define Ofw_SafeCalc_canCast_ullong(a) Ofw_SafeCalc_canCast_decl_u(ULLONG, a)
#define Ofw_SafeCalc_canCast_uint8(a) Ofw_SafeCalc_canCast_decl_u(UINT8, a)
#define Ofw_SafeCalc_canCast_uint16(a) Ofw_SafeCalc_canCast_decl_u(UINT16, a)
#define Ofw_SafeCalc_canCast_uint32(a) Ofw_SafeCalc_canCast_decl_u(UINT32, a)
#define Ofw_SafeCalc_canCast_uint64(a) Ofw_SafeCalc_canCast_decl_u(UINT64, a)
#define Ofw_SafeCalc_canCast_uintmax(a) Ofw_SafeCalc_canCast_decl_u(UINTMAX, a)
#define Ofw_SafeCalc_canCast_size(a) Ofw_SafeCalc_canCast_decl_u(SIZE, a)

#define Ofw_SafeCalc_canCast_decl_s(t, a) \
    (t##_MIN <= (a) && t##_MAX >= (a))

#define Ofw_SafeCalc_canCast_short(a) Ofw_SafeCalc_canCast_decl_s(SHRT, a)
#define Ofw_SafeCalc_canCast_int(a) Ofw_SafeCalc_canCast_decl_s(INT, a)
#define Ofw_SafeCalc_canCast_long(a) Ofw_SafeCalc_canCast_decl_s(LONG, a)
#define Ofw_SafeCalc_canCast_llong(a) Ofw_SafeCalc_canCast_decl_s(LLONG, a)
#define Ofw_SafeCalc_canCast_int8(a) Ofw_SafeCalc_canCast_decl_s(INT8, a)
#define Ofw_SafeCalc_canCast_int16(a) Ofw_SafeCalc_canCast_decl_s(INT16, a)
#define Ofw_SafeCalc_canCast_int32(a) Ofw_SafeCalc_canCast_decl_s(INT32, a)
#define Ofw_SafeCalc_canCast_int64(a) Ofw_SafeCalc_canCast_decl_s(INT64, a)
#define Ofw_SafeCalc_canCast_intmax(a) Ofw_SafeCalc_canCast_decl_s(INTMAX, a)
#define Ofw_SafeCalc_canCast_ptrdiff(a) Ofw_SafeCalc_canCast_decl_s(PTRDIFF, a)
#define Ofw_SafeCalc_canCast_sig_atomic(a) Ofw_SafeCalc_canCast_decl_s(SIG_ATOMIC, a)
#define Ofw_SafeCalc_canCast_ssize(a) Ofw_SafeCalc_canCast_decl_s(SSIZE, a)

/* (a + b <= MAX) -> (a <= MAX - b) */
#define Ofw_SafeCalc_canAdd_decl_u(t, a, b) \
    ((a) <= t##_MAX - (b))

#define Ofw_SafeCalc_canAdd_ushort(a, b) Ofw_SafeCalc_canAdd_decl_u(USHRT, a, b)
#define Ofw_SafeCalc_canAdd_uint(a, b) Ofw_SafeCalc_canAdd_decl_u(UINT, a, b)
#define Ofw_SafeCalc_canAdd_ulong(a, b) Ofw_SafeCalc_canAdd_decl_u(ULONG, a, b)
#define Ofw_SafeCalc_canAdd_ullong(a, b) Ofw_SafeCalc_canAdd_decl_u(ULLONG, a, b)
#define Ofw_SafeCalc_canAdd_uint8(a, b) Ofw_SafeCalc_canAdd_decl_u(UINT8, a, b)
#define Ofw_SafeCalc_canAdd_uint16(a, b) Ofw_SafeCalc_canAdd_decl_u(UINT16, a, b)
#define Ofw_SafeCalc_canAdd_uint32(a, b) Ofw_SafeCalc_canAdd_decl_u(UINT32, a, b)
#define Ofw_SafeCalc_canAdd_uint64(a, b) Ofw_SafeCalc_canAdd_decl_u(UINT64, a, b)
#define Ofw_SafeCalc_canAdd_uintmax(a, b) Ofw_SafeCalc_canAdd_decl_u(UINTMAX, a, b)
#define Ofw_SafeCalc_canAdd_size(a, b) Ofw_SafeCalc_canAdd_decl_u(SIZE, a, b)

/* (a + b <= MAX) -> (a <= MAX - b) (b>=0) */
/* (a + b >= MIN) -> (a >= MIN - b) (b<0) */
#define Ofw_SafeCalc_canAdd_decl_s(t, a, b) \
    (((b) >= 0) ? ((a) <= t##_MAX - (b)) : ((a) >= t##_MIN - (b)))

#define Ofw_SafeCalc_canAdd_short(a, b) Ofw_SafeCalc_canAdd_decl_s(SHRT, a, b)
#define Ofw_SafeCalc_canAdd_int(a, b) Ofw_SafeCalc_canAdd_decl_s(INT, a, b)
#define Ofw_SafeCalc_canAdd_long(a, b) Ofw_SafeCalc_canAdd_decl_s(LONG, a, b)
#define Ofw_SafeCalc_canAdd_llong(a, b) Ofw_SafeCalc_canAdd_decl_s(LLONG, a, b)
#define Ofw_SafeCalc_canAdd_int8(a, b) Ofw_SafeCalc_canAdd_decl_s(INT8, a, b)
#define Ofw_SafeCalc_canAdd_int16(a, b) Ofw_SafeCalc_canAdd_decl_s(INT16, a, b)
#define Ofw_SafeCalc_canAdd_int32(a, b) Ofw_SafeCalc_canAdd_decl_s(INT32, a, b)
#define Ofw_SafeCalc_canAdd_int64(a, b) Ofw_SafeCalc_canAdd_decl_s(INT64, a, b)
#define Ofw_SafeCalc_canAdd_intmax(a, b) Ofw_SafeCalc_canAdd_decl_s(INTMAX, a, b)
#define Ofw_SafeCalc_canAdd_ptrdiff(a, b) Ofw_SafeCalc_canAdd_decl_s(PTRDIFF, a, b)
#define Ofw_SafeCalc_canAdd_sig_atomic(a, b) Ofw_SafeCalc_canAdd_decl_s(SIG_ATOMIC, a, b)
#define Ofw_SafeCalc_canAdd_ssize(a, b) Ofw_SafeCalc_canAdd_decl_s(SSIZE, a, b)

/* (a - b >= 0) -> (a >= b) */
#define Ofw_SafeCalc_canSub_decl_u(t, a, b) \
    ((a) >= (b))

#define Ofw_SafeCalc_canSub_ushort(a, b) Ofw_SafeCalc_canSub_decl_u(USHRT, a, b)
#define Ofw_SafeCalc_canSub_uint(a, b) Ofw_SafeCalc_canSub_decl_u(UINT, a, b)
#define Ofw_SafeCalc_canSub_ulong(a, b) Ofw_SafeCalc_canSub_decl_u(ULONG, a, b)
#define Ofw_SafeCalc_canSub_ullong(a, b) Ofw_SafeCalc_canSub_decl_u(ULLONG, a, b)
#define Ofw_SafeCalc_canSub_uint8(a, b) Ofw_SafeCalc_canSub_decl_u(UINT8, a, b)
#define Ofw_SafeCalc_canSub_uint16(a, b) Ofw_SafeCalc_canSub_decl_u(UINT16, a, b)
#define Ofw_SafeCalc_canSub_uint32(a, b) Ofw_SafeCalc_canSub_decl_u(UINT32, a, b)
#define Ofw_SafeCalc_canSub_uint64(a, b) Ofw_SafeCalc_canSub_decl_u(UINT64, a, b)
#define Ofw_SafeCalc_canSub_uintmax(a, b) Ofw_SafeCalc_canSub_decl_u(UINTMAX, a, b)
#define Ofw_SafeCalc_canSub_size(a, b) Ofw_SafeCalc_canSub_decl_u(SIZE, a, b)

/* (a - b >= MIN) -> (a >= MIN + b) (b>=0) */
/* (a - b <= MAX) -> (a <= MAX + b) (b<0) */
#define Ofw_SafeCalc_canSub_decl_s(t, a, b) \
    (((b) >= 0) ? ((a) >= t##_MIN + (b)) : ((a) <= t##_MAX + (b)))

#define Ofw_SafeCalc_canSub_short(a, b) Ofw_SafeCalc_canSub_decl_s(SHRT, a, b)
#define Ofw_SafeCalc_canSub_int(a, b) Ofw_SafeCalc_canSub_decl_s(INT, a, b)
#define Ofw_SafeCalc_canSub_long(a, b) Ofw_SafeCalc_canSub_decl_s(LONG, a, b)
#define Ofw_SafeCalc_canSub_llong(a, b) Ofw_SafeCalc_canSub_decl_s(LLONG, a, b)
#define Ofw_SafeCalc_canSub_int8(a, b) Ofw_SafeCalc_canSub_decl_s(INT8, a, b)
#define Ofw_SafeCalc_canSub_int16(a, b) Ofw_SafeCalc_canSub_decl_s(INT16, a, b)
#define Ofw_SafeCalc_canSub_int32(a, b) Ofw_SafeCalc_canSub_decl_s(INT32, a, b)
#define Ofw_SafeCalc_canSub_int64(a, b) Ofw_SafeCalc_canSub_decl_s(INT64, a, b)
#define Ofw_SafeCalc_canSub_intmax(a, b) Ofw_SafeCalc_canSub_decl_s(INTMAX, a, b)
#define Ofw_SafeCalc_canSub_ptrdiff(a, b) Ofw_SafeCalc_canSub_decl_s(PTRDIFF, a, b)
#define Ofw_SafeCalc_canSub_sig_atomic(a, b) Ofw_SafeCalc_canSub_decl_s(SIG_ATOMIC, a, b)
#define Ofw_SafeCalc_canSub_ssize(a, b) Ofw_SafeCalc_canSub_decl_s(SSIZE, a, b)

/* (a * b <= MAX) -> ((b == 0) || (a <= MAX / b)) */
#define Ofw_SafeCalc_canMul_decl_u(t, a, b) \
    (((b) == 0) || ((a) <= t##_MAX / b))

#define Ofw_SafeCalc_canMul_ushort(a, b) Ofw_SafeCalc_canMul_decl_u(USHRT, a, b)
#define Ofw_SafeCalc_canMul_uint(a, b) Ofw_SafeCalc_canMul_decl_u(UINT, a, b)
#define Ofw_SafeCalc_canMul_ulong(a, b) Ofw_SafeCalc_canMul_decl_u(ULONG, a, b)
#define Ofw_SafeCalc_canMul_ullong(a, b) Ofw_SafeCalc_canMul_decl_u(ULLONG, a, b)
#define Ofw_SafeCalc_canMul_uint8(a, b) Ofw_SafeCalc_canMul_decl_u(UINT8, a, b)
#define Ofw_SafeCalc_canMul_uint16(a, b) Ofw_SafeCalc_canMul_decl_u(UINT16, a, b)
#define Ofw_SafeCalc_canMul_uint32(a, b) Ofw_SafeCalc_canMul_decl_u(UINT32, a, b)
#define Ofw_SafeCalc_canMul_uint64(a, b) Ofw_SafeCalc_canMul_decl_u(UINT64, a, b)
#define Ofw_SafeCalc_canMul_uintmax(a, b) Ofw_SafeCalc_canMul_decl_u(UINTMAX, a, b)
#define Ofw_SafeCalc_canMul_size(a, b) Ofw_SafeCalc_canMul_decl_u(SIZE, a, b)

/* (a * b <= MAX) -> (a <= MAX / b) (a>0 && b>0)  */
/* (a * b >= MIN) -> (b >= MIN / a) (a>0 && b<=0) */
/* (a * b >= MIN) -> (a >= MIN / b) (a<=0 && b>0) */
/* (a * b <= MAX) -> (b >= MAX / a) (a<0 && b<=0) */
#define Ofw_SafeCalc_canMul_decl_s(t, a, b) \
    (((a) > 0) ? (((b) > 0) ? ((a) <= t##_MAX / (b)) \
                            : ((b) >= t##_MIN / (a))) \
               : (((b) > 0) ? ((a) >= t##_MIN / (b)) \
                            : ((a) == 0 || (b) >= t##_MAX / (a))))

#define Ofw_SafeCalc_canMul_short(a, b) Ofw_SafeCalc_canMul_decl_s(SHRT, a, b)
#define Ofw_SafeCalc_canMul_int(a, b) Ofw_SafeCalc_canMul_decl_s(INT, a, b)
#define Ofw_SafeCalc_canMul_long(a, b) Ofw_SafeCalc_canMul_decl_s(LONG, a, b)
#define Ofw_SafeCalc_canMul_llong(a, b) Ofw_SafeCalc_canMul_decl_s(LLONG, a, b)
#define Ofw_SafeCalc_canMul_int8(a, b) Ofw_SafeCalc_canMul_decl_s(INT8, a, b)
#define Ofw_SafeCalc_canMul_int16(a, b) Ofw_SafeCalc_canMul_decl_s(INT16, a, b)
#define Ofw_SafeCalc_canMul_int32(a, b) Ofw_SafeCalc_canMul_decl_s(INT32, a, b)
#define Ofw_SafeCalc_canMul_int64(a, b) Ofw_SafeCalc_canMul_decl_s(INT64, a, b)
#define Ofw_SafeCalc_canMul_intmax(a, b) Ofw_SafeCalc_canMul_decl_s(INTMAX, a, b)
#define Ofw_SafeCalc_canMul_ptrdiff(a, b) Ofw_SafeCalc_canMul_decl_s(PTRDIFF, a, b)
#define Ofw_SafeCalc_canMul_sig_atomic(a, b) Ofw_SafeCalc_canMul_decl_s(SIG_ATOMIC, a, b)
#define Ofw_SafeCalc_canMul_ssize(a, b) Ofw_SafeCalc_canMul_decl_s(SSIZE, a, b)

#endif /* Ofw_SafeCalc_H_ */
