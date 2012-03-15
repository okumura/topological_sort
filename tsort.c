#include "tsort.h"
#include <stdio.h>

#include <stdio.h>  /* for printf() */
#include <stdlib.h> /* for malloc(), free() */

struct tsort_t {
	unsigned int length;
	unsigned char *adjacent;   /* adjacent[length][length] */
	tsort_mark_t *visited;     /* visited[length] */
	tsort_callback_t callback; /* call on sorting */
};

static int visit(tsort_t *self, int to);

tsort_e tsort_init(tsort_t **self, unsigned int len, tsort_callback_t cb) {
	tsort_t *tmp = NULL;

	if (!self) {
		return TSORT_EINVAL;
	} else if (*self) {
		return TSORT_EINVAL;
	} else if (!len) {
		return TSORT_EINVAL;
	} else if (!cb) {
		return TSORT_EINVAL;
	} else if (!(tmp = malloc(sizeof(tsort_t)))) {
		return TSORT_ENOMEM;
	} else if (!(tmp->adjacent = malloc(len * len))) {
		free(tmp);
		return TSORT_ENOMEM;
	} else if (!(tmp->visited = malloc(sizeof(tsort_mark_t) * len))) {
		free(tmp->adjacent);
		free(tmp);
		return TSORT_ENOMEM;
	} else {
		tmp->length = len;
		tmp->callback = cb;
		*self = tmp;
		return TSORT_EOK;
	}
}

tsort_e tsort_free(tsort_t *self) {
	if (!self) {
		return TSORT_EINVAL;
	} else {
		free(self->visited);
		free(self->adjacent);
		free(self);
		return TSORT_EOK;
	}
}

tsort_e tsort_mark(tsort_t *self, unsigned int from, unsigned int to) {
	if (!self) {
		return TSORT_EINVAL;
	} else if (self->length <= from) {
		return TSORT_EINVAL;
	} else if (self->length <= to) {
		return TSORT_EINVAL;
	} else {
		/* accept from == to. */
		self->adjacent[from * self->length + to] = 1;
		return TSORT_EOK;
	}
}

tsort_e tsort_sort(tsort_t *self) {
	int from, to;

	for (to = 0; to < self->length; to++) {
		self->visited[to] = TSORT_MARK_NONE;
	}

	for (to = 0; to < self->length; to++) {
		if (visit(self, to)) {
			return TSORT_ECYCLIC;
		}
	}

	return TSORT_EOK;
}

static int visit(tsort_t *self, int to) {
	int j;

	switch (self->visited[to]) {
	case TSORT_MARK_VISITING:
		return 1;
	case TSORT_MARK_VISITED:
		return 0;
	default:
		self->visited[to] = TSORT_MARK_VISITING;

		for (j = 0; j < self->length; j++) {
			if (!self->adjacent[to * self->length + j]) {
				continue;
			} else if (visit(self, j)) {
				return 1;
			}
		}

		self->visited[to] = TSORT_MARK_VISITED;

		self->callback(to);

		return 0;
	}
}

