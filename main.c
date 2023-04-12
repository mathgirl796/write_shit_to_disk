#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <zlib.h>

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
    if (argc < 3)
    {
        printf("\nUsage: %s <n_byte> <time> [buf_size]\n\n\t\
Write <n_byte> bytes from memory to a tmp_file <time> times, print used time to console.\
 Using a [buf_size] buffer (default 1).\n\n", argv[0]);
        exit(1);
    }

    int n_byte = atoi(argv[1]);
    char *buf = (char *)malloc(n_byte * sizeof(char));
    memset(buf, '6', n_byte);

    int times = atoi(argv[2]);

    FILE *fp = tmpfile();
    gzFile gfp = gzdopen(fileno(tmpfile()), "w");
    long buf_size = argc>=4?atoi(argv[3]):1;
    setvbuf(fp, NULL, _IOFBF, buf_size);
    gzbuffer(gfp, buf_size);
    double ctime, rtime;

    ctime = cputime(), rtime = realtime();
    for (int i = 0; i < times; i++)
    {
        fwrite(buf, n_byte, 1, fp);
    }
    ctime = cputime() - ctime; rtime = realtime() - rtime;
    printf("\nFILE - CPU time: %f sec, Real time: %f sec\n\n", ctime, rtime);

    ctime = cputime(), rtime = realtime();
    for (int i = 0; i < times; i++)
    {
        gzfwrite(buf, n_byte, 1, gfp);
    }
    ctime = cputime() - ctime; rtime = realtime() - rtime;
    printf("\ngzFile - CPU time: %f sec, Real time: %f sec\n\n", ctime, rtime);

    return 0;
}
