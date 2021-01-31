#include <unistd.h>
#include <stdio.h>

int main()
{   
    char hostname[200];
    gethostname(hostname, 200);
    printf("Hostname is  %s",hostname);
    return 0;
}
