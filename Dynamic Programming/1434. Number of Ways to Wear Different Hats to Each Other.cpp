class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        
        int n = hats.size();
        vector<vector<int>>hats_to_person(40);
        long mod = 1e9 + 7;
        vector<long>mask((1<<n));
        mask[0] = 1;

        for(int i = 0; i < n; ++i){
            for(auto hat: hats[i])
                hats_to_person[hat-1].push_back(i);
        }

        for(int h = 0; h < 40; ++h) {
            for(int bit = (1 << n) - 1; bit >=0; --bit) {
                for(auto person: hats_to_person[h]) {
                    if ((bit & (1 << person )) == 0) {
                        mask[bit | (1 << person )] += mask[bit];
                        mask[bit | (1 << person )] %= mod;
                    }
                }
            }
        }
        return mask[(1<<n) - 1];
    }
};

"""
🧪 Example
hats = [[3,5,1],[3,5]]
Person 0 → {3,5,1}
Person 1 → {3,5}

👉 Only 2 people → 2-bit mask

🔄 Step 1: Reorganize
Hat 1 → [0]
Hat 3 → [0,1]
Hat 5 → [0,1]
🧠 Step 2: DP Setup
Mask	Binary	Meaning	ways
0	00	none	1 ✅
1	01	person 0	0
2	10	person 1	0
3	11	both 🎯	0

🎩 Step 3: Process Hat 1

👉 Hat 1 → person 0 only

From 00:

00 → 01
ways[01] = 1
DP now
Mask	ways
00	1
01	1
10	0
11	0


🎩 Step 4: Process Hat 3

👉 Hat 3 → persons [0,1]

From mask = 01 (p0 already has hat)
p0 ❌
p1 ✅
01 → 11
ways[11] += 1
From mask = 00
p0 → 01
p1 → 10
ways[01] += 1 → now 2
ways[10] += 1 → now 1
DP now
Mask	ways
00	1
01	2
10	1
11	1


🎩 Step 5: Process Hat 5

👉 Hat 5 → persons [0,1]

From mask = 11 (already full) → skip
From mask = 10 (p1 has hat)
p0 ✅
10 → 11
ways[11] += 1 → now 2
From mask = 01 (p0 has hat)
p1 ✅
01 → 11
ways[11] += 2 → now 4
From mask = 00
p0 → 01
p1 → 10
ways[01] += 1 → now 3
ways[10] += 1 → now 2
📊 Final DP
Mask	ways
00	1
01	3
10	2
11	4 ✅
🎯 Why Answer = 4

mask = 11 → both people assigned

We got:

ways[11] = 4
🔍 Let’s Map These 4 Ways Explicitly

Now connect DP → real assignments:

✅ Case 1
p0 → 3
p1 → 5

👉 (3,5)

✅ Case 2
p0 → 5
p1 → 3

👉 (5,3)

✅ Case 3
p0 → 1
p1 → 3

👉 (1,3)

✅ Case 4
p0 → 1
p1 → 5

👉 (1,5)



"""