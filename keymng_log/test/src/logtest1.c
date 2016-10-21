#include "keymnglog.h"

int main()
{
	KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], 1,"func err");
}
