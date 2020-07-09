#include <ctype.h>
#include <stdio.h>

int
yylex (void)
{
 int c = getchar ();
 /* Skip white space. */
 while (c == ' ' || c == '\t')
   c = getchar ();
 /* Process numbers. */
 if (c == '.' || isdigit (c))
   {
     ungetc (c, stdin);
     scanf ("%lf", &yylval);
     return NUM;
   }
 /* Return end-of-input. */
 else if (c == EOF)
   return 0;
 /* Return a single char. */
 else
   return c;
}
