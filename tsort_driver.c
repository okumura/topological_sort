#include "tsort.h"
#include <stdio.h>

int on_visited(unsigned int to) {
	printf("%d, ", to);
}

int main() {
	tsort_t *t = NULL;
	tsort_e e;

	if ((e = tsort_init(&t, 3, on_visited))) {
		printf("tsort_init() failed(%d).\n", e);
		return 1;
	} else {

		e = tsort_mark(t, 0, 1);
		e = tsort_mark(t, 1, 2);

		switch ((e = tsort_sort(t))) {
		case TSORT_ECYCLIC:
			printf("cyclic!\n");
			break;
		case TSORT_EOK:
			printf("not cyclic.\n");
			break;
		default:
			printf("tsort_sort() failed(%d).\n", e);
			break;
		}

		tsort_free(t);

		return 0;
	}
}
