#!/bin/bash

for (( noun=0; noun <= 99; noun = noun+1)); do
	for (( verb=0; verb <= 99; verb = verb+1)); do
		./a $noun $verb
	done
done