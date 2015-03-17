/* 
 * File:   header.h
 * Author: netdom
 *
 * Created on September 9, 2014, 1:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

void sobaka(char* key, char* fileInMemory, char* encryptedText);
void povodok(char* key, char* encryptedText, char* decryptedText);

#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */

