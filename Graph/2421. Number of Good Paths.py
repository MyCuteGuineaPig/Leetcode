class Solution:
    def numberOfGoodPaths(self, vals, edges):
        res = n = len(vals)
        f = list(range(n))
        count = [Counter({vals[i]: 1}) for i in range(n)]
        edges = sorted([max(vals[i], vals[j]),i,j] for i,j in edges)
        print(count)

        def find(x):
            if f[x] != x:
                f[x] = find(f[x])
            return f[x]

        for v,i,j in edges:
            fi, fj = find(i), find(j)
            ci, cj = count[fi][v], count[fj][v]
            #print("v", v,"i",i, "fi",fi , "j", j, "fj", fj, "ci", ci, " cj ", cj)
            res += ci * cj
            f[fj] = fi
            count[fi] = Counter({v: ci + cj})
            #print(count)
            
        return res