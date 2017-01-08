/*
 * idiom.c
 *
 *  Created on: Jan 8, 2017
 *      Author: top
 */
#include <stdlib.h>
#include "idiom.h"


/* Public Function Declarations */
ILD * parse_idiom_language_description(FILE *);

/*
 * Instance of Idiom Language Description
 */

struct _ILD_instance{
	ILD ild;
	char* language_id;
};
typedef struct _ILD_instance ILDI;

/*
 * Get Language Idenitifier
 */
char * ILD_get_language_id(ILD * inst){
	ILDI* i = (ILDI*)inst;
	return i->language_id;
}

/*
 * Desctructor for Instance of ILD.
 */
void ILD_destroy(ILD * inst){
	ILDI  * i = (ILDI*) inst;
	if (i->language_id != NULL && i->language_id != DEF_LANG_ID)
		free(i);
	free(i);
}


/*
 * ILD constructor
 */
ILDI * createILD(){
	ILDI * ild = malloc(sizeof(ILDI));
	ild->language_id = DEF_LANG_ID; //until ID is parsed, this is default
	ild->ild->destroy = ILD_destroy;
	ild->ild->get_language_id = ILD_get_language_id;
	return (ILD*)ild;
}




ILD * parse_idiom_language_description(FILE *src){
	return createILD();
}


