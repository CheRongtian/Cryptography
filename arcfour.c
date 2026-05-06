#include "arcfour.h"

export Arcfour *rc4init(int8 *key, int16 size)
{
    int x;
    int8 temp1, temp2;
    Arcfour *p;
    if(!(p=malloc(sizeof(struct s_arcfour))))
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for(x=0; x<256; x++)
        p->s[x] = 0;

    p->i = p->j = p->k = 0;
    temp1 = temp2 = 0;
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
    for(x=0; x<256; x++)
        p->s[x] = x;
    //for(p->i=0;p->i<256;p->i++)
    //    p->s[p->i] = p->i;
    
    for(x=0;x<256;x++)
    {
        temp1 = x % size;
        temp2 = p->j + p->s[x] + key[temp1];
        p->j = temp2 % 256;
        
        temp1 = p->s[x]; 
        temp2 = p->s[p->j];
        p->s[x] = temp2;
        p->s[p->j] = temp1;
    }
    p->i = p->j = 0;

    return p;
}

int8 rc4byte(Arcfour *p)
{
    int16 tmp1, tmp2;
    /*
    j := 0
    i := 0
    while GeneratingOutput:
        i := (i + 1) mod 256
        j := (j + S[i]) mod 256
        swap values of S[i] and S[j]
        t := (S[i] + S[j]) mod 256
        K := S[t]
        output K
    endwhile
    */
    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->s[p->i]) % 256;
    tmp1 = p->s[p->i]; 
    tmp2 = p->s[p->j];
    p->s[p->i] = tmp2;
    p->s[p->j] = tmp1;
    tmp1 = (p->s[p->i] + p->s[p->j]) % 256;
    p->k = p->s[tmp1];

    return p->k;
}

export int8 *rc4encrypt(Arcfour *p, int8 *cleartext, int16 size)
{
    int8 *ciphertext;
    int16 x;

    ciphertext = (int8 *)malloc(size+1);
    if(!ciphertext)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    
    ciphertext[size] = '\0';
    
    for(x=0; x<size; x++)
        ciphertext[x] = cleartext[x] ^ rc4byte(p);
    
    return ciphertext;
}