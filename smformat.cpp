#include "stdafx.h"
#include "Test.h"
#include "Testdlg.h"
#include <afx.h>

#include "SmFormat.h"

StreamFormat::StreamFormat(char *String)
{
	char *cp1, *cp2;
	struct StreamFormatBuffer **ppStreamFormatBuffer;
	
	cp1 = String;
	cp2 = String;

	StreamFormatBufferBase = NULL;
	ppStreamFormatBuffer = &StreamFormatBufferBase;

	while (1)
	{
		while (*cp1 && *cp1 != '\r' && *(cp1+1) != '\n')
			cp1++;

		if (!*cp1)
			break;

		*ppStreamFormatBuffer = new StreamFormatBuffer;
		VERIFY((*ppStreamFormatBuffer)->Line = (char *)malloc(cp1 - cp2 + 1)); // Platz für Zeile
		strncpy((*ppStreamFormatBuffer)->Line, cp2, cp1 - cp2);
		(*ppStreamFormatBuffer)->next = NULL;
		ppStreamFormatBuffer = &(*ppStreamFormatBuffer)->next;

		cp1 += 2;
		cp2 =  cp1;
	}
}


StreamFormat::~StreamFormat()
{
	struct StreamFormatBuffer *pStreamFormatBuffer;
	struct StreamFormatBuffer *pStreamFormatBuffer2;
	
	pStreamFormatBuffer = StreamFormatBufferBase;

	while(pStreamFormatBuffer)
	{
		 pStreamFormatBuffer2 = pStreamFormatBuffer->next;
		 free(pStreamFormatBuffer->Line);
		 delete pStreamFormatBuffer;
		 pStreamFormatBuffer = pStreamFormatBuffer2;
	}
}


char *StreamFormat::GetText(long Line, long left_bound, long right_bound)
{
	static char DirtyBuffer[200];
	long i;
 	struct StreamFormatBuffer *pStreamFormatBuffer;
	
	pStreamFormatBuffer = StreamFormatBufferBase;

	for (i = 0; i < Line && pStreamFormatBuffer; i++)
	{
		 pStreamFormatBuffer = pStreamFormatBuffer->next;
	}

	if (!pStreamFormatBuffer)
		*DirtyBuffer = '\0';
	else
	{
		if (right_bound - left_bound >= sizeof(DirtyBuffer))
			right_bound = left_bound + sizeof(DirtyBuffer) - 1;
		strncpy(DirtyBuffer, pStreamFormatBuffer->Line + left_bound, right_bound - left_bound);
	}
	DirtyBuffer[right_bound - left_bound] = '\0';

	return DirtyBuffer;
}

long StreamFormat::ColSum(long left_bound, long right_bound, char *date_from, char *date_to, char kuerzel)
{
	long counter;
	char buffer[200];
	long i;
 	struct StreamFormatBuffer *pStreamFormatBuffer;
	
	pStreamFormatBuffer = StreamFormatBufferBase;
	counter = 0L;

	for (i = 0; pStreamFormatBuffer; i++)
	{
		if ((!date_from || CompareDates(pStreamFormatBuffer->Line, date_from) >= 0) &&
			(!date_to || CompareDates(pStreamFormatBuffer->Line, date_to) <= 0))
		{
			if (right_bound - left_bound >= sizeof(buffer))
				right_bound = left_bound + sizeof(buffer) - 1;
			strncpy(buffer, pStreamFormatBuffer->Line + left_bound, right_bound - left_bound);
			if (!kuerzel || kuerzel == pStreamFormatBuffer->Line[27])
			counter += atol(buffer);
		}

		pStreamFormatBuffer = pStreamFormatBuffer->next;
	}

	return counter;
}

long StreamFormat::GetRows()
{
	long i;
 	struct StreamFormatBuffer *pStreamFormatBuffer;
	
	pStreamFormatBuffer = StreamFormatBufferBase;

	for (i = 0; pStreamFormatBuffer; i++)
	{

		pStreamFormatBuffer = pStreamFormatBuffer->next;
	}

	return i;
}

int StreamFormat::CompareDates(char * d1, char * d2)
{
	char buf1[20], buf2[20];

	buf1[0] = d1[6];
	buf1[1] = d1[7];
	buf1[2] = d1[3];
	buf1[3] = d1[4];
	buf1[4] = d1[0];
	buf1[5] = d1[1];
	buf1[6] = '\0';

	buf2[0] = d2[6];
	buf2[1] = d2[7];
	buf2[2] = d2[3];
	buf2[3] = d2[4];
	buf2[4] = d2[0];
	buf2[5] = d2[1];
	buf2[6] = '\0';

	return strcmp(buf1, buf2);
}