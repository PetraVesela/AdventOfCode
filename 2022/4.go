package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
)

func main() {
	// Read the input into int arrays
	fileHandle, err := os.Open("inputs/4.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	var num_contained int
	var num_overlapping int
	line_regex, _ := regexp.Compile("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)")
	for fileScanner.Scan() {
		digits := line_regex.FindStringSubmatch(fileScanner.Text())
		a, _ := strconv.Atoi(digits[1])
		b, _ := strconv.Atoi(digits[2])
		c, _ := strconv.Atoi(digits[3])
		d, _ := strconv.Atoi(digits[4])
		if a <= c && b >= d || c <= a && d >= b {
			num_contained++
		} else {
			if a >= c && a <= d || b >= c && b <= d {
				num_overlapping++
			}
		}
	}

	fileHandle.Close()
	fmt.Println("Part 1: ", num_contained)
	fmt.Println("Part 2: ", num_overlapping+num_contained)

}
