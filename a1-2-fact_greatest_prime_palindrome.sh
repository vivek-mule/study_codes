#!/bin/bash

factorial() {
  echo -n "Enter a number: "
  read num
  fact=1
  for (( i=1; i<=num; i++ ))
  do
    fact=$((fact * i))
  done
  echo "Factorial of $num is $fact"
}

greatest_of_three() {
  echo "Enter three numbers:"
  read a b c
  if [ $a -ge $b ] && [ $a -ge $c ]; then
    echo "$a is the greatest"
  elif [ $b -ge $a ] && [ $b -ge $c ]; then
    echo "$b is the greatest"
  else
    echo "$c is the greatest"
  fi
}

is_prime() {
  echo -n "Enter a number: "
  read num
  if [ $num -le 1 ]; then
    echo "$num is not a prime number"
    return
  fi
  for (( i=2; i*i<=num; i++ ))
  do
    if [ $((num % i)) -eq 0 ]; then
      echo "$num is not a prime number"
      return
    fi
  done
  echo "$num is a prime number"
}

is_number_palindrome() {
  echo -n "Enter a number: "
  read num
  temp=$num
  rev=0
  while [ $temp -gt 0 ]
  do
    rem=$((temp % 10))
    rev=$((rev * 10 + rem))
    temp=$((temp / 10))
  done

  if [ $num -eq $rev ]; then
    echo "$num is a palindrome"
  else
    echo "$num is not a palindrome"
  fi
}

is_string_palindrome() {
  echo -n "Enter a string: "
  read str
  rev=$(echo "$str" | rev)
  if [ "$str" = "$rev" ]; then
    echo "\"$str\" is a palindrome"
  else
    echo "\"$str\" is not a palindrome"
  fi
}

# Main menu loop
while true
do
  echo ""
  echo "==== MENU ===="
  echo "1. Factorial of a number"
  echo "2. Greatest of three numbers"
  echo "3. Check if a number is prime"
  echo "4. Check if a number is a palindrome"
  echo "5. Check if a string is a palindrome"
  echo "6. Exit"
  echo "Enter your choice: "
  read choice

  case $choice in
    1) factorial ;;
    2) greatest_of_three ;;
    3) is_prime ;;
    4) is_number_palindrome ;;
    5) is_string_palindrome ;;
    6) echo "Exiting program..."; break ;;
    *) echo "Invalid choice. Try again." ;;
  esac
done
