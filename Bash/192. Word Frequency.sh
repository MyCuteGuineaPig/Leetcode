# Solution 1 grep
grep -o '[[:alpha:]]\{1,\}' words.txt | sort | uniq -c | sed "s/^[[:space:]]*//" | sort -nr -k1 | awk '{t=$1; $1=$2;$2=t; print;}'
# remove prefix white space sed "s/^[[:space:]]*//" 

# 可以不用remove whitespace, awk $1, $2不会算white space
grep -o "[a-z]\+" words.txt | sort | uniq -c | sort -nr -k1 | awk '{t=$1;$1=$2;$2=t;print;}'

#or
grep -o "[a-z]\+" words.txt | sort | uniq -c | sort -nr -k1 | awk '{print $2, $1}'

#不用说 sort -k1, 自动按第一列sort
grep -o "[a-z]\+" words.txt | sort | uniq -c | sort -nr| awk '{print $2, $1}'



#Solution 2: xargs
cat words.txt | xargs -n1 |sort|uniq -c| sort -nr|awk '{print $2 " " $1}'

