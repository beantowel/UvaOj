#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

int k, maxd;
LL invalidN[5];
LL ans[30], v[30];
LL get_first(LL a, LL b)
{
    return (b - 1) / a + 1;
}
bool isvalid(LL n)
{
    for(int i = 0; i < k; i++)
        if(invalidN[i] == n) return false;
    return true;
}
bool better(int d)
{
    for(int i = d; i >= 0; i--)
        if(v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    return false;
}
LL gcd(LL a, LL b){
    //a<b
    LL t;
    while(a != 0){
        t = b % a;
        b = a;
        a = t;
    }
    return b;
}
bool dfs(int d, LL from, LL aa, LL bb)
{
    if(d == maxd) {
        if(bb % aa != 0) return false;
        if(!isvalid(bb / aa)) return false;
        v[d] = bb / aa;
        if(better(d)) memcpy(ans, v, sizeof(LL) * (d + 1));
        return true;
    }
    bool ok = false;
    from = max(from,get_first(aa,bb));
    for(int i=from;;i++){
        if(bb*(maxd+1-d) <= i*aa) break;
        if(!isvalid(i)) continue;
        v[d] = i;
        LL b2 = bb*i;
        LL a2 = aa*i-bb;
        LL g =gcd(a2,b2);
        if(dfs(d+1,i+1,a2/g,b2/g)) ok = true;
    }
    return ok;
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int ii=0;ii<n;ii++) {
        int a, b;
        scanf("%d%d%d", &a, &b, &k);
        for(int i = 0; i < k; i++)
            scanf("%d", &invalidN[i]);
        int ok = 0;
        for(maxd = 1;; maxd++) {
            memset(ans, -1, sizeof(ans));
            if(dfs(0, get_first(a, b), a, b)) {
                ok = 1;
                break;
            }
        }
        if(ok){
            printf("Case %d: %d/%d=", ii+1, a, b);
            for(int  i=0;i<maxd;i++) printf("1/%d+", ans[i]);
            printf("1/%d\n", ans[maxd]);
        }
    }
    return 0;
}