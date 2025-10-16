#define SUCCESS 0
#define FAIL -1

typedef struct psMax *ppsMax, **pppsMax;

// retorna o maior valor em max1
int getmax1(ppsMax ps, int *arr, int size, int *max1); 
// retorna o segundo maior valor em max2
int getmax2(ppsMax ps, int *arr, int size, int *max2);
// retorna o terceiro maior valor em max3
int getmax3(ppsMax ps, int *arr, int size, int *max3);

// retorna o produto entre os três maiores valores em product
int max_product(ppsMax ps, int *arr, int size, long long int *product);
// retorna a soma entre os três maiores valores em sum
int max_sum(ppsMax ps, int *arr, int size, int *sum);

// cria psMax
int cpsMax(pppsMax ps); 
// destroi psMax
int dpsMax(pppsMax ps); 