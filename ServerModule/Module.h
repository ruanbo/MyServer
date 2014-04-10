/*
 * Module.h
 *
 *  Created on: Apr 9, 2014
 *      Author: root
 */

#ifndef MODULE_H_
#define MODULE_H_




class Module {
public:
	Module();
	virtual ~Module();

public:
	bool start();

	void stop();
};




#endif /* MODULE_H_ */
