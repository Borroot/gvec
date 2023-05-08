#include "gvec.h"
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

int
gveci_init(gveci *v, size_t size, size_t bytes) {
	v->buffer = (char *)calloc(size, bytes);

	if (v->buffer == NULL)
		return ENOMEM;

	v->size = size;
	v->bytes = bytes;
	v->capacity = size;

	return 0;
}

void
gveci_free(gveci *v) {
	free(v->buffer);
	v->buffer = NULL;
}

void *
gveci_get(gveci *v, size_t index) {
	return (void *)&v->buffer[index * v->bytes];
}


void
gveci_set(gveci *v, size_t index, void *element) {
	for (size_t offset = 0; offset < v->bytes; offset++)
		v->buffer[index * v->bytes + offset] = ((char *)element)[offset];
}
