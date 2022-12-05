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

// SET VARIABLE part !!!

func main() {
	// Read the input file
	fileHandle, err := os.Open("inputs/5.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	// Initialize the starting positions
	var stacks [9][]string
	part := 2
	for fileScanner.Scan() {
		if strings.Contains(fileScanner.Text(), "[") {
			line_regex, _ := regexp.Compile("([A-Z])")
			letters := line_regex.FindAllString(fileScanner.Text(), -1)
			indices := line_regex.FindAllStringIndex(fileScanner.Text(), -1)

			for ind, letter := range letters {
				index := indices[ind][0]
				stacks[index/4] = append(stacks[index/4], letter)
			}
		} else {
			fileScanner.Scan() // Skip the newline
			break
		}
	}

	line_regex, _ := regexp.Compile("move ([0-9]+) from ([0-9]) to ([0-9])")
	for fileScanner.Scan() {
		// Parse the task
		digits := line_regex.FindStringSubmatch(fileScanner.Text())
		how_many, _ := strconv.Atoi(digits[1])
		src, _ := strconv.Atoi(digits[2])
		src--
		dest, _ := strconv.Atoi(digits[3])
		dest--
		// Make the move
		if part == 1 {
			for i := 0; i < how_many; i++ {
				to_move, removed_elem := stacks[src][0], stacks[src][1:]
				stacks[src] = removed_elem
				stacks[dest] = append([]string{to_move}, stacks[dest]...)
			}
		} else {
			to_move, removed_elem := stacks[src][:how_many], stacks[src][how_many:]
			tmp_removed_elem := make([]string, len(removed_elem))
			copy(tmp_removed_elem, removed_elem)
			tmp_to_move := make([]string, len(to_move))
			copy(tmp_to_move, to_move)
			stacks[src] = tmp_removed_elem
			stacks[dest] = append(tmp_to_move, stacks[dest]...)

		}

	}
	fileHandle.Close()

	fmt.Println("Part : ", part)
	for _, stack := range stacks {
		fmt.Print(stack[0])
	}
	fmt.Println()

}
