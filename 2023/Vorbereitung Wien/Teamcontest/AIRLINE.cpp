#include <assert.h>
#include <limits.h>
#include <iostream>
#include <vector>

#pragma GCC optimize "-O3"

#define NBITS 20

typedef long long llong;

int N;
struct node {
    std::vector<node*> edges;

    bool vis;
    int height;
    int entry, exit;

    node *lift[NBITS];

    int val;
    node *cdownA, *cdownB;
} nodes[1000005];

int dfs(node *n, int t = 0, node *p = NULL, int h = 0) {
    if(n->vis) return t;
    n->vis = true;
    n->height = h;

    n->lift[0] = p ? p : n;
    for(int i = 1; i < NBITS; i++) n->lift[i] = n->lift[i-1]->lift[i-1];

    n->entry = t++;
    for(node *u : n->edges) t = dfs(u, t, n, h+1);
    n->exit = t++;
    assert((n->exit - n->entry) % 2 == 1);

    return t;
}

static inline bool isansc(node *p, node *c) {
    return p->entry <= c->entry && c->exit <= p->exit;
}

static inline int numchilds(node *n) {
    return (n->exit - n->entry) / 2;
}

static inline node *liftlca(node *a, node *b) {
    if(isansc(a, b)) return a;
    if(isansc(b, a)) return b;
    for(int i = NBITS-1; i >= 0; i--){
        if(!isansc(a->lift[i], b)) a = a->lift[i];
    }
    a = a->lift[0];
    assert(isansc(a, b));
    return a;
}

struct cycle {
    node *a, *b, *lca;
    int len;

    cycle(node *a, node *b) : a(a), b(b), lca(liftlca(a, b)) {
        len = 1 + (a->height - lca->height) + (b->height - lca->height);

        a->cdownA = NULL;
        for(node *n = a; n != lca; n = n->lift[0]) {
            n->lift[0]->cdownA = n;
            n->val = numchilds(n)+1 - (n->cdownA ? numchilds(n->cdownA)+1 : 0);
        }

        b->cdownB = NULL;
        for(node *n = b; n != lca; n = n->lift[0]) {
            n->lift[0]->cdownB = n;
            n->val = numchilds(n)+1 - (n->cdownB ? numchilds(n->cdownB)+1 : 0);
        }

        lca->val = N;
        if(lca->cdownA) lca->val -= numchilds(lca->cdownA)+1;
        if(lca->cdownB) lca->val -= numchilds(lca->cdownB)+1;
    }

    inline bool contains(node *n) const {
        if(n == a || n == b || n == lca) return true;
        return !isansc(n, lca) && (isansc(n, a) || isansc(n, b));
    }

    inline node *prev(node *n) const {
        if(n == a) return b;
        if(!isansc(n, a)) return n->lift[0];
        return n->cdownA;
    }

    inline node *next(node *n) const {
        if(n == b) return a;
        if(!isansc(n, b)) return n->lift[0];
        return n->cdownB;
    }

    inline int getval(node *n) const {
        int v = 1;
        if(n == lca) v += N - numchilds(n) - 1;
        for(node *e : n->edges) {
            if(!isansc(e, n) && !contains(e))
                v += numchilds(e)+1;
        }
        return v;
    }
};

static int readint() {
    char c;
    while(!isalnum(c = getchar_unlocked()));

    int r = 0;
    do {
        r *= 10;
        r += c - '0';
    } while(isalnum(c = getchar_unlocked()));

    return r;
}

int main() {
    setvbuf(stdin, NULL, _IOFBF, 65536);
    setvbuf(stdout, NULL, _IOFBF, 65536);

    int Q;
    scanf("%d %d\n", &N, &Q);

    for(int i = 0; i < N-1; i++) {
        int u = readint(), v = readint();
        nodes[u-1].edges.push_back(nodes + v-1);
        nodes[v-1].edges.push_back(nodes + u-1);
    }

    dfs(nodes);

    for(int i = 0; i < Q; i++) {
        node *a = nodes + readint()-1, *b = nodes + readint()-1;
        cycle c(a, b);

        static node *bs[1000005];
        bs[0] = b;

        int ws = (c.len-1) / 2;
        for(int j = 1; j <= ws; j++) bs[j] = c.prev(bs[j-1]);

        node *s = a;
        llong res = 0;
        llong ac = a->val;
        for(int j = ws-1; j >= 0; j--) {
            res += ac * bs[j]->val;
            s = c.next(s);
            ac += s->val;
        }
        printf("%lld\n", res);
    }
}