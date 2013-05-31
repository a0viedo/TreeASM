/* 
 * File:   main.c
 * Author: aoviedo
 *
 * Created on April 18, 2013, 5:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char** argv) {
    tree *a = tree_create_int(10);
    
	tree *aa = tree_create_int(7);
	tree *ab = tree_create_int(60);
	tree *ac = tree_create_int(18);
	tree *ad = tree_create_int(12);

   	tree_add_child(a, aa);
	tree_add_child(a, ab);
	tree_add_child(ab, ac);
	tree_add_child(ab, ad);
	tree_prune(a, &es_bisiesto);

	tree *b = tree_create_int(10);
    
	tree *ba = tree_create_int(7);
	tree *bb = tree_create_int(60);
	tree *bc = tree_create_int(18);
	tree *bd = tree_create_int(12);

   	tree_add_child(b, ba);
	tree_add_child(b, bb);
	tree_add_child(bb, bc);
	tree_add_child(bb, bd);	

	tree_merge(b, &es_bisiesto, &sumar);
	
	tree_print(a, "extra", "output.txt");
	tree_print(b, "extra", "output.txt");
	
	tree_deep_delete(a);
	tree_deep_delete(b);

        char *str1 = "brmm";
        char *str2 = "zaraza";
        char *str3 = "grrrr";
        char *str4 = "yyyy...";
        char *str5 = "zarlanga";

        char *str_en_heap1 = malloc(strlen(str1) +1);
        char *str_en_heap2 = malloc(strlen(str2) +1);
        char *str_en_heap3 = malloc(strlen(str3) +1);
        char *str_en_heap4 = malloc(strlen(str4) +1);
        char *str_en_heap5 = malloc(strlen(str5) +1);
        strcpy(str_en_heap1, str1);
        strcpy(str_en_heap2, str2);
        strcpy(str_en_heap3, str3);
        strcpy(str_en_heap4, str4);
        strcpy(str_en_heap5, str5);



	tree *c = tree_create_string(str_en_heap1);
	tree *ca = tree_create_string(str_en_heap2);
	tree *cb = tree_create_string(str_en_heap3);
	tree *cc = tree_create_string(str_en_heap4);
	tree *cd = tree_create_string(str_en_heap5);

	tree_add_child(c, ca);
	tree_add_child(ca, cc);
	tree_add_child(c, cb);
	tree_add_child(cb, cd);

	tree_prune(c, &tiene_vocales);

        char *str_heap1 = malloc(strlen(str1) +1);
        char *str_heap2 = malloc(strlen(str2) +1);
        char *str_heap3 = malloc(strlen(str3) +1);
        char *str_heap4 = malloc(strlen(str4) +1);
        char *str_heap5 = malloc(strlen(str5) +1);
        strcpy(str_heap1, str1);
        strcpy(str_heap2, str2);
        strcpy(str_heap3, str3);
        strcpy(str_heap4, str4);
        strcpy(str_heap5, str5);

	tree *d = tree_create_string(str_heap1);
	tree *da = tree_create_string(str_heap2);
	tree *db = tree_create_string(str_heap3);
	tree *dc = tree_create_string(str_heap4);
	tree *dd = tree_create_string(str_heap5);

	tree_add_child(d, da);
	tree_add_child(da, dc);
	tree_add_child(d, db);
	tree_add_child(db, dd);

	tree_merge(d, &tiene_vocales, &intercalar);

	tree_print(c, "extra", "output.txt");
	tree_print(d, "extra", "output.txt");

	tree_deep_delete(c);
	tree_deep_delete(d);

	tree *e = tree_create_double(3.14);
	tree *ea = tree_create_double(271);
	tree *eb = tree_create_double(161);
	tree *ec = tree_create_double(1.41);
	tree *ed = tree_create_double(12);
	
	tree_add_child(e, ea);
	tree_add_child(ea, ec);
	tree_add_child(e, eb);
	tree_add_child(eb, ed);

	tree_prune(e, &es_mayor_que_sesenta);

	tree *f = tree_create_double(3.14);
	tree *fa = tree_create_double(271);
	tree *fb = tree_create_double(161);
	tree *fc = tree_create_double(1.41);
	tree *fd = tree_create_double(12);
	
	tree_add_child(f, fa);
	tree_add_child(fa, fc);
	tree_add_child(f, fb);
	tree_add_child(fb, fd);

	tree_merge(f, &es_mayor_que_sesenta, &multiplicar);

	tree_print(e, "extra", "output.txt");
	tree_print(f, "extra", "output.txt");

	tree_deep_delete(e);
	tree_deep_delete(f);
	

    return (EXIT_SUCCESS);
}
