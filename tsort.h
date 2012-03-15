#ifndef TSORT_H
#define TSORT_H

/*
 * topological sort module.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tsort_e {
	TSORT_EOK = 0,
	TSORT_EINVAL,
	TSORT_ENOMEM,
	TSORT_ECYCLIC,
} tsort_e;

typedef enum tsort_mark_t {
	TSORT_MARK_NONE,
	TSORT_MARK_VISITING,
	TSORT_MARK_VISITED
} tsort_mark_t;

typedef int (*tsort_callback_t)(unsigned int index);

typedef struct tsort_t tsort_t;

tsort_e tsort_init(tsort_t **self, unsigned int len, tsort_callback_t cb);
tsort_e tsort_free(tsort_t *self);
tsort_e tsort_mark(tsort_t *self, unsigned int from, unsigned int to);
tsort_e tsort_sort(tsort_t *self);

#ifdef __cplusplus
}
#endif

#endif /* TSORT_H */
