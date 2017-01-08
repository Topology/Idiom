/*
 * idiom.h
 *
 *  Created on: Jan 8, 2017
 *      Author: top
 */

#ifndef IDIOM_H_
#define IDIOM_H_

/*
 * Idiom Language Description
 *
 * This structure is the top level interface for a language description.
 * From the structure you can get an enumeration of the following entities:
 * 0) Dependencies On Other Language Descriptions.
 * 1) Types
 * 2) Phrases
 * 3) Alphabet
 * 4) Character Usage
 */
struct _idiom_language_description;
typedef struct _idiom_language_description  ILD;

struct _idiom_language_description{
	char* language_id;

	void (*destroy)(ILD* );
};

ILD * parse_idiom_language_description(FILE *);


#endif /* IDIOM_H_ */
