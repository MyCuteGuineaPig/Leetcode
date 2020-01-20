# Comment 

# The awk and sed solutions do not exit immediately after printing. 
# So in case of a large file, they will print the 10th line, but then keep on looping until the end of file.

# For my testcase, I created a file that has 100 million lines. 
# And then I use the "time" command to time each solution. 
# Notice that Solutions 1 and 4 are very fast - less than a second, 
# but solutions 2 and 3 take up anywhere from 12 to 19 seconds, which is an unnecessary time hog.

#The last two awk scripts exit right after printing and you can see that their run times have improved.

#Also, I replaced the "exit 0" in the shell script by a "return",
# which returns control to the shell prompt but does not close the terminal window.)



# Solution 1
cnt=0
while read line && [ $cnt -le 10 ]; do
  let 'cnt = cnt + 1'
  if [ $cnt -eq 10 ]; then
    echo $line
    exit 0
  fi
done < file.txt

# Solution 2
awk 'FNR == 10 {print }'  file.txt
# OR
awk 'NR == 10' file.txt

# Solution 3
sed -n 10p file.txt
#or
sed '10!D' file.txt


# Solution 4
tail -n+10 file.txt|head -1 

# Solution 5
head -10 file.txt | tail -1


cut -d$'\n' -f 10 file.txt # $:  $'string' are treated specially. 
#The word expands to string, with backslash-escaped characters replaced as specified by the ANSI C standard


# # ==========  Efficient awk ==========
time awk 'NR==10{print; exit}' file.txt

#Line 10

#real    0m0.031s
#user    0m0.000s
#sys     0m0.030s

time awk 'FNR==10{print; exit}' file.txt
Line 10

real    0m0.031s
user    0m0.000s
sys     0m0.030s


#General Solution
# Extract NLINES lines from STARTING line

STARTING=10; NLINES=1; cat file.txt | tail -n+${STARTING} | head -n${NLINES}