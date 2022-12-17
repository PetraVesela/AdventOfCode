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

type directory = map[string]any

func getAllDirSizes(m directory, allSizes *[]int) int {
	curDirSize := 0
	for _, v := range m {
		switch elem := v.(type) {
		case int:
			// File
			curDirSize += elem
		case directory:
			// Directory
			curDirSize += getAllDirSizes(elem, allSizes)
		}
	}
	*allSizes = append(*allSizes, curDirSize)
	return curDirSize
}

func addDir(m directory, curPath []string, dirName string) {
	if len(curPath) == 1 {
		newMap := make(directory)
		m[dirName] = newMap
	} else {
		x, curPath := curPath[0], curPath[1:]
		if nested, ok := m[x].(directory); ok {
			addDir(nested, curPath, dirName)
		}
	}
}

func addFile(m directory, curPath []string, fileName string, fileSize int) {
	if len(curPath) == 0 {
		m[fileName] = fileSize
	} else {
		x, curPath := curPath[0], curPath[1:]
		if nested, ok := m[x].(directory); ok {
			addFile(nested, curPath, fileName, fileSize)
		}
	}
}

func main() {
	// Open the input
	fileHandle, err := os.Open("7.txt")
	if err != nil {
		log.Fatalf("unable to read file: %v", err)
	}

	// Read the input line by line and construct a filesystem TRIE representation
	fileScanner := bufio.NewScanner(fileHandle)
	fileScanner.Split(bufio.ScanLines)

	filesystem := make(directory)
	var curPath []string

	cdRegex := regexp.MustCompile(`\$ cd ([a-z]+|/|..)`)
	for fileScanner.Scan() {
		// Change directory:
		if strings.Contains(fileScanner.Text(), "$ cd") {
			dirname := cdRegex.FindStringSubmatch(fileScanner.Text())[1]
			if dirname == ".." {
				// pop last
				curPath = curPath[:len(curPath)-1]
			} else {

				// append new directory name
				curPath = append(curPath, dirname)
				addDir(filesystem, curPath, dirname)
			}
		} else if fileScanner.Text() == "$ ls" || strings.Contains(fileScanner.Text(), "dir ") {
			continue
		} else {
			// a file
			res := strings.Split(fileScanner.Text(), " ")
			size, _ := strconv.Atoi(res[0])
			name := res[1]
			addFile(filesystem, curPath, name, size)
		}
	}

	// Part 1:
	// Get sizes of all directories
	var allSizes []int
	getAllDirSizes(filesystem, &allSizes)

	sum := 0
	for _, size := range allSizes {
		if size < 100000 {
			sum += size
		}
	}
	fmt.Println("Part 1:", sum)

	// Part 2:
	totalSpace := 70000000
	requiredSpace := 30000000

	sort.Sort(sort.Reverse(sort.IntSlice(allSizes)))
	freeSpace := totalSpace - allSizes[0]
	requiredExtraSpace := requiredSpace - freeSpace
	for i, dirSize := range allSizes {
		if dirSize <= requiredExtraSpace {
			fmt.Println("Part 2:", allSizes[i-1])
			break
		}
	}
}
