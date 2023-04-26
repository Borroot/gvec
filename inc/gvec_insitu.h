#ifndef GVEC_INSITU_H_
#define GVEC_INSITU_H_

#include <stddef.h>

/* Generic VECtor In situ */
typedef struct {
	void  *buffer;
	size_t size;     /* current size of the vector      */
	size_t capacity; /* capacity of the vector in bytes */
	size_t bytes;    /* number of bytes per element     */
} gveci;

int   gveci_init(gveci *, size_t size, size_t bytes);
void  gveci_free(gveci *);

void *gveci_get(gveci *, size_t index);
void  gveci_set(gveci *, size_t index, void *element);

void *gveci_pop(gveci *);
void  gveci_push(gveci *, void *element);

#endif /* GVEC_INSITU_H_ */
