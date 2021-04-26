#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

///This code has Checking and works correctly

///creating dynamic array
double* t;                   //time
size_t t_size=400;

double* X;                  //event
size_t X_size=400;

double ran_expo(double lambda){
    double u;
    u = rand() / (RAND_MAX + 1.0);
  //  u=(rand() / ((1 - 0 )+ 1.0)) + 0;
  printf("Random: %lf  lambda= %lf",u,lambda);
    //return -log(1- u) / lambda;
    return log(1/u)*(1/lambda);
}


int main(int argc,char *argv[]){
    srand(time(0));
     int i=0;  //c will keep track of whether the array has reached its full size or not after which we have to reallocate
     X= calloc(X_size, sizeof(double));
     t= calloc(t_size, sizeof(double));
     t[0]=0,X[0]=0;  ///dynamic arrays

     int tend=100;   ///final time
     double r1,r2;      ///generates random number.

     double tau;

     double rates[2];
     double rate_sum;
     double k=2.0;
     double gamma=0.1;

     while(t[i]<tend){
     ///printf("%lf\n",t[i]);

      rates[0]= k;
      rates[1]= gamma*X[i];
      rate_sum=rates[0]+rates[1];  //sum of rates
      ///here we take the a random time where we want to check what even may occur at that time

      r1=rand() / (RAND_MAX + 1.0);
      //tau=(double)(1.0/rate_sum)*log(1.0/1);
      tau=ran_expo(rate_sum);   //this works better than the expression before

      t[i+1]=t[i]+tau;
      printf("Tau=%lf  -> Time[%d]=%lf  X[%d]=%lf \n",tau,i,t[i],i,X[i]); //A checker to see if the values of tau and t[i] are updating

      ///here we take the probability of the even happening will be its rate over sum of all the rates.
       r2=rand() / (RAND_MAX + 1.0);
       if(r2*rate_sum < rates[0]){
       X[i+1]=X[i]+1;
       }
       else if((r2*rate_sum>rates[0] && r2*rate_sum) <= (rates[0]+rates[1]) ){
        X[i+1] =X[i]-1;
       }
       i++;
    }
free(X);
free(t);
}
