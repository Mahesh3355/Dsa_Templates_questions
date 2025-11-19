#include <bits/stdc++.h>
using namespace std;
#define sout(s) cout << s << endl
#define ll long long
#define ld long double
#define PI 3.14159265
#define all(x) std::sort(((x).begin()), ((x).end()))
#define allg(x) std::sort(((x).begin()), ((x).end()), greater<int>())
#define allgp(x) std::sort(((x).begin()), ((x).end()), greater<pair<int, int>>())
#define allc(x) std::sort(((x).begin()), ((x).end()), cmp)
#define rev(x) std::reverse(((x).begin()), ((x).end()))
#define mx(x) max_element(((x).begin()), ((x).end()))
#define mn(x) min_element(((x).begin()), ((x).end()))
/*
> read the question carefully,start from B
> improve implementation and speed
> decrease anxiety.
> check constraint always..
> if enough test cases are not given then anyazlise the question
and try to make test case for every case even edge case;
> check whether segmentation fault can occur or not
> stay clam analyze every move
> Always check the base case for the recursive solution properly
> Always check the code twice before running the test case and dry run a sample or
random test case and check the code answer with intuition answer
*/
void precomputation_of_substring_palindromic(vector<vector<int>> &palindromic, string &s)
{
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        palindromic[i][i] = 1;
    }
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;
            if (s[i] == s[j])
            {
                if (len == 2)
                {
                    palindromic[i][j] = 1;
                }
                else
                {
                    palindromic[i][j] = palindromic[i + 1][j - 1];
                }
            }
        }
    }
}
class DSU
{
    vector<int> parent, size, rank;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            size[i] = 1;
            rank[i] = 0;
        }
    }
    int findp(int u)
    {
        if (parent[u] == u)
        {
            return u;
        }
        return parent[u] = findp(parent[u]);
    }
    void joinbyrank(int u, int v)
    {
        int up_u = findp(u), up_v = findp(v);
        if (up_u == up_v)
        {
            return;
        }
        if (rank[up_u] > rank[up_v])
        {
            parent[up_u] = up_u;
        }
        else if (rank[up_v] > rank[up_u])
        {
            parent[up_v] = up_u;
        }
        else
        {
            parent[up_u] = up_v;
            rank[up_v]++;
        }
    }
    void joinbysize(int u, int v)
    {
        int up_u = findp(u), up_v = findp(v);
        if (up_v == up_u)
        {
            return;
        }
        if (size[up_v] > size[up_u])
        {
            parent[up_u] = up_v;
            size[up_v] += size[up_u];
        }
        else
        {
            parent[up_v] = up_u;
            size[up_u] += size[up_v];
        }
    }
};
template <typename T>
void in(vector<T> &a, int s, int e)
{
    for (int i = s; i < e; i++)
    {
        cin >> a[i];
    }
}
template <typename T>
void out(vector<T> &a, int s, int e)
{
    for (int i = s; i < e; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
bool isPrime(int n)
{
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; (1LL * i * 1LL * i) <= n; i++)
    {
        if (prime[i])
        {
            for (int j = (1LL * i * 1LL * i); j <= n; j += i)
            {
                prime[j] = false;
            }
        }
    }
    return prime[n];
}
long m = 1e9 + 7;
// a^n--->( n is even then (n^(a/2)*n^(a/2)) and n is odd then (n*n^(a/2)*n^(a/2)))
// Fermat’s Little Theorem, which states that if (p) is a prime number and (a) is an integer not divisible by (p),
// then (a^(p-1) = 1mod p). This implies that (a^(p-2)) is the modular inverse of (a) modulo (p)
long long pow1(long long n, long long y)
{
    long long result = 1;
    long long exponent = y;
    while (exponent)
    {
        if (exponent & 1)
        {
            result = (result * n);
            result %= m;
        }
        n = (n * n);
        n %= m;
        exponent /= 2;
    }
    return result;
}
void multiply(vector<vector<ll>> &A,
              vector<vector<ll>> &B)
{
    vector<vector<ll>> C(2, vector<ll>(2));
    // O(1)
    //  Matrix Multiply
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % m;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % m;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % m;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % m;

    // Copy the result back to the first matrix
    A[0][0] = C[0][0];
    A[0][1] = C[0][1];
    A[1][0] = C[1][0];
    A[1][1] = C[1][1];
}
vector<vector<ll>> power(vector<vector<ll>> ma, ll n)
{
    // O(log(n))
    vector<vector<ll>> res = {{1, 0}, {0, 1}};
    while (n > 0)
    {
        if (n & 1)
        {
            multiply(res, ma);
        }
        multiply(ma, ma);
        n >>= 1;
    }
    return res;
}
vector<int> lps(string &pat)
{
    int i = 1, len = 0, n = pat.length();
    vector<int> lp(n, 0);
    while (i < n)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lp[i] = len;
            i++;
        }
        else
        {
            if (!len)
            {
                i++;
            }
            else
            {
                len = lp[len - 1];
            }
        }
    }
    return lp;
}
ll nthFibonacc(ll n)
{
    // O(log(n))
    if (n == 0 || n == 1)
    {
        return n;
    }
    vector<vector<ll>> ma = {{1, 1}, {1, 0}};
    vector<vector<ll>> f = {{1, 0}, {0, 0}};
    vector<vector<ll>> res = power(ma, n - 1);
    multiply(res, f);
    return res[0][0] % m;
}
void solve()
{
    int n;
    cin>>n;
    cout<<n<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}