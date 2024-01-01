// A recursion is linear when inside the loop itself is called one time
// therefore, a tree recursion is when inside the loop we have more than one
// recursion calls
#include <stdio.h>

void treeRecursion(int n) {
  if (n > 0) {
    printf("%d ", n);
  }

  treeRecursion(n - 1);
  treeRecursion(n - 1);
}

int main() {
  treeRecursion(3);

  return 0;
}
