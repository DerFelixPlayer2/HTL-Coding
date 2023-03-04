#include <assert.h>
#include <iostream>

char mat[105][105];

int main() {
    int N, M, K;
    std::cin >> N >> M >> K;

    std::string grs;
    std::getline(std::cin, grs);
    std::getline(std::cin, grs);
    assert(grs.size() == K);

    for(int i = 0; i < N; i++) {
        std::string r;
        std::getline(std::cin, r);
        assert(r.size() == M);
        for(int j = 0; j < M; j++) mat[i][j] = r[j];
    }

    for(char d : grs) {
        switch(d) {
            case 'L': {
                for(int i = 0; i < N; i++) {
                    int nj = 0;
                    for(int j = 0; j < M; j++) {
                        if(mat[i][j] == '.') continue;
                        mat[i][nj++] = mat[i][j];
                    }
                    for(; nj < M; nj++) mat[i][nj] = '.';
                }
            } break;
            case 'R': {
                for(int i = 0; i < N; i++) {
                    int nj = M-1;
                    for(int j = M-1; j >= 0; j--) {
                        if(mat[i][j] == '.') continue;
                        mat[i][nj--] = mat[i][j];
                    }
                    for(; nj >= 0; nj--) mat[i][nj] = '.';
                }
            } break;
            case 'U': {
                for(int j = 0; j < M; j++) {
                    int ni = 0;
                    for(int i = 0; i < N; i++) {
                        if(mat[i][j] == '.') continue;
                        mat[ni++][j] = mat[i][j];
                    }
                    for(; ni < N; ni++) mat[ni][j] = '.';
                }
            } break;
            case 'D': {
                for(int j = 0; j < M; j++) {
                    int ni = N-1;
                    for(int i = N-1; i >= 0; i--) {
                        if(mat[i][j] == '.') continue;
                        mat[ni--][j] = mat[i][j];
                    }
                    for(; ni >= 0; ni--) mat[ni][j] = '.';
                }
            } break;
            default: assert(false);
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) putchar(mat[i][j]);
        putchar('\n');
    }

    return 0;
}