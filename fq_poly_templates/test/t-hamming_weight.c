/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Sebastian Pancratz 
    Copyright (C) 2012 Andres Goens
    Copyright (C) 2013 Mike Hansen

******************************************************************************/


#ifdef T

#include "templates.h"

#include <stdio.h>
#include <stdlib.h>

#include "ulong_extras.h"
#include "long_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("hamming_weight... ");
    fflush(stdout);

    /* Check consistency */
        for (i = 0; i < 2000; i++)
    {
        slong len;
        TEMPLATE(T, ctx_t) ctx;
	long w1,w2;
        TEMPLATE(T, poly_t) a, b;

        len = n_randint(state, 15) + 1;
        TEMPLATE(T, ctx_randtest)(ctx, state);
        TEMPLATE(T, poly_init)(a, ctx);
        TEMPLATE(T, poly_init)(b, ctx);

        TEMPLATE(T, poly_randtest)(a, state, len, ctx);
	TEMPLATE(T, poly_set)(b, a, ctx);

	w1 = TEMPLATE(T, poly_hamming_weight)(a, ctx);
	w2 = TEMPLATE(T, poly_hamming_weight)(b, ctx);

        result = (w1 == w2);
        if (!result)
        {
            flint_printf("FAIL:\n\n");
            flint_printf("a = "), TEMPLATE(T, poly_print_pretty)(a, "X", ctx), flint_printf("\n");
            flint_printf("b = "), TEMPLATE(T, poly_print_pretty)(b, "X", ctx), flint_printf("\n");
	    flint_printf("w1 = %wd \n w2 = %wd \n",w1,w2);
            abort();
        }

        TEMPLATE(T, poly_clear)(a, ctx);
        TEMPLATE(T, poly_clear)(b, ctx);


        TEMPLATE(T, ctx_clear)(ctx);
	}

    /* Check that wt(a+b) \leq wt(a) + wt(b) */
        for (i = 0; i < 2000; i++)
    {
        slong len;
        TEMPLATE(T, ctx_t) ctx;
	long w1,w2,wsum;
        TEMPLATE(T, poly_t) a, b, c;

        len = n_randint(state, 15) + 1;
        TEMPLATE(T, ctx_randtest)(ctx, state);
        TEMPLATE(T, poly_init)(a, ctx);
        TEMPLATE(T, poly_init)(b, ctx);
        TEMPLATE(T, poly_init)(c, ctx);

        TEMPLATE(T, poly_randtest)(a, state, len, ctx);
        TEMPLATE(T, poly_randtest)(b, state, len, ctx);
	TEMPLATE(T, poly_add)(c,a,b,ctx);
	
	w1 = TEMPLATE(T, poly_hamming_weight)(a, ctx);
	w2 = TEMPLATE(T, poly_hamming_weight)(b, ctx);
	wsum = TEMPLATE(T, poly_hamming_weight)(c, ctx);
	
        result = (wsum <= w1+w2);
        if (!result)
        {
            flint_printf("FAIL:\n\n");
            flint_printf("a = "), TEMPLATE(T, poly_print_pretty)(a, "X", ctx), flint_printf("\n");
            flint_printf("b = "), TEMPLATE(T, poly_print_pretty)(b, "X", ctx), flint_printf("\n");
	    flint_printf("w1 = %wd \n w2 = %wd \n wsum = %wd",w1,w2,wsum);
            abort();
        }

        TEMPLATE(T, poly_clear)(a, ctx);
        TEMPLATE(T, poly_clear)(b, ctx);
        TEMPLATE(T, poly_clear)(c, ctx);


        TEMPLATE(T, ctx_clear)(ctx);
	} 

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}



#endif
