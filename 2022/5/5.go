package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

var (
	moveRegex   = regexp.MustCompile("move ([0-9]+) from ([0-9]) to ([0-9])")
	letterRegex = regexp.MustCompile("([A-Z])")
)

// SET VARIABLE part !!!

func main() {
	// Read the input file
	fileHandle, err := os.Open("5.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v\n", err)
	}
	defer fileHandle.Close()

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	// Initialize the starting positions
	var stacks [9][]string
	part := 2

	for fileScanner.Scan() {
		if strings.Contains(fileScanner.Text(), "[") {
			letters := letterRegex.FindAllString(fileScanner.Text(), -1)
			indices := letterRegex.FindAllStringIndex(fileScanner.Text(), -1)

			for ind, letter := range letters {
				index := indices[ind][0]
				stacks[index/4] = append(stacks[index/4], letter)
			}
		} else {
			fileScanner.Scan() // Skip the newline
			break
		}
	}

	for fileScanner.Scan() {
		// Parse the task
		digits := moveRegex.FindStringSubmatch(fileScanner.Text())
		howMany, _ := strconv.Atoi(digits[1])
		src, _ := strconv.Atoi(digits[2])
		src--
		dest, _ := strconv.Atoi(digits[3])
		dest--
		// Make the move
		if part == 1 {
			for i := 0; i < howMany; i++ {
				toMove, removedElem := stacks[src][0], stacks[src][1:]
				stacks[src] = removedElem
				stacks[dest] = append([]string{toMove}, stacks[dest]...)
			}
		} else {
			toMove, removedElem := stacks[src][:howMany], stacks[src][howMany:]
			tmpRemovedElem := make([]string, len(removedElem))
			copy(tmpRemovedElem, removedElem)
			tmpToMove := make([]string, len(toMove))
			copy(tmpToMove, toMove)
			stacks[src] = tmpRemovedElem
			stacks[dest] = append(tmpToMove, stacks[dest]...)
		}
	}

	fmt.Println("Part : ", part)
	for _, stack := range stacks {
		fmt.Print(stack[0])
	}
	fmt.Println()
}
