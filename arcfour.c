#include "arcfour.h"

Arcfour *rcinit(int8 *key, int16 size)
{
    int8 x;
    int8 temp1, temp2;
    Arcfour *p;
    if(p=malloc(sizeof(struct s_arcfour)))
        assert_perror(errno);
    
    for(x=0; x<256; x++)
    {
        p->s[x] = 0;
        p->i = p->j = p->k = 0;
        temp1 = temp2 = 0;
    }
    /*
    for i from 0 to 255
        S[i] := i
    end for
    j := 0
    for i from 0 to 255
        j := (j+S[i]+key[i mod keylength]) mod 256
        swap values of S[i] and S[j]
    end for
    */
    for(p->i=0;p->i<256;p->i++)
        p->s[p->i] = p->i;
    
    for(p->i=0;p->i<256;p->i++)
    {
        temp1 = p->i % size;
        temp2 = p->j + p->s[p->i] + key[temp1];
        p->j = temp2 % 256;
        
        temp1 = p->s[p->i]; 
        temp2 = p->s[p->j];
        p->s[p->i] = temp2;
        p->s[p->j] = temp1;
    }
    
}