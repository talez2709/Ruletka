#pragma once
#ifndef MT_H
#define MT_H_

typedef unsigned long long ulong;

__forceinline extern void InicjujMT(unsigned int x0);
__forceinline extern unsigned int MersenneTwister();

static unsigned int MT[624];
static int mti = 0;

#endif