/*
 * tools.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */
#include "tools.h"

/*******************************************************************************
 *
 */
void buffcpy(void* buff_dst, const void* buff_src, int length)
{
    int cnt;
    char* dest = (char*)buff_dst;
    const char* sorc = (const char*)buff_src;

    for (cnt = 0; cnt < length; cnt++, dest++, sorc++)
        *dest = *sorc;
}

/*******************************************************************************
 *
 */
int buffcmp(const void* buff_dst, const void* buff_src, int length)
{
    int cnt;
    int rc = 0;
    const char* dest = (const char*)buff_dst;
    const char* sorc = (const char*)buff_src;

    for (cnt = 0; cnt < length; cnt++, dest++, sorc++)
    {
        if (0 != (*dest - *sorc))
        {
            rc = cnt + 1;
            break;
        }
    }
    return rc;
}

/*******************************************************************************
 *
 */
void bufffill(void* buff_dst, char data, int length)
{
    int cnt;
    unsigned char* dest = (unsigned char*)buff_dst;

    for (cnt = 0; cnt < length; cnt++, dest++)
        *dest = data;
}
