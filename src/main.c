#include "json.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    json_object *object = json_parse(argv[1]);
    printf("%s\n", json_stringify(object));
    json_free(object);

    return 0;
}