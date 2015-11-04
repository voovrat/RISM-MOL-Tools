#ifndef strcpyUntil_h
#define strcpyUntil_h


//
// copy src to dsc until the one character in separators
// the function returns the pointer to the end of the resulted string (to the \0 character)
//

char *strcpyUntil(	char *dst,
			const char *src,
			const char *separators
		);

#endif
