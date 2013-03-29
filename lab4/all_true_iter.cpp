#include <iostream>
#include <cstdlib>

using namespace std;

bool all_true(bool* b, int n)
{
  for (int i = 0; i < n; ++i)
	if (!b[i]) return false;
  return true;
}

int main(int argc, char*argv[])
{
  int n = atoi(argv[1]);
  
  bool* a = new bool[n];

  for (int i = 0; i < n; ++i)
    a[i] = true;

  bool x = all_true(a, n);

  cout << boolalpha << x << endl;

  return 0;
}
