/*============================================================================*
 * Copyright (c) 2012 Andrew T. Canaday
 *
 * This file is part of ymo_assert, which is licensed under the MIT license.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *----------------------------------------------------------------------------*/
#ifndef YMO_ASSERT_H
#define YMO_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YMO_ASSERT_VERBOSE
#define YMO_ASSERT_VERBOSE 0
#endif /* YMO_ASSERT_VERBOSE */

#ifndef YMO_ASSERT_QUIET
# define YMO_ASSERT_QUIET 0
#endif /* YMO_ASSERT_QUIET */



/*--------------------------------------------------
 *              Convenience Macros:
 *--------------------------------------------------*/
#ifndef ymo_assert_test_abort
# if defined(YMO_TEST_ABORT_RETURN) && (YMO_TEST_ABORT_RETURN==1)
#  define ymo_assert_test_abort() return 0
# else
/** Function used to abort test execution */
#  define ymo_assert_test_abort() exit(-1)
# endif /*YMO_TEST_ABORT_RETURN */
#endif /* ymo_assert_test_abort */


#if YMO_ASSERT_QUIET == 0
/** Function used to report test failure and abort */
# define ymo_assert_test_fail(test_desc) \
    fprintf(stderr, "\n\033[00;31mFAIL: %s (%s:%s:%i)\033[00;m\n", \
        test_desc, __FILE__, __func__, __LINE__); \
    ymo_assert_test_abort();
#else
# define ymo_assert_test_fail(test_desc) ((void)0)
#endif /* YMO_ASSERT_QUIET */


#if (YMO_ASSERT_VERBOSE == 1) && (YMO_ASSERT_QUIET != 1)
/** Function used to report test success, if verbose is defined */
#define ymo_assert_test_pass(test_desc) \
    fprintf(stderr, "\033[00;32mPASS: %s (%s:%s:%i)\033[00;m\n", \
        test_desc, __FILE__, __func__, __LINE__);
#else
#define ymo_assert_test_pass(test_desc) ((void)0)
#endif /* YMO_ASSERT_VERBOSE */


/** Convenience macro used to execute tests and report failure */
#ifndef NDEBUG
#define ymo_assert_test(test_cond, test_desc) \
    do { \
        if( !(test_cond) ) { \
            ymo_assert_test_fail(test_desc); \
        }; \
        ymo_assert_test_pass(test_desc); \
    } while(0)
#else
#define ymo_assert_test(test_cond, test_desc) ((void)0)
#endif /* NDEBUG */


/*-------------------------------------
           General Assertion
 *-------------------------------------*/
#define ymo_assert( test_cond ) ymo_assert_test(test_cond, #test_cond)


/*------------------------------
 *       String Assertions
 *------------------------------*/
/** String equality:
 *  - pass if two non-null strings are lexicographically equal
 *  - pass if both strings are the NULL pointer
 */
#define ymo_assert_str_eq( x, y ) ymo_assert_test( \
        (x && y && !strcmp((const char*)x,(const char*)y)) \
            || ((x == NULL) && (y == NULL)), #x " == " #y )


/** String inequality
 *  - pass if two non-null strings are not lexicographically equal
 *  - pass if one string is NULL and the other isn't
 */
#define ymo_assert_str_ne( x, y ) ymo_assert_test( \
        (x && y && strcmp((const char*)x,(const char*)y)) \
        || ((x == NULL || y == NULL) && (x!=y)), #x " != " #y )


/** Substring matching: pass if x is a substring of y */
#define ymo_assert_str_contains( x, y ) ymo_assert_test( \
        x && y && strstr(x, y) != NULL, #x " contains " #y)


/** Prefix matching: pass if x starts with y */
#define ymo_assert_str_startswith( x, y ) ymo_assert_test( \
        x && y && ((const char*)strstr(x, y)) == (const char*)x, \
        #x " starts with " #y)


#endif /* YMO_ASSERT_H */
/* EOF */

