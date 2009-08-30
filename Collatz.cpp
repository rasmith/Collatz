/*
 * Collatz.cpp
 *
 *  Created on: Aug 28, 2009
 *      Author: rsmith
 */


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char buf[8];
unsigned int idx=0;
char ch;

unsigned int compute_cycle_len(unsigned int);

unsigned int get_cached_len(unsigned int n) {
	return 0;
}

unsigned int get_cycle_len(unsigned int n) {
	unsigned int l = get_cached_len(n);
	if(l==0) {
		l=compute_cycle_len(n);
	}
	return l;
}

unsigned  int compute_cycle_len(unsigned int n) {
	unsigned int len=1;
	unsigned int m=n;
	while(m!=1) {
		//printf("m=%u, len=%u\n",m,len);
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

unsigned long int compute_max_cycle_len(unsigned int min, unsigned int max) {
	unsigned int maxlen=0;
	unsigned int curlen=0;
	for(unsigned int i=min;i<=max;i++) {
		curlen = get_cycle_len(i);
		//printf("curlen=%u, maxlen=%u\n",curlen,maxlen);
		if(curlen>maxlen) {
			maxlen=curlen;
		}
	}
	return maxlen;
}

int main (int argc, char ** argv) {
	unsigned  int min;
	unsigned  int max;
	unsigned  int min0;
	unsigned  int max0;
	unsigned  int  maxlen;
	unsigned  int temp;
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
