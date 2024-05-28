#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
    int P, S, A, L;
    node(int P = 0, int S = 0, int A = 0, int L = 0) : P(P), S(S), A(A), L(L) {}
};
node merge(const node &a, const node &b)
{
    int P = (a.P == a.L) ? a.L + b.P : a.P;
    int S = (b.S == b.L) ? b.L + a.S : b.S;
    int A = max({a.A, b.A, a.S + b.P});
    int L = a.L + b.L;
    return node(P, S, A, L);
}

const int MAXN = 200005;
node tree0[4 * MAXN], tree1[4 * MAXN];
node val0(0, 0, 0, 1), val1(1, 1, 1, 1);
int n;
void build(node tree[], int t, int tl, int tr, node dval)
{
    if (tl == tr)
    {
        tree[t] = dval;
        return;
    }
    int tm = (tl + tr) / 2;
    build(tree, t * 2, tl, tm, dval);
    build(tree, t * 2 + 1, tm + 1, tr, dval);
    tree[t] = merge(tree[t * 2], tree[t * 2 + 1]);
}
void update(node tree[], int i, node v, int t, int tl, int tr)
{
    if (tl == tr)
    {
        tree[t] = v;
        return;
    }
    int tm = (tl + tr) / 2;
    if (i <= tm) update(tree, i, v, t * 2, tl, tm);
    else update(tree, i, v, t * 2 + 1, tm + 1, tr);
    tree[t] = merge(tree[t * 2], tree[t * 2 + 1]);
}

node query(node tree[], int l, int r, int t, int tl, int tr, node dval)
{
    if (r < tl || l > tr) return dval;
    if (l <= tl && tr <= r) return tree[t];
    int tm = (tl + tr) / 2;
    return merge(query(tree, l, r, t * 2, tl, tm, dval), query(tree, l, r, t * 2 + 1, tm + 1, tr, dval));
}
int main()
{
    string S;
    cin >> S;
    n = S.size();
    build(tree0, 1, 0, n - 1, val0);
    build(tree1, 1, 0, n - 1, val0);
    for (int i = 0; i < n; i++)
    {
        if (S[i] == '0')
        {
            update(tree0, i, val1, 1, 0, n - 1);
            update(tree1, i, val0, 1, 0, n - 1);
        }
        else if (S[i] == '1')
        {
            update(tree0, i, val0, 1, 0, n - 1);
            update(tree1, i, val1, 1, 0, n - 1);
        }
    }

    int Q;
    cin >> Q;
    while (Q--)
    {
        int x;
        cin >> x;
        x--;
        if (S[x] == '0')
        {
            update(tree0, x, val0, 1, 0, n - 1);
            update(tree1, x, val1, 1, 0, n - 1);
            S[x] = '1';
        }
        else if (S[x] == '1')
        {
            update(tree1, x, val0, 1, 0, n - 1);
            update(tree0, x, val1, 1, 0, n - 1);
            S[x] = '0';
        }
        cout << max(query(tree0, 0, n - 1, 1, 0, n - 1, val0).A, query(tree1, 0, n - 1, 1, 0, n - 1, val0).A) << ' ';
    }
    return 0;
}
//https://cses.fi/problemset/task/1188/
