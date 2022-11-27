package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	// Read input into an int array
	file, err := os.Open("inputs/1.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}
	var numbers []int
	fscanner := bufio.NewScanner(file)
	for fscanner.Scan() {
		intVar, _ := strconv.Atoi(fscanner.Text())
		numbers = append(numbers, intVar)
	}

	// Part 1
	count_increases := 0
	for previous_ind, this_num := range numbers[1:] {
		if this_num > numbers[previous_ind] {
			count_increases++
		}
	}
	fmt.Println("Part 1: ", count_increases)

	// Part 2
	count_increases = 0
	for previous_ind, this_num := range numbers[3:] {
		if this_num > numbers[previous_ind] {
			count_increases++
		}
	}
	fmt.Println("Part 2: ", count_increases)
}
