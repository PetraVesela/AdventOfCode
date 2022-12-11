package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"sort"
	"strconv"
	"strings"
)

type directory = map[string]interface{}

func print_filesystem(m directory, level int) {
	offset := strings.Repeat(" ", level*2)
	for k, v := range m {
		_, ok := v.(int)
		if ok {
			// File
			fmt.Printf("%s - %s (file, size= %d)\n", offset, k, v)
		} else {
			nested, ok := v.(directory)
			if ok {
				// Directory
				fmt.Println(offset, "-", k, "(dir)")
				print_filesystem(nested, level+1)
			}
		}
	}
}

func get_all_dir_sizes(m directory, all_sizes *[]int) int {
	cur_dir_size := 0
	for _, v := range m {
		size, ok := v.(int)
		if ok { // File
			cur_dir_size += size
		} else {
			nested, ok := v.(directory)
			if ok {
				// Directory
				cur_dir_size += get_all_dir_sizes(nested, all_sizes)
			}
		}
	}
	*all_sizes = append(*all_sizes, cur_dir_size)
	return cur_dir_size
}

func add_dir(m directory, cur_path []string, dir_name string) {
	if len(cur_path) == 1 {
		new_map := make(directory)
		m[dir_name] = new_map
	} else {
		x, cur_path := cur_path[0], cur_path[1:]
		nested, ok := m[x].(directory)
		if ok {
			add_dir(nested, cur_path, dir_name)
		}
	}
}

func add_file(m directory, cur_path []string, file_name string, file_size int) {
	if len(cur_path) == 0 {
		m[file_name] = file_size
	} else {
		x, cur_path := cur_path[0], cur_path[1:]
		nested, ok := m[x].(directory)
		if ok {
			add_file(nested, cur_path, file_name, file_size)
		}
	}
}

func main() {

	// Open the input
	fileHandle, err := os.Open("inputs/7.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	// Read the input line by line and construct a filesystem TRIE representation
	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	filesystem := make(directory)
	var cur_path []string

	cd_regex, _ := regexp.Compile("\\$ cd ([a-z]+|/|..)")
	for fileScanner.Scan() {
		// Change directory:
		if strings.Contains(fileScanner.Text(), "$ cd") {
			dir_name := cd_regex.FindStringSubmatch(fileScanner.Text())[1]
			if dir_name == ".." {
				// pop last
				cur_path = cur_path[:len(cur_path)-1]
			} else {

				// append new directory name
				cur_path = append(cur_path, dir_name)
				add_dir(filesystem, cur_path, dir_name)
			}
		} else if fileScanner.Text() == "$ ls" || strings.Contains(fileScanner.Text(), "dir ") {
			continue
		} else {
			// a file
			res := strings.Split(fileScanner.Text(), " ")
			size, _ := strconv.Atoi(res[0])
			name := res[1]
			add_file(filesystem, cur_path, name, size)
		}
	}

	// print_filesystem(filesystem, 0)

	// Part 1:
	// Get sizes of all directories
	var all_sizes []int
	get_all_dir_sizes(filesystem, &all_sizes)

	sum := 0
	for _, size := range all_sizes {
		if size < 100000 {
			sum += size
		}
	}
	fmt.Println("Part 1: ", sum)

	// Part 2:
	total_space := 70000000
	required_space := 30000000

	sort.Sort(sort.Reverse(sort.IntSlice(all_sizes)))
	free_space := total_space - all_sizes[0]
	required_extra_space := required_space - free_space
	for ind, dir_size := range all_sizes {
		if dir_size <= required_extra_space {
			fmt.Println("Part 2:", all_sizes[ind-1])
			break
		}
	}
}
