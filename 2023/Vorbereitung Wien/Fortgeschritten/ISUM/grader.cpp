#include "ISUM.h"
#include <cstdio>

int main() {
	int N, Q, qu, p, q, v, query_type;
	scanf("%d %d", &N, &Q);
	
	init(N);
	for(qu = 0; qu < Q; qu++) {
		scanf("%d", &query_type);
		if (query_type == 0) {
			scanf("%d %d %d", &p, &q, &v);
			update(p, q, v);
		} else if (query_type == 1) {
			scanf("%d %d", &p, &q);
			printf("%lld\n", query(p, q));
		}
	}
	
	return 0;
}
