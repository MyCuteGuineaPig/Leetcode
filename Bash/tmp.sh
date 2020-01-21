#194	 Transpose File    
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



# Solution: sort without awk
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
