package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func is_visible_from_top(trees [][]int, x int, y int) bool {
	for i := 0; i < x; i++ {
		if trees[i][y] >= trees[x][y] {
			return false
		}
	}
	return true
}

func is_visible_from_bottom(trees [][]int, x int, y int) bool {
	for i := len(trees) - 1; i > x; i-- {
		if trees[i][y] >= trees[x][y] {
			return false
		}
	}
	return true
}

func is_visible_from_left(trees [][]int, x int, y int) bool {
	for i := 0; i < y; i++ {
		if trees[x][i] >= trees[x][y] {
			return false
		}
	}
	return true
}

func is_visible_from_right(trees [][]int, x int, y int) bool {
	for i := len(trees) - 1; i > y; i-- {
		if trees[x][i] >= trees[x][y] {
			return false
		}
	}
	return true
}

func get_scenic_score(trees [][]int, x int, y int) int {
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
	body, err := os.ReadFile("inputs/8.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	lines := strings.Split(string(body), "\n")
	trees := make([][]int, len(lines))

	for r, line := range lines {
		line_trees := strings.Split(line, "")
		trees[r] = make([]int, len(line_trees))
		for c, tree := range line_trees {
			tree_height, _ := strconv.Atoi(tree)
			trees[r][c] = tree_height
		}
	}

	// Part 1:
	// The trees on the edge are always visible
	num_visible := len(lines)*2 + 2*(len(lines)-2)
	// Then for each tree inside the always-visible circle...
	for r := 1; r < len(lines)-1; r++ {
		for c := 1; c < len(lines)-1; c++ {
			// ... check if it is visible from some direction
			if is_visible_from_top(trees, r, c) || is_visible_from_bottom(trees, r, c) || is_visible_from_right(trees, r, c) || is_visible_from_left(trees, r, c) {
				num_visible++
			}
		}
	}
	fmt.Println("Part 1: ", num_visible)

	max_scenic_score := 0
	// Part 2:
	// Skip the edges again
	for r := 1; r < len(lines)-1; r++ {
		for c := 1; c < len(lines)-1; c++ {
			this_score := get_scenic_score(trees, r, c)
			if this_score > max_scenic_score {
				max_scenic_score = this_score
			}
		}
	}
	fmt.Println("Part 2: ", max_scenic_score)
}
