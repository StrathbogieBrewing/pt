// MIT License

// Copyright (c) 2023 Strathbogie Brewing Company

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef CTEST_H
#define CTEST_H
    void ctest_callback(const char* name, int line); 
    #ifdef CTEST_ENABLED
        #define CTEST_DO_STRINGIFY(x) #x
        #define CTEST_STRINGIFY(s) CTEST_DO_STRINGIFY(s)
        #define CTEST_RUN(function) do { \
            void ctest_##function##_unit_test(const char* name); \
            ctest_##function##_unit_test(CTEST_STRINGIFY(function)); } while (0)
        #define CTEST_FUNCTION(function) \
            void ctest_##function##_unit_test(const char* name)
        #define CTEST_ASSERT(assertion) do { if (assertion) ctest_callback(name, __LINE__); else ctest_callback(name, -(__LINE__));  } while (0)
    #else   // CTEST_ENABLED - DISABLE AND REMOVE FROM BUILD
        #define CTEST_RUN(function)
        #define CTEST_FUNCTION(function) static inline __attribute__((always_inline)) void ctest_##function##_unit_test(const char* name)  
        #define CTEST_ASSERT(assertion)
    #endif  // CTEST_ENABLED
#endif  // CTEST_H