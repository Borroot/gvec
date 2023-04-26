#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <gvec_insitu.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

Test(gvec_insitu, init_success)
{
	size_t size = 10;
	size_t bytes = sizeof(int);

	gveci v;
	int err = gveci_init(&v, size, bytes);

	cr_assert(eq(int, err, 0));
	cr_assert(ne(ptr, v.buffer, NULL));

	cr_assert(eq(sz, v.size, size));
	cr_assert(eq(sz, v.bytes, bytes));
	cr_assert(eq(sz, v.capacity, size));

	gveci_free(&v);

	cr_assert(eq(ptr, v.buffer, NULL));
}

Test(gvec_insitu, init_fail)
{
	size_t size = SIZE_MAX;
	size_t bytes = sizeof(int);

	gveci v;
	int err = gveci_init(&v, size, bytes);

	cr_assert(eq(int, err, ENOMEM));
	cr_assert(eq(ptr, v.buffer, NULL));

	gveci_free(&v);

	cr_assert(eq(ptr, v.buffer, NULL));
}

Test(gvec_insitu, set_sz)
{
	size_t size = 10;
	size_t bytes = sizeof(size_t);

	size_t max = SIZE_MAX; /* bytes * 8 number of 1's */
	size_t min = 0;

	gveci v;
	gveci_init(&v, size, bytes);

	/* populate the vector alternating SIZE_MAX and 0 */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			gveci_set(&v, i, (void *)&max);
		else
			gveci_set(&v, i, (void *)&min);
	}

	/* check the buffer for alternating 1's and 0's */
	for (size_t i = 0; i < size * bytes; i++) {
		if ((i / bytes) % 2 == 0)
			cr_assert(eq(chr, v.buffer[i], 0xff));
		else
			cr_assert(eq(chr, v.buffer[i], 0x00));
	}

	gveci_free(&v);
}

Test(gvec_insitu, get_sz)
{
	size_t size = 10;
	size_t bytes = sizeof(size_t);

	size_t max = SIZE_MAX; /* bytes * 8 number of 1's */
	size_t min = 0;

	gveci v;
	gveci_init(&v, size, bytes);

	/* populate the vector alternating SIZE_MAX and 0 */
	for (size_t i = 0; i < size * bytes; i++) {
		if ((i / bytes) % 2 == 0)
			v.buffer[i] = 0xff;
		else
			v.buffer[i] = 0x00;
	}

	/* check the buffer for alternating 1's and 0's */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			cr_assert(eq(sz, *(size_t *)gveci_get(&v, i), max));
		else
			cr_assert(eq(sz, *(size_t *)gveci_get(&v, i), min));
	}

	gveci_free(&v);
}

Test(gvec_insitu, set_and_get_sz)
{
	size_t size = 10;
	size_t bytes = sizeof(size_t);

	size_t max = SIZE_MAX; /* bytes * 8 number of 1's */
	size_t min = 0;

	gveci v;
	gveci_init(&v, size, bytes);

	/* populate the vector alternating SIZE_MAX and 0 */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			gveci_set(&v, i, (void *)&max);
		else
			gveci_set(&v, i, (void *)&min);
	}

	/* check the buffer for alternating 1's and 0's */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			cr_assert(eq(sz, *(size_t *)gveci_get(&v, i), max));
		else
			cr_assert(eq(sz, *(size_t *)gveci_get(&v, i), min));
	}

	gveci_free(&v);
}

Test(gvec_insitu, set_and_get_char)
{
	size_t size = 10;
	size_t bytes = sizeof(unsigned char);

	size_t max = UCHAR_MAX; /* bytes * 8 number of 1's */
	size_t min = 0;

	gveci v;
	gveci_init(&v, size, bytes);

	/* populate the vector alternating SIZE_MAX and 0 */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			gveci_set(&v, i, (void *)&max);
		else
			gveci_set(&v, i, (void *)&min);
	}

	/* check the buffer for alternating 1's and 0's */
	for (size_t i = 0; i < size; i++) {
		if (i % 2 == 0)
			cr_assert(eq(chr, *(size_t *)gveci_get(&v, i), max));
		else
			cr_assert(eq(chr, *(size_t *)gveci_get(&v, i), min));
	}

	gveci_free(&v);
}
