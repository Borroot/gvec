#ifndef GVEC_H_
#define GVEC_H_

#include <stddef.h>

/* Generic vector in situ */
typedef struct {
	char   *buffer;
	size_t  size;     /* current size of the vector  */
	size_t  capacity; /* capacity of the vector      */
	size_t  bytes;    /* number of bytes per element */
} gveci;

int   gveci_init(gveci *, size_t size, size_t bytes);
void  gveci_free(gveci *);

void *gveci_get(gveci *, size_t index);
void  gveci_set(gveci *, size_t index, void *element);

void *gveci_pop(gveci *);
void  gveci_push(gveci *, void *element);

#endif /* GVEC_H_ */
