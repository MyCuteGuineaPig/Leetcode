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

#Solution 3: tr 
cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -r | awk '{ print $2, $1 }'


#Solution 4:  Sed
cat words.txt | tr -s '[[:space:]]' '\n'| sort | uniq -c | sort -r | sed -r -e 's/[[:space:]]*([[:digit:]]+)[[:space:]]*([[:alpha:]]+)/\2 \1/g'

#Solution 5: 
cat words.txt | awk '{for(i=1;i<=NF;++i){count[$i]++}} END{for(i in count) {print i,count[i]}}' | sort -k2nr
# NF column 个数


#下面结果不是sort的
#!/usr/bin/env bash

declare -A HashWord
File="words.txt"

function ReadTxtFile
{
    while read Line
    do
        Word=(${Line})
        for Var in ${Word[@]}
        do
            HashWord+=( [${Var}]='1')
            #Word[${Var}]=
            #for i in ${Word[@]}
           # do
            #    if [[ ${Var} == ${i} ]];then
           #         Value=${HashWord[${Var}]}
          #      fi
          #  done

        done
    done < ${File}


    for Key in ${!HashWord[*]}
    do
        echo "${Key} ${#HashWord[${Key}]}"
    done
} 
ReadTxtFile
