#!/bin/bash

DB_FILE="student_db.txt"

add_student() {
  echo "Enter Roll Number:"
  read roll
  echo "Enter Name:"
  read name
  echo "Enter Marks:"
  read marks
  echo "$roll,$name,$marks" >> "$DB_FILE"
  echo "Student added successfully!"
}

view_students() {
  if [[ -s "$DB_FILE" ]]; then
    echo "Roll No | Name        | Marks"
    echo "------------------------------"
    column -t -s',' "$DB_FILE"
  else
    echo "No student records found."
  fi
}

search_student() {
  echo "Enter Roll Number to search:"
  read roll
  grep "^$roll," "$DB_FILE" > /dev/null
  if [[ $? -eq 0 ]]; then
    echo "Record Found:"
    grep "^$roll," "$DB_FILE" | column -t -s','
  else
    echo "Student with Roll No $roll not found."
  fi
}

delete_student() {
  echo "Enter Roll Number to delete:"
  read roll

  roll=$(echo "$roll" | tr -d '[:space:]')

  if grep -q "^$roll," "$DB_FILE"; then
    grep -v "^$roll," "$DB_FILE" > temp.txt
    mv temp.txt "$DB_FILE"
    echo "Student record deleted."
  else
    echo "Student with Roll No $roll not found."
  fi
}


update_student() {
  echo "Enter Roll Number to update:"
  read roll

  if grep -q "^$roll," "$DB_FILE"; then
    echo "Enter new Name:"
    read name
    echo "Enter new Marks:"
    read marks

    new_record="$roll,$name,$marks"

    grep -v "^$roll," "$DB_FILE" > temp.txt
    echo "$new_record" >> temp.txt
    mv temp.txt "$DB_FILE"

    echo "Student record updated."
  else
    echo "Student with Roll No $roll not found."
  fi
}

while true; do
  echo ""
  echo "====== Student Database Menu ======"
  echo "1. Add Student"
  echo "2. View Students"
  echo "3. Search Student"
  echo "4. Delete Student"
  echo "5. Update Student"
  echo "6. Exit"
  echo "Choose an option:"
  read choice

  case $choice in
    1) add_student ;;
    2) view_students ;;
    3) search_student ;;
    4) delete_student ;;
    5) update_student ;;
    6) echo "Exiting..."; break ;;
    *) echo "Invalid option, try again." ;;
  esac
done
