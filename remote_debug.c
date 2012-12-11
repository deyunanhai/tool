#include <stdio.h>
#include <stdlib.h>

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
    printf("%s\n", "delete javascript debug code");
    printf("%s\n", "-i inputfile");
    printf("%s\n", "-o outputfile");
    return 1;
}

int main(int argc, char *argv[]) {

    char buffer[BUFFER_SIZE];
    FILE *in,*out;
    int start_delete, i;

    in = out = 0;
    start_delete = 0;
    for(i=1;i<argc;i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'i':
                    if((++i) > argc-1) return usage();
                    in = fopen(argv[i], "rb");
                    if(!in) {
                        fprintf(stderr, "can't open file to read. %s", argv[i]);
                        return 2;
                    }
                    break;
                case 'o':
                    if((++i) > argc-1) return usage();
                    out = fopen(argv[i], "wb+");
                    if(!out) {
                        fprintf(stderr, "can't open file to read. %s", argv[i]);
                        return 2;
                    }
            }
        }
    }

    if(!in) in = stdin;
    if(!out) out = stdout;

    while(fgets(buffer, BUFFER_SIZE, in)) {
        if(!start_delete) {
            if(is(buffer, START_DEBUG_CODE)) {
                start_delete = 1;
            } else {
                fprintf(out, "%s", buffer);
            }
        } else {
            if(is(buffer, END_DEBUG_CODE)) {
                start_delete = 0;
            }
        }
    }
}
