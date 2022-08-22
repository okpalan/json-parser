
#include "json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to open file '%s'\n", filename);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *data = (char *)calloc(1, size + 1);
    fread(data, size, 1, fp);
    data[size] = '\0';

    fclose(fp);

    return data;
}

json_object *json_parse(const char *filename)
{
    char *data = read_file(filename);

    json_object *object = json_object_new_object();

    char *key = data;
    char *value = strchr(data, ':');
    *value = '\0';
    value++;

    while (1)
    {
        char *end = strchr(value, ',');
        if (end)
            *end = '\0';

        json_object *val;

        if (value[0] == '{')
        {
            size_t len = strlen(value);
            value[len - 1] = '\0';
            val = json_parse(value + 1);
        }
        else
        {
            val = json_object_new_string(value);
        }

        json_object_object_add(object, key, val);

        if (!end)
            break;

        key = end + 1;
        value = strchr(key, ':');
        *value = '\0';
        value++;
    }

    free(data);

    return object;
}
char *json_stringify(json_object *object)
{
    size_t size = json_object_to_json_string_len(object);
    char *data = (char *)calloc(1, size + 1);
    json_object_to_json_string(data, size, object);
    return data;
}
int json_object_put(struct json_object *jso)
{
    int ref_cnt;

    if (!jso)
        return -1;

    ref_cnt = json_object_get_ref_count(jso);
    if (ref_cnt == 1)
    {
        json_object_generic_delete(jso);
        free(jso);
    }

    return 0;
}
json_object_new_string(const char *s)
{
    struct json_object *jso = json_object_new(json_type_string);
    if (!s)
    {
        jso->_string.len = 0;
        jso->_string.buf = jsonp_strdup("");
    }
    else
    {
        jso->_string.len = strlen(s);
        jso->_string.buf = jsonp_strdup(s);
    }
    return jso;
}

json_object_new_object()
{
    struct json_object *jso = json_object_new(json_type_object);
    jso->_object.head = NULL;
    return jso;
}

json_object_generic_delete(struct json_object *jso)
{
    switch (jso->o_type)
    {
    case json_type_string:
        jsonp_free(jso->_string.buf);
        break;
    case json_type_object:
        jsonp_free(jso->_object.head);
        break;
    default:
        break;
    }
    jsonp_free(jso);
}

json_object_get_ref_count(struct json_object *jso)
{
    return jso->_ref_count;
}

json_object_to_json_string_len(struct json_object *jso)
{
    switch (jso->o_type)
    {
    case json_type_string:
        return jso->_string.len;
    case json_type_object:
        return jso->_object.head;
    default:
        break;
    }
}
void json_free(json_object *object)
{
    json_object_put(object);
}