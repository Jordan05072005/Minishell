#!/bin/bash

# Check if the user provided the number of lines
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_lines>"
  exit 1
fi

# Generate the specified number of lines
for ((i = 0; i < $1; i++)); do
  # Generate a random 16-letter string
  RANDOM_STR=$(cat /dev/urandom | tr -dc 'A-Za-z0-9' | head -c 16)
  echo "export $RANDOM_STR=$RANDOM_STR"
done

echo export