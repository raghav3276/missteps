// Copyright 2009-2017 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2017, Sandia Corporation
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	const int LENGTH = 1024*1024;

	int* buf = (int*) malloc(sizeof(int) * LENGTH);

	int i = 0;
	for(i = 0; i < LENGTH; i++){
		buf[i] = i;
	}
	int sum = 0;
	for(i = 0; i < LENGTH; i++){
		sum += buf[i];
	}

	printf("%d\n", sum);

	free(buf);
}
