#include <stdio.h>
#include <stdlib.h>

#include "../pt.h"

#include "ctest.h"

typedef struct pt_counter_ctx_t {
    PT_CONTROL;
    uint8_t counter;
} pt_counter_ctx_t;

PT_THREAD pt_counter(pt_counter_ctx_t *ctx) {
    PT_BEGIN(ctx);
    ctx->counter = 10;
    PT_WAIT_WHILE(ctx, ++(ctx->counter) < 13);
    PT_YIELD(ctx);
    ctx->counter = 20;
    PT_END(ctx);
}

CTEST_FUNCTION(pt_tests) {
    pt_counter_ctx_t ctx = {0};

    bool busy = pt_counter(&ctx);
    CTEST_ASSERT(busy);
    CTEST_ASSERT(ctx.counter == 11);
    
    busy = pt_counter(&ctx);
    CTEST_ASSERT(busy);
    CTEST_ASSERT(ctx.counter == 12);

    busy = pt_counter(&ctx);
    CTEST_ASSERT(busy);
    CTEST_ASSERT(ctx.counter == 13);

    busy = pt_counter(&ctx);
    CTEST_ASSERT(!busy);
    CTEST_ASSERT(ctx.counter == 20);

    busy = pt_counter(&ctx);
    CTEST_ASSERT(busy);
    CTEST_ASSERT(ctx.counter == 11);
}

/* Must define a call back function to log test results */
void ctest_callback(const char *name, int line) {
    if (line < 0) {
        printf("CTEST : fail in %s line %d\n", name, -line);
    } else {
        printf("CTEST : pass in %s line %d\n", name, line);
    }
}

/* Process that runs the tests */
int main(int argc, char *argv[]) {
    CTEST_RUN(pt_tests);
    return EXIT_SUCCESS;
}
