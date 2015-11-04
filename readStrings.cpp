#include <stdio.h>
#include <string.h>
#include <string>
#include <list>

void readStrings(	FILE *f,
			std::list<std::string> *strings,
			int trimStrings,	// remove spaces from begin/end
			int removeEmptyStrings //boolean
		)
{

char s[1024];
char *s0;
int L;
std::string str;
while(!feof(f))
{
	if(!fgets(s,1024,f)) break;
	L = strlen(s)-1;
	while(L>=0 && ( s[L]<' ' || trimStrings && s[L]<=' ' ) ) 
		{s[L]=0; L--;}	

	s0=s;
	if(trimStrings)
	{	
		while(*s0 && *s0<=' ') s0++;
	}	
		
	if(!removeEmptyStrings || L>0)
	{	str = s0;
		strings->push_back(str);
	}
}

}

/*
main()
{

FILE *f = fopen("strings.txt","r");
std::list<std::string> l;

readStrings( f, &l);

std::list<std::string>::iterator it;
for(it=l.begin(); it!=l.end(); it++)
{
	printf("[%s]\n",(*it).c_str());
}
return 0;
}
*/
