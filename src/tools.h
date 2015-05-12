/*
 * tools.h
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */

#ifndef SRC_TOOLS_H_
#define SRC_TOOLS_H_

/**
 *
 * @param buff_dst
 * @param buff_src
 * @param length
 */
void buffcpy(void* buff_dst, const void* buff_src, int length);

/**
 *
 * @param buff_dst
 * @param buff_src
 * @param length
 * @return
 */
int buffcmp(const void* buff_dst, const void* buff_src, int length);

/**
 *
 * @param buff_dst
 * @param data
 * @param length
 */
void bufffill(void* buff_dst, char data, int length);


#endif /* SRC_TOOLS_H_ */
