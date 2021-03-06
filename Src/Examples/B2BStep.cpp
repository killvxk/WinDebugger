// 分支到分支单步执行
//

#include <cstdio>
#include "DvrAgent.h"


#define DEBUGCTRL_MSR	0x1D9
#define BTF	2

int main(int argc, char *argv[])
{
	int m, n;
	MSR_STRUCT msr;
	CDvrAgent da;

	if (!da.Init())
	{ 
		printf("Failed to initialize.\n");
		return -1;
	}

	memset(&msr, 0, sizeof(MSR_STRUCT));
	msr.MsrNum = DEBUGCTRL_MSR;
	msr.MsrLo |= BTF;
	da.WRMSR(msr);

	// beginning of the code which will run in full speed.
	m = 10, n = 2;
	m = n * 2 - 1;
	if (m == m*m / m)
	{
		m = 1;
	}
	else
	{
		m = 2;
	}
	// end of the code which runs in full speed.
	m *= m;

	if (da.RDMSR(msr))
	{
		printf("MSR=0x%x\n", msr.MsrLo);
	}
	else
	{
		printf("Failed to ReadMSR().\n");
	}

	return 0;
}
