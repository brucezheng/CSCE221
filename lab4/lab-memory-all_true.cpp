#include <iostream>

bool all_true(bool* b, int i, int n)
{
  if (i < n)
    return b[i] && all_true(b, i+1, n);
  else
    return true;
}

int main()
{
  const int n = 100000;

  bool* a = new bool[n];

  for (int i = 0; i < n; ++i)
    a[i] = true;

  bool x = all_true(a, 0, n);

  std::cout << std::boolalpha << x << std::endl;

  return 0;
}