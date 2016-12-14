
#include <mars/mars.h>

int main(int argc, char* argv[]) {

    unsigned int vectorSrc[10] = {6,3,9,8,9,6,6,2,1,3};
    unsigned int vectorDest[10];
    unsigned int vectorIndexes[10];

    sort_ascend_unsignedint(vectorDest, vectorIndexes, (const unsigned int *) vectorSrc, 10);
    

}