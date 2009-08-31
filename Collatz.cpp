/*
 * Collatz.cpp
 *
 *  Created on: Aug 28, 2009
 *      Author: rsmith
 */


#include <stdlib.h>
#include <stdio.h>

#define CACHE_MASK 0x1FFFF
#define CACHE_SIZE ( (CACHE_MASK)+1)
#define CACHEINDEX(n) (n & (CACHE_MASK))

typedef unsigned int uint;

struct entry  {
	uint value;
	short unsigned int cycle_len;
	short unsigned int hits;
};

entry cache[CACHE_SIZE];

uint compute_cycle_len(uint);

inline bool lookup_cached_len(uint n) {
	return (cache[ CACHEINDEX(n) ].value  == n);
}

inline uint get_cached_len(uint n) {
	uint result=0;
	uint idx = CACHEINDEX(n);
	entry * e = cache+idx;
	if(n==e->value) {
		result=e->cycle_len;
		e->hits++;
	}
	return result;
}

inline void put_cached_len(uint n, uint l) {
	uint idx =  CACHEINDEX(n);
	entry * e = cache+idx;
	if(l > e->cycle_len*e->hits) {
		e->cycle_len=l;
		e->value=n;
		e->hits=1;
	}
}

inline uint get_cycle_len(uint n) {
	uint l = get_cached_len(n);
	if(l==0) {
		l=compute_cycle_len(n);
		put_cached_len(n,l);
	} 
	return l;
}

inline uint compute_cycle_len(uint n) {
	register uint len=1;
	register uint m=n;
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

inline uint compute_max_cycle_len(uint min, uint max) {
	register uint maxlen=0;
	register uint curlen=0;
	register uint i;
	for(i=min;i<=max;i++) {
		curlen = get_cycle_len(i);
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
	}
	
	
	return 0;
}
