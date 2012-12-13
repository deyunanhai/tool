/*
 * Copyright (C) 2003-2012 bocelli.hu <bocelli.hu@gmail.com>
 * 
 * This file is part of JSTools.
 * 
 * JSTools is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * JSTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with JSTools.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define START_DEBUG_CODE "--start debug--"
#define END_DEBUG_CODE "--end debug--"

static const char* trim_start(const char *s) {
    while(*s == ' ' || *s == '\t') s++;
    return s;
}

int is(const char *s, const char *control) {

    s = trim_start(s);
    if(*s++ == '/' && *s++ == '/') {
        s = trim_start(s);
        size_t len = sizeof(control);
        return (strncmp(s, control, len) == 0);
    }
    return 0;
}

int usage() {
    printf("%s\n", "remove javascript debug code");
    printf("%s\n", "-i inputfile");
    printf("%s\n", "-o outputfile");
    printf("%s\n", "-s remove debug code start control string. default is " START_DEBUG_CODE);
    printf("%s\n", "-o remote debug code end control string. default is " END_DEBUG_CODE);
    return 1;
}

int main(int argc, char *argv[]) {

    char buffer[BUFFER_SIZE];
    FILE *in,*out;
    int start_delete, i;
    char *start_debug_code, *end_debug_code;

    in = out = 0;
    start_delete = 0;
    start_debug_code = end_debug_code = 0;
    for(i=1;i<argc;i++) {
        if(argv[i][0] == '-') {
#define check_more_args() do { if((++i) > argc-1) return usage(); } while(0)
            switch(argv[i][1]) {
                case 'i':
                    check_more_args();
                    in = fopen(argv[i], "rb");
                    if(!in) {
                        fprintf(stderr, "can't open file to read. %s", argv[i]);
                        return 2;
                    }
                    break;
                case 'o':
                    check_more_args();
                    out = fopen(argv[i], "wb+");
                    if(!out) {
                        fprintf(stderr, "can't open file to read. %s", argv[i]);
                        return 2;
                    }
                    break;
                case 's':
                    check_more_args();
                    start_debug_code = argv[i];
                    break;
                case 'e':
                    check_more_args();
                    end_debug_code = argv[i];
                    break;
                default:
                    return usage();
            }
#undef chec_more_args
        }
    }

    if(!in) in = stdin;
    if(!out) out = stdout;
    if(!start_debug_code) start_debug_code = START_DEBUG_CODE;
    if(!end_debug_code) end_debug_code = END_DEBUG_CODE;


    while(fgets(buffer, BUFFER_SIZE, in)) {
        if(!start_delete) {
            if(is(buffer, start_debug_code)) {
                start_delete = 1;
            } else {
                fprintf(out, "%s", buffer);
            }
        } else {
            if(is(buffer, end_debug_code)) {
                start_delete = 0;
            }
        }
    }

    return 0;
}
