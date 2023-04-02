#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

double cputime()
{
	struct rusage r;
	getrusage(RUSAGE_SELF, &r);
	return r.ru_utime.tv_sec + r.ru_stime.tv_sec + 1e-6 * (r.ru_utime.tv_usec + r.ru_stime.tv_usec);
}

double realtime()
{
	struct timeval tp;
	struct timezone tzp;
	gettimeofday(&tp, &tzp);
	return tp.tv_sec + tp.tv_usec * 1e-6;
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("\nUsage: %s <n_byte> <time>\n\n\tWrite <n_byte> bytes from memory to a tmp_file <time> times, print used time to console.\n\n", argv[0]);
        exit(1);
    }

    int n_byte = atoi(argv[1]);
    int time = atoi(argv[2]);
    FILE *fp = tmpfile();

    char *buf = (char *)malloc(n_byte * sizeof(char));
    memset(buf, '6', n_byte);

    double ctime = cputime(), rtime = realtime();
    for (int i = 0; i < time; i++)
    {
        fwrite(buf, n_byte, 1, fp);
    }
    ctime = cputime() - ctime; rtime = realtime() - rtime;

    printf("\nCPU time: %f sec\nReal time: %f sec\n\n", ctime, rtime);

    fclose(fp);
    return 0;
}
