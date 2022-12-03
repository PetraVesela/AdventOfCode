package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

type set_rune = map[rune]bool

func intersect(s1 set_rune, s2 set_rune) set_rune {
	s_intersection := set_rune{}
	if len(s1) > len(s2) {
		s1, s2 = s2, s1 // better to iterate over a shorter set
	}
	for k, _ := range s1 {
		if s2[k] {
			s_intersection[k] = true
		}
	}
	return s_intersection
}

func stringToSet(s string) set_rune {
	set := make(set_rune)
	for _, x := range s {
		set[x] = true
	}
	return set
}

func getItemValue(item rune) rune {
	if item >= 97 { // lowercase
		return item - 96
	} else { // uppercase
		return item - (64 - 26)
	}
}

func main() {
	// Read the input line by line
	fileHandle, err := os.Open("inputs/3.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	var prioritySum rune
	var rucksacks []string
	for fileScanner.Scan() {
		var rucksack = fileScanner.Text()
		// store for the Part 2 processing
		rucksacks = append(rucksacks, rucksack)
		// Split each rucksack in two compartments and make them a set

		compartment_1 := stringToSet(rucksack[:len(rucksack)/2])
		compartment_2 := stringToSet(rucksack[len(rucksack)/2:])

		var common = intersect(compartment_1, compartment_2)
		for s, _ := range common {
			prioritySum += getItemValue(s)
		}
	}
	fileHandle.Close()

	fmt.Println("Part 1: ", prioritySum)

	prioritySum = 0
	// Part 2
	for i := 0; i < len(rucksacks); i += 3 {
		a := stringToSet(rucksacks[i])
		b := stringToSet(rucksacks[i+1])
		c := stringToSet(rucksacks[i+2])

		ab := intersect(a, b)
		abc := intersect(ab, c)
		for s, _ := range abc {
			prioritySum += getItemValue(s)
		}
	}

	fmt.Println("Part 2: ", prioritySum)

}
