package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func isVisibleFromTop(trees [][]int, x int, y int) bool {
	for i := 0; i < x; i++ {
		if trees[i][y] >= trees[x][y] {
			return false
		}
	}
	return true
}

func isVisibleFromBottom(trees [][]int, x int, y int) bool {
	for i := len(trees) - 1; i > x; i-- {
		if trees[i][y] >= trees[x][y] {
			return false
		}
	}
	return true
}

func isVisibleFromLeft(trees [][]int, x int, y int) bool {
	for i := 0; i < y; i++ {
		if trees[x][i] >= trees[x][y] {
			return false
		}
	}
	return true
}

func isVisibleFromRight(trees [][]int, x int, y int) bool {
	for i := len(trees) - 1; i > y; i-- {
		if trees[x][i] >= trees[x][y] {
			return false
		}
	}
	return true
}

func getScenicScore(trees [][]int, x int, y int) int {
	top := 0
	for i := x - 1; i >= 0; i-- {
		top++
		if trees[i][y] >= trees[x][y] {
			break
		}

	}
	bottom := 0
	for i := x + 1; i < len(trees); i++ {
		bottom++
		if trees[i][y] >= trees[x][y] {
			break
		}
	}
	left := 0
	for i := y - 1; i >= 0; i-- {
		left++
		if trees[x][i] >= trees[x][y] {
			break
		}

	}
	right := 0
	for i := y + 1; i < len(trees); i++ {
		right++
		if trees[x][i] >= trees[x][y] {
			break
		}
	}
	return top * bottom * left * right
}

func main() {
	// Read input into a 2D int array
	body, err := os.ReadFile("8.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	lines := strings.Split(string(body), "\n")
	trees := make([][]int, len(lines))

	for r, line := range lines {
		lineTrees := strings.Split(line, "")
		trees[r] = make([]int, len(lineTrees))
		for c, tree := range lineTrees {
			treeHeight, _ := strconv.Atoi(tree)
			trees[r][c] = treeHeight
		}
	}

	// Part 1:
	// The trees on the edge are always visible
	numVisible := len(lines)*2 + 2*(len(lines)-2)
	// Then for each tree inside the always-visible circle...
	for r := 1; r < len(lines)-1; r++ {
		for c := 1; c < len(lines)-1; c++ {
			// ... check if it is visible from some direction
			if isVisibleFromTop(trees, r, c) || isVisibleFromBottom(trees, r, c) || isVisibleFromRight(trees, r, c) || isVisibleFromLeft(trees, r, c) {
				numVisible++
			}
		}
	}
	fmt.Println("Part 1: ", numVisible)

	maxScenicScore := 0
	// Part 2:
	// Skip the edges again
	for r := 1; r < len(lines)-1; r++ {
		for c := 1; c < len(lines)-1; c++ {
			score := getScenicScore(trees, r, c)
			if score > maxScenicScore {
				maxScenicScore = score
			}
		}
	}
	fmt.Println("Part 2: ", maxScenicScore)
}
