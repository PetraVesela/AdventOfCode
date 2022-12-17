package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
)

var lineRegex = regexp.MustCompile("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)")

func main() {
	// Read the input into int arrays
	fileHandle, err := os.Open("4.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v\n", err)
	}
	defer fileHandle.Close()

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	var numContained int
	var numOverlapping int

	for fileScanner.Scan() {
		digits := lineRegex.FindStringSubmatch(fileScanner.Text())
		a, _ := strconv.Atoi(digits[1])
		b, _ := strconv.Atoi(digits[2])
		c, _ := strconv.Atoi(digits[3])
		d, _ := strconv.Atoi(digits[4])
		if a <= c && b >= d || c <= a && d >= b {
			numContained++
		} else {
			if a >= c && a <= d || b >= c && b <= d {
				numOverlapping++
			}
		}
	}

	fmt.Println("Part 1: ", numContained)
	fmt.Println("Part 2: ", numOverlapping+numContained)
}
