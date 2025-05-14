#!/bin/bash

# Function to find biggest of three numbers
biggest_of_three() {
  if [ $# -ne 3 ]; then
    echo "Usage: $0 a b c"
    return
  fi
  a=$1
  b=$2
  c=$3
  if [ $a -ge $b ] && [ $a -ge $c ]; then
    echo "$a is the biggest"
  elif [ $b -ge $a ] && [ $b -ge $c ]; then
    echo "$b is the biggest"
  else
    echo "$c is the biggest"
  fi
}

# Function to reverse a number
reverse_number() {
  if [ $# -ne 1 ]; then
    echo "Usage: $0 number"
    return
  fi
  num=$1
  rev=0
  while [ $num -gt 0 ]; do
    rem=$((num % 10))
    rev=$((rev * 10 + rem))
    num=$((num / 10))
  done
  echo "Reversed number: $rev"
}

# Function to print word N times
print_word_n_times() {
  if [ $# -ne 2 ]; then
    echo "Usage: $0 N word"
    return
  fi
  N=$1
  word=$2
  for ((i=1; i<=N; i++)); do
    echo "$word"
  done
}

# Function to sum digits of a 4-digit number
sum_digits() {
  if [ $# -ne 1 ]; then
    echo "Usage: $0 4-digit-number"
    return
  fi
  num=$1
  if ! [[ $num =~ ^[0-9]{4}$ ]]; then
    echo "Please enter a 4-digit number"
    return
  fi
  sum=0
  for ((i=0; i<${#num}; i++)); do
    digit=${num:$i:1}
    sum=$((sum + digit))
  done
  echo "Sum of digits: $sum"
}

# Menu-driven based on first argument
case $1 in
  a)
    shift
    biggest_of_three "$@"
    ;;
  b)
    shift
    reverse_number "$@"
    ;;
  c)
    shift
    print_word_n_times "$@"
    ;;
  d)
    shift
    sum_digits "$@"
    ;;
  *)
    echo "Usage:"
    echo "$0 a num1 num2 num3      # Find biggest"
    echo "$0 b number              # Reverse number"
    echo "$0 c N word              # Print word N times"
    echo "$0 d 4-digit-number      # Sum of digits"
    ;;
esac
