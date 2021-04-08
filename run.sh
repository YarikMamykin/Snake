#!/bin/bash

if [ -d "build" ]; then
	pushd ${PWD}
	cd build/src
	if [ -e "Snake" ]; then
		./Snake
	fi
	popd
fi
