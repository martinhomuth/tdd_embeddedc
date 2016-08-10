#ifndef __RUNTIME_ERROR_STUB_H
#define __RUNTIME_ERROR_STUB_H

void RuntimeErrorStub_Reset(void);
const char *RuntimeErrorStub_GetLastError(void);
int RuntimeErrorStub_GetLastParameter(void);

#endif
