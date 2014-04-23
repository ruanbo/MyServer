/*
 * DebugProxy.h
 *
 *  Created on: Apr 23, 2014
 *      Author: Robert
 */

#ifndef DEBUGPROXY_H_
#define DEBUGPROXY_H_


#ifdef LOCAL_DEBUG
	#define SYS_DEBUG_INFO true
#else
	#define SYS_DEBUG_INFO false
#endif

#define debug_info(...) if(SYS_DEBUG_INFO){printf(__VA_ARGS__); printf("\n");}





#endif /* DEBUGPROXY_H_ */
