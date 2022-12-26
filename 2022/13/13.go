package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"reflect"
	"sort"
)

func toSlice(i interface{}) []interface{} {
	var out []interface{}

	switch v := i.(type) {
	case []interface{}:
		for x := 0; x < len(v); x++ {
			out = append(out, v[x])
		}
	case float64:
		out = append(out, v)
	default:
		fmt.Printf("invalid type: %T\n", v)
	}
	return out
}

func compare(a, b []interface{}) int {
	// returns -1 if wrong order, 1 if correct order, 0 if cannot decide
	for ind, elemA := range a {
		if ind == len(b) {
			// right one ran out first
			return -1
		}
		elemB := b[ind]

		if reflect.TypeOf(elemA) == reflect.TypeOf(elemB) {
			// both ints
			switch elemA.(type) {
			case float64:
				if elemA.(float64) < elemB.(float64) {
					return 1
				}
				if elemA.(float64) > elemB.(float64) {
					return -1
				}
			case []interface{}:
				// both are slices
				if val := compare(toSlice(elemA), toSlice(elemB)); val != 0 {
					return val
				}
			}
		} else {
			// One of the compared values is an int
			if val, ok := elemA.(float64); ok {
				if val := compare(toSlice(val), toSlice(elemB)); val != 0 {
					return val
				}
			}
			if val, ok := elemB.(float64); ok {
				if val := compare(toSlice(elemA), toSlice(val)); val != 0 {
					return val
				}
			}
		}
	}
	if len(a) < len(b) {
		return 1
	}
	return 0
}

func main() {
	// Read the input line by line
	fileHandle, err := os.Open("13.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}
	defer fileHandle.Close()

	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	sumIndices, ind := 0, 1
	var packets [][]interface{}

	two := toSlice(float64(2))
	six := toSlice(float64(6))

	packets = append(packets, two, six)

	for fileScanner.Scan() {
		if len(fileScanner.Text()) == 0 {
			continue
		}
		// Read a pair of packets and parse them into interface slices
		var first, second []interface{}
		json.Unmarshal(fileScanner.Bytes(), &first)
		fileScanner.Scan()
		json.Unmarshal(fileScanner.Bytes(), &second)
		packets = append(packets, first, second)

		if ok := compare(first, second); ok == 1 {
			sumIndices += ind
		}
		ind++
	}
	fmt.Println("Part 1:", sumIndices)

	// Part 2:
	// Sort the packets using the custom function
	sort.Slice(packets, func(i, j int) bool {
		res := compare(packets[i], packets[j])
		return res > 0
	})

	decoderKey := 1
	for ind, p := range packets {
		if reflect.DeepEqual(p, two) || reflect.DeepEqual(p, six) {
			decoderKey *= ind + 1
		}
	}
	fmt.Println("Part 2:", decoderKey)
}
