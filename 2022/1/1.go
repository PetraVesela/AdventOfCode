package main

import (
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {
	// Read input into int arrays
	body, err := os.ReadFile("1.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v\n", err)
	}

	elves := strings.Split(string(body), "\n\n")
	var calories []int
	for _, elf := range elves {
		snacks := strings.Split(elf, "\n")
		cal := 0
		for _, snack := range snacks {
			snackCal, _ := strconv.Atoi(snack)
			cal += snackCal
		}
		calories = append(calories, cal)
	}

	// Get the maximum elements
	sort.Sort(sort.Reverse(sort.IntSlice(calories)))
	fmt.Println("Part 1: ", calories[0])
	fmt.Println("Part 2: ", calories[0]+calories[1]+calories[2])
}
