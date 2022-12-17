package main

import (
	"fmt"
	"log"
	"os"
)

type runeSet = map[rune]bool

func stringToSet(s string) runeSet {
	set := make(runeSet)
	for _, x := range s {
		set[x] = true
	}
	return set
}

func main() {
	// Read input string
	body, err := os.ReadFile("6.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	partLimits := []int{4, 14}
	for ind, num := range partLimits {
		for i := 0; i < len(body); i++ {
			set := stringToSet(string(body)[i : i+num])
			if len(set) == num {
				fmt.Println("Part ", ind+1, ":", i+num)
				break
			}
		}
	}

}
