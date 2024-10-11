#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

static_assert(sizeof(uintptr_t) == 8 , "64 bits platform needed!");
static_assert(sizeof(uintptr_t) == sizeof(void*), "void* and uintptr_t size mismatch!");

void* tag(void* p, uint64_t tag)
{
  assert(tag < 8);
  return (void*)((uintptr_t)p | (tag << 61));
}

uint64_t get_tag(void* p)
{
  return (uintptr_t)p >> 61;
}

void* ptr(void* p)
{
  return (void*) ((uintptr_t)p & 0x1FFFFFFFFFFFFFFFu);
}

int main()
{
  int* p = malloc(sizeof(int));
  assert(p != NULL && "Memory exhausted");
  assert(((uintptr_t)p & 0xE000000000000000u) == 0);
  *p = 1021;

  p = tag(p, 5);
  assert(get_tag(p) == 5);
 
  int* tmp = (int*)ptr(p);
  assert(*tmp == 1021);

  free(ptr(p));

  return EXIT_SUCCESS;
}


