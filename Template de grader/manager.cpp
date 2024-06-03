#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include <climits>
#include <csignal>
#include <cstdarg>
using namespace std;

/******************************** NO TOCAR, TEMPLATE DE MANEJO DE ARCHIVOS ********************************/

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
const TResult _ok = "AC: Respuesta Correcta";
const TResult _wa = "WA: Respuesta Erronea";
const TResult _fail = "Fallo del evaluador; Contacta al staff!";
const TResult _points = "PA: Parcialmente Correcta";

NORETURN void quit(TResult result, string message = "") {
	fprintf(stdout, "%d\n", ((result==_ok) ? 1 : 0));
	if (!message.empty()) fprintf(stderr, "%s\n", message.c_str());
	exit(0);
}

#ifdef __GNUC__
__attribute__ ((format (printf, 2, 3)))
#endif
NORETURN void quitf(TResult result, const char* fmt, ...) {
	FMT_TO_RESULT(fmt, fmt, message);
	quit(result, message);
}

FILE *grader1in,*grader1out, *grader2in, *grader2out;

#ifdef __GNUC__
__attribute__ ((format (printf, 3, 4)))
#endif

NORETURN inline void die(TResult result, bool sendDie, const char* fmt, ...) { // die para comunicacion
	if (sendDie) {
	  fprintf(grader2out, "-1\n");
	  fflush(grader2out);
	}
	FMT_TO_RESULT(fmt, fmt, message);
	quit(result, message);
}

inline FILE* openFile(const char* name, const char* mode) {
	FILE* file = fopen(name, mode);
	if (!file) quitf(_fail, "No se pudo abrir el archivo '%s' con modo '%s'.", name, mode);
	return file;
}

inline void assertInput(bool cond, string message = "No se pudo leer el Input.") {
	if (!cond) quit(_fail, message);
}

/********************************* NO TOCAR, TEMPLATE DE MANEJO DE ARCHIVOS *********************************/

int main (int argc, char **argv) {

    /********************** TEMPLATE **********************/

    if (argc < 5) {
		quit(_fail, "Insuficiente #args para el manager.");
	}

    { // mantener en broken pipes
		//signal(SIGPIPE, SIG_IGN);
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		sigaction(SIGPIPE, &sa, NULL);
	}

    grader1out = openFile(argv[2], "a"); // primera llamada
	grader1in = openFile(argv[1], "r");
	grader2out = openFile(argv[4], "a"); // segunda llamada
	grader2in = openFile(argv[3], "r");

    /********************** TEMPLATE **********************/

    // TU MANAGER VA AQUI

	fclose(grader1out);
	fclose(grader1in);
	fclose(grader2out);
	fclose(grader2in);
    return 0;
}
