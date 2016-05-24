#include <math.h>   // M_E
#include <stdio.h>  // printf

int main()
{
  double account = M_E - 1;

  printf("%lf\n", account);
  for (int i = 1; i <= 25; i++)
  {
    account = 2 * account - 1;
    account = account > 0 ? account : 0;
    printf("%lf\n", account);
  }
}
