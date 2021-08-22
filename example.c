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

#include "ymo_assert.h"


/*-------------------------------------------------------------*
 * Tests:
 *-------------------------------------------------------------*/
void basic_assertions(void)
{
    int two = 2;
    int three = 3;
    ymo_assert(two < three);
    ymo_assert(10 > 1);
    ymo_assert(1 <= two);
    ymo_assert(two <= two);
    ymo_assert(three >= two);
    ymo_assert(three >= three);
    ymo_assert( ((164 % 100) & 0x40) == ((6-4) << 5) );
    ymo_assert(two == two);
    ymo_assert(two != three);
    return;
}


void string_assertions(void)
{
    const char* this_str = "This";
    const char* this_str_cpy = strdup(this_str);
    const char* that_str = "That";
    const char* null_str = NULL;
    const char* haystack = "prefix string";
    const char* needle = "pre";

    ymo_assert_str_eq("This", this_str);
    ymo_assert_str_eq(that_str, strdup(that_str));
    ymo_assert_str_eq(this_str, this_str_cpy);
    ymo_assert_str_eq(null_str, NULL);
    ymo_assert_str_ne(this_str, that_str);
    ymo_assert_str_ne(this_str, null_str);
    ymo_assert_str_ne(this_str, NULL);
    ymo_assert_str_contains("the subway is neat", "sub");
    ymo_assert_str_startswith(haystack, needle);
    return;
}

/*-------------------------------------------------------------*
 * Main:
 *-------------------------------------------------------------*/
int main(int argc, char** argv)
{
    basic_assertions();
    string_assertions();
    return 0;
}
