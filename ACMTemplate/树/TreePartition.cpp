/*
 * 首先执行initial()进行初始化
 * 在调用时，先将subtree_size[1] = n,之后调用solve_subproblem(1)
 */
void initial() {
    memset(head, -1, sizeof(head));
    memset(centroid, 0, sizeof centroid);
    side = 0;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
    pair <int, int> ret = make_pair(INF, -1);
    int mx = 0;
    subtree_size[x] = 1;
    for (int i = head[x]; ~i; i = e[i].next) {
        if (centroid[e[i].to] || e[i].to == pre) {
            continue;
        }
        ret = min(ret, find_centroid(e[i].to, x, sum));
        mx = max(mx, subtree_size[e[i].to]);
        subtree_size[x] += subtree_size[e[i].to];
    }
    mx = max(mx, sum - subtree_size[x]);
    return min(ret, make_pair(mx, x));
}

void deal(int x, int pre, int value) {
    tds[len_tds++] = value;
    for (int i = head[x]; ~i; i = e[i].next) {
        if (centroid[e[i].to] || e[i].to == pre) {
            continue;
        }
        deal(e[i].to, x, e[i].val + value);
    }
}

int count_pairs(int a[], int len) {
    int ret = 0;
    sort(a, a + len);
    int l = 0, r = len - 1;
    while (l < r) {
        while (l < r && a[l] + a[r] > k) {
            r--;
        }
        ret += r - l;
        l++;
    }
    return ret;
}

void solve_subproblem(int x) {
    int u = find_centroid(x, -1, subtree_size[x]).second;
    centroid[u] = true;
    len_ds = 0;
    ds[len_ds++] = 0;
    for (int i = head[u]; ~i; i = e[i].next) {
        if (centroid[e[i].to])
            continue;
        len_tds = 0;
        deal(e[i].to, u, e[i].val);
        subtree_size[e[i].to] = len_tds;
        ans -= count_pairs(tds, len_tds);
        for (int j = 0; j < len_tds; ++j)
            ds[len_ds++] = tds[j];
    }
    ans += count_pairs(ds, len_ds);
    for (int i = head[u]; ~i; i = e[i].next) {
        if (centroid[e[i].to])
            continue;
        solve_subproblem(e[i].to);
    }
}
