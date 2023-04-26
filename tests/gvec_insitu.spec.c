#include <criterion/criterion.h>
#include <gvec_insitu.h>
#include <stdint.h>
#include <errno.h>

Test(gvec_insitu, init_success)
{
	size_t size = 10;
	size_t bytes = sizeof(int);

	gveci v;
	int err = gveci_init(&v, size, bytes);

	cr_assert_eq(err, 0);
	cr_assert_neq(v.buffer, NULL);

	cr_assert_eq(v.size, size);
	cr_assert_eq(v.bytes, bytes);
	cr_assert_eq(v.capacity, size * bytes);

	gveci_free(&v);

	cr_assert_eq(v.buffer, NULL);
}

Test(gvec_insitu, init_fail)
{
	size_t size = SIZE_MAX;
	size_t bytes = sizeof(int);

	gveci v;
	int err = gveci_init(&v, size, bytes);

	cr_assert_eq(err, ENOMEM);
	cr_assert_eq(v.buffer, NULL);

	cr_assert_eq(v.size, NULL);
	cr_assert_eq(v.bytes, NULL);
	cr_assert_eq(v.capacity, NULL);

	gveci_free(&v);

	cr_assert_eq(v.buffer, NULL);
}
