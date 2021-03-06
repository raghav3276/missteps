#include "pcm.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void write_fn(void* row){
	int i = 0;
	int *buf = (int *) row;
	for(i = 0; i < PCM_ROW_SIZE/sizeof(int); i++){
		buf[i] = i;
	}
}

int main(int argc, char* argv[]) {
	char* buf = (char *) malloc(PCM_SIZE);
	struct pcm_thread pcm_threads[PCM_NUM_BANKS];

	memset(pcm_threads, 0, sizeof(pcm_threads));

	struct timeval t1, t2;
	float execution_time;

	int r, b;
	for(r = 0; r < PCM_NUM_ROWS; r++) {
		int bank = PCM_R2B(r);
        pcm_thread_add_row(pcm_threads + bank, buf, r);
	}

	gettimeofday(&t1, NULL);

	for(b = 0; b < PCM_NUM_BANKS; b++) {
		struct pcm_thread * pth = pcm_threads + b;
		pth->fn = write_fn;
	}

	pcm_threads_spawn(pcm_threads, PCM_NUM_BANKS);
	pcm_threads_join(pcm_threads, PCM_NUM_BANKS);

	gettimeofday(&t2, NULL);
	execution_time = ((t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec)) / (float) 1000;
	printf("Time taken: %.2f ms\n", execution_time);

	free(buf);
}
