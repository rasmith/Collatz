/*
 * Collatz.cpp
 *
 *  Created on: Aug 28, 2009
 *      Author: rsmith
 */


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef unsigned int uint;

struct entry  {
	uint value;
	uint cycle_len;
	uint count;
};



char buf[8];
uint idx=0;
char ch;

#define CACHE_MASK 0x1FFFF
#define CACHE_SIZE ( (CACHE_MASK)+1)
#define BUCKET_SIZE 4
#define CACHEINDEX(n) (n & (CACHE_MASK))

entry cache[CACHE_SIZE];

uint compute_cycle_len(uint);
//uint lens[600];
//uint misses=0;
//uint hits=0;

inline bool lookup_cached_len(uint n) {
	return (cache[ CACHEINDEX(n) + 0].value  == n);
}

inline uint get_cached_len(uint n) {
	uint result=0;
	uint idx = CACHEINDEX(n);
	if(n==cache[idx].value) {
		//cache[idx].count++;
		result=cache[idx].cycle_len;
	}
	//	hits++;
	//} else {
	//	misses++;
	//}
	return result;
}

inline uint put_cached_len(uint n, uint l) {
	uint idx =  CACHEINDEX(n);
	if(l > cache[idx].cycle_len) {
		cache[idx].cycle_len=l;
		cache[idx].value=n;
	}
}

uint get_cycle_len(uint n) {
	uint l = get_cached_len(n);
	if(l==0) {
		l=compute_cycle_len(n);
		put_cached_len(n,l);
	} 
	return l;
}

uint compute_cycle_len(uint n) {
	uint len=1;
	uint m=n;
	while(m!=1) {
		if(lookup_cached_len(m)) {
			return len+get_cached_len(m)-1;
		} else
		if( (m & 0x1)  == 0) {		
				m = m >> 1;
				len++;
		} else {
			m = (m << 1) + m + 1;
			len++;
		}
	}
	return len;
}

uint compute_max_cycle_len(uint min, uint max) {
	uint maxlen=0;
	uint curlen=0;
	for(uint i=min;i<=max;i++) {
		curlen = get_cycle_len(i);
	//	lens[curlen]++;
		//printf("curlen=%u, maxlen=%u\n",curlen,maxlen);
		if(curlen>maxlen) {
			maxlen=curlen;
		}
	}
	return maxlen;
}

int main (int argc, char ** argv) {
	uint min;
	uint max;
	uint min0;
	uint max0;
	uint  maxlen;
	uint temp;
	
	while(scanf("%u %u",&min,&max)==2) {
		min0=min;
		max0=max;
		if(min > max) {
			temp = min;
			min = max;
			max = temp;
		}
		maxlen =compute_max_cycle_len(min,max);
		printf("%u %u %u\n",min0,max0,maxlen);
	//	printf("%d %d",misses,hits);
	}
	
	
	return 0;
}
