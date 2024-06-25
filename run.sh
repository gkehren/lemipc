#!/bin/bash

export TEAM_NUMBERS=(1 2 3)
export PROCESSES=5

for TEAM_NUMBER in "${TEAM_NUMBERS[@]}"; do
	echo "Starting $PROCESSES processes for team number $TEAM_NUMBER"
	for i in $(seq 1 $PROCESSES); do
		./lemipc $TEAM_NUMBER &
	done
	echo "All processes for team number $TEAM_NUMBER have been started"
done

echo "All processes for all teams have been started"
