/*
 *  libdict_c, a simple implementation of python dictonaries in C
 *  Copyright (C) 2021 CFOV, github [dot] fox [at] thevoid [dot] email
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "libdict_c.c"

#define DICT_FUZZER_ENABLED 1
//For Fuzzer
#if DICT_FUZZER_ENABLED > 0
#include <time.h>
#define STR_CONT 5 //Max. Number from 0 to STR_CONT (both included) to generate strings from
#define MAX_DEPTH 6 //MAX Depht of path, min. is 1, max. is 10, see fuzz_dict_update(...)
int loglevel = 1;
bool exit_now = false;
long long int num_del = 0;
long long int num_upd = 0;
#endif

int test_dict(){
    struct dict* dict = dict_new();
    struct dict* search_dict = NULL;
    struct dict* ret = NULL;
    struct array* array = NULL;
    union json_type value;
    char* output = 0;


    fprintf(stderr, "Pointer to dict: %p\n", dict);

    fprintf(stderr, "\n\n\n************************************************************************************ TEST START #####\n");
    loglevel = 0;

/* 
    value.object = dict_new();
    ret = dict_update(dict, JSON_OBJ, value, 1, "0");
    fprintf(stderr, "Success 0 : %s\n\n", ret ? "true" : "false");
    dict_dump(stderr, dict); fprintf(stderr,"\n");

    value.object = dict_new();
    ret = dict_update(dict, JSON_OBJ, value, 2, "0", "2");
    fprintf(stderr, "Success 0 2:%s\n\n", ret ? "true" : "false");
    dict_dump(stderr, dict); fprintf(stderr,"\n");

    value.object = dict_new();
    ret = dict_update(dict, JSON_OBJ, value, 3, "0", "2", "1");
    fprintf(stderr, "Success 0 2 1: %s\n\n", ret ? "true" : "false");



    value.object = dict_new();
    ret = dict_update(dict, JSON_OBJ, value, 4, "0", "2", "1", "No");
    fprintf(stderr, "Success 0 2 1: %s\n\n", ret ? "true" : "false");


    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    dict_free(dict);

    //test update
    
    value.string = "test";
    ret = dict_update(dict, JSON_STR, value, 3, "0", "2", "1");
    fprintf(stderr, "Success str: %s\n\n", ret ? "true" : "false");
    dict_dump(stderr, dict); fprintf(stderr,"\n");
*/
    

    value.string = "2";
    ret = dict_update(dict, JSON_STR, value, 1, "2");
    fprintf(stderr, "Success str: %s\n\n", ret ? "true" : "false");
    dict_dump(stderr, dict); fprintf(stderr,"\n");
    
    dict_del(&dict, 1, "2");
    dict_dump(stderr, dict); fprintf(stderr,"\n");

    value.integer = 5;
    ret = dict_update(dict, JSON_INT, value, 1, "Lamb");
    fprintf(stderr, "(ret = %p) %s\n", ret, output = dict_dumpstr(dict)); free(output);

/*
    value.string = "Hurz";
    dict_update(dict, JSON_STR, value, 1, "Wolf");
*/
    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    //dict_del(&dict, 1, "Lamb");
    //fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);

    

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    fprintf(stderr, "\n");

    value.object = dict_new();
    dict_update(dict, JSON_OBJ, value, 1, "INNER");
    search_dict = __dict_plainsearch(dict, "INNER", &search_dict);
    dict_printelement(stderr, search_dict);

    value.string = "Hurz";
    dict_update(dict, JSON_STR, value, 1, "Tiger");

    dict_printelement(stderr, dict_get(dict, 1, "INNER"));

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);

    value.boolean = false;
    dict_update(dict, JSON_BOOL, value, 2, "INNER", "Cougar");

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);


    dict_update(dict, JSON_NULL, value, 2, "INNER", "Rabbit");
    value.boolean = true;
    dict_update(dict, JSON_BOOL, value, 2, "INNER", "Fox");
  
    value.array = array_new();
    dict_update(dict, JSON_ARRAY, value, 2, "INNER", "ARRAY");

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    ret = dict_update(dict, JSON_NULL, value, 5, "0", "1", "2", "3", "No");
    ret = dict_update(dict, JSON_NULL, value, 5, "INNER", "1", "2", "3", "five");
    

    value.hex.number = 10; value.hex.format = HEX_FORMAT_04;
    array_add(dict_get(dict, 2, "INNER", "ARRAY")->value.array, JSON_HEX, value);
    value.string = "asdfjklo";
    array_add(dict_get(dict, 2, "INNER", "ARRAY")->value.array, JSON_STR, value);
    value.object = dict_new();
    array_add(dict_get(dict, 2, "INNER", "ARRAY")->value.array, JSON_OBJ, value);

    value.hex.number = 0xDEADBEEF; value.hex.format = HEX_FORMAT_STD;
    dict_update(array_get(dict_get(dict, 2, "INNER", "ARRAY")->value.array, 2)->value.object, JSON_HEX, value, 1, "DEADBEEF");

    array_dump(stderr, array_get(dict_get(dict, 2, "INNER", "ARRAY")->value.array, 2)); fprintf(stderr, "\n");

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);

    dict_free(dict); return 0;

    search_dict = dict_get(dict, 2, "INNER", "ARRAY");
    fprintf(stderr, "Type %d\n", search_dict ? search_dict->type : -1);
    dict_printelement(stderr, dict_get(dict, 2, "INNER", "ARRAY"));

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    fprintf(stderr, "\n");

    search_dict = dict_get(dict, 1, "Lamb");
    fprintf(stderr, "Type %d\n", search_dict ? search_dict->type : -1);

    value.boolean = false;
    dict_update(dict, JSON_BOOL, value, 2, "INNER", "Carlin");


    //Array operations
    array = dict_get(dict, 2, "INNER", "ARRAY")->value.array;
    fprintf(stderr, "%s\n", output = array_dumpstr(array)); free(output);
    array_del(array, 2);
    fprintf(stderr, "%s\n", output = array_dumpstr(array)); free(output);
    array_del(array, 1);
    fprintf(stderr, "%s\n", output = array_dumpstr(array)); free(output);
    array_del(array, 0);
    fprintf(stderr, "%s\n", output = array_dumpstr(array)); free(output);
    //fprintf(stderr, "array_len: %ld\n", array_len(array));
    //fprintf(stderr, "Array pos %d: ", 1);
    //array_printelement(stderr, array_get(array, 1));
    fprintf(stderr, "\n");

    //dict_del(&dict, 2, "INNER", "Cougar");

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);

    dict_del(&dict, 2, "INNER", "Carlin");
    //dict_del(&dict, 2, "INNER", "ARRAY");
    dict_del(&dict, 2, "INNER", "Rabbit");
    dict_del(&dict, 2, "INNER", "Fox");

    value.boolean = true;
    dict_update(dict, JSON_BOOL, value, 2, "INNER", "Bear");
    
    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    fprintf(stderr, "\n");

    //delete dict contents

    fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "Cougar"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "Rabbit"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "Carlin"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 1, "Lamb"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 1, "Tiger"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 1, "Wolf"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "Fox"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "Bear"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 2, "INNER", "ARRAY"));
    //fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 1, "INNER"));
    fprintf(stderr, "RETURN: %d\n", dict_del(&dict, 1, "Wolf"));

    dict_printelement(stderr, dict_get(dict, 1, "INNER"));
    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);

    fprintf(stderr, "\n\n\n************************************************************************************ TEST START #####\n%s\n", output = dict_dumpstr(dict)); free(output);
    
    //dict_update existing
    value.floating = 3.14;
    dict_update(dict, JSON_FLOAT, value, 2, "INNER", "ARRAY"); 

    fprintf(stderr, "%s\n", output = dict_dumpstr(dict)); free(output);
    dict_free(dict);
    return 0;
}

unsigned long int random_at_most(long max) {
    unsigned long int num_bins = (unsigned long) max + 1;
    unsigned long int num_rand = (unsigned long int) RAND_MAX + 1;
    unsigned long int bin_size = num_rand / num_bins;
    unsigned long int defect   = num_rand % num_bins;

    unsigned long int x;
    do
        x = random();
    while (num_rand - defect <= (unsigned long)x);

    return x/bin_size;
}


u_int8_t getrandtype() {
    u_int8_t rand = random_at_most(69 - 10 ) + 10; //spare out type 0 (JSON_EMPTY)
    if(rand <= 9)
        return 0;
    if(rand <= 19)
        return 10;
    if(rand <= 29)
        return 20;
    if(rand <= 39) {
        rand = random_at_most(2);
        if(rand == 0)
            return 30;
        if(rand == 1)
            return 31;
        return 32;
    }
    if(rand <= 49)
        return 40;
    if(rand <= 59)
        return 50;
    if(rand <= 69)
        return 60;
    return rand; //low probability for last number!
}

char* getrandkey() {
    char* str = malloc(10);
    sprintf(str, "%ld", (random_at_most(STR_CONT)));
    return str;
}

char** getrandvars(int path_len, char** vars){
    vars = malloc(sizeof(char*) * path_len);
    for(int i = 0; i<path_len; i++)
        vars[i] = getrandkey();
    return vars;
}

void freerandvars(int path_len, char** vars){
    for(int i = 0; i<path_len; i++)
        free(vars[i]);
    free(vars);
    return;
}

void test(int path_len, ...){
    va_list valist;
    char* next_key = 0;

    va_start(valist, path_len);
    fprintf(stdout, "test: ");
    for(int i = 0; i < path_len; i++) {
        next_key = va_arg(valist, char *);
        fprintf(stdout, "[%s]", next_key);
    }
    fprintf(stdout, "\n");
    va_end(valist);
    return;
}

struct dict* fuzz_dict_update_del(struct dict** dict_ptr, u_int8_t type, union json_type value){
    char** vars = 0;
    int path_len = 0;
    path_len = random_at_most(MAX_DEPTH -1 ) + 1;
    for(int i = 0; i < MAX_DEPTH; i++) { //Make path_len equaly distributed over depth (roughly)
        switch(path_len) {
            case 1:
                if(random_at_most(9)) { path_len = random_at_most(MAX_DEPTH -1 ) + 1; }
                break;
            case 2:
                if(random_at_most(8)) { path_len = random_at_most(MAX_DEPTH -2 ) + 2; }
                break;
            case 3:
                if(random_at_most(7)) { path_len = random_at_most(MAX_DEPTH -3 ) + 3; }
                break;
            case 4:
                if(random_at_most(6)) { path_len = random_at_most(MAX_DEPTH -4 ) + 4; }
                break;
            case 5:
                if(random_at_most(5)) { path_len = random_at_most(MAX_DEPTH -5 ) + 5; }
                break;
            case 6:
                if(random_at_most(4)) { path_len = random_at_most(MAX_DEPTH -6 ) + 6; }
                break;
            case 7:
                if(random_at_most(3)) { path_len = random_at_most(MAX_DEPTH -7 ) + 7; }
                break;
            case 8:
                if(random_at_most(2)) { path_len = random_at_most(MAX_DEPTH -8 ) + 8; }
                break;
            case 9:
                if(random_at_most(1)) { path_len = random_at_most(MAX_DEPTH -9 ) + 9; }
                break;
            case 10: break;
            default:
                path_len = MAX_DEPTH;
                break;
        }
    }

    vars = getrandvars(path_len, vars);
    struct dict* ret = 0;
    static bool del_or_update = true; //begin with an update
    //del_or_update = !del_or_update; //toggle between deletion and update. An alternative would be random_at_most(1);
    del_or_update = !random_at_most(9); //delete only every 10th time (10%)
    if(del_or_update)
        num_del++;
    else 
        num_upd++;

    if(loglevel) {
        fprintf(stderr, "del_or_update: %s\n", del_or_update ? "del" : "update");
        //fprintf(stderr, "dict_update(dict=%p, type=%s, value=%p, path_len=%d , vars=%s)\n", dict, json_typetostr(type), value.string, path_len, vars[0]);

        fprintf(stderr, "Vars: ");
        for(int i  = 0; i < path_len; i++)
            fprintf(stderr, " [%s] ", vars[i]);
        fprintf(stderr, "\n");
    }
    //if(no_update_existing && dict_get(dict, path_len, )) return 0; //do not update existing elements
    //fprintf(stderr, "existing: %s", dict_get(dict, path_len, vars[0]) != NULL ? "true" : "false");
    switch(path_len){ //MAX_DEPTH is set to 10! Is there a more clever, dynamic solution?
        case  1: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0]);
                 break;
        case  2: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1]);
                 break;
        case  3: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2]);
                 break;
        case  4: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3]);
                 break;
        case  5: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4]);
                 break;
        case  6: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5]);
                 break;
        case  7: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6]);
                 break;
        case  8: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7]);
                 break;
        case  9: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7], vars[8]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7], vars[8]);
                 break;
        case 10: if(del_or_update)  { ret =  (struct dict*) dict_del(dict_ptr, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7], vars[8], vars[9]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0], vars[1], vars[2], vars[3], vars[4], vars[5], vars[6], vars[7], vars[8], vars[9]);
                 break;
        default: if(del_or_update)  { dict_del(dict_ptr, path_len, vars[0]); break; }
                 ret = dict_update(*dict_ptr, type, value, path_len, vars[0]);
                 break;
    }
    freerandvars(path_len, vars);
    //If Update fails, del has been executed or a string is provied, calling function ist responsible to deal with new string, array, or object
    if((!ret && del_or_update == false ) || del_or_update || type == JSON_STR){
        switch(type){
            case JSON_STR: free(value.string); break;  //Strings are allways copied, thus calling function ist responsible to deal with new string in every case
            case JSON_OBJ: dict_free(value.object); break;
            case JSON_ARRAY: array_free(value.array); break;
            default: break; //no freeable type provided
        }
    }
    /*
    if(path_len == MAX_DEPTH && ret){
        fprintf(stderr,"Exit now set to true, MAX_DEPTH reached\n");
        exit_now = true; //Max depth reached
    }
    */
    return ret;
}

int fuzzer(int argc, char *argv[]) {
    fprintf(stderr, "To test for memory leaks, use e.g.\nvalgrind --leak-check=full -s --exit-on-first-error=yes --error-exitcode=17 %s\n", argv[0]);
    struct dict* dict = dict_new();
    struct dict* ret = 0;
    u_int8_t type = 0;
    union json_type value, array_value;
    time_t now, start = time(NULL);

    srandom(start);
    long long unsigned int loop = 0;
    long long unsigned int max_loops = 10000000;//4000000000;
    for(loop = 0; loop<max_loops; loop++) {
        type = getrandtype();
        if(loglevel || loop % 100000 == 0) {
            now = time(NULL);
            fprintf(stderr, "Loop %lld of %lld with type %s after %ld sec. ", loop, max_loops, json_typetostr(type), now - start);
            fprintf(stderr, "Percentage of deletes is %.2lf%%. ETA in %lld sec.\n",\
                                (num_del ? ( (double) num_del/(num_upd + num_del) * 100 ) : 0) ,\
                                (long long int) (loop ? ( (double) max_loops/loop * (now-start)  - (now - start) ) : -1) );
        }

        if(loglevel || loop % 1000000 == 0) {
            now = time(NULL);
            dict_dump(stdout, dict); fprintf(stdout, "\n");
        }

        switch(type) { //Fuzz dict_update(...)
            case JSON_NULL:
                value.integer = 0;
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_BOOL:
                value.boolean = true;
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_HEX:
                //value.hex.number = 0xdeadbeef;
                value.hex.number = 0x5;
                value.hex.format = HEX_FORMAT_02; //HEX_FORMAT_04;
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_INT: break;
                value.integer = 17;
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_FLOAT:
                value.floating = 3.14;
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            break;
            case JSON_STR:
                value.string = malloc(11);
                snprintf(value.string, 10, "%ld", random_at_most(STR_CONT));
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_ARRAY: //TODO: Make Arrays also dynamicly tested here
                value.array = array_new();
                array_value.integer = 42;
                array_add(value.array, JSON_INT, array_value);
                array_value.hex.number = 0xA;
                array_value.hex.format = HEX_FORMAT_04;
                array_add(value.array, JSON_HEX, array_value);
                array_value.string = "Fox";
                array_add(value.array, JSON_STR, array_value);
                array_value.array = array_new();
                array_add(value.array, JSON_ARRAY, array_value);
                array_value.object = dict_new();
                array_add(value.array, JSON_OBJ, array_value);
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            case JSON_OBJ:
                value.object = dict_new();
                ret = fuzz_dict_update_del(&dict, type, value);
                break;
            default: fprintf(stderr,"Unknown Type %u\n", type); break;
        }
        if (loglevel) {
            fprintf(stdout, "Success: %s\n", ret ? "true" : "false");
            dict_dump(stdout, dict); fprintf(stdout, "\n\n");
        }
        if(exit_now) break;
    }
    fprintf(stderr, "\n##### FUZZER STOP ##### (in loop %lld with exit_now: %s)\nTime elapsed %ld sec.\n", loop, exit_now ? "true" : "false", now-start);
    if(!loglevel) {
        dict_dump(stdout, dict); fprintf(stdout, "\n");
    }
    dict_free(dict);
    return 0;
}

int main(int argc, char *argv[]) {
    fprintf(stderr, "libdict_c  Copyright (C) 2021 CFOV, github [dot] fox [at] thevoid [dot] email\nThis program comes with ABSOLUTELY NO WARRANTY;\nThis is free software, and you are welcome to redistribute it under certain conditions");
    loglevel = 0;
    return fuzzer(argc, argv);
    //return test_dict();
    //demo();
    return 0;
}