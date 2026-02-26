#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree (1-based indexing)
vector<long long> tree;
int n;

/*
 Function: add(k, x)
 Increases element at index k by x.
 
 Why O(log n)?
 Because we move upward in tree by:
 k += (k & -k)
 which removes the lowest set bit.
*/
void add(int k, long long x) {
    while(k <= n) {
        tree[k] += x;
        k += (k & -k);
    }
}

/*
 Function: sum(k)
 Returns sum from index 1 to k.
 
 Why O(log n)?
 Because we jump using:
 k -= (k & -k)
 which removes lowest set bit each time.
*/
long long sum(int k) {
    long long s = 0;
    while(k >= 1) {
        s += tree[k];
        k -= (k & -k);
    }
    return s;
}

int main() {
    int q;
    cin >> n >> q;

    tree.assign(n+1, 0);

    // Build tree
    // Each insertion takes O(log n)
    for(int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        add(i, x);
    }

    /*
    Query types:
    1 idx val   → increase element at idx by val
    2 l r       → range sum query
    */

    while(q--) {
        int type;
        cin >> type;

        if(type == 1) {
            int idx;
            long long val;
            cin >> idx >> val;
            add(idx, val);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l-1) << endl;
        }
    }

    return 0;
}