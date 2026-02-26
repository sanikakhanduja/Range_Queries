#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    // Original array
    vector<long long> arr(n);

    // Prefix array where:
    // prefix[i] = sum of elements from index 0 to i
    vector<long long> prefix(n);

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Build prefix sum array
    // TC: O(n)
    prefix[0] = arr[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }

    // Answer queries
    // Each query in O(1)
    while(q--) {
        int l, r;   // 0-based indexing
        cin >> l >> r;

        long long ans = prefix[r];

        // If l > 0 subtract sum till l-1
        if(l > 0) {
            ans -= prefix[l-1];
        }

        cout << ans << endl;
    }

    return 0;
}