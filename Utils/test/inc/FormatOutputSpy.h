#ifndef D_FORMAT_OUTPUT_SPY_H
#define D_FORMAT_OUTPUT_SPY_H

void FormatOutputSpy_Create(int size);
void FormatOutputSpy_Destroy(void);
char* FormatOutputSpy_GetOutput(void);
int FormatOutputSpy(const char* input, ...);

#endif
