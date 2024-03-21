#ifndef COQUE_COMMON_H
#define COQUE_COMMON_H

#define u8 unsigned char
#define i8 char
#define u16 unsigned short
#define i16 short
#define u32 unsigned int
#define i32 int
#define u64 unsigned long long
#define i64 unsigned long long
#define nullptr 0

typedef struct {
  float vel;
  u8 hp;
  u8 mp;
} stats_t;

#endif
