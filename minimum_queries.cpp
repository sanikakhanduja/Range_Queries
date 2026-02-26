#include <bits/stdc++.h>
using namespace std;

/*
 Sparse Table for Range Minimum Query (RMQ)

 Supports:
    - Range minimum query in O(1)
 Does NOT support:
    - Updates

 Preprocessing: O(n log n)
 Query: O(1)
 Space: O(n log n)
*/

int main() {

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    /*
     K = maximum power of 2 needed
     If n = 16 → log2(16) = 4
     So we need columns 0..4
    */
    int K = log2(n) + 1;

    /*
     st[i][j] = minimum in range starting at i
                of length 2^j

     So:
        st[i][0] = arr[i]
        st[i][1] = min of 2 elements
        st[i][2] = min of 4 elements
        st[i][3] = min of 8 elements
    */
    vector<vector<int>> st(n, vector<int>(K));

    // Base case: intervals of length 1
    for(int i = 0; i < n; i++) {
        st[i][0] = arr[i];
    }

    /*
     Build table

     For each power j:
         combine two blocks of size 2^(j-1)

     st[i][j] =
        min( st[i][j-1],
             st[i + 2^(j-1)][j-1] )
    */
    for(int j = 1; j < K; j++) {
        for(int i = 0; i + (1 << j) <= n; i++) {
            st[i][j] = min(
                st[i][j-1],
                st[i + (1 << (j-1))][j-1]
            );
        }
    }

    /*
     Process queries
     Each query in O(1)
    */
    while(q--) {
        int l, r;  // 0-based indexing
        cin >> l >> r;

        int len = r - l + 1;

        // Largest power of 2 <= len
        int k = log2(len);

        int ans = min(
            st[l][k],
            st[r - (1 << k) + 1][k]
        );

        cout << ans << endl;
    }

    return 0;
}