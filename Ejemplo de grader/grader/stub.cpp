#include <bits/stdc++.h>
#include "ruido.h"

using namespace std;

static FILE *fin;
static FILE *fout;

int main(int argc, char **argv) {
	if (argc != 4) {
		fprintf(stderr, "grader error\n");
		fprintf(stderr, "number of arguments isn't 4\n");
		exit(0);
	}

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "a");

    //^^^^^^^^^^^^^^template^^^^^^^^^^^^^^^^//

	if (string(argv[3]) == "0") { // grader A

        // read input
        int L, N;

		if (fscanf(fin, "%d", &L) != 1) {
			fprintf(stderr, "grader A error\n");
			fprintf(stderr, "could not read 'L'\n");
			exit(0);
		}
		if (L < 0) exit(0);
		vector <int> P(L);
        for (int i = 0; i < L; i++) {
            if (fscanf(fin, "%d", &P[i]) != 1) {
				fprintf(stderr, "grader A error\n");
				fprintf(stderr, "could not read 'P'\n");
				exit(0);
			}
			if (P[i] < 0) exit(0);
        }

		if (fscanf(fin, "%d", &N) != 1) {
			fprintf(stderr, "grader A error\n");
			fprintf(stderr, "could not read 'N'\n");
			exit(0);
		}
		if (N < 0) exit(0);
		vector <int> A(N, 0);
        for (int i = 0; i < N; i++) {
            if (fscanf(fin, "%d", &A[i]) != 1) {
				fprintf(stderr, "grader A error\n");
				fprintf(stderr, "could not read 'A'\n");
				exit(0);
			}
			if (A[i] < 0) exit(0);
        }

        // get first function answer
        string S;
        for (auto &it : P) S.push_back((char)(it + 'a'));

        vector<int> B = filtrador_de_ruido_cosmico(S, A);

        if (B.empty()) {
            fprintf(stderr, "error, 'B' is empty\n");
            fflush(fout);
            exit(0);
        }

        // check if B is a subsequence of A
        int j = 0;
        for (auto &it : A)
            if (j < B.size() && it == B[j]) j++;

        if (j != B.size()) {
            fprintf(stderr, "error, B is not a subsequence of A\n");
            fflush(fout);
            exit(0);
        }

        // send first function answer
        fprintf(fout, "%d\n", (int)B.size());
        fflush(fout);

        for (auto &it : B)
            fprintf(fout, "%d ", it);
        fprintf(fout, "\n");
        fflush(fout);
	} else if (string(argv[3]) == "1") { // grader B

	    // read input
        int N_C;

		if (fscanf(fin, "%d", &N_C) != 1) {
			fprintf(stderr, "grader B error\n");
			fprintf(stderr, "could not read 'N_C'\n");
			exit(0);
		}
		if (N_C < 0) { // error somewhere in manager or grader A
			exit(0);
		}
		vector <int> C(N_C, 0);
		for (int i = 0; i < N_C; i++) {
            if (fscanf(fin, "%d", &C[i]) != 1) {
				fprintf(stderr, "grader B error\n");
				fprintf(stderr, "could not read 'C'\n");
				exit(0);
			}
			if (C[i] < 0) exit(0);
		}

        // get second function answer
		string S2 = mensaje_para_jp(C);

		if (S2.empty() || S2.size() > 15) {
            fprintf(stderr, "error, 'S2' is empty or isnt correct\n");
            fflush(fout);
            exit(0);
        }

        // send second answer
        int L_ANS = S2.size();

        if (L_ANS < 0) exit(0);

        vector <int> ANS(L_ANS, 0);
        for (int i = 0; i < L_ANS; i++)
           ANS[i] = (int)(S2[i] - 'a');

        fprintf(fout, "%d\n", L_ANS);
        fflush(fout);

        for (int i = 0; i < L_ANS; i++)
            fprintf(fout, "%d ", ANS[i]);
        fprintf(fout, "\n");
        fflush(fout);

	} else {
		fprintf(stderr, "grader error\n");
		fprintf(stderr, "unknown grader type %s\n", argv[3]);
		exit(0);
	}
	return 0;

}

