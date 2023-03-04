#include <assert.h>
#include <iostream>

typedef long long llong;

int ivals[200005];

struct node {
    int l, r;
    node *lc, *rc, *p;
    llong sum;
} nodes[400005], *nnode = nodes, *cnodes[200005];

node *build(int l, int r, node *p=NULL) {
    node *n = nnode++;
    n->l = l;
    n->r = r;
    n->p = p;

    if(l == r-1) {
        n->lc = n->rc = NULL;
        n->sum = ivals[l];
        cnodes[l] = n;
    } else {
        int m = l + (r-l)/2;
        n->lc = build(l, m, n);
        n->rc = build(m, r, n);
        n->sum = n->lc->sum + n->rc->sum;
    }

    return n;
}

llong query(node *n, int l, int r) {
    if(l <= n->l && n->r <= r) return n->sum;
    if(r <= n->l || n->r <= l) return 0;
    return query(n->lc, l, r) + query(n->rc, l, r);
}

void update(int i, int v) {
    node *c = cnodes[i];
    c->sum = v;
    for(node *n = c->p; n; n = n->p) n->sum = n->lc->sum + n->rc->sum;
}

int binsearch(node *t, int N, int l, int r) {
    if(l == r-1) return l;
    int m = l + (r-l)/2;
    if(query(t, m, N) < query(t, 0, m)) return binsearch(t, N, l, m);
    else return binsearch(t, N, m, r);
}

int calc(node *t, int N) {
    int i = binsearch(t, N, 0, N);
    int r = (int) std::abs(query(t, 0, i) - query(t, i, N));
    if(i < N-1) r = std::min(r, (int) std::abs(query(t, 0, i+1) - query(t, i+1, N)));
    return r;
}

int main() {
    int N;
    std::cin >> N;
    N--;

    for(int i = 0; i < N; i++) std::cin >> ivals[i];
    node *t = build(0, N);

    std::cout << calc(t, N) << std::endl;

    int K;
    std::cin >> K;
    for(int i = 0; i < K; i++) {
        int j, nt;
        std::cin >> j >> nt;
        update(j-1, nt);
        std::cout << calc(t, N) << std::endl;
    }

    return 0;
}