# Solution 1: AWK

awk '
{   
    for (i = 1; i <= NF; i++) {   #每一行都会run for loop
        if(NR == 1) {
            s[i] = $i;
        } else {
            s[i] = s[i] " " $i;
        }
    }
}
END {
    for (i = 1; s[i] != ""; i++) {
        print s[i];
    }
}' file.txt

# END part will run after it dealt with every line

#OR 
awk '
{
    for (f=1;f<=NF;f++) 
        col[f] = col[f]" "$f}  #第一个词前面有空格
    END {
        for (f=1;f<=NF;f++) 
            print col[f]
}' | cut -d" " -f2- # -f2-  是因 第二个field 之后的, 因为第一个开始就有空格


# Read from the file file.txt and print its transposed content to stdout.
awk '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str" "a[i,j];
        }
        print str
    }
}' file.txt


# Solution 2: loop each col + using paste
col="$(head -1 file.txt | wc -w)"

for i in $(seq 1 $col)
do 
    awk '{ print $'$i' }' file.txt | paste -s -d" "
done



col=`head -1 file.txt|wc -w`
for i in `seq 1 $col`
do 
    cut -d" " -f$i file.txt | paste -d" " -s #cut 是竖着打印的, paste 是给他横过来
done 



#or 
col=`head -1 file.txt|wc -w`
for i in `seq 1 $col`
do 
    echo `cut -d" " -f$i file.txt` #echo 也可以给他横过来
    # or 
    #echo $(cut -d' ' -f$i file.txt)
done 


for col in $(seq 1 $(( $(head -1 file.txt | grep -o ' ' | wc -l) + 1))); do
    echo $(cut -d' ' -f$col file.txt)
done





# Solution 3: sort without awk
totalLine=`wc -l file.txt | cut -d" " -f1` #wc 打印结果是 3 file.txt 想要3 所以用cut
i=0
while IFS= read -r line 
do 
    j=0
    let i++
    for word in $line
    do 
        let j++
        echo $i $j $word
    done 
done < file.txt | sort -n -k2 -k1 | while read i j word #先运行上面的while, 然后output 再进行下面的sort, while 
do 
    if [ $i -eq $totalLine ]
    then
        echo $word
    else 
        echo -n "$word " #不加空格会 接着打 比如 aliceryan 而不是 alice ryan
    fi
done 


#Solution 4: Using associative array 
declare -A matrix
col=1
row=1

while read line; do
    col=1
    for word in $line; do
            matrix[$row,$col]=$word
            ((col++))
    done
    ((row++))
done < file.txt

for ((i=1;i<col;i++)) do
    echo -n ${matrix[1,$i]} 
    for((j=2;j<row;j++)) do
            echo -n ' '${matrix[$j,$i]}
    done
    echo
done


