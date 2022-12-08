package main

import (
	"fmt"
	"log"
	"os"
)

type set_rune = map[rune]bool

func stringToSet(s string) set_rune {
	set := make(set_rune)
	for _, x := range s {
		set[x] = true
	}
	return set
}

func main() {
	// Read input string
	body, err := os.ReadFile("inputs/6.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	part_limits := []int{4, 14}
	for ind, num := range part_limits {
		for i := 0; i < len(body); i++ {
			set := stringToSet(string(body)[i : i+num])
			if len(set) == num {
				fmt.Println("Part ", ind+1, ":", i+num)
				break
			}
		}
	}

}
