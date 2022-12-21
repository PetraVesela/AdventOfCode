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

var addRegex = regexp.MustCompile("addx (-?[0-9]+)")

func isCheckpoint(tick int) bool {
	// {20, 60, 100, 140, 180, 220}
	return tick <= 220 && tick%40 == 20
}

func updateScreen(screen [][]string, tick int, x int) {
	row := tick / 40
	col := tick % 40
	if col == x || col == x-1 || col == x+1 {
		screen[row][col] = "#"
	}
}

func main() {
	// Read the input line by line
	fileHandle, err := os.Open("10.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}
	defer fileHandle.Close()

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	// Prepare the variables
	var tick, signalStrength, x = 0, 0, 1
	screen := make([][]string, 6)
	// Initialize the screen:
	for i := range screen {
		screen[i] = make([]string, 40)
		for j := range screen[i] {
			screen[i][j] = "."
		}
	}

	for fileScanner.Scan() {
		if strings.Contains(fileScanner.Text(), "noop") {
			updateScreen(screen, tick, x)
			tick++
			if isCheckpoint(tick) {
				signalStrength += tick * x
			}
		} else if strings.Contains(fileScanner.Text(), "addx") {
			submatch := addRegex.FindStringSubmatch(fileScanner.Text())
			d, _ := strconv.Atoi(submatch[1])
			// Add takes 2 cycles to finish
			for i := 0; i < 2; i++ {
				updateScreen(screen, tick, x)
				tick++
				if isCheckpoint(tick) {
					signalStrength += tick * x
				}
			}
			x += d
		}
	}
	fmt.Println("Part 1:", signalStrength)

	// Print the screen
	fmt.Println("Part 2:")
	for _, row := range screen {
		fmt.Println(row)
	}
}
