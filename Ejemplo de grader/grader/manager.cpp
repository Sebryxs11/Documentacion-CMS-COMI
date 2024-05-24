#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <random>
#include <csignal>
#include <cstdarg>

using namespace std;

/******************************** Begin testlib-similar material ********************************/

#ifdef _MSC_VER
#   define NORETURN __declspec(noreturn)
#elif defined __GNUC__
#   define NORETURN __attribute__ ((noreturn))
#else
#   define NORETURN
#endif


static char __testlib_format_buffer[16777216];

#define FMT_TO_RESULT(fmt, cstr, result)  std::string result;                              \
            va_list ap;                                                                    \
            va_start(ap, fmt);                                                             \
            vsnprintf(__testlib_format_buffer, sizeof(__testlib_format_buffer), cstr, ap); \
            va_end(ap);                                                                    \
            __testlib_format_buffer[sizeof(__testlib_format_buffer) - 1] = 0;              \
            result = std::string(__testlib_format_buffer);                                 \


typedef string TResult;
const TResult _ok = "Correct";
const TResult _wa = "Wrong Answer";
const TResult _fail = "Judge Failure; Contact staff!";
const TResult _points = "Partially Correct";

NORETURN void quit(TResult result, string message = "", int idx = 0) {
	fprintf(stdout, "%d\n", ((result==_ok) ? 1 : 0));
	//fprintf(stderr, "%s\n", result.c_str());
	if (!message.empty())
		fprintf(stderr, "%s %i\n", message.c_str(), idx);
	exit(0);
}

NORETURN void quitp(double points, string message = "") {
	fprintf(stdout, "%.12lf\n", points);
	fprintf(stderr, "%s\n", _points.c_str());
	if (!message.empty())
		fprintf(stderr, "%s\n", message.c_str());
	exit(0);
}

#ifdef __GNUC__
__attribute__ ((format (printf, 2, 3)))
#endif
NORETURN void quitf(TResult result, const char* fmt, ...) {
	FMT_TO_RESULT(fmt, fmt, message);
	quit(result, message);
}

#ifdef __GNUC__
__attribute__ ((format (printf, 2, 3)))
#endif
NORETURN void quitpf(double points, const char* fmt, ...) {
	FMT_TO_RESULT(fmt, fmt, message);
	quitp(points, message);
}

FILE *grader1in,*grader1out, *grader2in, *grader2out;

#ifdef __GNUC__
__attribute__ ((format (printf, 3, 4)))
#endif
NORETURN inline void die(TResult result, bool sendDie, const char* fmt, ...) {
	if (sendDie) {
	  fprintf(grader2out, "-1\n");
	  fflush(grader2out);
	}
	FMT_TO_RESULT(fmt, fmt, message);
	quit(result, message);
}


inline FILE* openFile(const char* name, const char* mode) {
	FILE* file = fopen(name, mode);
	if (!file) {
		quitf(_fail, "Could not open file '%s' with mode '%s'.", name, mode);
	}
	return file;
}

inline void assertInput(bool cond, string message = "Input failed") {
	if (!cond) {
		quit(_fail, message);
	}
}

/********************************* End testlib-similar material *********************************/


mt19937_64 rnd(831);

const int MAXN = 1e5 + 5;
const int MAXS = 20;

int L_P, L_ANS, N_A, N_B, N_C, j = 0;
int A[MAXN], B[MAXN], C[MAXN], P[MAXS], ANS[MAXS];

int main (int argc, char **argv) {
    if (argc < 5) {
		quit(_fail, "Insufficient #args for manager of 'ruido'");
	}

    {//Keep alive on broken pipes
		//signal(SIGPIPE, SIG_IGN);
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		sigaction(SIGPIPE, &sa, NULL);
	}

    grader1out = openFile(argv[2], "a");
	grader1in = openFile(argv[1], "r");
	grader2out = openFile(argv[4], "a");
	grader2in = openFile(argv[3], "r");

    //^^^^^^^^^^^^^^template^^^^^^^^^^^^^^^^//

	// read input
    assertInput(scanf("%d", &L_P) == 1, "Input 'L' failed");
    for (int i = 0; i < L_P; i++)
        assertInput(scanf("%d", &P[i]) == 1, "Input 'P' failed");

    assertInput(scanf("%d", &N_A) == 1, "Input 'N' failed");
	for (int i = 0; i < N_A; i++)
        assertInput(scanf("%d", &A[i]) == 1, "Input 'A' failed");

    fclose(stdin);

    // send input
    fprintf(grader1out, "%d\n", L_P);
	fflush(grader1out);
    for (int i = 0; i < L_P; i++)
        fprintf(grader1out, "%d ", P[i]);
    fprintf(grader1out, "\n");
	fflush(grader1out);

    fprintf(grader1out, "%d\n", N_A);
	fflush(grader1out);
	for (int i = 0; i < N_A; i++)
        fprintf(grader1out, "%d ", A[i]);
    fprintf(grader1out, "\n");
	fflush(grader1out);

	// read processed input
    if (fscanf(grader1in, "%d", &N_B) != 1)
        die(_wa, true, "Could not read 'N_B' from first grader (solution possibly terminated)");

    for(int i = 0; i < N_B; i++)
        if (fscanf(grader1in, "%d", &B[i]) != 1)
            die(_fail, true, "Could not read array elements");

	fclose(grader1out);
	fclose(grader1in);

	// erase 1/2 of the elements of B to create C
	for (int i = 0; i < N_B; i++)
        if (rnd()%2) {
            C[j] = B[i];
            j++;
        }
    N_C = j;

    // send C
    fprintf(grader2out, "%d\n", N_C);
	fflush(grader2out);
	for (int i = 0; i < N_C; i++)
        fprintf(grader2out, "%d ", C[i]);
    fprintf(grader2out, "\n");
	fflush(grader2out);

	// read ANS
	if (fscanf(grader2in, "%d", &L_ANS) != 1)
        quit(_wa, "Could not read 'L_ANS'");
    for(int i = 0; i < L_ANS; i++) {
        if (fscanf(grader2in, "%d", &ANS[i]) != 1)
            quit(_wa, "Could not read 'ANS'", i);
    }

    fclose(grader2out);
	fclose(grader2in);

    // check answer
    if (L_ANS != L_P)
        quit(_wa);
    for (int i = 0; i < L_P; i++)
        if (ANS[i] != P[i])
            quit(_wa);
    quit(_ok);
    return 0;
}
