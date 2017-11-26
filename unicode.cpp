#include <iostream>
#include <string>
#include "utf8.h"
#include <cstdint>

#define UTF8_ACCEPT 0
#define UTF8_REJECT 12

static const uint8_t utf8d[] = {
  // The first part of the table maps bytes to character classes that
  // to reduce the size of the transition table and create bitmasks.
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
   7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
   8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

  // The second part is a transition table that maps a combination
  // of a state of the automaton and a character class to a state.
   0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
  12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
  12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
  12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
  12,36,12,12,12,12,12,12,12,12,12,12, 
};

uint32_t inline
decode(uint32_t* state, uint32_t* codep, uint32_t const byte) {
  uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state + type];
  return *state;
}

void
printCodePoints(uint8_t* s) {
  uint32_t codepoint;
  uint32_t state = 0;

  for (; *s; ++s)
    if (!decode(&state, &codepoint, *s))
      printf("U+%04X\n", codepoint);

  if (state != UTF8_ACCEPT)
    printf("The string is not well-formed\n");

}

int
countCodePoints(uint8_t const* s, size_t* count) {
  uint32_t codepoint;
  uint32_t state = 0;

  for (*count = 0; *s; ++s)
    if (!decode(&state, &codepoint, *s))
      *count += 1;

  return state != UTF8_ACCEPT;
}

int main(int argc, char const *argv[])
{
	std::string s1 = u8"this is 中文字符";

	utf8::iterator<std::string::iterator> iter(s1.begin(), s1.begin(), s1.end());

	for(int i = 0; i < utf8::distance(s1.begin(), s1.end()); i++, ++iter)
	{
	    std::cout<< (*iter);
	}
	printf("\n");

	//////////////////////////////////////////
	size_t count;
	int state = countCodePoints( reinterpret_cast<uint8_t const*>( s1.c_str() ), &count );
	printf("count code point: %d\n", count );

	return 0;
}