// DIESE DATEI NICHT BEARBEITEN
#include <iostream>

#include "fse.h"

using namespace std;

int main(int argc, char const *argv[]) {
  int n, m;
  cin >> n >> m;
  vector<string> lines(n);
  for (auto &line : lines) cin >> line;
  int solution = solve(lines);
  cout << solution<<endl;
  return 0;
}
