#include <stdio.h>
#include <Concerto/Core/Types.h>

int main(void)
{

#ifdef CCT_LANGUAGE_CPP
#error Not a C compiler!
#endif
	return 0;
}