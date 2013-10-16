#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

long getinstanttime()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return((tv.tv_sec*1000000) + tv.tv_usec);
}


typedef int16_t int16;
typedef int8_t int8;

/* Converting from raw data to degrees/second. */

float calcGyro(int16 raw)
{
  float v;

  //-- calculate rotation, unit deg/s, range -250, +250
  v = (raw * 1.0) / (65536/ 500);

  return v;
}

#define BUILD_INT16(loByte, hiByte) ((int16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

int main(int argc, char **argv) {
		int16 hexX, hexY, hexZ;
	int hex1, hex2, hex3;
	int8 pData[6]; 
	int inp, i;
	FILE *fp;

	char filename[200];

	filename[0] = 0;
	strcat(filename, "/home/optimus-prime/DR-SensorTag/");
	strcat(filename, argv[argc-1]);

	fp = fopen(filename, "a+");
	//fp = fopen("/home/optimus-prime/DR-SensorTag/op.txt", "a+");


	for(i=0;i<4;i++) {
		sscanf(argv[i+1], "%x", &inp);		
		pData[i] = (int8)inp;
	}


	hexX = BUILD_INT16(pData[0], pData[1]);
	hexY = BUILD_INT16(pData[2], pData[3]);
	hexZ = BUILD_INT16(pData[4], pData[5]);

	fprintf(fp, "\n---------------------------------------------------------");
	fprintf(fp, "\nGyroscope Data [%ld]", getinstanttime());
	fprintf(fp, "\nX : %5.3f", calcGyro(hexX));
	fprintf(fp, "\tY : %5.3f", calcGyro(hexY));
	fprintf(fp, "\tZ : %5.3f", calcGyro(hexZ));
	fprintf(fp, "\n---------------------------------------------------------");
	fclose(fp);

}
