/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#include <iostream>
#include <ctime>
#include <chrono>
#include "logging_util.h"

#define COLOUR_OUT_BRIGHT_RED    "\x1B[1;31m"
#define COLOUR_OUT_CYAN          "\x1B[36m"
#define COLOUR_OUT_RESET         "\x1B[0m"

/**
 * Writes a log message to stdout or stderr.
 *
 * @param type the type of the message
 * @param msg the error message
 */
static void output_log(char type, const std::string &msg) {
	std::string color;
	bool err = false;
	std::string typemsg;

	switch (type) {
		case 'E':
			color = COLOUR_OUT_BRIGHT_RED;
			err = true;
			typemsg = "ERROR";
			break;

		case 'I':
			color = COLOUR_OUT_CYAN;
			typemsg = "INFO";
			break;

		default:
			color = "";
			typemsg = "DEBUG";
	}

	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timestr[100] = {0};
	std::strftime(timestr, sizeof(timestr), "%H:%M:%S", std::localtime(&now));

	if (err) {
		std::cerr << '[' << timestr << "] "
		          << color << typemsg << COLOUR_OUT_RESET << ' '
		          << msg << std::endl;
	} else {
		std::cout << '[' << timestr << "] "
		          << color << typemsg << COLOUR_OUT_RESET << ' '
		          << msg << std::endl;
	}
}

void log_info(const std::string &msg) {
	output_log('I', msg);
}

void throw_error(const std::string &msg) {
	output_log('E', msg);
}