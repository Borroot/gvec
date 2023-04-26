#include "gvec_insitu.h"
#include <stdlib.h>
#include <errno.h>

int
gveci_init(gveci *v, size_t size, size_t bytes) {
	v->buffer = calloc(size, bytes);

	if (v->buffer == NULL)
		return ENOMEM;

	v->size = size;
	v->bytes = bytes;
	v->capacity = size * bytes;

	return 0;
}

void  gveci_free(gveci *v) {
	free(v->buffer);
	v->buffer = NULL;
}

void *gveci_get(gveci *, size_t index);
void  gveci_set(gveci *, size_t index, void *element);

void *gveci_pop(gveci *);
void  gveci_push(gveci *, void *element);
