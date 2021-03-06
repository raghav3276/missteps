#ifndef PCM_H_
#define PCM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <omp.h>

#define PCM_NUM_BANKS		8
//#define PCM_ROWS_PER_BANK	(1024 * 32)
#define PCM_ROWS_PER_BANK	(128 * 1)
#define PCM_ROW_SIZE		(1024 * 8)
#define PCM_BANK_SIZE		(PCM_ROWS_PER_BANK * PCM_ROW_SIZE)
#define PCM_NUM_ROWS		(PCM_NUM_BANKS * PCM_ROWS_PER_BANK)
#define PCM_SIZE			(PCM_NUM_ROWS * PCM_ROW_SIZE)

#define PCM_OFF(base, p)    ((char*)p - (char *)base)
#define PCM_P2R(base, p)    (PCM_OFF(base, p) % PCM_ROW_SIZE)
#define PCM_P2B(base, p)    (PCM_OFF(base, p) % PCM_BANK_SIZE)
#define PCM_R2B(r)          (r % PCM_NUM_BANKS)
#define PCM_R2P(base, r)    ((char *)base + (r * PCM_ROW_SIZE))

struct pcm_thread {
	pthread_t pthread;
	unsigned long (* count_fn)(void *row);
	unsigned long count;
	void (* fn)(void *row);
	int num_rows;
	void * rows[PCM_ROWS_PER_BANK];
};

void pcm_thread_add_row(struct pcm_thread * pth, void * base, int row);
void pcm_threads_map_fn(
		struct pcm_thread pcm_threads[], int num_threads,
		void (* fn)(void *row)
		);
void pcm_threads_map_count_fn(
		struct pcm_thread pcm_threads[], int num_threads,
		unsigned long (* count_fn)(void *row)
		);
void pcm_threads_reduce_count_fn(
		struct pcm_thread pcm_threads[], int num_threads,
		void (* count_reduce)(unsigned long count)
		);

void pcm_threads_spawn(struct pcm_thread pcm_threads[], int num_threads);
void pcm_threads_join(struct pcm_thread pcm_threads[], int num_threads);

#endif /* PCM_H_ */
