/*
 * key_scan.h
 *
 * Created: 14/09/2019 16:03:01
 *  Author: jeroenvandezande
 */ 


#ifndef KEY_SCAN_H_
#define KEY_SCAN_H_


void keyscan_init();
int scankeys();
bool getResetState();


#endif /* KEY_SCAN_H_ */