题意：RT

思路：快速幂

注意两种情况：1）n为负数；2）n为$-2^{31}$

代码

```
class Solution {
    public double myPow(double x, int n) {
        double ans = 1.0;
        boolean flag = true;
        long tn = n;
        if (tn < 0) {
            flag = false;
            tn = -tn;
        }
        while(tn > 0) {
            
            if ((tn & 1) > 0)
                ans = ans * x;
            tn = (tn >> 1);
            x = (x * x);
            System.out.printf("tn = %d, x = %f, ans = %f\n", tn, x, ans);
        }
        if (flag == false)
            ans = 1.0 / ans;
        return ans;
    }
}
```

