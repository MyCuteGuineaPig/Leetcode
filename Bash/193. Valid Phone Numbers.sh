#Solution 1: Extended Regular Expression (EREs)
grep -E "(^[0-9]{3}-[0-9]{3}-[0-9]{4}$)|(^\([0-9]{3}\)\ [0-9]{3}-[0-9]{4}$)" file.txt
# 表示 3个数字-3个数字-4个数字|(3个数字) 3个数字-4个数字
#注意 )|( 中间不能有空格，
# 或者不用加括号
grep -E "^[0-9]{3}-[0-9]{3}-[0-9]{4}$|^\([0-9]{3}\)\ [0-9]{3}-[0-9]{4}$" file.txt
grep -E "^([0-9]{3}-[0-9]{3}-[0-9]{4}|\([0-9]{3}\)\ [0-9]{3}-[0-9]{4})$" file.txt


#Solution 2:
grep -E "^([0-9]{3}-|\([0-9]{3}\)\ )[0-9]{3}-[0-9]{4}$" file.txt
# 表示 (3个数字|(3个数字) )-3个数字-4个数字
#or 
grep -E "^([0-9]{3}-|\([0-9]{3}\)[ ])[0-9]{3}-[0-9]{4}$" file.txt


#Solution 3: 
grep   '^\(([0-9]\{3\})[ ]\|[0-9]\{3\}-\)[0-9]\{3\}[-][0-9]\{4\}$' file.txt
#加不加e 都可以
grep    '^\([0-9]\{3\}-\|([0-9]\{3\}) \)[0-9]\{3\}-[0-9]\{4\}$' file.txt
grep  -e  '^\([0-9]\{3\}-\|([0-9]\{3\}) \)[0-9]\{3\}-[0-9]\{4\}$' file.txt


#Solution 4: PCREs
#-P
#--perl-regexp
#Interpret patterns as Perl-compatible regular expressions (PCREs).
grep -P '^(\d{3}-|\(\d{3}\) )\d{3}-\d{4}$' file.txt


#Solution 5: Using sed:
sed -n -r '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/p' file.txt

#Solution 6: Using awk:
awk '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/' file.txt
#or
awk '/^([[:digit:]]{3}-|\([[:digit:]]{3}\) )[[:digit:]]{3}-[[:digit:]]{4}$/' file.txt
