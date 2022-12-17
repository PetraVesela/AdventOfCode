package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	// Read the input into int arrays
	fileHandle, err := os.Open("2.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v\n", err)
	}
	defer fileHandle.Close()

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)
	var me []int
	var elf []int

	for fileScanner.Scan() {
		elf = append(elf, int(fileScanner.Text()[0]-64)) // 'A' = 65
		me = append(me, int(fileScanner.Text()[2]-87))   // 'X' = 88
	}

	RPS := [][]int{
		{3, 0, 6},
		{6, 3, 0},
		{0, 6, 3},
	}

	// Part 1:
	var myScore int
	for ind, myDraft := range me {
		myScore += myDraft
		myScore += RPS[myDraft-1][elf[ind]-1]
	}

	fmt.Println("Part 1: ", myScore)

	// Part 2:
	myScore = 0
	var result int
	for ind, expectedResult := range me {
		// points for result:
		result = (expectedResult - 1) * 3
		myScore += result

		// points for the draft:
		// Find the expected result in the corresponding row
		for i := 1; i < 4; i++ {
			if RPS[i-1][elf[ind]-1] == result {
				myScore += i
				break
			}
		}
	}
	fmt.Println("Part 2: ", myScore)
}
