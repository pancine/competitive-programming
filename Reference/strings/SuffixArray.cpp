// Returns suffixArray that each index of the array is the starting of the suffix which is i’th in the sorted suffix array
// Complexity: O(n * log(n))
vector<int> suffixArray(string s) {
    s.push_back('$');
    int n = (int)s.size();
    const int alphabet = 256;

    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

    for (auto ch : s) cnt[ch]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);

    vector<int> p_new(n), c_new(n);

    for (int k = 0; (1 << k) < n; ++k) {
        int classes = c[p[n - 1]] + 1;
        fill(cnt.begin(), cnt.begin() + classes, 0);

        for (int i = 0; i < n; i++) p_new[i] = (p[i] - (1 << k) + n) % n;
        for (int i = 0; i < n; i++) cnt[c[p_new[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[p_new[i]]]] = p_new[i];

        c_new[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            pair<int, int> curr = { c[p[i]], c[(p[i] + (1 << k)) % n] };
            pair<int, int> prev = { c[p[i - 1]], c[(p[i-1] + (1 << k)) % n] };

            c_new[p[i]] = c_new[p[i - 1]] + (prev != curr);
        }

        c.swap(c_new);
    }

    p.erase(p.begin());

    return p;
}