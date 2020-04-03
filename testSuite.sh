#!/bin/bash
: '
  This is a test file for credit.c
  Add test cases to numbers.txt if you would like
'
arrOfNumbers=(`cat ./numbers.txt`)
for (( i = 0; i < ${#arrOfNumbers[@]}; i++ )); do
  result=`gcc -w credit.c -o run && ./run ${arrOfNumbers[i]}`
  [[ $result == **"INVALID"** ]] && /bin/echo "$(tput setaf 1)$(tput setab 7)CHECK $i (${arrOfNumbers[i]}): result -> $result$(tput sgr 0)" || /bin/echo "$(tput setaf 2)$(tput setab 7)CHECK $i (${arrOfNumbers[i]}): result -> $result$(tput sgr 0)"
done

# EOF
