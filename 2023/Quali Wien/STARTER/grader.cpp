#include <cstdio>
#include "starter.h"

int main() {
  int subtask;
  scanf("%d", &subtask);
  if (subtask == 1) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", subtask1(a, b));
  } else if (subtask == 2) {
    int n;
    scanf("%d", &n);
    printf("%d\n", subtask2(n));
  } else if (subtask == 3) {
    int n;
    scanf("%d", &n);
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &v[i]);
    int x;
    scanf("%d", &x);
    printf("%s\n", subtask3(v, x) ? "true" : "false");
  } else {
    printf("invalid subtask %d\n", subtask);
    return 1;
  }
  return 0;
}
