#include <iostream>
using namespace std;

const int M = 75;
const int L = 200;

int f[M][L];

int prime[168] = 
   {2,    3,    5,    7,   11,   13,   17,   19,   23,   29, 
   31,   37,   41,   43,   47,   53,   59,   61,   67,   71, 
   73,   79,   83,   89,   97,  101,  103,  107,  109,  113, 
  127,  131,  137,  139,  149,  151,  157,  163,  167,  173, 
  179,  181,  191,  193,  197,  199,  211,  223,  227,  229, 
  233,  239,  241,  251,  257,  263,  269,  271,  277,  281, 
  283,  293,  307,  311,  313,  317,  331,  337,  347,  349, 
  353,  359,  367,  373,  379,  383,  389,  397,  401,  409, 
  419,  421,  431,  433,  439,  443,  449,  457,  461,  463, 
  467,  479,  487,  491,  499,  503,  509,  521,  523,  541, 
  547,  557,  563,  569,  571,  577,  587,  593,  599,  601, 
  607,  613,  617,  619,  631,  641,  643,  647,  653,  659, 
  661,  673,  677,  683,  691,  701,  709,  719,  727,  733, 
  739,  743,  751,  757,  761,  769,  773,  787,  797,  809, 
  811,  821,  823,  827,  829,  839,  853,  857,  859,  863, 
  877,  881,  883,  887,  907,  911,  919,  929,  937,  941, 
  947,  953,  967,  971,  977,  983,  991,  997};
	
const int N = 10;
void multiply(int *a, int c){
  	int i;
   	a[1] = a[1] * c;
	for (i = 2; i <= a[0]; i++){
       	a[i] *= c;
     	a[i] += a[i-1] / N;
		a[i-1] %= 10;
    }
    while (a[a[0]] >= N){
      	a[0]++;
	   	a[a[0]] = a[a[0]-1] / N;
	   	a[a[0]-1] %= N;
    }
}

bool smart(int *a, int *b)
{
    if (a[0] < b[0]) return true;
    if (a[0] > b[0]) return false;
    
    //cout<<"="<<endl;
    for (int i = a[0]; i > 0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    
    //cout<<"=="<<endl;
    return false;
}

int main()
{
    memset(f, 0, sizeof(f));
    f[1][0] = 1;    f[1][1] = 1;
    for (int i = 2; i < M; i++)
    {
        for (int j = 0; j < L; j++) f[i][j] = f[i - 1][j];
        multiply(f[i], prime[i - 2]);
    }
    /*
    for (int i = 1; i < M; i++)
    {
        for (int j = f[i][0]; j > 0; j--)
        {
            cout<<f[i][j];
        }
        cout<<endl;
    }
    
    system("pause");
    */
    int t;
    scanf("%d", &t);
    getchar();
    char s[200];
    int d[200];
    while(t--)
    {
        gets(s);
        memset(d, 0, sizeof(d));
        d[0] = strlen(s);
        for (int i = 1; i <= d[0]; i++)
        {
            d[i] = s[d[0] - i] - '0';
        }

        for (int i = 1; i < M; i++)
        {
            //cout<<i<<"X"<<endl;
            if (smart(d, f[i]))
            {
                for (int j = f[i - 1][0]; j > 0; j--)
                {
                    printf("%d", f[i - 1][j]);
                }
                printf("\n");
                break;
            }
        }
    }
    
    //system("pause");
    return 0;
}
