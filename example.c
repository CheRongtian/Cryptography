#include "arcfour.h"

#define F fflush(stdout)

// ef20 ac12 
void printbin(int8 *input, const int16 size)
{
    int16 i;
    int8 *p;
    
    assert(size > 0);
    for(i=size, p=input; i; i--, p++)
    {
        if(!(i%2)) printf(" ");
        printf("%.02x", *p);
    }
    printf("\n");
    
    return;
}

int main()
{
    Arcfour *rc4;
    int16 skey, stext;
    char *key, *from, *encrypted, *decrypted;
    
    key = from = encrypted = decrypted = 0;

    skey = stext = 0;


    key = "tomatoes"; /* 8 bits -> 2048 bits */
    skey = strlen(key);
    from = "Shall I compare three to a summer's day?";
    stext = strlen(from);
    
    printf("\nInitializing encryption..."); F;
    rc4 = rc4init((int8 *)key, skey);
    printf("done\n");

    printf("'%s'\n ->", from);
    encrypted = (char *)rc4encrypt(rc4, (int8 *)from, stext);
    printbin((int8 *)encrypted, stext);
    rc4uninit(rc4);
    
    printf("\nInitializing decryption..."); F;
    rc4 = rc4init((int8 *)key, skey);
    printf("done\n");

    decrypted = (char *)rc4decrypt(rc4, (int8 *)encrypted, stext);
    printf(" -> '%s'\n", decrypted);
    rc4uninit(rc4);

    return 0;
}