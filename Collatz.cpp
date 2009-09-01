/*
 * Collatz.cpp
 *
 *  Created on: Aug 28, 2009
 *      Author: rsmith
 */


#include <stdlib.h>
#include <stdio.h>

#define CACHE_MASK 0x01FFFF
#define CACHE_SIZE ( (CACHE_MASK)+1)
#define CACHEINDEX(n) (n & (CACHE_MASK))

typedef unsigned int uint;

struct entry  {
	uint value;
	short unsigned int cycle_len;
};

entry cache[CACHE_SIZE];

uint compute_cycle_len(uint);
/**
inline uint get_cached_len(uint n) {
	entry * e = cache+CACHEINDEX(n);
	return (n==e->value ? e->hits++, e->cycle_len : 0);
}

inline void put_cached_len(uint n, uint l) { 
	entry * e = cache + CACHEINDEX(n);
	if(l > e->cycle_len*e->hits) {
		e->cycle_len=l;
		e->value=n;
		e->hits=1;
	}
}**/

inline uint get_cached_len(uint n) {
	entry * e = cache + (n & 0x1FFFF);
	if(n==e->value) {
		return e->cycle_len;
	}
	return 0;
}

inline void put_cached_len(uint n, uint l) { 
	entry * e = cache + (n & 0x01FFFF);
	if(l>=e->cycle_len) {
		e->cycle_len=l;
		e->value=n;
	}
	return;
}

inline uint compute_cycle_len(uint n) {
	register uint len=1;
	register uint m=n;
	register uint lookup=0;
	while(m!=1) {
		lookup=get_cached_len(m);
		if(lookup != 0) {
			len = len+lookup-1;
			break;
		} else
		if( (m & 0x1)  == 0) {		
				m = m >> 1;
				len++;
		} else {
			m = (m << 1) + m + 1;
			len++;
		}
	}
	put_cached_len(n,len);
	return len;
}

inline uint compute_max_cycle_len(uint min, uint max) {
	register uint maxlen=0;
	register uint curlen=0;
	register uint i;
	for(i=min;i<=max;i++) {
		curlen = compute_cycle_len(i);
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
